// Sophie Lancaster
// January 30, 2017
// CSE 20312
// Lab 2

  // card deck driver / main

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
#include "BlackJack.h" // pound includes the card deck class

int main()
{
  srand(time(NULL));// need to use srand to change the random number seed for shuffle

  BlackJack deck; // instantiates a blackJack object

  deck.continuePlaying(); // calls the continuePlaying function to run the game

  return 0;
}
