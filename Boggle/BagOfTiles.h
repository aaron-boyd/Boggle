#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Tile.h"

using namespace std;

#ifndef BagOfTiles_H
#define BagOfTiles_H

class bagotiles {
public:

	tile* bagoftiles = new tile[150];


	void fill() {
		long x = 1;
		fstream tilefile;
		string line1, line2, line3;
		tilefile.open("Letters.txt");
		while (!tilefile.eof()) {
			tilefile >> line1;
			tilefile >> line2;
			tilefile >> line3;
			for (int i = 1; i <= stoi(line3); i++) {
				bagoftiles[x].letter = line1;
				bagoftiles[x].value = stoi(line2);
				bagoftiles[x].used = false;
				x++;
			}
		}
		tilefile.close();
	}

	void shuffle() {
		tile temp;
		int rnum;
		srand(time(NULL));
		for (int i = 1; i <= 100; i++) {
			rnum = rand() % (101 - i) + 1;
			temp = bagoftiles[rnum];
			bagoftiles[rnum] = bagoftiles[101 - i];
			bagoftiles[101 - i] = temp;
		}
	}

private:
};

#endif