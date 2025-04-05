/**
 * Copyright 2024 University of Oulu
 * Authors:
 *   Elmeri Uotila <roope.uotila@oulu.fi>
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include "canvas.h"
#include <iostream>

Canvas::Canvas()
{
	layers.reserve(10);
}

// Just delete the list, the individual layers are handled by main
Canvas::~Canvas()
{
	layers.clear();
	layercount = 0;
}

// Add an layer at the end of the list
void Canvas::Add(size_t x, size_t y, const Vector2& pos, const Vector2& scale, const RGBAPixel& col, const std::string& name)
{
    PNGLayer layer(x, y, pos, scale, col, name);
    layers.push_back(layer);
	layercount++;
}

// Get the latest layer added to the canvas
// Return as pointer to allow editing or drawing on it
PNGLayer & Canvas::GetTopLayer(){
	if (layers.empty()) {
		throw std::runtime_error("No layers in the canvas.");
	}
	return layers.back();
}

// Get a layer by its name
// Return by reference to allow editing or drawing on it
PNGLayer& Canvas::GetByName(const std::string& name){
	for (PNGLayer& layer : layers) {
		if (layer.getName() == name) {
			return layer;
		}
	}
	throw std::runtime_error("Layer doesn't exist.");
}

// Find and remove layer by name
// If layer is not found, do nothing
void Canvas::Remove(const std::string& name)
{
    for (auto it = layers.begin(); it != layers.end(); ++it) {
        if (it->getName() == name) {
            layercount--;
            layers.erase(it);
            break;
        }
    }
}


// Find given layers from list and swap their positions
// Swap only if both layers are found
void Canvas::Swap(const std::string& name1, const std::string& name2)
{
    auto it1 = layers.end();
    auto it2 = layers.end();

    for (auto it = layers.begin(); it != layers.end(); ++it) {
        if (it1 == layers.end() && (it)->getName() == name1) {
            it1 = it;
        }
        if (it2 == layers.end() && (it)->getName() == name2) {
            it2 = it;
        }
    }

    if (it1 != layers.end() && it2 != layers.end()) {
        std::iter_swap(it1, it2);
    }
}

void Canvas::draw(PNG& canvas) const
{
	for(size_t i=0; i<layercount; i++) {
		//update this line
		const PNGLayer& layer = layers[i];
		for(size_t x=0, xmax = layer.width(); x<xmax; x++){
			for(size_t y=0, ymax = layer.height(); y<ymax; y++){
				// This gets the pixel color blended with layer color
				// Check pnglayer.cpp
				RGBAPixel coli = layer.getBlendedPixel(x,y);
				Vector2 sc = layer.getScale();
				
				Vector2 pos = layer.getPosition();
				
				// A loop is needed in case it must be scaled up, or we end up with gaps
				for(int xs=0; xs < std::abs((int)(sc.x()-0.001))+1; xs++){
					for(int ys=0; ys < std::abs((int)(sc.y()-0.001))+1; ys++){
						int x1 = static_cast<int>(pos.x() + x * sc.x() + xs);
                    	int y1 = static_cast<int>(pos.y() + y * sc.y() + ys);
					  
						// Check that it's within bounds
						if(x1 >= 0 && x1 < (int)canvas.width() && y1 >= 0 && y1 < (int)canvas.height()) {
							// Current color of the canvas
							RGBAPixel& colc = canvas(x1,y1);
														
							colc.red   = (coli.red * coli.alpha + colc.red * (255 - coli.alpha)) / 255;
                            colc.green = (coli.green * coli.alpha + colc.green * (255 - coli.alpha)) / 255;
                            colc.blue  = (coli.blue * coli.alpha + colc.blue * (255 - coli.alpha)) / 255;

							// We can keep the canvas opaque, no reason to change it
							colc.alpha = 255;
						}
					}
				}
			}
		}
	}
}
