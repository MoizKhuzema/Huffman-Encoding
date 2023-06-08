#include "HuffmanAlgorithm.h"

int main() {
	arrayPair p1;
	HuffmanAlgorithm huffman;
	FileHandler file_handler;

	p1 = file_handler.create_character_dictionary("input.txt");

	huffman.huffman_encoding(p1.arr, p1.freq, p1.size, "input.txt");

	huffman.huffman_decoding("encoded_file.txt");
}