// Lab1.3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

bool attack(const vector<char> &encrypted, char &key) {
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
		return false;
	}
}

ifstream ReadableFile(string fileName) {
	ifstream inputFile;
	inputFile.open(fileName, ifstream::in | ifstream::binary);

	if (!inputFile) {
		cout << "No file";
		exit(1);
	}

	return inputFile;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Not enough arguments!";
		return 0;
	}

	auto inputFile = ReadableFile(argv[1]);

	vector<char> buffer;
	while (!inputFile.eof()) {
		char t;
		inputFile.get(t);
		if (inputFile.eof()) {
			break;
		}
		buffer.push_back(t);
	}

	char key;
	if (attack(buffer, key)) {
		cout << key;
	}
	else {
		cout << "damn";
	}
	cout << "ready";

	return 0;
}

