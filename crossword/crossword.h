// Sophie Lancaster
// November 14, 2016
// Lab 9 (crossword.h)
// CSE 20311

  // crossword interface

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Crossword {

public:
  Crossword(); // constructor
  Crossword(vector<string>); // constructor that brings in the words vector and orders it from longest word to shortest word
  ~Crossword(); // destructor

  void setMiddle(string); // function for putting the longest string in the middle of the board
  void placeWords(vector<string>); // function for placing the words on the board
  void displaySolBoard(); // function for displaying the solution board
  void displayClueBoard(); // function for displaying the clue board
  void addBlanks(); // function that adds blank spaces on the clue board where words go
  vector<string> getAnagrams(); // function that returns a vector of anagrams from the original vector of words
  bool checkBounds(int, int); // function that checks the bounds of the board to aid in the word placement
  bool isRoom(string, bool, int &, int &, int&); // function that checks to see if there is enough room to place a particular word
  bool findMatch(string, int&, int&, int&, int&); // function that finds where a given word intersects with words already on the board
  void displayClues(); // function that displays the coordinates, orientation, and anagrams for each word placed on the board
  void placeVertical(string, int&, int&, int&, int&); // function that places the word vertically on the board
  void placeHorizontal (string, int&, int&, int&, int&); // function that places the word horizontally on the board

private:
  char clueBoard[15][15]; // board filled with #s and blank spaces
  char solutionBoard[15][15]; // board filled with .s and words
  int clues[20][4];
    // clues[x][0] = row
    // clues[x][1] = col
    // clues[x][2] = orientation
    // clues[x][3] = boolean value
      // 1 = horizontal
      // 2 = vertical
  vector<string> words; // a vector of strings filled with the given words
};
