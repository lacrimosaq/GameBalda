//
// Created by ADMIN on 18.04.2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <set>
#include <algorithm>
#include "Game.h"

using namespace std;

Game::Game()
{
    menu();
    //computer_turn();
}
void Game::word() {
    string word;
    vector<string> words;
    ifstream file("cmake-build-debug\\input.txt");
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
    find_words.insert(word);
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
cout << endl;
}


/*
bool Game::checker(string find_word, int x, int y) {
    int nuller = 0;
    bool result = false;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (find_word[nuller] == table[i][j]) {
                i = 0;
                j = 0;
                nuller++;
            }
        }
    }

    if (nuller == find_word.size())
        result = true;
    return result;
}*/

bool Game::checker(string find_word){
    int nuller = 0;
    int temp = 0;
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
                        }
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

                        if (i != 0) {
                            i--;
                            if (find_word[nuller] == table[i][j]) nuller++;
                            else i++;
                        }
                        if (nuller == find_word.size()){i+=5; j+=5;}
                        checker++;
                    }
                    temp = nuller;
                    nuller = 0;
                }
            }
        }
    } else {
        cout << "The word has been used before" << endl;
        return false;
    }
    if (temp >= find_word.size()) {
        result = true;
        find_words.insert(find_word);
    }
    return result;
}


void Game::user1Turn() {
    string find_word;
    skipper1 = true;
    for (int iter = 0; iter < 2; iter++) {
        cout << "\n---------------------First player--------------------\n";
        cout << "Enter coords where do you want to add a letter (x;y)\n "
             << "(5;5)" << "-  to skip a turn    : ";
        skipper1 = set_letter(iter);
        show_table();
        cout << "Enter what word do you want to write\n (q - to quit): ";
        cin >> find_word;
        if (find_word[0] != 'q') {
            if (helper_checkWord(find_word)) {
                if (checker(find_word)) {
                    pointsUser1 += find_word.size();
                    cout << "You earned " << find_word.size() << " point --- " << " Your points - " << pointsUser1
                         << endl;
                } else {
                    cout << "There are no such word" << endl;
                    cout << "Your points - " << pointsUser1 << endl;
                }
            } else cout << "There are no such word in dictionary!\n";
        } else iter++;
    }
}

void Game::user2Turn() {
    string find_word;
    skipper2 = true;
    for (int iter = 0; iter < 2; iter++) {
        cout << "\n-------------------Second player-------------------\n";
        cout << "Enter coords where do you want to add a letter (x;y)\n "
             << "(5;5)" << "-  to skip a turn    : ";
        skipper2 = set_letter(iter);
        show_table();
        cout << "Enter what word do you want to write (q - to quit): ";
        cin >> find_word;
        if (find_word[0] != 'q'){
            if (helper_checkWord(find_word)) {
            if(checker(find_word)) {
                pointsUser2 +=find_word.size();
                cout << "You earned "<<find_word.size() <<" point --- "<<" Your points - " << pointsUser2 << endl;
            }
            else {
                cout << "There are no such word" << endl;
                cout << "Your points - " << pointsUser2 << endl;
            }
            } else cout << "There are no such word in dictionary!\n";

        }else iter++;
    }
}

void Game::gameOver1() const{
    cout << "\n-----------------Point of players------------------\n"
              "----------------- ["<< pointsUser1 <<':'<<pointsUser2 <<"]------------------\n";
    if (pointsUser1 > pointsUser2)
        cout << "-----------------You won !!!-----------------" << endl;
    else if (pointsUser1 == pointsUser2)
        cout << "--------------------Dry----------------------" << endl;
    else
        cout << "-----------------You lost !!!----------------" << endl;
}

void Game::gameOver2() const{
    cout << "\n-----------------Point of players------------------\n"
            "----------------------["<< pointsUser1 <<':'<<pointsUser2 <<"]----------------------\n";
    if (pointsUser1 > pointsUser2)
        cout << "------------First player won !!!-----------" << endl;
    else if (pointsUser1 == pointsUser2)
        cout << "------------------------Dry------------------------" << endl;
    else
        cout << "-------------Second player won !!!---------" << endl;
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

  //  word = " " + word + " ";
    int offset;
    string line;
    ifstream Myfile;
    Myfile.open ("cmake-build-debug\\dict.txt");

    if (Myfile.is_open())
    {
        while (!Myfile.eof())
        {
            getline(Myfile,line);
            if ((offset = line.find(word, 0)) != string::npos)
            {
                //cout << "found '" << word << "' in '" << line << "'" << endl;
                Myfile.close();
                return true;
            }
            /*else
            {
                cout << " not found '" << word << "' in '" << line << "'" << endl;
            }*/
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
    string word = "q";
    vector<int> unavaibleCells = {};

    //word = tmp_recurse(unavaibleCells, word, 0, 0); //this for test method tmp_recurse
    //cout << "Answer: " + word; //this for test method tmp_recurse

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

bool Game::set_letter(int i) {
    int x, y;
    char letter;
    bool check = true;
    while (check) {
        cin >> x >> y;
        if (x != 5 || y != 5) {
        if (table[x][y] == '\\') {
                unusedPlaces--;
                cout << "Enter a letter: ";
                cin >> letter;
                table[x][y] = letter;
            } else cout << "You cannot put a letter there\n";
            check = false;
        }  else {
            cout << "First player skipped the turn\n";
            return false;
        }


    }
    return true;
}


int main(){
    Game gamer;
    return 0;
}