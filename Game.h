//
// Created by ADMIN on 18.04.2023.
//
#include <string>

#ifndef GAMEBALDA_GAME_H
#define GAMEBALDA_GAME_H

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
    bool skipper1 = true;
    bool skipper2 = true;
public:
    int getPointsUser() const;
    int getPointsComp() const;

public:

    Game();
    void word();  //take random word from files with words
    void show_table(); //display table into console
    bool checker(std::string find_word , int x, int y);
    void user1Turn (); //turns of users
    void user2Turn (); //turns of users
    void gameOver(); // display the result of game
    void play1(); //console user interface turn
    void play2(); //console user interface turn for 2 users
    void menu(); //console user interface menu
};


#endif //GAMEBALDA_GAME_H
