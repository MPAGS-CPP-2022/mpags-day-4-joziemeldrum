#include "PlayfairCipher.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>


PlayfairCipher::PlayfairCipher(const std::string& key)
{setKey(key);
}

void PlayfairCipher::setKey(const std::string& key)
{

    // store the original key
    key_ = key;
    
    // Append the alphabet
    key_ += alphabet_;
    
    // Make sure the key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);
    
    // Remove non-alpha characters
    auto isntalpha = [] (char inChar) {
        return !std::isalpha(inChar);
        };

    auto rem_nonalpha_iter = std::remove_if(key_.begin(), key_.end(), isntalpha);
    key_.erase(rem_nonalpha_iter, key_.end());
    
    // Change J -> I
    auto isJ = [] (char inChar){
        if (inChar == 'J'){
            return 'I';
        }else{
            return inChar;
        }
    };

    std::transform(key_.begin(), key_.end(), key_.begin(), isJ);
    
    // Remove duplicated letters
    std::string found_letters{""};
    auto isduplicate = [&found_letters] (char inChar){
        if (found_letters.find(inChar) != std::string::npos){
            return true;
        }else{
            found_letters += inChar;
            return false;
        }
    };

    auto rem_duplicates_iter = std::remove_if(key_.begin(), key_.end(), isduplicate);
    key_.erase(rem_duplicates_iter, key_.end());
  
    // Store the coords of each letter

    // create a label for the coordinate data type:
    using SizePair_t = std::pair<size_t, size_t>; // row then column coord

    std::map<char, SizePair_t > letter2coord;
    std::map<SizePair_t, char> coord2letter;

    // make some variables to break up the calculation to find the coordinates
    size_t key_index{0};
    SizePair_t coord{ 0, 0 };

    for (char letter : alphabet_){
        if (letter == 'J'){
            continue;
            }
        key_index = key_.find(letter);
        coord.first = int(key_index/5);
        coord.second = key_index % 5;
        letter2coord[letter] = coord;
        coord2letter[coord] = letter;
    }
    
    // Store the playfair cipher key map
    for (auto p : letter2coord){
        std::cout << p.first << " : {" << p.second.first << " , " << p.second.second << " }" << std::endl;
    }

}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode ) const
{
// Change J → I


// If repeated chars in a digraph add an X or Q if XX

// if the size of input is odd, add a trailing Z

// Loop over the input in Digraphs

// - Find the coords in the grid for each digraph

// - Apply the rules to these coords to get 'new' coords

// - Find the letter associated with the new coords

// return the text
return ""; 
}

std::string PlayfairCipher::getKey(){
    return key_;
}