// Sophie Lancaster
// November 17, 2016
// Lab 9 (crosswordimp.cpp)
// CSE 20311

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <algorithm>
using namespace std;
#include "crossword.h" // pound includes the crossword class

Crossword::Crossword()
{} // default constructor

Crossword::Crossword(vector<string> w)
{
  words = w; // sets the private words vector equal to the ordered vector that was created in crosswordmain.cpp

  // initializes the current board to a 15 by 15 board full of #s
  for (int r = 0; r < 15; r++) { // r = rows
    for (int c = 0; c < 15; c++) { // c = columns
      clueBoard[r][c] = '#'; // single quotes for characters, double quotes for strings
    }
  }

  // initializes the solution board to a 15 by 15 board full of periods
  for (int r = 0; r < 15; r++) { // r = rows
    for (int c = 0; c < 15; c++) { // c = columns
      solutionBoard[r][c] = '.'; // single quotes for characters, double quotes for strings
    }
  }

  setMiddle(words[0]); // calls the function that places the longest word horizontally in the middle of the board
  placeWords(words); // calls the function that places all of the other words
}

Crossword::~Crossword()
{} // default destructor

// function for putting the longest string in the middle of the board
void Crossword::setMiddle(string s)
{
  int difference, count = 0;
  // if statement that places the word in the middle of the board if it is 15 letters long
  if (s.size() == 15) {
    // for loop that iterates through the word and places the letters in order in the 7th row
    for (int j = 1; j < 16; j++) {
      solutionBoard[7][j-1] = s[j-1];
    }
    clues[0][0] = 7;
    clues[0][1] = 0;
    clues[0][2] = 1;
    clues[0][3] = 1;
  }
  // else statement that places the word in the middle of the board if it is less than 15 letters long
  else {
    difference = (15 - s.size())/2; // calculates the point where the word should start
    solutionBoard[7][difference] = s[0]; // places the first letter of the word
    // for loop that iterates through the word and places the letters in order in the 7th row
    for (int k = difference; k < s.size() + difference; k++) {
      solutionBoard[7][k] = s[count];
      count++;
    }
    clues[0][0] = 7;
    clues[0][1] = difference;
    clues[0][2] = 1;
    clues[0][3] = 1;
  }
}

// function for placing the words on the board
void Crossword::placeWords(vector <string> words)
{
  int r, c, index;
  // for loop that runs through every word in the words vector
  for (int num = 1; num < words.size(); num++) {
    // initializes the variables r, c, and index
    r = 0;
    c = 0;
    index = 0;
    // if statement that only executes if a match cannot be found for a certain word
    if (!findMatch(words[num], r, c, index, num)) {
      cout << " " << endl;
      cout << "Word could not be placed!" << endl;
      break; // after the above message is displayed the if statement is broken out of
    }
  }
}

// function for displaying the solution board
void Crossword::displaySolBoard()
{
  // nested for loops that run through every element of the solution board and displays it
  for (int r = 0; r < 15; r++) {
    for (int c = 0; c < 15; c++) {
      cout << solutionBoard[r][c];
    }
    cout << endl;
  }
}

// function for displaying the clue board
void Crossword::displayClueBoard()
{
  // nested for loops that run through every element of the clue board and displays it
  for (int r = 0; r < 15; r++) {
    for (int c = 0; c < 15; c++) {
      cout << clueBoard[r][c];
    }
    cout << endl;
  }
}

// function for adding blank spaces where words go and displaying to user
void Crossword::addBlanks()
{
  // nested for loops that run through every element of the board
  for (int r = 0; r < 15; r++) {
    for (int c = 0; c < 15; c++) {
      // if statement that changes says if there is a letter in that element of the solutionBoard make that spot a blank space on the clueBoard
      if (solutionBoard[r][c] >= 'A' && solutionBoard[r][c] <= 'Z') {
        clueBoard[r][c] = ' ';
      }
    }
  }
}

// function for creating / displaying the clue / anagrams
vector <string> Crossword::getAnagrams()
{
  vector<string> anagrams; // creates a vector of strings to store the anagrams
  for (auto word : words) {
    random_shuffle(word.begin(), word.end()); // makes use of the random_shuffle algorithm which shuffles the characters in a string
    anagrams.push_back(word); // adds the shuffled words to the anagrams vector
  }
  return anagrams; // returns the anagrams vector
}

// function that formats the displaying of the clues
void Crossword::displayClues()
{
  // declares and initializes the anagrams vector
  vector<string> anagrams = getAnagrams();
  for (int i = 0; i < words.size(); i++) {
    // if statement that says to display the info if the boolean value for that word is 1 (or true)
    if(clues[i][3]) {
      cout << setw(3) << right << clues[i][0] << ", " << setw(3) << left << clues[i][1]; // displays the coordinates
      // if statement that displays across if the word is horizontal
      if (clues[i][2] == 1) {
        cout << setw(8) << left << "Across";
      }
      // if statement that displays down if the word is vertical
      else if (clues[i][2] == 2) {
        cout << setw(8) << left << "Down";
      }
      cout << setw(16) << left << anagrams[i] << endl; // displays the anagrams
    }
  }
}

// function that checks the bounds of the board
bool Crossword::checkBounds(int r, int c)
{
  // function that checks if the cell is in the bounds or not
  if (r < 0 || r >= 15 || c < 0 || c >= 15)
    return false;
  else return true; // else statement that sets the boolean to true if it is on the board
}

// function that determines if the word can be placed
bool Crossword::isRoom(string s, bool orientation, int &row, int &col, int&index)
{
  // if statement that determines if there is room when the word is going to be placed horizontally
  if (orientation == true) {
    // if statement that checks if the point to the right of the matching letter is in bounds
    if (checkBounds(row, col+1)) {
      // if statement that checks if the point to the right of the matching letter is another letter
      if (solutionBoard[row][col+1] != '.') {
        return false;
      }
    }
    // if statement that checks if the point to the left of the matching letter is in bounds
    if (checkBounds(row, col-1)) {
      // if statement that checks if the point to the left of the matching letter is another letter
      if (solutionBoard[row][col-1] != '.') {
        return false;
      }
    }
    // for loop that checks all the spots necessary for letters to be placed to the right of the index
    for (int k = col + 1; k <= s.length() - index + col; k++) {
      // if statement that checks if the points above the letters to be placed are in bounds
      if (checkBounds(row+1, k)) {
        // if statement that checks if the points above the letters to be placed are letters
        if (solutionBoard[row+1][k] != '.') {
          return false;
        }
      }
      // if statement that checks if the points below the letters to be placed are in bounds
      if (checkBounds(row-1, k)) {
        // if statement that checks if the points below the letters to be placed are letters
        if (solutionBoard[row-1][k] != '.') {
          return false;
        }
      }
    }
    // if statement that checks if the point beside the first letter is in bounds
    if (checkBounds(row, col + s.length() - index)) {
      // if statement that checks if the point beside the first letter is another letter
      if (solutionBoard[row][col + s.length() - index] != '.') {
        return false;
      }
    }
    else return false;

    // for loop that checks all the spots necessary for letters to be placed to the left of the index
    for (int k = col - index; k < col; k++) {
      // if statement that checks if the points above the letters to be placed are in bounds
      if (checkBounds(row+1, k)) {
        // if statement that checks if the points above the letters to be placed are letters
        if (solutionBoard[row+1][k] != '.') {
          return false;
        }
      }
      // if statement that checks if the points below the letters to be placed are in bounds
      if (checkBounds(row-1, k)) {
        // if statement that checks if the points below the letters to be placed are letters
        if (solutionBoard[row-1][k] != '.') {
          return false;
        }
      }
    }
    // if statement that checks if the point beside the last letter is in bounds
    if (checkBounds(row, col - index - 1)) {
      // if statement that checks if the point beside the last letter is another letter
      if (solutionBoard[row][col - index - 1] != '.') {
        return false;
      }
    }
    else return false;
    return true;
  }

  // else statement that determines if there is room when the word is going to be placed vertically
  else {
    // if statement that checks if the point above the matching letter is in bounds
    if (checkBounds(row+1, col)) {
      // if statement that checks if the point above the matching letter is another letter
      if (solutionBoard[row+1][col] != '.') {
        return false;
      }
    }
    // if statement that checks if the point below the matching letter is in bounds
    if (checkBounds(row-1, col)) {
      if (solutionBoard[row-1][col] != '.') {
        return false;
      }
    }
    // for loop that checks all the spots necessary for letters to be placed below the index
    for (int k = row + 1; k < s.length() + index - 1 + row; k++) {
      // if statement that checks if the points to the right of the letters to be placed are in bounds
      if (checkBounds(k, col+1)) {
        // if statement that checks if the points to the right of the letters to be placed are letters
        if (solutionBoard[k][col+1] != '.') {
          return false;
        }
      }
      // if statement that checks if the points to the left of the letters to be placed are in bounds
      if (checkBounds(k, col-1)) {
        // if statement that checks if the points to the left of the letters to be placed are letters
        if (solutionBoard[k][col-1] != '.') {
          return false;
        }
      }
    }
    // if statement that checks if the point below the last letter is in bounds
    if (checkBounds(row + s.length() - index, col)) {
      // if statement that checks if the point below the last letter is another letter
      if (solutionBoard[row + s.length() - index][col] != '.') {
        return false;
      }
    }
    else return false;

    // for loop that checks all the spots necessary for letters to be placed above the index
    for (int k = row - 1 - index; k < row; k++) {
      // if statement that checks if the points to the right of the letters to be placed are in bounds
      if (checkBounds(k, col+1)) {
        // if statement that checks if the points to the right of the letters to be placed are letters
        if (solutionBoard[k][col+1] != '.') {
          return false;
        }
      }
      // if statement that checks if the points to the left of the letters to be placed are in bounds
      if (checkBounds(k, col-1)) {
        // if statement that checks if the points to the left of the letters to be placed are letters
        if (solutionBoard[k][col-1] != '.') {
          return false;
        }
      }
    }
    // if statement that checks if the point above the first letter is in bounds
    if (checkBounds(row - index - 1, col)) {
      // if statement that checks if the point above the first letter is another letter
      if (solutionBoard[row - index - 1][col] != '.') {
        return false;
      }
    }
    else return false;
    return true;
  }
}

// function that compares the letters of the strings to find a match on the board
bool Crossword::findMatch(string s, int &row, int &col, int&index, int& num)
{

  for (int i = 0; i < s.length(); i++) { // for loop that runs through every character of the word
    for (int r = 0; r < 15; r++) { // for loop that runs through every row of the board
      for (int c = 0; c < 15; c++) { // for loop that runs through every column of the board
          // if statement that says if the letter in the word matches the letter on the board save those values
          if (s[i] == solutionBoard[r][c]) {
            row = r;
            col = c;
            index = i;
            // if statement that checks if there is room on the board to place the word and if there is it places it vertically
            if (isRoom(s, false, row, col, index)) {
              placeVertical(s, row, col, index, num); // calls the placeVertical function
              return true;
            }
            // if statement that checks if there is room on the board to place the word and if there is it places it horizontally
            if (isRoom(s, true, row, col, index)) {
              placeHorizontal(s, row, col, index, num); // calls the placeHorizontal function
              return true;
            }
          }
      }
    }
  }
  return false;
}

// function that places the word horizontally on the board
void Crossword::placeHorizontal(string word, int &row, int &col, int& index, int& num)
{
  // sets the matching spot on the board to the matching letter
  solutionBoard[row][col] = word[index];
  int count = index - 1; // initializes a count variable for the for loop
    // for loop that runs through the columns to the right of the index and places the letters until the first letter is placed
    for (int i = col - 1; i >= col - index; i--) {
      solutionBoard[row][i] = word[count];
      count--; // decrements the count variable so that the previous letters are placed
    }
  count = index + 1; // initializes a count variable for the for loop
    // for loop that runs through the columns to the left of the index and places the letters until the last letter is placed
    for (int i = col + 1; i <= col + word.length() - (index + 1); i++) {
      solutionBoard[row][i] = word[count];
      count++; // increments the count variable so that the next letters in the word are placed
    }
    // adds the starting location of the word and the word's orientation to the clues array
    clues[num][0] = row;
    clues[num][1] = col - index;
    clues[num][2] = 1;
    clues[num][3] = 1;
}

// function that places the word vertically on the board
void Crossword::placeVertical(string word, int &row, int &col, int& index, int& num)
{
  // sets the matching spot on the board to the matching letter
  solutionBoard[row][col] = word[index];
  int count = index - 1; // initializes a count variable for the for loop
    // for loop that runs through the rows above the index and places the letters until the first letter is placed
    for (int i = row - 1; i >= row - index; i--) {
      solutionBoard[i][col] = word[count];
      count--; // decrements the count variable so that the previous letters are placed
    }
  count = index + 1; // initializes a count variable for the for loop
    // for loop that runs through the rows below the index and places the letters until the last letter is placed
    for (int i = row + 1; i <= row + word.length() - (index + 1); i++) {
      solutionBoard[i][col] = word[count];
      count++; // increments the count variable so that the next letters in the word are placed
    }
    // adds the starting location of the word and the word's orientation to the clues array
    clues[num][0] = row - index;
    clues[num][1] = col;
    clues[num][2] = 2;
    clues[num][3] = 1;
}
