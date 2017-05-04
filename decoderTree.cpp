/*
 * decoder_HMT.cpp
 * created by: Jaspreet Bajwa
 */
#include <iostream>
#include <string>
#include <fstream>
#include "decoder.h"

using namespace std;

/*
 * generates decode huffman tree and the decoded.txt file
 */
int main(int arg, char const *argc[]) {

	if (arg != 3) {
		cout << "Usage: " << argc[0] << " encoded.bin code_table.txt" << endl;
		return 0;
	}

	std::ifstream f(argc[1], ios::binary | ios::in);
	if (!f.is_open()) {
		std::cout << "Could not open file\n";
		return 0;
	}

	ifstream ct(argc[2], ios::in);
	if (!ct.is_open()) {
		std::cout << "Could not open file\n";
		return 0;
	}

	Decoder dec = Decoder();
	int a;
	string b;
	cout << "Building Decoded Tree" << endl;
	while (ct >> a >> b) {
		dec.addLeaf(a, b);
	}

	cout << "Decoding binary file" << endl;
	ofstream outfile("decoded.txt", std::ios::out);

	char c;
	string resultChunk;
	while (f.get(c)) {
		for (int i = 7; i >= 0; i--) {
			int d = (c >> i) & 1;
			resultChunk.append(to_string(d));
			if (dec.getAt(resultChunk) != -1) {

				outfile << dec.getAt(resultChunk) << endl;
				resultChunk = "";
			}
		}

	}
	outfile.close();
	f.close();
	ct.close();
	return 0;
}

