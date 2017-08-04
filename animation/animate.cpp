// Sophie Lancaster
// November 28, 2016
// Lab 10 (animate.cpp)
// CSE 20311

  // write an interesting program that incorporates the following things:
    // multiple shapes and colors
    // circular motion of some kind
    // user control of the display in some way

#include "gfx.h" // pound includes the necessary graphics library
using namespace std;
#include <iostream>
#include <cmath>
#include <unistd.h> // used for usleep

// function used to create the beachball
void beachball(double, double, int, int, int, int, double);

int main()
{
  int windWd = 700, windHt = 500; // window dimenstions
  double xc = 300, yc = 400; // starting x and y coordinates of the beachball
  double vy = 0, vx = 0; // velocity of the beachball
  int rad1 = 30, rad2 = 8; // radii used to make the outer and inner circle of the beachball
  double dx = 0; // used for incrementing the angle of the lines to create circular motion
  double ddx = 0.25; // again used for incrementing the angle of the lines to create circular motion
  char c = ' '; // loop variable
  bool bouncing = false; // boolean variable to start and end the bouncing motion of the ball
  bool wasMovingLeft = false; // flag to determine which way the ball was traveling

  gfx_open(windWd, windHt, "Beach Ball Animation"); // opens a window

  // outputs the options for the user
  cout << " " << endl;
  cout << "w: speed up the ball" << endl;
  cout << "s: slow down the ball" << endl;
  cout << "a: move the ball to the left" << endl;
  cout << "d: move the ball to the right" << endl;
  cout << "mouse left click: make the ball bounce" << endl;
  cout << "q: quit" << endl;

  // while loop that stops when q is pressed
  while (c != 'q') {

    beachball(xc, yc, windWd, windHt, rad1, rad2, dx); // runs the beachball function to create the beachball
    dx += ddx; // increments the dx variable used to create the motion of the lines
    xc += vx; // increments the position of the ball so that it moves left and right
    yc += vy; // increments the position of the ball so that it moves up and down

    // if statement that says if the ball isn't moving then the lines also shouldnt move
    if (vx < 0.5 && vx > -0.5) {
      dx = 0;
      vx = 0;
    }

    // if statement that doesn't let the ball go off the screen on the right
    if (xc > windWd - rad1 - 2) {
      xc = windWd - rad1 - 2;
      vx = -vx; // changes the velocity so the ball travels in the opposite direction
      // if statement that changes the direction of the lines when the ball hits a wall
      if (ddx > 0) {
        ddx = -ddx;
      }
    }
    // if statement that doesn't let the ball go off the screen on the left
    if (xc < rad1 + 2) {
      xc = rad1 + 2;
      vx = -vx; // changes the velocity so the ball travels in the opposite direction
      // if statement that changes the direction of the lines when the ball hits a wall
      if (ddx < 0) {
        ddx = -ddx;
      }
    }

    // if statement that executes if the bouncing variable is true
    if (bouncing == true) {
      // if statement that sends the ball back down after it reaches the max value
      if (yc < 200) {
        vy = 5;
      }
      // if statement that stops the vertical motion of the ball when it reaches its starting location
      if (yc >= 400) {
        vy = 0;
        bouncing = false; // ends the bouncing motion
      }
    }

    gfx_flush(); // flushes the output to the screen
    usleep(70000); // used to slow down the animation

    // the gfx_event_waiting allows for the animations
    if (gfx_event_waiting()) {
      c = gfx_wait();

      // if statemant for when the d button is pressed
      if (c == 'd') {
        // sets the velocity so that the ball moves to the right
        if (vx != 0) {
          vx = vx;
          // if statement that says if the velocity is negative make it positive so that it travels right
          if (vx < 0) {
            vx = -vx;
          }
          // if statement that changes the direction of lines if necessary
          if (ddx < 0) {
            ddx = -ddx;
          }
        }
      }
      // if statemant for when the a button is pressed
      if (c == 'a') {
        // sets the velocity so that the ball moves to the left
        if (vx != 0) {
          vx = -vx;
          // if statement that says if the velocity is positive make it negative so that it travels left
          if (vx > 0) {
            vx = -vx;
          }
          // if statment that changes the direction of lines if necessary
          if (ddx > 0) {
            ddx = -ddx;
          }
        }
      }
      // if statement for when the w button is pressed
      if (c == 'w') {
        // if statement that executes when the velocity is zero
        if (vx == 0) {
          if (wasMovingLeft) {
            vx = -1; // if the ball was originally moving left velocity is set to -1
          }
          else vx = 1; // if the ball was originally moving right velocity is set to 1
        }
        else vx = 2*vx; // increases the velocity variable
      }
      // if statement for when the s button is pressed
      if (c == 's') {
        vx = vx/2; // decreases the velocity variable
        // if statement that sets the value of the direction flag
        if (vx < 0) {
          wasMovingLeft = true;
        }
        else wasMovingLeft = false;
      }
      // if statement for when the left mouse button is clicked
      if (c == 1) {
        vy = -5;
        bouncing = true; // sets bouncing flag to true so the bouncing motion starts
      }
    }
  }

return 0;
}

// function used to create the beachball
void beachball(double xc, double yc, int windWd, int windHt, int rad1, int rad2, double dx) {
  gfx_clear_color(204, 255, 255); // changes the background color to blue
  gfx_clear();

  gfx_color(242, 232, 183); // changes the color to sand color

  // for loop to creates the sand rectangle
  for (int i = 0; i < windHt - 200; i++) {
    gfx_line(0, (windHt - 200 + i), windWd, (windHt - 200 + i));
  }

  gfx_color(255, 0, 0); // changes the color to red
  // for loop that creates the the beachball
  for (int i = 0; i < rad1; i++) {
    gfx_circle(xc, yc, rad1 - i);
  }

  gfx_color(255, 255, 255); // changes the color to white
  // for loop that creates five equally spaced line
  for (int i = 1; i <= 6; i++) {
    float angle = (2*M_PI)/5;
    double x = rad1*cos((angle + dx) + (angle*i)); // creates a x coordinate based on the angle which then gets changed by dx to create motion
    double y = rad1*sin((angle + dx) + (angle*i)); // creates a y coordinate based on the angle which then gets changed by dx to create motion
    gfx_line(xc, yc, xc + x, yc + y); // creates the lines
  }

  // for loop that creates the inner circle of the beachball
  for (int i = 0; i < rad2; i++) {
    gfx_circle(xc, yc, rad2 - i);
  }

  // for loop that creates the clouds
  for (int i = 0; i < 50; i++) { // creates a large circle in the middle of the cloud
    gfx_circle(200, 100, 50 - i);
  }
  // creates seven smaller circles equally spaced surrounding the bigger circle
  for (int j = 0; j < 7; j++) {
    for (int i = 0; i < 30; i++) {
      float angle = (2*M_PI)/7;
      gfx_circle (200 + 50*cos(angle + (angle*j)), 100 + 50*sin(angle + (angle*j)), 30 - i);
    }
  }
  for (int i = 0; i < 50; i++) {
    gfx_circle(250, 100, 50 - i);
  }
  // creates seven smaller circles equally spaced surrounding the bigger circle
  for (int j = 0; j < 7; j++) {
    for (int i = 0; i < 30; i++) {
      float angle = (2*M_PI)/7;
      gfx_circle (250 + 50*cos(angle + (angle*j)), 100 + 50*sin(angle + (angle*j)), 30 - i);
    }
  }

  for (int i = 0; i < 25; i++) { // creates a circle in the middle of the cloud
    gfx_circle(500, 150, 25 - i);
  }
  // creates seven smaller circles equally spaced surrounding the bigger circle
  for (int j = 0; j < 7; j++) {
    for (int i = 0; i < 15; i++) {
      float angle = (2*M_PI)/7;
      gfx_circle (500 + 25*cos(angle + (angle*j)), 150 + 25*sin(angle + (angle*j)), 15 - i);
    }
  }
  for (int i = 0; i < 25; i++) { // creates another circle for the middle of the cloud
    gfx_circle(550, 150, 25 - i);
  }
  // creates seven smaller circles equally spaced surrounding the bigger circle
  for (int j = 0; j < 7; j++) {
    for (int i = 0; i < 15; i++) {
      float angle = (2*M_PI)/7;
      gfx_circle (550 + 25*cos(angle + (angle*j)), 150 + 25*sin(angle + (angle*j)), 15 - i);
    }
  }

}
