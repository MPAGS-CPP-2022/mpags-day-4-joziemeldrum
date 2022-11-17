#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"

#include <string>
#include <map>


/**
 * \file Playfair.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher {

    public:

        /**
         * \brief Create a new PlayfairCipher with the given key
         *
         * \param key the key to use in the cipher
         */
        explicit PlayfairCipher(const std::string& key);

        /**
         * \brief Create map using input string
         * 
         * \param key the string to create the map
        */

        void setKey(const std::string& key);

        /**
         * \brief get value of private member variable key_ to check function setKey working while devleoping
        */

        std::string getKey();


        /**
         * \brief Apply the cipher to the provided text
         *
         * \param inputText the text to encrypt or decrypt
         * \param cipherMode whether to encrypt or decrypt the input text
         * 
         * \return the result of applying the cipher to the input text
         */
        std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;


    private:

        /// The key for the cipher, just a string
        std::string key_{""};

        /// The alphabet - used in creating the key
        const std::string alphabet_{"ABCDEFGHIJKLMNOPQRSTUVWQXYZ"};

        /// The maps to go between letters and their coordinates on the Playfair cipher grid
        std::map<char, std::pair<size_t, size_t>> letterToPosition_;
        std::map<std::pair<size_t, size_t>, char> positionToLetter_;

};

#endif