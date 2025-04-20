/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    ifstream words(filename);
    string word;
    if (words.is_open()) {
        while (getline(words, word)) {
            string sorted_word = word;
            std::sort(sorted_word.begin(), sorted_word.end());
            auto& anagram_list = dict[sorted_word];
            if (std::find(anagram_list.begin(), anagram_list.end(), word) == anagram_list.end()) {
                anagram_list.push_back(word);
            }
        }
    }
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    for (const string& word : words) {
        string sorted_word = word;
        std::sort(sorted_word.begin(), sorted_word.end());
        auto& anagram_list = dict[sorted_word];
        if (std::find(anagram_list.begin(), anagram_list.end(), word) == anagram_list.end()) {
            anagram_list.push_back(word);
        }
    }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    string sorted_word = word;
    std::sort(sorted_word.begin(), sorted_word.end());

    auto it = dict.find(sorted_word);
    if (it != dict.end()) {
        return it->second;
    }
    return vector< string >();
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> all_anagrams;

    for (const auto& pair : dict) {
        if (pair.second.size() >= 2) {
            all_anagrams.push_back(pair.second);
        }
    }

    return all_anagrams;
}


