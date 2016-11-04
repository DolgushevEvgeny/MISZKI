// Lab1.2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4) {
		cout << "Not enough arguments!";
		return 0;
	}

	ifstream inputFile;
	inputFile.open(argv[1], ifstream::in | ifstream::binary);

	if (!inputFile) {
		cout << "No file";
		return 0;
	}

	ofstream outputFile;
	outputFile.open(argv[2], ofstream::out | ifstream::binary);

	if (!outputFile) {
		cout << "No file";
		return 0;
	}

	string key = argv[3];

	int i = 0;
	while (!inputFile.eof()) {
		char t;
		inputFile.get(t);
		if (inputFile.eof()) {
			break;
		}
		cout << t;
		char encrypted = t - key[i % key.length()];
		++i;
		outputFile.put(encrypted);
	}

	inputFile.close();
	outputFile.close();
	return 0;
}

