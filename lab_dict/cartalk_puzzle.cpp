/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream words(word_list_fname);
    string word;
    if(words.is_open()){
      while(getline(words,word)){
        if(word.length()==5){
          string t1 = word.substr(1,word.length()-1);
          string t2 = word.substr(0,1);
          string t3 = word.substr(2,word.length()-2);
          t2.append(t3);
          if(d.homophones(t1,t2)){
            ret.push_back(make_tuple(word,t1,t2));
          }
        }
      }

    }
    return ret;
}
