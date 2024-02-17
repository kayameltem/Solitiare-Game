#ifndef SLOT_H_
#define SLOT_H_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Card.h"
using namespace std;

class Slot {
private:
    Card *arr[28] = {};
    int length = -1;
    char suit = 'X';
public :

    Slot() {}

    Slot(char suit) {
        this->suit = suit;
    }

    void add(Card *c) {
        length++;
        arr[length] = c;

    }

    Card *del() {
        length--;
        return arr[length + 1];
    }

    int getLength() {
        return length;
    }

    Card *last() {
        return arr[length];

    }

    bool isEmpty() {
        if (length == -1) { return 1; }
        else { return 0; }

    }

    Card *element(int index) {
        return arr[index];

    }

    char getSuit() {
        return suit;

    }

    bool toPile(int index, Slot *pile){
        int indexCopy = index;
        if (!isEmpty() && arr[length-index]->isOpened()  && ((pile->isEmpty() && arr[length - index]->getValue() == 13) ||
                                                             (!pile->isEmpty() && pile->last()->isOpened() && pile->last()->getColor() != arr[length - index]->getColor() &&
                                                              pile->last()->getValue() == arr[length - index]->getValue() + 1))) {

            for (; index >= 0; index--) {
                pile->add(arr[length - index]);
            }
            length -= (indexCopy + 1);
            return 1;
        }
        return 0;
    }
    bool wasteFromStock(Slot* stock) {
        if (stock->isEmpty()) {
            while (!isEmpty()) {
                last()->closeCard();
                stock->add(del());
            }
            return 1;
        }
        else {
            int i = 3;
            while (!stock->isEmpty() && i > 0 ) {
                stock->last()->openCard();
                add(stock->del());
                i--;
            }
            return 1;
        }
        return 0;

    }
    bool wasteToFoundation(Slot* f[]){
        int index = 0;
        for (; index<4 ; index++) {
            if(!isEmpty() && last()->getSuit() == f[index]->getSuit()) {
                if( (f[index]->isEmpty() && last()->getValue() == 1 )||(!f[index]->isEmpty() && last()->getValue() == f[index]->last()->getValue() +1 )) {
                    f[index]->add(del());
                    return 1;
                }
            }

        }
        return 0;
    }
    bool wasteToPile(Slot* p){
        if (!isEmpty() && ((p->isEmpty() && last()->getValue() == 13 ) ||
                           (!p->isEmpty()&& p->last()->isOpened() && last()->getColor() != p->last()->getColor() && p->last()->getValue() == last()->getValue() +1))) {
            p->add(del());
            return 1;
        }
        return 0;
    }
    bool foundationToPile(Slot* p){
        if(! isEmpty() && ((p->isEmpty() && last()->getValue() == 13) ||
                           (!p->isEmpty() && p->last()->isOpened() && p->last()->getValue() == last()->getValue() +1 && last()->getColor() != p->last()->getColor())))
        {
            p->add(del());
            return 1;
        } return 0;

    }
    bool pileToFoundation(Slot* f[]){
        int index = 0;
        for (;index <4;index++) {
            if  ( !isEmpty() && last()->isOpened() && last()->getSuit() == f[index]->getSuit()) {
                if((f[index]->isEmpty() && last()->getValue() == 1) ||(!f[index]->isEmpty()&& f[index]->last()->getValue() == last()->getValue() -1)) {
                    f[index]->add(del());
                    return 1;
                }
            }
        } return 0;
    }
};

#endif /* SLOT_H_ */
