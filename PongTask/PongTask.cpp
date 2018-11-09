// PongTask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 }; //Direction of the ball

class pongBall {
	
private:
	int x, y; //Position of the ball on the screen
	int originalX, originalY; //Starting pos
	eDir direction;
public:
	pongBall(int posX, int posY) {

		originalX = posX;
		originalY = posY; //Will save the original pos of ball, used for reset
		x = posX; y = posY; //Current position
		direction = STOP;
	}

	void Reset() {
		x = originalX;
		y = originalY;
		direction = STOP;
	}

	void changeDirection(eDir dir) {
		direction = dir; //New direction
	}
};


int main()
{
	return 0;
}


