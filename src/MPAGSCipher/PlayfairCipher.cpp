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

    std::cout << key_ << std::endl;
  
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

    // Store maps for later
    letterToPosition_ = letter2coord;
    positionToLetter_ = coord2letter;
    
}

std::string PlayfairCipher::applyCipher(const std::string& inputText /*, const CipherMode cipherMode*/ ) const
{
    size_t text_length{inputText.size()};

    std::string outputText{""};

    using CharPair_t = std::pair<char, char>;
    CharPair_t digraph{'x', 'x'};

    using SizePair_t = std::pair<size_t, size_t>; // row then column coord
    SizePair_t coordinates[2] = {{0, 0}, {0, 0}};

    size_t temp_storage{0}; // temporary storage for when shuffling coordinates later

    // Change J → I
    for (size_t i{0} ; i < text_length ; i++){
        //make a digraph
        // check for J:
        if (inputText[i] == 'J'){
            digraph.first = 'I';
        }
        else{
            digraph.first = inputText[i];
        }
        // second part of digraph could be I, X, Z, or the next letter:
        // 1. check for J:
        if (inputText[i+1] == 'J'){
            digraph.second = 'I';
            i++;
        }
        // 2. check for repeated letter:
        else if (inputText[i+1] == inputText[i]){
            digraph.second = 'X';
        }
        // 3. check for last character in string
        else if ( i+1 == text_length){
            digraph.second = 'Z';
        }
        // 4. otherwise just use the next character
        else {
            digraph.second = inputText[i+1];
            i++;
        }


        // Find the coordinates:
        coordinates[0] = letterToPosition_.at(digraph.first);
        coordinates[1] = letterToPosition_.at(digraph.second);

        // Option 1 - letters on the same row
        if (coordinates[0].first == coordinates[1].first){
            // add one to each coordinate column
            for (int j{0}; j < 2; j++){
                coordinates[j].second++;

                // check for wrapping:
                if (coordinates[j].second > 5){
                    coordinates[j].second %= 5;
                }
            }
        }
        // Option 2 - letters in same column
        else if(coordinates[0].second == coordinates[1].second){
            for (int j{0}; j < 2; j++){
                // add one to each coordinate row
                coordinates[j].first++;

                // check for wrapping:
                if (coordinates[j].first > 4){
                    coordinates[j].first %= 5; //THINK THERE IS A PROBLEM HERE
                }
            }
        }
        // Option 3 - forms a rectangle
        else{
            // row of each stay the same
            // swap column indices of each coord
            temp_storage = coordinates[0].second;
            coordinates[0].second = coordinates[1].second;
            coordinates[1].second = temp_storage;         
        }
        
        // Convert back to text
        digraph.first = positionToLetter_.at(coordinates[0]);
        digraph.second = positionToLetter_.at(coordinates[1]);

        // Add it to the output text
        outputText += digraph.first + digraph.second;      
    } 


return outputText; 
}

std::string PlayfairCipher::getKey(){
    return key_;
}