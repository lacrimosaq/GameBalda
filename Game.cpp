//
// Created by ADMIN on 18.04.2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <set>
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


bool Game::checker1(string find_word){
    set<string> find_words;
    int nuller = 0;
    int checker = 0;
    bool result = false;
    if(!find_words.count(find_word)){
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (find_word[nuller] == table[i][j]) {
                    nuller++;
                    while (checker < find_word.size() + 1) {
                        if (j != 4) {
                            j++;
                            if (find_word[nuller] == table[i][j]) nuller++;
                            else j--;
                            if (j != 0) {
                                j--;
                                if (find_word[nuller] == table[i][j]) nuller++;
                                else j++;
                            }
                            if (i != 4) {
                                i++;
                                if (find_word[nuller] == table[i][j]) nuller++;
                                else i--;
                            }
                        }
                        if (i != 0) {
                            i--;
                            if (find_word[nuller] == table[i][j]) nuller++;
                            else i++;
                        }
                        if (nuller == find_word.size()){i+=5; j+=5;}
                        checker++;
                    }
                }
            }
        }
    } else {
        cout << "The word has been used before" << endl;
        return false;
    }
    if (nuller >= find_word.size()) {
        result = true;
        find_words.insert(find_word);
    }
    return result;
}

void Game::user1Turn() {
    int x, y;
    char letter;
    string find_word;
    skipper1 = true;
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
        show_table();
        cout << "Enter what word do you want to write (q - to quit): ";
        cin >> find_word;
        if (find_word[0] != 'q'){
            if(checker1(find_word)) {
                pointsUser1++;
                cout << "You earned 1 point --- "<<" Your points - " << pointsUser1 << endl;
            }
            else {
                cout << "There are no such word" << endl;
                cout << "Your points - " << pointsUser1 << endl;
            }
        }
        show_table();
    }
}

void Game::user2Turn() {
    int x, y;
    char letter;
    string find_word;
    skipper2 = true;
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
        show_table();
        cout << "Enter what word do you want to write (q - to quit): ";
        cin >> find_word;
        if (find_word[0] != 'q'){
            if(checker1(find_word)) {
                pointsUser2++;
                cout << "You earned 1 point --- "<<" Your points - " << pointsUser2 << endl;
            }
            else {
                cout << "There are no such word" << endl;
                cout << "Your points - " << pointsUser2 << endl;
            }
        }
        show_table();
    }
}

void Game::gameOver1() const{
    if (pointsUser1 > pointsUser2)
        cout << "You won !!!" << endl;
    else if (pointsUser1 == pointsUser2)
        cout << "\nDry" << endl;
    else
        cout << "You lost !!!" << endl;
    cout << "You reached - " << pointsUser1 << " --- ";
    cout << "Comp reached - " << pointsUser2 << endl;
}

void Game::gameOver2() const{
    if (pointsUser1 > pointsUser2)
        cout << "First player won !!!" << endl;
    else if (pointsUser1 == pointsUser2)
        cout << "\nDry" << endl;
    else
        cout << "Second player won !!!" << endl;
    cout << "First player reached - " << pointsUser1 << " --- ";
    cout << "Second player reached - " << pointsUser2 << endl;
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
    gameOver1();
}

void Game::play2() {
    word();
    show_table();
    while (unusedPlaces != 0 && (skipper1 || skipper2)) {
        user1Turn();
        user2Turn();
    }
    gameOver2();
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

