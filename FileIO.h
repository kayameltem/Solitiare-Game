#ifndef DENEMECPP_FILEIO_H
#define DENEMECPP_FILEIO_H
#include  <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Slot.h"
#include "Card.h"
class FileIO {
    private :
    Slot* pile[7] = {new Slot(),new Slot(),new Slot(),new Slot(),new Slot(),new Slot(),new Slot()} ;
    Slot* foundation[4] = {new Slot('H'), new Slot('D'), new Slot('S'), new Slot('C')};
    Slot waste,stock,cards;
    public :
    FileIO() {}
        void input(char* argv){
            string line;
            ifstream deck(argv);
            int i = 0, j = 0;
            while (getline(deck,line)) {

                if (stock.getLength() <23) {
                    stock.add(new Card(line));
                }
                else { cards.add(new Card(line));
                }
            }
            deck.close();

            for (; i < 7 ; i++) {
                cards.last()->openCard();
                for(j = i;j < 7 ; j++) {
                    pile[j]->add(cards.del());
                }
            }
        }
        string display(Slot* stock, Slot* waste, Slot* f[], Slot* p[]) {
            int i = 2, j = 0, x = 0;
            string display = "";
            if (stock->isEmpty()) { display.append("___ ");}
            else {display.append("@@@ ");}
            if (waste->isEmpty()) {display.append("___ ___ ___ ");}
            else {
                while (i >=0 ) {
                    if (!waste->isEmpty() && waste->getLength() -i >= 0 ) {
                        display.append(waste->element(waste->getLength()-i)->getID().append(" "));
                    }
                    else {
                        display.append("____ ");
                    } i--;
                }
            }
            display.append("        ");
            j = 0;
            for(; j<4;j++) {
                if (f[j]->isEmpty()) {
                    display.append("___ ");
                }
                else {
                    display.append(f[j]->last()->getID().append(" "));
                }

            }
            display.append("\n\n");
            i = 0;
            while(i < 19 && x!= 7) {
                x = 0;
                for(j = 0;j < 7 ; j++) {
                    if (p[j]->isEmpty() || p[j]->getLength() < i) {
                        display.append("      ");
                        x++;
                    }
                    else if (p[j]->element(i)->isOpened()) {
                        display.append(p[j]->element(i)->getID() + "   ");
                    }
                    else {
                        display.append("@@@   ");

                    }
                }
                i++;
                display.append("\n");
            }
            return display;

        }

        string output(string c,Slot *s, Slot* w, Slot* f[], Slot* p[]) {
            if(c.find("open from stock") == 0 && w->wasteFromStock(s)) {
                return c;
            }
            else if(c.find("open" ) == 0 && !p[(int)c[5]-48]->isEmpty() && p[(int)c[5]-48]->last()->openCard()) {
                return c;
            }
            else if (c.find("move pile") == 0) {
                if (c.length() == 15 && p[(int)c[10]-48]->toPile((int)c[12]-48, p[(int)c[14]-48])) {
                    return c ;
                }
                else if ( c.length() == 16 && p[(int)c[10]-48]->toPile(stoi(c.substr(12,2)), p[(int)c[15]-48])){
                    return c ;
                }
            }
            else if (c.find( "move waste" ) == 0 && w->wasteToPile(p[(int)c[11]-48])){
                return c;
            }

            else if (c.find("move foundation" ) == 0 && f[(int)c[16]-48]->foundationToPile(p[(int)c[18]-48])){
                return c;
            }
            else if (c.find("move to foundation pile") == 0 && p[(int)c[24]-48]->pileToFoundation(f) ){
                return c;}
            else if (c.find("move to foundation waste" ) == 0 && w->wasteToFoundation(f)){
                return c;}
            return c.append("\n\nInvalid Move !");

        }
            void out(char* comd,char* argv3){
                string line;
				remove(argv3);
                fstream command(comd);
                ofstream sout(argv3, ios::app);
                sout << display(&stock, &waste, foundation, pile) ;
                while (getline(command,line)) {
                    if (line.find("exit") == 0) {
                        sout << "exit\n" << endl ;
                        break;
                    }
                    sout<< output(line,&stock,&waste,foundation,pile).append("\n") << endl;
                    sout << "****************************************\n" << endl;
                    sout << display(&stock, &waste, foundation, pile) ;
                }
                sout << "****************************************" << endl;
                if (foundation[0]->getLength() == 12 && foundation[1]->getLength() == 12 && foundation[2]->getLength() == 12 && foundation[3]->getLength() == 12 ) {
                    sout <<"You win !\n" << endl;
                }
                sout<< "\nGame Over !" << endl;
                command.close();
        }




};

#endif //DENEMECPP_FILEIO_H
