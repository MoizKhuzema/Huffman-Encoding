#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <fstream>
#include <string>

// container to hold character and frequency arrays
struct arrayPair {
    char* arr;
    int* freq;
    int size;
};


class FileHandler {
private:
    std::fstream fs;
    std::fstream new_fs;

    // function maps each character to its huffman code
    void encode(Heap::Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode)
    {
        if (root == nullptr)
            return;

        // found a leaf node
        if (root->left == nullptr && root->right == nullptr) 
            huffmanCode[root->data] = (str != "") ? str : "1";

        encode(root->left, str + "0", huffmanCode);
        encode(root->right, str + "1", huffmanCode);
    }

    void decode(Heap::Node* root, int& index, std::string str)
    {
        if (root == nullptr)
            return;

        // found a leaf node
        if (root->left == nullptr && root->right == nullptr) {
            new_fs << root->data;
            return;
        }

        index++;

        if (str[index] == ' ') {
            new_fs << ' ';
            return;
        }

        else if (str[index] == '0')
            decode(root->left, index, str);

        else
            decode(root->right, index, str);
    }

public:
    // parses input file and returns a character array and the corresponding frequency array
    struct arrayPair create_character_dictionary(const std::string& filename) {
        std::fstream fs(filename);
        std::map<char, int> mp;
        char word;

        // Keep reading words while there are words to read
        while (fs >> word) {
            // If this is first occurrence of word
            if (mp.count(word) == 0)
                mp.insert(std::pair<char, int>(word, 1));
            else
                mp[word]++;
        }

        fs.close();

        const int SIZE = mp.size();
        struct arrayPair pair1;
        pair1.arr = new char[SIZE];
        pair1.freq = new int[SIZE];
        pair1.size = SIZE;

        int i = 0;
        // insert all characters in arr
        // insert corresponding frequencies in freq
        for (auto p = mp.begin(); p != mp.end(); p++) {
            pair1.arr[i] = p->first;
            pair1.freq[i] = p->second;

            i++;
        }

        return pair1;
    } 
    
    // function creates a new file containing huffman code of the originial file
    void file_encoder(struct Heap::Node* root, const std::string& filename) {

        // input file
        fs.open(filename, std::ios::in);
        // output file
        new_fs.open("encoded_file.txt", std::ios::out);

        std::unordered_map<char, std::string> huffmanCode;
        encode(root, "", huffmanCode);

        // traverse file by each character
        char ch;
        while (fs.get(ch)) {
            if (ch == ' ') {
                new_fs << ' ';
                continue;
            }

            if (ch == '\n') {
                new_fs << '\n';
                continue;
            }

            // input corresponding huffman code in output file
            new_fs << huffmanCode[ch];
        }

        
        new_fs.close();
        fs.close();
    }

    void file_decoder(struct Heap::Node* root, const std::string& filename) {

        fs.open(filename, std::ios::in);
        new_fs.open("decoded_file.txt", std::ios::out);

        if (root->left == nullptr && root->right == nullptr) {
            // Special case: For input like a, aa, aaa, etc.
            while (root->freq--) {
                std::cout << root->data;
            }
        }
        else {
            // Traverse the Huffman Tree again and this time,
            // decode the encoded string
            std::string str;
            while (std::getline(fs, str)) {
                int index = -1;
                while (index < (int)str.size() - 1) {
                    decode(root, index, str);
                }

                new_fs << '\n';
            }
        }

        fs.close();
        new_fs.close();
    }
};
