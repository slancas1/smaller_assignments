// Sophie Lancaster
// January 30, 2017
// CSE 20312
// Lab 2

  // black jack class interface

#include <iostream>
using namespace std;
#ifndef BLACKJACK_H
#define BLACKJACK_H

class BlackJack {
  friend ostream& operator<< (ostream &, BlackJack &); // overloads the cout operator

public:
  ~BlackJack(); // default deconstructor
  BlackJack(int = 52); // non-default constructor

  // member functions
  int getSize(); // function that returns the size of the current deck
  void shuffle(); // function that performs a shuffle using Knuth's algorithm
  int Deal(); // function that gets cards from your deck for the game
  void checkWinner(); // function that determines if there is a winner and who it is
  void playBlackJack(); // function that is used to play the game of blackjack
  void continuePlaying(); // function that is used to continually ask the player if they want to keep playing

private:
  int * deck; // pointer to deck which will have its memory allocated in the implementation
  int size; // int that stores the current size of the deck
  int cardIndex; // where i am in the deck of cards
  int playerScore; // int that keeps track of the score the player currently has
  int computerScore; // int that keeps track of the score the computer currently has
  int playerWins; // int that keeps track of the number of times the player has won
  int computerWins; // int that keeps track of the number of times the computer has won
};

#endif
