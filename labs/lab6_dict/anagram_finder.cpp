/**
 * @file anagram_finder.cpp
 * Uses the AnagramDict class in an executable capable of finding all
 * anagrams of a word (or all words).
 * @author Matt Jora
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <iostream>
#include <cstring>
#include <fstream>

using std::vector;
using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::string;
using std::endl;

const string USAGE = 
"USAGE: anagram_finder -w [WORD_LIST] -o [FILE]\n"
"Finds anagrams using a given word list file (where each word is newline-separated).\n"
"\n"
"  -a       Finds all anagrams in the word list.";

int main(int argc, char* argv[])
{
	string word_list_filename = "words.txt";
	vector< string > args;
	bool find_all = false;
	string out_filename = "";
	/* Parse arguments. */
	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-w") == 0) {
			i++;
			if(i != argc) {
				word_list_filename = argv[i];
			}
		}
		else if(strcmp(argv[i], "-o") == 0) {
			i++;
			if(i != argc) {
				out_filename = argv[i];
			}
		}
		else if(strcmp(argv[i], "-a") == 0) {
			find_all = true;
		}
		else {
			args.push_back(argv[i]);
		}
	}
	ifstream word_list_file(word_list_filename);
	/* Only proceed of we have a good wordlist, AND either args aren't empty
	 * (there's a word to find anagrams of) or we are finding all anagrans. */
	if(word_list_file.good() && (! args.empty() || find_all)) {
		AnagramDict dict(word_list_filename);
		ofstream fout(out_filename);
		ostream& out = fout.good() ? fout : cout;

		if(!find_all) {
			for(string& arg : args) {
				out << "Anagrams for " << arg << ":" << endl;
				vector< string > anagrams = dict.get_anagrams(arg);
				for(string& anagram : anagrams) {
					out << anagram << endl;
				}   
			}
		}
		else {
			vector< vector< string > > anagram_groups = dict.get_all_anagrams();
			for(vector< string >& anagram_group : anagram_groups) {
				for(string& anagram: anagram_group) {
					out << anagram << endl;
				}
				out << endl;
			}
		}

	}
	else if(args.empty()) {
		cerr << USAGE << endl;
		return -1;
	}
	else {
		cerr << "File " << word_list_filename << " does not exist." << endl;
		return -1;
	}
}
