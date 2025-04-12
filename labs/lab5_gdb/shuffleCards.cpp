/**
 * @file shuffleCards.cpp
 * @author Anna LaValle
 * @date Created: Spring 2025
 */

 void shuffleCards() {
    const std::string OUTPUT_FILE = "shuffle.png";
    std::string INPUT_FILE = "Images/";
    PNG out("Images/canvas.png");
    int WIDTH = out.width();
    int HEIGHT = out.height();
    const int num_cards = 10;
    Canvas outputCanvas;
    
    List<PNGLayer> list;
    
    for (int i = 1; i <= num_cards; i++) {
        PNGLayer p(WIDTH, HEIGHT, Vector2(0.0, 0.0), Vector2(1.0, 1.0), RGBAPixel(255, 255, 255, 255), std::to_string(i));
        p.readFromFile(INPUT_FILE + std::to_string(i) + ".png");
        list.insertBack(p);
    }
    
    list.shuffle();
    
    int index = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        it->SetPosition(Vector2(WIDTH / 100 + (WIDTH - WIDTH / 9) / num_cards * index, HEIGHT / 4));
        outputCanvas.Add(*it);
        index++;
    }

    outputCanvas.draw(out);
    out.writeToFile(OUTPUT_FILE);
}
