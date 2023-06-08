#pragma once
#include <iostream>

// class provides a priority queue-based implementation of Heap Data Structure
class Heap {
private:
	// implementation of node class used in heap
	struct Node {
		char data;
		int freq;
		struct Node* left;
		struct Node* right;

		Node(const char& d, const int& f) : data{ d }, freq{ f }, left{ nullptr }, right{ nullptr }  {}
	};

	int size;
	int capacity;
	// array of type - node pointer
	struct Node** array;

public:
	
	// constructor
	Heap(const int& c) : size{ 0 }, capacity{ c }  {
		array = new struct Node * [capacity];
	}

	// rescursively sorts heap in ascending order of frequency for a given index
	void heapify(const int& idx) {
		// initialize index node as smallest
		int smallest = idx;
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;

		// if left node has less frequency
		if (left < size && array[left]->freq < array[smallest]->freq)
			smallest = left;
		
		// if right node has less frequency
		if (right < size && array[right]->freq < array[smallest]->freq)
			smallest = right;

		// if smallest node is not equal to index node
		if (smallest != idx) {
			// swap smallest node with index node
			std::swap(array[smallest], array[idx]);
			// repeat recursively
			heapify(std::move(smallest));
		}
	}

	// return true if only one node in heap
	bool isSizeOne() {
		return (size == 1);
	}

	// remove first node from heap
	struct Node* remove_node() {

		struct Node* temp = array[0];
		array[0] = array[size - 1];
		--size;
		heapify(0);
		return temp;
	}

	// insert node in heap
	void insert_node(struct Node* new_node) {
		size++;
		int i = size - 1;

		while (i > 0 && new_node->freq < array[ (i - 1) / 2 ]->freq) {
			array[i] = array[(i - 1) / 2];
			i = (i - 1) / 2;
		}

		array[i] = new_node;
	}

	// sort heap in ascending order for all indexes
	void heap_sort() {
		int n = size - 1;
		for (int i = (n - 1) / 2; i >= 0; --i)
			heapify(i);
	}

	// construct min heap from array of unique characters and array of respective frequency
	static Heap* build_min_heap(char data[], int freq[], int size) {
		Heap* min_heap = new Heap(size);

		for (int i = 0; i < size; i++)
			min_heap->array[i] = new Node(data[i], freq[i]);

		min_heap->size = size;
		min_heap->heap_sort();

		return min_heap;
	}

	friend class HuffmanAlgorithm;
	friend class FileHandler;
};