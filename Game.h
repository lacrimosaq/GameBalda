//
// Created by ADMIN on 18.04.2023.
//

#ifndef GAMEBALDA_GAME_H
#define GAMEBALDA_GAME_H
using namespace std;

class Game {
private:
    int pointsUser = 0;
    int pointsComp = 0;
    int unusedPlaces = 20;
    char table[5][5] = {{'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},};

public:

    Game();
    void word(char (*table)[5]); //take random word from files with words
    void show_table(char (*table)[5]); //display table into console
    void play1(char (*table)[5]); //console user interface turn
    void play2(char (*table)[5]); //console user interface turn for 2 users
    void menu(char (*table)[5]); //console user interface menu


};


#endif //GAMEBALDA_GAME_H
