//
// Created by ADMIN on 18.04.2023.
//

#ifndef GAMEBALDA_GAME_H
#define GAMEBALDA_GAME_H
#include <vector>
#include <set>
#include <string>
using namespace std;

class Game {
private:
    int pointsUser1 = 0;
    int pointsUser2 = 0;
    int unusedPlaces = 20;
    char main_table[5][5] = {{'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},
                        {'\\','\\','\\','\\','\\'},};
    char tmp_table[5][5] = {    //helper game table for check and using in method
            {'q','w','e','r','t'},
            {'a','s','d','f','g'},
            {'z','x','c','v','b'},
            {'y','u','i','o','p'},
            {'h','j','k','l','m'},};
    set<string> find_words; //already used words
    bool skipper1 = true; //true if turn done - false if turn skipped
    bool skipper2 = true; //true if turn done - false if turn skipped
    bool helper_threadIsEnd = false; //helper variable for method waitForComputer()

public:

    Game();
    string toLowerCaseString(string str); //string to lowercase
    string computer_turn_recurse(vector<int> unavaibleCells, string word, int x, int y); //helper method for check any word in table
    bool helper_checkWord(string word); //helper check word in file
    string randomWordFromFile();  //take random word from files with words
    bool checkGoodPlaceForLetter(int x, int y); // check if in this cells letter can touch with any else letters
    void show_table(char table[5][5]); //display table into console
    bool checker(std::string find_word, char table[5][5]); // new checker with algorithm
    bool userTurn (); //turns of users return if user complete turn
    void gameOver1() const; // display the result of game with computer
    void gameOver2() const;// display the result of game 2 users
    void playVersusComputer(); //console user interface turn
    void playVersusPlayer(); //console user interface turn for 2 users
    string computer_turn(); //turn by computer
    void menu(); //console user interface menu
    void resetVariable(); //reset all variable before game start
    void waitForComputer(); //(additional thread) console write message that computer still making turn


};


#endif //GAMEBALDA_GAME_H
