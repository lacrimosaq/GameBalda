//
// Created by ADMIN on 18.04.2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "Game.h"

using namespace std;

Game::Game()
{
    //menu(table);
    computer_turn();

}
void Game::word(char (*table)[5]) {
    string word;
    vector<string> words;
    ifstream file("C:\\input.txt");
    while (!file.eof()) {
        string word;
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

void Game::show_table(char (*table)[5]) {
    cout.fill('-');
    cout.width(28);
    cout << "GAME";
    cout.fill('-');
    cout.width(25);
    cout << "-\n\n";
    cout << "o      ";
    unusedPlaces--;
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

void Game::play1(char (*table)[5]) {
    show_table(table);
    bool skipper = true;
    int x, y;
    char letter;
    while (unusedPlaces != 0 && skipper) {
        for (int i = 0; i < 2; i++) {
            cout << "\nEnter coords where do you want to add a letter (x;y): ";
            cin >> x >> y;
            cout << "\nEnter a letter: ";
            cin >> letter;
            table[x][y] = letter;
            unusedPlaces--;
        }
        show_table(table);
        cout << endl;
    }
}

void Game::play2(char (*table)[5]) {
    show_table(table);
    bool result = true;
    int x, y;
    char letter;
    while (result) {
        for (int i = 0; i < 2; i++) {
            cout << "\nFirst player\n";
            cout << "Enter coords where do you want to add a letter (x;y): ";
            cin >> x >> y;
            cout << "Enter a letter: ";
            cin >> letter;
            table[x][y] = letter;
        }
        show_table(table);
        for (int i = 0; i < 2; i++) {
            cout << "\nSecond player\n";
            cout << "Enter coords where do you want to add a letter (x;y): ";
            cin >> x >> y;
            cout << "Enter a letter: ";
            cin >> letter;
            table[x][y] = letter;
        }
        show_table(table);
    }
}

bool Game::helper_checkWord(string word){

    word = " " + word + " ";
    int offset;
    string line;
    ifstream Myfile;
    Myfile.open ("dictionary.txt");

    if (Myfile.is_open())
    {
        while (!Myfile.eof())
        {
            getline(Myfile,line);
            if ((offset = line.find(word, 0)) != string::npos)
            {
                cout << "found '" << word << "' in '" << line << "'" << endl;
                Myfile.close();
                return true;
            }
            else
            {
                cout << " not found '" << word << "' in '" << line << "'" << endl;
            }
        }
        Myfile.close();
    }
    else
        cout << "Unable to open this file." << endl;

    return false;
}

string Game::tmp_recurse(vector<int> unavaibleCells, string word, int x, int y){ // x, y - coord last added

    string tmp_word;
    unavaibleCells.push_back(x*10 + y);
    //if(horizontal){
        for(int i = 1; i < 5 - x; i++)
        {
            if(count(unavaibleCells.begin(), unavaibleCells.end(), (x+i)*10 + y)){ //check any next turn
                break;
            }
            tmp_word = word + tmp_table[x + i][y];
            if(helper_checkWord(tmp_word)){
                return tmp_word;
            }
            tmp_word = tmp_recurse(unavaibleCells, tmp_word, x + i, y);
            if(tmp_word != "-1"){
                return tmp_word;
            }
            break;
        }
        for(int i = 1; i <= x; i++)
        {
            if(count(unavaibleCells.begin(), unavaibleCells.end(), (x-i)*10 + y)){ //check any next turn
                break;
            }
            tmp_word = word + tmp_table[x - i][y];

            if(helper_checkWord(tmp_word)){
                return tmp_word;
            }

            tmp_word = tmp_recurse(unavaibleCells, tmp_word, x - i, y);
            if(tmp_word != "-1"){
                return tmp_word;
            }
            break;
        }
    //}
    //else{
        for(int j = 1; j < 5 - y; j++)
        {
            if(count(unavaibleCells.begin(), unavaibleCells.end(), x*10 + y + j)){ //check any next turn
                break;
            }
            tmp_word = word + tmp_table[x][y + j];

            if(helper_checkWord(tmp_word)){
                return tmp_word;
            }

            tmp_word = tmp_recurse(unavaibleCells, tmp_word, x , y + j);
            if(tmp_word != "-1"){
                return tmp_word;
            }
            break;
        }
        for(int j = 1; j <= y; j++)
        {
            if(count(unavaibleCells.begin(), unavaibleCells.end(), x*10 + y - j)){ //check any next turn
                break;
            }
            tmp_word = word + tmp_table[x][y - j];

            if(helper_checkWord(tmp_word)){
                return tmp_word;
            }

            tmp_word = tmp_recurse(unavaibleCells, tmp_word, x, y - j);
            if(tmp_word != "-1"){
                return tmp_word;
            }
            break;
        }

    //}
    return "-1";

}
string Game::computer_turn()
{
    string word = "";
    vector<int> unavaibleCells = {};

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(tmp_table[i][j] == '\\')
            {
               for(int l = 'a'; l <= 'z'; l++){
                    //tmp_table = table;
                    tmp_table[i][j] = 'a';
                    for(int k = 0; k < 5; k++)
                    {
                        for (int m = 0; m < 5; m++)
                        {
                            if(tmp_table[k][m] != '\\') {
                                word = "";
                                word += tmp_table[k][j];
                                word = tmp_recurse(unavaibleCells, word, i, j);
                                cout << "Answer: " + word;
                                if(word != "-1")
                                {
                                    //table = tmp_table
                                    return word;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return "-1";

}

void Game::menu(char (*table)[5]) {
    cout << "\n 1. Play Royal Baldu with computer" << endl;
    cout << " 2. Play Royal Baldu with other user" << endl;
    cout << " 3. Exit\n" << endl;
    int switcher;
    cout << "CHOOSE: ";
    cin >> switcher;
    switch (switcher) {
        case 1:
            word(table);
            play1(table);
            break;
        case 2:
            word(table);
            play2(table);
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