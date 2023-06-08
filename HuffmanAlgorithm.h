#pragma once
#include <iostream>
#include "Heap.h"
#include "FileHandler.h"

// provides implemetation of huffman encoding and huffman decoding algorithms
class HuffmanAlgorithm {
private:
	struct Heap::Node* root;
	FileHandler f;

	// returns true if root node is a leaf node
	bool isLeaf (struct Heap::Node* root) {
		return (root->left == nullptr) and (root->right == nullptr);
	}

	// create huffman tree from array of unique character and array of respective frequency
	struct Heap::Node* create_huffman_tree(char data[], int freq[], int size) {
		struct Heap::Node* right, * left, * top;

		// build min heap from inputs
		Heap* min_heap = Heap::build_min_heap(data, freq, size);

		// repeat until only one node in heap
		while (!min_heap->isSizeOne()) {
			// remove first two (minimum) nodes
			left = min_heap->remove_node();
			right = min_heap->remove_node();

			// insert new node with frequency as sum of frequency of first two nodes removed
			top = new Heap::Node('$', left->freq + right->freq);
			top->left = left;
			top->right = right;

			min_heap->insert_node(top);
		}

		// return the root node of huffman tree
		return min_heap->remove_node();
	}

public:
	void huffman_encoding(char data[], int freq[], int size, std::string filename) {
		root = create_huffman_tree(data, freq, size);
		f.file_encoder(root, filename);
	}

	void huffman_decoding(std::string filename) {
		f.file_decoder(root, filename);
	}
};