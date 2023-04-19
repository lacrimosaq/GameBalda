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
    menu(table);
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
    bool result = true;
    int x, y;
    char letter;
    while (result) {
        for (int i = 0; i < 2; i++) {
            cout << "\nEnter coords where do you want to add a letter (x;y): ";
            cin >> x >> y;
            cout << "\nEnter a letter: ";
            cin >> letter;
            table[x][y] = letter;
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