//
// Created by ADMIN on 18.04.2023.
//

#ifndef GAMEBALDA_GAME_H
#define GAMEBALDA_GAME_H
#include <vector>
using namespace std;

class Game {
private:
    int pointsUser1 = 0;
    int pointsUser2 = 0;
    int unusedPlaces = 20;
    char table[5][5] = {{'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},};
    char tmp_table[5][5] = {
            {'q','w','e','r','t'},
            {'a','s','d','f','g'},
            {'z','x','c','v','b'},
            {'y','u','i','o','p'},
            {'h','j','k','l','m'},};

    string tmp_recurse(vector<int> unavaibleCells, string word, int x, int y); //helper method
    bool helper_checkWord(string word); //helper check word in file
    bool skipper1 = true;
    bool skipper2 = true;

    Game();
    void word();  //take random word from files with words
    void show_table(); //display table into console
   // bool checker(std::string find_word , int x, int y); // old checher
    bool checker1(std::string find_word); // new checker with algoritm
    void user1Turn (); //turns of users
    void user2Turn (); //turns of users
    void gameOver1() const; // display the result of game with computer
    void gameOver2() const;// display the result of game 2 users
    void play1(); //console user interface turn
    void play2(); //console user interface turn for 2 users
    string computer_turn(); //turn by computer
    void menu(); //console user interface menu

};


#endif //GAMEBALDA_GAME_H
