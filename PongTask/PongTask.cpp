// PongTask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include<conio.h>
using namespace std;
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 }; //Direction of the ball

class pongBall 
{
	
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

	void Reset() 
	{
		x = originalX;
		y = originalY;
		direction = STOP;
	}

	void changeDirection(eDir dir)
	{
		direction = dir; //Current direction = New direction
	}

	void randomDirection() //Random direction for the ball
	{
		direction = (eDir)((rand() % 6) + 1 ); // It will cast random numbers from the direction list 1 - 6
	}

	inline int getX() { return x; } //Inline makes the function replace the current position
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }

	void Move() //Ball Movement 
	{
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
			x--; //Decrease X coordinate
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNLEFT: 
			x--; y++;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		default:
			break;
		}
	}

	friend ostream & operator << (ostream & o, pongBall p)
	{
		o << "Ball [" << p.x << "," << p.y << "][" << p.direction << "]" ;
		return o;
	}
};

class playerPaddle 
{
private:
	int x, y;
	int originalX, originalY;
public:
	playerPaddle()
	{
		x = y = 0; //Curr pos
	}

	playerPaddle(int posX, int posY) : playerPaddle()
	{
		originalX = posX; //Start Pos
		originalY = posY;
		x = posX;
		y = posY;
	}

	inline void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y--; } //Direction of movement
	inline void moveDown() { y++; }

	friend ostream & operator << (ostream & o,playerPaddle pp)
	{
		o << "Paddle [" << pp.x << "," << pp.y << "]";
		return o;
	}
};

class GameManager 
{
private:
	int width, height;
	int score1, score2; //Score for players
	char up1, down1, up2, down2; //Player controls
	bool quit;
	pongBall * ball;
	playerPaddle * player1;
	playerPaddle * player2;
public:
	GameManager(int w, int h)
	{
		srand(time(NULL)); //Randomize random number genrator, units time stamp;
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new pongBall(w / 2, h / 2);
	}
};

int main()
{


	return 0;
}


