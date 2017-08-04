## Beach Ball Animation

In order to start learning about working with different graphics libraries we were given the assignment to create a simple animation that utilized key and mouse input. The graphics library used in this assignment was provided by the professor of my Fundamentals of Computing class, Ramzi Bualuan. For more details about the program refer to the *report.txt* file. 

## Use

**The game works best when played locally but you will need to have XQuartz installed.**

1. Clone the repository
2. Compile animate.cpp using the following command: `g++ -std=c++11 -lX11 animate.cpp -o animate` --> FIX THIS IT ISN'T RIGHT
3. Run the executable: `./animate`
4. A window will open and the user can control the animation using the following commands (as the window describes):
	* w: speed up the ball
	* s: slow down the ball
	* a: move the ball to the left
	* d: move the ball to the right
	* mouse left click: make the ball bounce
	* q: quit


