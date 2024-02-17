#ifndef CARD_H_
#define CARD_H_

#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

class Card {
	private:
		bool opened;
		char suit;
		int value;
		string id;
		char color ;
	public:
		Card(){}
		Card(string card) {
		    value = stoi(card.substr(1,2));
			id  = card;
			suit = card[0];

			if (suit == 'C' || suit == 'S') {
				color = 'B';
			}
			else if  (suit == 'D' || suit == 'H') {
				color = 'R';
			}
			opened = 0;
		}
		bool isOpened() {
			return opened ;
		}
		bool openCard() {
		    if (!opened) {
                opened = 1;
                return 1;
            }
		    else {return 0;}
		}
		void closeCard() {
            opened = 0;
		}
		string getID() {
			return id;
		}

		char getSuit() {
			return suit;
		}
		int getValue() {
			return value;
		}
		char getColor() {
			return color;

		}

};

#endif /* CARD_H_ */
