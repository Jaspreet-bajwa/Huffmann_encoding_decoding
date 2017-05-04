/*
 * encoder.cpp
 * created by: Jaspreet Bajwa
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <ctime>
#include <stack>
#include <string>
#include <queue>
#include "binaryHeap.h"
#include "fourheap.h"
#include "hnode.h"
#include "pheap.h"

/*
 * function to compute the frequencies
 */
void FillFrequencyMapFromFile(std::ifstream &inputfile,
		std::unordered_map<int, unsigned int> &freqMap) {

	int number;
	while (inputfile >> number) {
		auto it_f = freqMap.find(number);
		if (it_f != freqMap.end()) {
			it_f->second++;
		} else {
			freqMap[number] = 1;
		}
	}
}

/*
 * function to create the node of a huffman tree using frequency map
 */
void CreateHnodeVecFromFreqMap(
		std::unordered_map<int, unsigned int> const &freqMap,
		std::vector<hnode const*> &hnode_vec) {

	for (auto it : freqMap) {
		hnode* huff_node = new hnode(it.first, it.second, NULL, NULL);
		hnode_vec.push_back(huff_node);
	}
}

/*
 * function to build huffman tree using four way heap
 */
hnode const* BuildTreeFheap(
		std::unordered_map<int, unsigned int> const &freqMap) {

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVecFromFreqMap(freqMap, hnode_vec);

	fourheap fheap(hnode_vec);

	unsigned int freq;

	while (fheap.size() > 4) {
		//std::cout<<"iteration:"<<std::endl;
		hnode const *left = fheap.getmin();
		fheap.deletemin();
		//fheap_obj.displayheap();

		hnode const *right = fheap.getmin();
		fheap.deletemin();
		//fheap_obj.displayheap();

		freq = left->freq + right->freq;
		//std::cout<<"Result Freq:"<<freq<<std::endl;
		//data to be -1 since it is an internal node...
		hnode const* parent = new hnode(-1, freq, left, right);
		fheap.insert(parent);
		//fheap_obj.displayheap();
	}
	return fheap.getmin();
}

/*
 * function to create the huffman tree using binary heap
 */
hnode const* BuildTreeBheap(
		std::unordered_map<int, unsigned int> const &freqMap) {

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVecFromFreqMap(freqMap, hnode_vec);

	binaryHeap bheap(hnode_vec);

	//bheap.displayheap();
	unsigned int freq;

	int count = 0;
	while ((bheap.size() > 1)) {
		count++;
		//std::cout<<"iteration:"<<std::endl;
		hnode const *left = bheap.getmin();
		bheap.deletemin();
		//bheap_obj.displayheap();

		hnode const *right = bheap.getmin();
		bheap.deletemin();
		//bheap_obj.displayheap();

		freq = left->freq + right->freq;
		//std::cout<<"Result Freq:"<<freq<<std::endl;
		//data to be -1 since it is an internal node...
		hnode const* parent = new hnode(-1, freq, left, right);
		bheap.insert(parent);
		//bheap_obj.displayheap();
	}
	return bheap.getmin();
}

/*
 * function to create the huffman tree using pairing heap
 */
hnode const* BuildTreePheap(
		std::unordered_map<int, unsigned int> const &freqMap) {

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVecFromFreqMap(freqMap, hnode_vec);

	pheap pheapObj(hnode_vec);

	pheapObj.displayheap();
	unsigned int freq;

	while ((pheapObj.size() > 1)) {
		hnode const *left = pheapObj.findMin();
		pheapObj.deleteMin();
		hnode const *right = pheapObj.findMin();
		pheapObj.deleteMin();

		freq = left->freq + right->freq;
		//std::cout<<"Result Freq:"<<freq<<std::endl;
		//data to be -1 since it is an internal node...
		hnode const* parent = new hnode(-1, freq, left, right);
		pheapObj.Insert(parent);
	}
	return pheapObj.findMin();
}

/*
 *  traverses the tree to generate code values and store it in code table
 */
void printCodes(hnode const *root, std::string str,
		std::unordered_map<int, std::string> &codeTableMap) {

	if (!root)
		return;

	if (root->data != -1) {
		//std::cout << root->data << ": " << str << "\n";
		codeTableMap[root->data] = str;
	}

	printCodes(root->left, str + "0", codeTableMap);
	printCodes(root->right, str + "1", codeTableMap);
}

char setBit(char num, int i) {
	return num | (1 << i);
}

/*
 * function that performs the 8 bit compression process
 */
void compress(std::string &value, std::vector<char> &result) {

	char res = 0;
	char str;
	for (long i = 0; i < value.size();) {
		res = 0;
		for (int j = 7; j >= 0; j--) {
			if (value[i] == '1')
				res = setBit(res, j);
			i++;
		}
		result.push_back(res);
	}
}

/*
 * generates the encoded binary file using the code table.
 */
void binfilecreate(std::unordered_map<int, std::string> &codeTableMap,
		char *filename, char const *out) {

	std::ifstream infile(filename);
	std::ofstream onfile(out, std::ios::out | std::ios::binary);

	int number;
	std::string value;
	while (infile >> number) {
		auto it_f = codeTableMap.find(number);
		if (it_f != codeTableMap.end()) {
			value += it_f->second;

		} else {
			std::cout << "-----------This cannot happen : " << (it_f->first)
					<< std::endl;
		}
	}
	std::cout << "File writing reached" << std::endl;
	std::vector<char> result;
	compress(value, result);
	std::cout << "Result size:" << result.size() << ", String size:"
			<< value.size() << std::endl;
	char *res = &result[0];
	onfile.write(res, result.size());
	onfile.close();
	infile.close();

}

//Fail safe
struct compare {
	bool operator()(hnode* l, hnode* r) {
		return (l->freq > r->freq);
	}
};

hnode* failsafe(std::unordered_map<int, unsigned int> const &freq_map) {

	std::priority_queue<hnode*, std::vector<hnode*>, compare> minHeap;
	for (auto it : freq_map) {
		hnode* huff_node = new hnode(it.first, it.second, NULL, NULL);
		minHeap.push(huff_node);
	}

	hnode *left, *right, *top;
	while ((minHeap.size() > 1)) {
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		top = new hnode(-1, left->freq + right->freq, left, right);
		minHeap.push(top);
	}

	return minHeap.top();
}
//Fail safe
/*
 * main method
 */
int main(int argc, char *argv[]) {

	if (argc != 2) {
		std::cout << "Usage:./" << argv[0] << " <input_file_name>\n";
		return 0;
	}

	std::ifstream infile(argv[1]);
	if (!infile.is_open()) {
		std::cout << "Could not open file\n";
		return 0;
	}

	//create the frequency map used by the program...
	std::unordered_map<int, unsigned int> freq_map;
	FillFrequencyMapFromFile(infile, freq_map);

	infile.close();

	clock_t start_time;
//
//	std::cout << "Huffman binary heap starts:" << std::endl;
//	start_time = clock();
//	hnode const* rootb = BuildTreeBheap(freq_map);
//	std::unordered_map<int, std::string> code_table_map1;
//	printCodes(rootb, "", code_table_map1);
//	std::cout << "Time using binary heap (microsecond):  "
//			<< (clock() - start_time) / 10 << std::endl;

	std::string of;
	std::cout << "Huffman 4way heap starts:" << std::endl;
	start_time = clock();
	hnode const* rootf = BuildTreeFheap(freq_map);
	std::unordered_map<int, std::string> code_table_map2;
	printCodes(rootf, "", code_table_map2);
	of = "encoded.bin";
	char const *o2 = of.c_str();
	binfilecreate(code_table_map2, argv[1], o2);
	std::cout << "Time using 4-way heap (microsecond):  "
			<< (clock() - start_time) / 10 << std::endl;

	std::cout << "Encode table:" << std::endl;
	std::string code_table_file_name = "code_table.txt";
	std::ofstream onfile(code_table_file_name, std::ios::out);
	for (auto it : code_table_map2) {
		onfile << it.first << " " << it.second << "\n";
	}
	onfile.close();

//	std::cout << "Huffman pairing heap starts:" << std::endl;
//	start_time = clock();
//	hnode const* rootp = BuildTreePheap(freq_map);
//	std::unordered_map<int, std::string> code_table_map3;
//	printCodes(rootp, "", code_table_map3);
//	std::cout << "Time using pairing heap (microsecond):  "
//			<< (clock() - start_time) / 10 << std::endl;

	return 0;
}

