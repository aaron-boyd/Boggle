#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef Words_H
#define Words_H

class words {
public:
	string* arrwords = new string[54402];
	void openwords() {
		long x = 1;
		fstream wordfile;
		wordfile.open("Short Dictionary.txt");
		while (!wordfile.eof()) {
			wordfile >> arrwords[x];
			//cout << arrwords[x] << " ";
			x++;
		}
		wordfile.close();
	}

private:


};
class guessword {
public:
	string letter;
	bool used;
};

#endif