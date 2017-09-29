#include "Words.h"
#include "BagOfTiles.h"
#include "Player.h"
#include "TopTen.h"

void deal(), playerguess();
void dealcontinued(), begingame();
int checkword(string guess);
int checkscore(string w, tile word[7]);
words open;
bagotiles bag;
player plyer;
Topten tt;
int tilesused = 0;

int main() {
	open.openwords();
	tt.open();
	bag.fill();
	bag.shuffle();
	begingame();
}

void begingame() {
	//cout << "Welcome to Scrabble!\n-Top ten = TOPTEN\n-New game = NEWGAME\n-End game = END\nPlease enter your initials: ";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "|                                            ~~~ Welcome to Scrabble! ~~~                                            |" << endl;
	cout << "|                                         --To get a new hand enter NEWHAND                                          |" << endl;
	cout << "|                                           --To see top ten enter TOPTEN                                            |" << endl;
	cout << "|                                         --To start new game enter NEWGAME                                          |" << endl;
	cout << "|                                               --To exit enter EXIT                                                 |" << endl;;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl << endl;
	cout << "Please enter your initials: ";
	cin >> plyer.name;
	if (plyer.name.length() != 3) {
		do {
			cout << "ERROR! Please enter three(3) initials: ";
			cin >> plyer.name;
		} while (plyer.name.length() != 3);
	}
	tilesused = 0;
	plyer.score = 0;
	deal();
}
void deal() {
	string letters;
	for (int i = 0; i <= 6; i++) {
		tilesused++;
		plyer.hand[i] = bag.bagoftiles[tilesused];
	}
	cout << "---------------------------------------------------------" << endl;
	cout << "|       |       |       |       |       |       |       |" << endl;
	cout << "|   " << plyer.hand[0].letter << "   |   " << plyer.hand[1].letter << "   |   " << plyer.hand[2].letter << "   |   " << plyer.hand[3].letter << "   |   " << plyer.hand[4].letter << "   |   " << plyer.hand[5].letter << "   |   " << plyer.hand[6].letter << "   |" << endl;
	cout << "|      " << plyer.hand[0].value << "|      " << plyer.hand[1].value << "|      " << plyer.hand[2].value << "|      " << plyer.hand[3].value << "|      " << plyer.hand[4].value << "|      " << plyer.hand[5].value << "|      " << plyer.hand[6].value << "|" << endl;
	cout << "---------------------------------------------------------" << endl;
	playerguess();
}

void dealcontinued() {
	string letters;
	for (int i = 0; i <= 6; i++) {
		if (plyer.hand[i].used == true) {
			tilesused++;
			if (tilesused == 100) {
				bag.shuffle();
				tilesused = 1;
			}
			plyer.hand[i] = bag.bagoftiles[tilesused];
		}
	}
	cout << "---------------------------------------------------------" << endl;
	cout << "|       |       |       |       |       |       |       |" << endl;
	cout << "|   " << plyer.hand[0].letter << "   |   " << plyer.hand[1].letter << "   |   " << plyer.hand[2].letter << "   |   " << plyer.hand[3].letter << "   |   " << plyer.hand[4].letter << "   |   " << plyer.hand[5].letter << "   |   " << plyer.hand[6].letter << "   |" << endl;
	cout << "|      " << plyer.hand[0].value << "|      " << plyer.hand[1].value << "|      " << plyer.hand[2].value << "|      " << plyer.hand[3].value << "|      " << plyer.hand[4].value << "|      " << plyer.hand[5].value << "|      " << plyer.hand[6].value << "|" << endl;
	cout << "---------------------------------------------------------" << endl;
	playerguess();
}

void playerguess() {
	string guess, cont;
	int score;
	cout << "Please enter your guess: ";
	cin >> guess; 
	if (guess == "TOPTEN") {
		tt.topten[10] = plyer;
		tt.sort();
		tt.display();
		cout << "Would you like to continue? (Y/N): ";
		cin >> cont;
		if (cont == "Y" | cont == "y") {
			playerguess();
		}
		else if (cont == "N" | cont == "n") {
			tt.save();
			exit(EXIT_SUCCESS);
		}
	}
	else if (guess == "EXIT") {
		tt.save();
		cout << "Thanks for playing! Goodbye!" << endl;
		exit(EXIT_SUCCESS);
	}
	else if (guess == "NEWGAME") {
		tt.save();
		begingame();
	}
	else if (guess == "NEWHAND") {
		cout << "Are you sure you want a new hand? You will lose 20 points: ";
		cin >> cont;
		if (cont == "Y" | cont == "y") {
			plyer.score -= 20;
			deal();
			playerguess();
		}
		else if (cont == "N" | cont == "n") {
			playerguess();
		}
	}
		 else{
			score = checkword(guess);
			if (score == 0) {
				cout << "Thats not a word silly goose!" << endl;
				playerguess();
			}
			else {
				cout << "You recieved " << score << " points!" << endl;
				plyer.score += score;
				cout << "Your score " << plyer.score << endl << endl;
			}
			dealcontinued();
		}
	}

int checkword(string g) {
	guessword wd[7];
	tile word[7];
	string w;
	int count = 0;
	int limit = g.length();

	for (int i = 0; i <= 6; i++) {
		plyer.hand[i].used = false;
	}

	for (int i = 0; i < limit; i++) {
		wd[i].letter = g.substr(i, 1);
		wd[i].used = false;
	}


	for (int i = 0; i < limit; i++) {
		for (int x = 0; x <= 6; x++) {
			if (wd[i].letter == plyer.hand[x].letter) {
				if (plyer.hand[x].used == false && wd[i].used == false) {
					word[count] = plyer.hand[x];
					count++;
					w += wd[i].letter;
					plyer.hand[x].used = true;
					wd[i].used = true;

				}
			}
		}
	}

	return(checkscore(w, word));
}

int checkscore(string w, tile word[7]) {
	int score = 0;
	int limit = w.length();
	for (int i = 1; i <= 54402; i++) {
		if (w == open.arrwords[i]) {
					for (int i = 0; i < limit; i++) {
						score += word[i].value;
					}
		}
	}
	return(score);
}