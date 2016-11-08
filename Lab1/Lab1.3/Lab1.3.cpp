#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

set<char> FillAlphabet() {
	set<char> alphabet;

	alphabet.insert('\n');
	alphabet.insert('\r');
	alphabet.insert('!');
	alphabet.insert('?');
	alphabet.insert('.');
	alphabet.insert(',');
	alphabet.insert(':');
	alphabet.insert(';');
	alphabet.insert('"');
	alphabet.insert('\'');
	alphabet.insert('`');
	alphabet.insert(')');
	alphabet.insert('(');
	alphabet.insert('-');
	alphabet.insert(' ');

	for (char c = 'a'; c <= 'z'; ++c) {
		alphabet.insert(c);
	}
	for (char c = 'A'; c <= 'Z'; ++c) {
		alphabet.insert(c);
	}

	return alphabet;
}

set<char> FillKeys() {
	set<char> keys;
	for (unsigned char c = 0x80; c <= 0xAF; ++c) {
		keys.insert(c);
	}

	for (unsigned char c = 0xE0; c <= 0xF1; ++c) {
		keys.insert(c);
	}

	for (char c = '0'; c <= '9'; ++c) {
		keys.insert(c);
	}

	return keys;
}

bool attack(const vector<char> &encrypted, char &key) {
	auto alphabet = FillAlphabet();
	auto keys = FillKeys();

	for (char c_enc : encrypted) {
		start:
		for (char k : keys) {
			unsigned char decrypted = c_enc - k;
			if (alphabet.find(decrypted) == alphabet.end()){
				keys.erase(keys.find(k));
				goto start;
			}
		}
		cout << "test";
	}

	if (keys.size() == 1) {
		key = *keys.begin();
		return true;
	}
	else {
		if (keys.size() > 0) {
			key = *(--keys.end());
			return true;
		}
		return false;
	}
}

ifstream ReadableFile(const string &fileName) {
	ifstream inputFile;
	inputFile.open(fileName, ifstream::in | ifstream::binary);

	if (!inputFile) {
		cout << "No file";
		exit(1);
	}

	return inputFile;
}

vector<char> ReadFromFile(ifstream &file) {
	vector<char> buffer;
	while (!file.eof()) {
		char t;
		file.get(t);
		if (file.eof()) {
			break;
		}
		buffer.push_back(t);
	}

	return buffer;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Not enough arguments!";
		return 0;
	}

	auto inputFile = ReadableFile(argv[1]);
	auto buffer = ReadFromFile(inputFile);

	bool flag = true;
	int shift = 1;
	int steps = 1;
	vector<char> resultKey;
	while (flag) {
		resultKey.clear();
		for (int i = 0; i < steps; ++i) {
			vector<char> temp;
			for (size_t j = i; j < buffer.size(); j += shift) {
				//cout << buffer[j];
				temp.push_back(buffer[j]);
			}
			char key;
			if (attack(temp, key)) {
				//cout << key;
				resultKey.push_back(key);
				if (i == steps - 1) {
					flag = false;
					break;
				}
			}
			else {
				cout << "DAMN";
			}
		}
		++steps;
		++shift;
	}

	if (resultKey.size() == steps - 1) {
		cout << "\n" << "key : ";
		for (size_t i = 0; i < resultKey.size(); ++i) {
			cout << resultKey[i];
		}
		
	} else {
		cout << "DAMN";
	}

	return 0;
}

