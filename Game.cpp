//
// Created by ADMIN on 18.04.2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <set>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <windows.h>
#include "Game.h"

using namespace std;

Game::Game()
{
    menu();
}
string Game::randomWordFromFile() {
    int offset;
    int countOfWords;
    string line;
    ifstream Myfile;
    Myfile.open ("dictionary.txt");

    //get count of words in file
    if (Myfile.is_open())
    {
        while ( getline(Myfile,line))
        {
            countOfWords++;
        }
    }
    do{
        int numberOfWord = rand() % countOfWords+1;
        Myfile.clear();
        Myfile.seekg(0);

        //get word by random index
        if (Myfile.is_open())
        {
            for(int i = 0; i < numberOfWord; i++)
            {
                if(!getline(Myfile,line)){
                }
            }
        }
        else
            cout << "Unable to open this file." << endl;
    } while(line.size() != 5);
    Myfile.close();
    return line;
}
string Game::toLowerCaseString(string str){
    string strR = "";
    for (int i=0; i<str.size(); i++)
        strR += tolower(str.c_str()[i]);
    return strR;
}
void Game::show_table(char table[5][5]) {
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


bool Game::checker(string find_word, char table[5][5]){
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
    }
    else {
        //cout << "The word has been used before" << endl;
        return false;
    }
    if (temp >= find_word.size()) {
        result = true;
        find_words.insert(find_word);
    }
    return result;
}


bool Game::userTurn() {
    string answer; //user input
    char letter;
    int x, y;
    cout << "Enter coords where do you want to add a letter (x;y)\n";
    while (true) {
        while (true) {
            while (true) {
                cout << "Enter x \n(q - to quit): ";
                cin >> answer;
                answer = toLowerCaseString(answer);

                if (equal(answer.begin(), answer.end(), "q")) return false;
                else if (!equal(answer.begin(), answer.end(), "0") && atoi(answer.c_str()) == 0)
                    cout << "Invalid value" << endl;
                else if (atoi(answer.c_str()) > 4 || atoi(answer.c_str()) < 0)
                    cout << "Invalid value" << endl;
                else {
                    x = atoi(answer.c_str());
                    break;
                }
            }
            while (true) {
                cout << "Enter y \n(q - to quit): ";
                cin >> answer;
                answer = toLowerCaseString(answer);
                if (equal(answer.begin(), answer.end(), "q")) return false;
                else if (!equal(answer.begin(), answer.end(), "0") && atoi(answer.c_str()) == 0)
                    cout << "Invalid value" << endl;
                else if (atoi(answer.c_str()) > 4 || atoi(answer.c_str()) < 0)
                    cout << "Invalid value" << endl;
                else {
                    y = atoi(answer.c_str());
                    break;
                }
            }
            if (!checkGoodPlaceForLetter(x,y)){
                cout << "This is bad place for new letter! Try again!\n";
            }
            else if(tmp_table[x][y] == '\\'){
                break;
            }
            else
                cout << "You cannot put a letter there! Try again!\n";
        }
        while (true) {
            cout << "Enter a letter\n(q - to quit):  ";
            cin >> answer;
            answer = toLowerCaseString(answer);
            if (equal(answer.begin(), answer.end(), "q")) return false;
            else if(answer.length() != 1) cout << "Invalid value" << endl;
            else if(!isalpha(answer.c_str()[0])) cout << "Invalid value" << endl;
            else {
                letter = answer.c_str()[0];
                if(letter >= 'A' && letter <= 'Z') letter += 'a' - 'A';
                break;
            }
        }
        unusedPlaces--;
        tmp_table[x][y] = letter;


        show_table(tmp_table);
        while(true){
            cout << "Enter what word do you want to write\n(q - to quit): ";
            cin >> answer;
            answer = toLowerCaseString(answer);
            if (!equal(answer.begin(), answer.end(), "q")) {
                if (helper_checkWord(answer)) {
                    if (checker(answer, tmp_table)) {
                        pointsUser1 += answer.size();
                        cout << "You earned " << answer.size() << endl;
                        copy(&tmp_table[0][0], &tmp_table[0][0]+5*5, &main_table[0][0]);
                        return true;
                    }
                    else {
                        cout << "You cannot put this word!" << endl;
                    }
                }
                else {
                    cout << "There are no such word in dictionary!\n";
                }
            }
            else {
                copy(&main_table[0][0], &main_table[0][0]+5*5, &tmp_table[0][0]);
                return false;
            }
            while(true) {
                cout << "Do you want try again to put word?\n(yes/no): ";
                cin >> answer;
                answer = toLowerCaseString(answer);
                if (equal(answer.begin(), answer.end(), "yes")) {
                    break;
                } else if (equal(answer.begin(), answer.end(), "no")) {
                    break;
                } else {
                    cout << "Invalid value" << endl;
                }
            }
            if (equal(answer.begin(), answer.end(), "no"))
                break;
        }
        while(true) {
            cout << "Do you want try again to put letter?\n(yes/no): ";
            cin >> answer;
            answer = toLowerCaseString(answer);
            copy(&main_table[0][0], &main_table[0][0]+5*5, &tmp_table[0][0]); //tmp_table = main_table;
            if (equal(answer.begin(), answer.end(), "yes")) {
                break;
            } else if (equal(answer.begin(), answer.end(), "no")) {
                return false;
            } else {
                cout << "Invalid value" << endl;
            }
        }
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

void Game::resetVariable() {
    string startWord = randomWordFromFile();
    find_words.clear();
    find_words.insert(startWord);
    skipper1 = true;
    skipper2 = true;
    pointsUser1 = 0;
    pointsUser2 = 0;
    unusedPlaces = 20;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++){
            (i == 2) ? main_table[i][j] = startWord[j] : main_table[i][j] = '\\';
            (i == 2) ? tmp_table[i][j] = startWord[j] : tmp_table[i][j] = '\\';
        }
    }
}
void Game::waitForComputer()
{

    while(!helper_threadIsEnd){
        this_thread::sleep_for(chrono::milliseconds(200));
        if(helper_threadIsEnd) break;
        this_thread::sleep_for(chrono::milliseconds(200));
        if(helper_threadIsEnd) break;
        this_thread::sleep_for(chrono::milliseconds(200));
        if(helper_threadIsEnd) break;
        this_thread::sleep_for(chrono::milliseconds(200));
        if(helper_threadIsEnd) break;
        this_thread::sleep_for(chrono::milliseconds(200));
        if(helper_threadIsEnd) break;
        cout << "Waiting for computer...\n";
    }
}
void Game::playVersusComputer() {
    string computer_word;
    resetVariable();
    show_table(main_table);
    while (unusedPlaces != 0 && (skipper1 || skipper2)) {
        cout << "\n---------------------First player--------------------\n";
        skipper1 = userTurn();
        cout << "First player's points - " << pointsUser1 << endl;
        cout << "Second player's points - " << pointsUser2 << endl;
        show_table(main_table);

        cout << "\n-------------------Second player-------------------\n";

        helper_threadIsEnd = false;
        thread t1(&Game::waitForComputer, this);
        computer_word = computer_turn();
        helper_threadIsEnd = true;
        t1.join();

        skipper2 = equal(computer_word.begin(), computer_word.end(), "-1") ? false : true;
        equal(computer_word.begin(), computer_word.end(), "-1") ? cout << "Computer skip turn" << endl : cout << "Computer word is " << computer_word << endl;
        cout << "First player's points - " << pointsUser1 << endl;
        cout << "Second player's points - " << pointsUser2 << endl;
        show_table(main_table);
    }
    gameOver1();
}

void Game::playVersusPlayer() {
    resetVariable();
    show_table(main_table);
    while (unusedPlaces != 0 && (skipper1 || skipper2)) {
        cout << "\n---------------------First player--------------------\n";
        skipper1 = userTurn();
        cout << "First player's points - " << pointsUser1 << endl;
        cout << "Second player's points - " << pointsUser2 << endl;
        show_table(main_table);

        cout << "\n-------------------Second player-------------------\n";
        skipper2 = userTurn();
        cout << "First player's points - " << pointsUser1 << endl;
        cout << "Second player's points - " << pointsUser2 << endl;
        show_table(main_table);
    }
    gameOver2();
}




bool Game::helper_checkWord(string word){

    string line;
    ifstream Myfile;
    Myfile.open ("dictionary.txt");

    if (Myfile.is_open())
    {
        while (!Myfile.eof())
        {
            getline(Myfile,line);
            if ((word.compare(line)) == 0)
            {
                Myfile.close();
                return true;
            }
        }
        Myfile.close();
    }
    else
        cout << "Unable to open this file." << endl;

    return false;
}

string Game::computer_turn_recurse(vector<int> unavaibleCells, string word, int x, int y){ // x, y - coord last added

    string tmp_word;
    unavaibleCells.push_back(x*10 + y);
    //if(horizontal){
    for(int i = 1; i < 5 - x; i++)
    {
        if(tmp_table[x + i][y] == '\\'){ //check if next letter
            break;
        }
        if(count(unavaibleCells.begin(), unavaibleCells.end(), (x+i)*10 + y)){ //check any next turn
            break;
        }
        tmp_word = word + tmp_table[x + i][y];
        //cout << tmp_word << endl;
        if(helper_checkWord(tmp_word)){
            return tmp_word;
        }
        tmp_word = computer_turn_recurse(unavaibleCells, tmp_word, x + i, y);
        if(tmp_word != "-1"){
            return tmp_word;
        }
        break;
    }
    for(int i = 1; i <= x; i++)
    {
        if(tmp_table[x - i][y] == '\\'){ //check if next letter
            break;
        }
        if(count(unavaibleCells.begin(), unavaibleCells.end(), (x-i)*10 + y)){ //check any next turn
            break;
        }
        tmp_word = word + tmp_table[x - i][y];
        //cout << tmp_word << endl;

        if(helper_checkWord(tmp_word)){
            return tmp_word;
        }

        tmp_word = computer_turn_recurse(unavaibleCells, tmp_word, x - i, y);
        if(tmp_word != "-1"){
            return tmp_word;
        }
        break;
    }
    //}
    //else{
    for(int j = 1; j < 5 - y; j++)
    {
        if(tmp_table[x][y + j] == '\\'){ //check if next letter
            break;
        }
        if(count(unavaibleCells.begin(), unavaibleCells.end(), x*10 + y + j)){ //check any next turn
            break;
        }
        tmp_word = word + tmp_table[x][y + j];
        //cout << tmp_word << endl;

        if(helper_checkWord(tmp_word)){
            return tmp_word;
        }

        tmp_word = computer_turn_recurse(unavaibleCells, tmp_word, x , y + j);
        if(tmp_word != "-1"){
            return tmp_word;
        }
        break;
    }
    for(int j = 1; j <= y; j++)
    {
        if(tmp_table[x][y - j] == '\\'){ //check if next letter
            break;
        }
        if(count(unavaibleCells.begin(), unavaibleCells.end(), x*10 + y - j)){ //check any next turn
            break;
        }
        tmp_word = word + tmp_table[x][y - j];
        //cout << tmp_word << endl;

        if(helper_checkWord(tmp_word)){
            return tmp_word;
        }

        tmp_word = computer_turn_recurse(unavaibleCells, tmp_word, x, y - j);
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
                for(int l = 'a'; l <= 'z'; l++)
                {
                    if(!checkGoodPlaceForLetter(i, j)) break;

                    copy(&main_table[0][0], &main_table[0][0]+5*5, &tmp_table[0][0]); //tmp_table = main_table;
                    tmp_table[i][j] = 'a';
                    for(int k = 0; k < 5; k++)
                    {
                        for (int m = 0; m < 5; m++)
                        {
                            if(tmp_table[k][m] != '\\') {
                                word = "";
                                word += tmp_table[k][m];
                                word = computer_turn_recurse(unavaibleCells, word, k, m);
                                //cout << "Answer: " + word << endl;
                                if(word != "-1" && (find_words.find(word) == find_words.end()))
                                {
                                    copy(&tmp_table[0][0], &tmp_table[0][0]+5*5, &main_table[0][0]); //main_table = tmp_table
                                    unusedPlaces--;
                                    pointsUser2 += word.size();
                                    find_words.insert(word);
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
bool Game::checkGoodPlaceForLetter(int x, int y){
    if((x == 0 && y > 0) && (x < 4 && y < 4)){
        if(tmp_table[x+1][y] == '\\' && tmp_table[x][y+1] == '\\' && tmp_table[x][y-1] == '\\') return false;
    }
    if((x > 0 && y > 0) && (x == 4 && y < 4)){
        if( tmp_table[x-1][y] == '\\' && tmp_table[x][y+1] == '\\' && tmp_table[x][y-1] == '\\') return false;
    }
    if((x > 0 && y == 0) &&(x < 4 && y < 4)){
        if(tmp_table[x+1][y] == '\\' && tmp_table[x-1][y] == '\\' && tmp_table[x][y+1] == '\\') return false;
    }
    if((x > 0 && y > 0) &&(x < 4 && y == 4)){
        if(tmp_table[x+1][y] == '\\' && tmp_table[x-1][y] == '\\' && tmp_table[x][y-1] == '\\') return false;
    }
    if((x > 0 && y > 0) &&(x == 4 && y == 4)){
        if(tmp_table[x-1][y] == '\\' && tmp_table[x][y-1] == '\\') return false;
    }
    if((x == 0 && y > 0) &&(x < 4 && y == 4)){
        if(tmp_table[x+1][y] == '\\' && tmp_table[x][y-1] == '\\') return false;
    }
    if((x == 0 && y == 0) &&(x < 4 && y < 4)){
        if(tmp_table[x+1][y] == '\\' && tmp_table[x][y+1] == '\\') return false;
    }
    if((x > 0 && y == 0) &&(x == 4 && y < 4)){
        if(tmp_table[x-1][y] == '\\' && tmp_table[x][y+1] == '\\') return false;
    }
    if(tmp_table[x+1][y] == '\\' && tmp_table[x-1][y] == '\\' && tmp_table[x][y+1] == '\\' && tmp_table[x][y-1] == '\\') return false;
    return true;
};

void Game::menu() {
    string switcher;
    while(true){
        cout << "\n 1. Play Royal Baldu with computer" << endl;
        cout << " 2. Play Royal Baldu with other user" << endl;
        cout << " 3. Exit\n" << endl;
        cout << "CHOOSE: ";
        cin >> switcher;
        switcher = toLowerCaseString(switcher);
        switch (atoi(switcher.c_str())) {
            case 1:
                playVersusComputer();
                break;
            case 2:
                playVersusPlayer();
                break;
            case 3:
                cout << "Goodbye -___-" << endl;
                return;
            default:
                cout << "Invalid value" << endl;
                break;
        }
    }
}


