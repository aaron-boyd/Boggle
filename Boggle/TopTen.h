#pragma once
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include "Player.h"

class Topten {
public:
	player topten[10];

	void open() {
		long x = 0;
		fstream tilefile;
		string line1, line2;
		tilefile.open("TopTen.txt");
		while (!tilefile.eof()) {
			tilefile >> line1;
			tilefile >> line2;
			topten[x].name = line1;
			topten[x].score = stoi(line2);
			//cout << (x+1) << "." << topten[x].name << " " << topten[x].score << endl;
			x++;
		}
		tilefile.close();
	}

	void save() {
		ofstream myfile;
		string line;
		char buff[10];
		myfile.open("TopTen.txt");
		for (int i = 0; i <= 9; i++) {
			sprintf_s(buff, "%i", topten[i].score);
			line = topten[i].name + " " + buff + "\n";
			myfile << line;
		}
		myfile.close();
	}

	void sort() {
		player temp;
		for (int front = 0; front <= 9; front++) {
			for (int back = front + 1; back <= 10; back++) {
				if (topten[front].score < topten[back].score) {
					temp = topten[front];
					topten[front] = topten[back];
					topten[back] = temp;
				}
			}
		}
	}

	void display() {
		for (int i = 0; i <= 9; i++) {
			cout << (i + 1) << "." << topten[i].name << " " << topten[i].score << endl;
		}
	}

};