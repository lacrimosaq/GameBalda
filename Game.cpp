//
// Created by ADMIN on 18.04.2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "Game.h"

using namespace std;

Game::Game()
{
    menu();
}
void Game::word() {
    string word;
    vector<string> words;
    ifstream file("C:\\input.txt");
    while (!file.eof()) {
        file >> word;
        words.push_back(word);
    }
    default_random_engine gen{std::random_device()()};
    uniform_int_distribution<> dist(0, words.size() - 1);
    word = words[dist(gen)];
    for (int i = 0; i < 5; i++) {
        table[2][i] = word[i];
    }
}
void Game::show_table() {
    cout.fill('-');
    cout.width(28);
    cout << "GAME";
    cout.fill('-');
    cout.width(25);
    cout << "-\n\n";
    cout << "o      ";
    for (int i = 0; i < 5; i++) {
        if (i != 4)
            cout << 'Y' << i << '\t';
        else cout << 'Y' << i << "      o";
    }
    cout << endl;
    cout << '\t';
    for (int i = 0; i < 5; i++) {
        cout << "_" << '\t';
    }
    cout << endl;
    for (int i = 0; i < 5; i++) {
        cout << 'X' << i << '|' << '\t';
        for (int j = 0; j < 5; j++) {
            if (table[i][j] != '\\')
                cout << table[i][j] << '\t';
            else cout << '*' << '\t';
        }

        cout << "|X" << i << endl;
    }
    cout << '\t';
    for (int i = 0; i < 5; i++) {
        cout << "_" << '\t';
    }
    cout << endl;
    cout << "o      ";
    for (int i = 0; i < 5; i++) {
        if (i != 4)
            cout << 'Y' << i << '\t';
        else cout << 'Y' << i << "      o";
    }
}

int Game::getPointsUser() const {
    return pointsUser;
}

int Game::getPointsComp() const {
    return pointsComp;
}
bool Game::checker(string find_word, int x, int y){
    int nuller = 0;
    bool result = false;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if(find_word[nuller] == table[i][j]){
                i = 0;
                j = 0;
                nuller++;
            }
        }
    }
    if (nuller == find_word.size())
        result = true;
    return result;
}

void Game::user1Turn() {
    int x, y;
    char letter;
    string find_word;
    for (int i = 0; i < 2; i++) {
        cout << "\nFirst player\n";
        cout << "Enter coords where do you want to add a letter (x;y), " << "(5;5)" << " to skip a turn : ";
        cin >> x >> y;
        if (x != 5 && y != 5) {
            unusedPlaces--;
            cout << "Enter a letter: ";
            cin >> letter;
            table[x][y] = letter;
        } else {
            skipper1 = false;
            i++;
            cout << "First player skipped the turn\n";
        }
        cout << "Enter what word do you want to write (q - to quit): ";
        cin >> find_word;
        if (find_word[0] != 'q'){
            if(checker(find_word, x, y)) {
                pointsUser++;
                cout << "Your points - " << pointsUser << endl;
            }
        }
        show_table();
    }
}

void Game::user2Turn() {
    int x, y;
    char letter;
    string find_word;
    for (int i = 0; i < 2; i++) {
        cout << "\nSecond player\n";
        cout << "Enter coords where do you want to add a letter (x;y), " << "(5;5)" << " to skip a turn : ";
        cin >> x >> y;
        if (x != 5 && y != 5) {
            unusedPlaces--;
            cout << "Enter a letter: ";
            cin >> letter;
            table[x][y] = letter;
        } else {
            skipper2 = false;
            i++;
            cout << "Second player skipped the turn\n";
        }
        cout << "Enter what word do you want to write (q - to quit): ";
        cin >> find_word;
        if (find_word[0] != 'q'){
            if(checker(find_word, x, y)) {
                pointsUser++;
                cout << "Your points - " << pointsUser << endl;
            }
        }
        show_table();
    }
}

void Game::gameOver(){
    if (getPointsUser() > getPointsComp())
        cout << "You won !!!" << endl;
    else if (getPointsComp() == getPointsUser())
        cout << "\nDry" << endl;
    else
        cout << "You lost !!!" << endl;
    cout << "You reached - " << getPointsUser() << " --- ";
    cout << "Comp reached - " << getPointsComp() << endl;
}

void Game::play1() {
    word();
    show_table();
    while (unusedPlaces != 0 && (skipper1 || skipper2)) {
        user1Turn();
        show_table();
        user2Turn();
        show_table();
    }
    gameOver();
}

void Game::play2() {
    word();
    show_table();
    while (unusedPlaces != 0 && (skipper1 || skipper2)) {
        user1Turn();
        user2Turn();
    }
    gameOver();
}

void Game::menu() {
    cout << "\n 1. Play Royal Baldu with computer" << endl;
    cout << " 2. Play Royal Baldu with other user" << endl;
    cout << " 3. Exit\n" << endl;
    int switcher;
    cout << "CHOOSE: ";
    cin >> switcher;
    switch (switcher) {
        case 1:
            play1();
            break;
        case 2:
            play2();
            break;
        case 3:
            cout << "Goodbye -___-" << endl;
            break;
        default:
            cout << "Invalid value" << endl;
            cout << "CHOOSE: ";
            cin >> switcher;
            break;
    }
}

int main(){
    Game gamer;
    return 0;
}