// Sophie Lancaster
// January 30, 2017
// CSE 20312
// Lab 2

  // black jack class implementation
  // blackjack rules
    // players that exceed 21 lose
    // if the final value is less than 21 the dealer takes cards up until 17 or higher
      // if the player’s value is higher, they win otherwise they lose
    // aces are always 11
    // players have only two options (hit or stand)
    // dealers always stop when they reach 17 or higher
    // need to implement a Deal() public member function
      // get cards from your deck for the game
    // keep track of how many times a player wins and the dealer wins in your game
    // ask the user if they want to continue playing after each game
    // when there are fewer than 15 cards, open a “new” deck and shuffle it before continuing the game

#include <iostream>
#include <stdlib.h>
using namespace std;
#include "BlackJack.h" // pound includes the black jack class

BlackJack::BlackJack(int n) // non-default constructor
{
  size = n; // sets the size of the deck equal to the int that was inputted
  // initializes all the other private data members to zero
  cardIndex = 0;
  playerScore = 0;
  computerScore = 0;
  playerWins = 0;
  computerWins = 0;

  deck = new int[size]; // allocates the memory for the deck array using numCards as the number of cards

  // initializes the array to have numbers in it
  for (int i = 0; i < size; i++) {
    deck[i] = i%13 + 2;
  }
}

BlackJack::~BlackJack() // default deconstructor
{
  delete [] deck; // default deconstructor that is called whenever the objects are destroyed
}

int BlackJack::getSize() // function that returns the size of the current deck
{
  return size;
}

void BlackJack::shuffle() // function that performs a shuffle using Knuth's algorithm
{
  // uses a for loop and a temporary variable to excute Knuth's algorithm and shuffle the number
  for (int i = 0; i < size; i++) {
    int randNum = rand() % size; // uses rand to randomly generate a number
    int temp = deck[i]; // uses the temp variable to swap numbers
    deck[i] = deck[randNum];
    deck[randNum] = temp;
  }
}

int BlackJack::Deal() // function that gets cards from your deck for the game
{
  // if statement that checks if the number of cards left in the deck is less than 15 and creates / shuffles a new deck if it is
  if (cardIndex > 52 - 15) {
    // creates the new deck
    for (int i = 0; i < size; i++) {
      deck[i] = i%13 + 2;
    }
    shuffle(); // shuffles the new deck
    cardIndex = 0; // resets the cardIndex to 0
  }
  if (deck[cardIndex] == 14) { // if statement that sets the value of any card with a value of 14 to 11
    deck[cardIndex] = 11;
  }
  else if (deck[cardIndex] >= 11) { // if statement that sets the value of any card with a value of 11 or over to 10
    deck[cardIndex] = 10;
  }
  return deck[cardIndex++]; // returns the card in that spot of the deck and then increments the card index
}

void BlackJack::checkWinner() // function that determines if there is a winner and who it is
{
  // if the computer has a score over 21 they automatically use and player wins
  if (computerScore > 21) {
    cout << "Computer busted, you win!" << endl;
    playerWins+= 1; // increments the playerWins variable by one
    // displays the number of wins for the player and the computer
    cout << "You have " << playerWins << " total wins." << endl;
    cout << "The computer has " << computerWins << " total wins." << endl;
  }
  // if the player has a score greater than the computer the player wins
  else if (playerScore > computerScore) {
    cout << "You win!" << endl;
    playerWins+= 1; // increments the playerWins variable by one
    // displays the number of wins for the player and the computer
    cout << "You have " << playerWins << " total wins." << endl;
    cout << "The computer has " << computerWins << " total wins." << endl;
  }
  // if the computer has a score greater than the player the computer wins
  else if (computerScore > playerScore) {
    cout << "Computer wins!" << endl;
    computerWins+= 1; // increments the computerWins variable by one
    // displays the number of wins for the player and the computer
    cout << "You have " << playerWins << " total wins." << endl;
    cout << "The computer has " << computerWins << " total wins." << endl;
  }
  // if the computer and player tie then the rules of the game say that the computer wins
  else if (computerScore == playerScore) {
    cout << "It was a tie. Therefore, by default, computer wins!" << endl;
    computerWins+= 1; // increments the computerWins variable by one
    // displays the number of wins for the player and the computer
    cout << "You have " << playerWins << " total wins." << endl;
    cout << "The computer has " << computerWins << " total wins." << endl;
  }
}

void BlackJack::playBlackJack() // function that is used to play the game of blackjack
{
  int dealtCard; // creates a variable called dealtCard that represents the card given to each player
  char hitOrStand = 'h'; // creates a variable used to keep track of the player's decision
  bool playerDone = false;
  // re-initializes the player and computer score to zero
  playerScore = 0;
  computerScore = 0;

  shuffle(); // shuffles the deck of cards

  // while loop used for the player's turn -- ends if the playerDone variable gets set to true
  while (!playerDone) {
    dealtCard = Deal(); // uses the deal function
    playerScore += dealtCard; // increments the player's score by the value of the dealt card
    // if the player's score is greater than 21 the player busted and the computer wins
    if (playerScore > 21) {
      cout << "Your score is " << playerScore << ", which means you busted, the computer wins!" << endl;
      playerDone = true; // sets the playerDone variable to true to end the player's turn
      computerWins+= 1; // increments the computerWins variable by one
      // displays the number of wins for the player and the computer
      cout << "You have " << playerWins << " total wins." << endl;
      cout << "The computer has " << computerWins << " total wins." << endl;
      return;
    }
    // outputs the player's current score and asks them if they want to continue playing or stand
    cout << "Your card was worth " << dealtCard << " points. Your total score is " << playerScore << "." << endl;
    cout << "Hit (h) or stand (s)? ";
    cin >> hitOrStand; // takes in the player's answer as the hitOrStand variable
    // if the player decides to stand the playerDone variable to true ending the player's turn
    if (hitOrStand == 's') {
      playerDone = true;
    }
  }

  // while loop used for the computer's turn -- starts when the playerDone variable gets set to true
  while (playerDone) {
    dealtCard = Deal(); // uses the deal function
    computerScore += dealtCard; // increments the computer's score by the value of the dealt card
    cout << "The computer's score is " << computerScore << "." << endl;
    // if statement that stops dealing cards to the computer if their score is greater than or equal to 17
    if (computerScore >= 17) {
      break;
    }
  }
  checkWinner(); // calls the checkWinner function to see if anyone won the game / if there was a tie
}

void BlackJack::continuePlaying() // function that is used to continually ask the player if they want to keep playing
{
  bool quit = false; // creates and initializes a variable called quit which ends the while loop when the player inputs n
  char answer;
  // while loop that is exited when the player answers no to the do you want to play another game question
  while (!quit) {
    playBlackJack(); // calls the playBlackJack function
    // asks the user if they want to play another game
    cout << "Do you want to play another game? Yes (y) or no (n): ";
    cin >> answer;
    // if statement that ends the while loop when the player enters an n for no more games
    if (answer == 'n') {
      quit = true; // sets the quit variable equal to true so the while loop is exited
    }
  }
}

ostream& operator<< (ostream &s, BlackJack &blkjk) // overloaded output operator
{
  // displays the entries in the deck using a for loop
  for (int i = 0; i < blkjk.size; i++) {
    s << blkjk.deck[i];
    if (i < blkjk.size - 1) s << ", ";
  }
  s << " " << endl; // overloads the output operator

  return s;
}
