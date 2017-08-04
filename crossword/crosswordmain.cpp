// Sophie Lancaster
// November 14, 2016
// Lab 9 (crosswordmain.cpp)
// CSE 20311

  // given a list of words creates a blank crossword anagram puzzle
    // can be played with paper and pencil
  // the program will also provide a solution for the player
  // the resulting crossword will be a board where most of the cells are filled in
  // blank spaces indicate places where the player can fill in letters
  // where spaces intersect the words must share a common letter
  // clue for each word is given by giving an anagram
  // the player will only enter single words

// pound includes all the necessary classes
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <fstream>
using namespace std;
#include "crossword.h"

bool compare(const string &, const string &); // function that creates the conditions for comparing the words
bool readWords(vector<string> &); // function that reads in the words from the user
void orderStrings(vector<string> &); // function that calls the compare function and orders the strings in the words vector
bool wordsFromFile(vector<string> &, string); // function that inputs words from a file when argc == 2

int main(int argc, char *argv[]) // use argc and argv to add the extra credit functionalities
{
  vector<string> words; // creates the vector of strings

  cout << " " << endl;
  cout << "Anagram Crossword Puzzle Generator" << endl;
  cout << "-----------------------------------" << endl;

  // if statements that determine if the words should be read in from the keyboard or the file
  if (argc == 2) {
    string inputFileName = argv[1];
    bool success = wordsFromFile(words, inputFileName);
    if (!success) {
      return 1;
    }
  }
  if (argc == 1) {
    bool success = readWords(words);
    if (!success) {
      return 1;
    }
  }

  orderStrings(words); // calls the function that orders the words in the vector

  Crossword cw(words); // creates the crossword object

  cout << " " << endl;
  cout << "Solution:" << endl;
  cout << " " << endl;
  cw.displaySolBoard(); // calls the crossword display solution board function
  cout << " " << endl;

  cout << "Crossword Puzzle:" << endl;
  cout << " " << endl;
  cw.addBlanks(); // calls the crossword function to add blanks to the solution board
  cw.displayClueBoard(); // calls the crossword display clue board function
  cout << " " << endl;

  cout << "Clues (points are ordered row, column with the first row / column being 0):" << endl;
  cout << " " << endl;
  cw.displayClues(); // calls the crossword display clues function
  cout << " " << endl;

return 0;
}

// function for reading in words using argv and argc
bool wordsFromFile(vector<string> &words, string fileName)
{
  ifstream ifs; // creates the ifstream object

  ifs.open(fileName); // opens the file

  string s;
  bool quit = false;

  // while loop that runs as long the boolean variable quit is not true
  while (!quit) {
    ifs >> s;
    // if statement that breaks out of the while loop if s is a period
    if (s[0] == '.') {
      break;
    }
    // if statement that ends the program if the string is too long
    if (s.length() > 15) {
      cout << "Your string is too long." << endl;
      return false;
    }
    // for loop that uppercases all the letters in the string
    for (int i = 0; i < s.size(); i++) {
      s[i] = toupper(s[i]);
    }
    // for loop that ends the program if a character that is not a letter is entered
    for (char c : s) {
      if (!isalpha(c)) {
        cout << "You entered a non-alphabetic character." << endl;
        return false;
      }
    }
    words.push_back(s); // function that adds the words into the vector
    // function that exits the while loop if more than 20 words are entered but still continues the program
    if (words.size() >= 20) {
      cout << "You entered more than 20 words. Only the first 20 will be used." << endl;
      quit = true;
    }
  }
  return true;
}

// function for reading in the words
bool readWords(vector<string> &words)
{
  // prompt user to enter list of up to 20 words with up to 15 letters each
  cout << "Enter a list of up to 20 words with up to 15 letters each followed by a period: " << endl;

  string s;
  bool quit = false;

  // while loop that runs as long the boolean variable quit is not true
  while (!quit) {
    cin >> s;
    // if statement that breaks out of the while loop if s is a period
    if (s[0] == '.') {
      break;
    }
    // if statement that ends the program if the string is too long
    if (s.length() > 15) {
      cout << "Your string is too long." << endl;
      return false;
    }
    // for loop that uppercases all the letters in the string
    for (int i = 0; i < s.size(); i++) {
      s[i] = toupper(s[i]);
    }
    // for loop that ends the program if a character that is not a letter is entered
    for (char c : s) {
      if (!isalpha(c)) {
        cout << "You entered a non-alphabetic character." << endl;
        return false;
      }
    }
    words.push_back(s); // function that adds the words into the vector
    // function that exits the while loop if more than 20 words are entered but still continues the program
    if (words.size() >= 20) {
      cout << "You entered more than 20 words. Only the first 20 will be used." << endl;
      quit = true;
    }
  }
  return true;
}

// function that contains the condition for ordering the strings (used in orderStrings)
bool compare(const string &a, const string &b)
{
  return (a.size() > b.size()); // tells the function to order the strings by decreasing length
}

// function for ordering the strings by length
void orderStrings(vector<string> &words)
{
  sort(words.begin(), words.end(), compare); // calls the sort algorithm and starts at the beginning of the vector and compares the words using the compare function
}
