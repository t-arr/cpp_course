#include "common_words.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

using std::vector;
using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::string;
using std::endl;

bool file_exists (const string& name) {
	ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	} else {
		f.close();
		return false;
	}   
}

const string USAGE = 
"USAGE: find_common_words [TEXT FILE ..] -n [NUM] -o [FILE]\n"
"Finds all words who appear >= n times in ALL the parameter text files.";

int main(int argc, char* argv[])
{    
	vector<string> in_files;
	string out_filename = "";
	unsigned int n = 0;
	for(int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			i++;
			if (i != argc) {
				out_filename = argv[i];
			}
		}
		else if (strcmp(argv[i], "-n") == 0) {
			i++;
			if (i != argc) {
				try {
					n = std::stoi(argv[i]);
				}
				/* stoi() will except for non-numeric values. */
				catch(std::invalid_argument& e) {
					cerr << USAGE << endl;
					return -1;
				}
				catch(std::out_of_range& e) {
					cerr << "Number too large to take as input." << endl;
					return -1;
				}   
			}
		}
		else if (file_exists(argv[i])) {
			in_files.push_back(argv[i]);
		}
		else {
			cerr << "Could not read file: " << argv[i] << endl;
		}
	}
	CommonWords cw(in_files);
	vector<string> words = cw.get_common_words(n);
	ofstream fout(out_filename);
	ostream& out = fout.good() ? fout : cout;

	for (string& str : words) {
		out << str << endl;
	}

	if (in_files.empty()) {
		cerr << USAGE << endl;
	}
	return 0;
}

