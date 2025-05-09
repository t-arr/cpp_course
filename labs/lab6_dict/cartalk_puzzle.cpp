/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using std::vector;
using std::string;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    std::ifstream word_file(word_list_fname);
    vector< StringTriple > results;

    if (!word_file.is_open()) return results;

    string word;
    while (word_file >> word) {
        if (word.length() < 5) {
            continue;   
        }
        string w1 = word.substr(1);
        string w2 = word[0] + word.substr(2);

        if (d.homophones(word, w1) && d.homophones(word, w2)) {
            results.emplace_back(word, w1, w2);
        }
    }

    return results;
}


