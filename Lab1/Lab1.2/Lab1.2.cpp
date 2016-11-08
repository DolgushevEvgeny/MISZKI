// Lab1.2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

ifstream ReadableFile(const string &fileName) {
	ifstream inputFile;
	inputFile.open(fileName, ifstream::in | ifstream::binary);

	if (!inputFile) {
		cout << "No file";
		exit(1);
	}

	return inputFile;
}

ofstream WriteableFile(const string &fileName) {
	ofstream outputFile;
	outputFile.open(fileName, ofstream::out | ifstream::binary);

	if (!outputFile) {
		cout << "No file";
		exit(1);
	}

	return outputFile;
}

int main(int argc, char* argv[])
{
	if (argc != 4) {
		cout << "Not enough arguments!";
		return 0;
	}

	auto inputFile = ReadableFile(argv[1]);
	auto outputFile = WriteableFile(argv[2]);

	string key = argv[3];

	int i = 0;
	while (!inputFile.eof()) {
		char t;
		inputFile.get(t);
		if (inputFile.eof()) {
			break;
		}
		//cout << t;
		char decrypted = t - key[i % key.length()];
		++i;
		outputFile.put(decrypted);
	}

	inputFile.close();
	outputFile.close();
	return 0;
}

