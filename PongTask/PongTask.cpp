// PongTask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <time.h>
#include<conio.h>
#include <Windows.h>
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

class GameManager //Draw and game logic 
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
		player1 = new playerPaddle(1, h / 2 - 3);
		player2 = new playerPaddle(w - 2, h / 2 - 3);
	}



	~GameManager() //Destructur
	{

		delete ball, player1, player2;

	}


	void ScoreUp(playerPaddle * player)
	{
		if (player == player1) //Increase score
			score1++;
		else if (player == player2)
			score2++;

		//Reset when score reached
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}


	void Draw()
	{
		system("cls"); //Clear console screen
		/*BOOL WINAPI WriteConsoleOutputAttribute(
			_In_   HANDLE hConsoleOutput,
			_In_   const WORD *lpAttribute,
			_In_   DWORD nLength,
			_In_   COORD dwWriteCoord,
			_Out_  LPDWORD lpNumberOfAttrsWritten
		); */
		
		for (int i = 0; i < width + 2; i++)
			cout << "|"; //Walls
		cout << endl;

		for (int i = 0; i < height; i++) //I = Y coordinate height
		{
			for (int j = 0; j < width; j++) // J = X coordinate width
			{
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();

				if (j == 0) //Wall
					cout << "|";

				if (ballx == j && bally == i)
					cout << "0"; //Ball
				else if (player1x == j && player1y == i)
					cout << "#"; //Player one
				else if (player2x == j && player2y == i)
					cout << "#"; //Player two

				else if (player1x == j && player1y + 1 == i)
					cout << "#"; //Player one
				else if (player1x == j && player1y + 2== i)
					cout << "#"; //Player one	  
				else if (player1x == j && player1y + 3== i)
					cout << "#"; //Player one	  

				else if (player2x == j && player2y + 1== i)
					cout << "#"; //Player two	   
				else if (player2x == j && player2y + 2== i)
					cout << "#"; //Player two	   
				else if (player2x == j && player2y + 3== i)
					cout << "#"; //Player two
				else
					cout << " ";

				if (j == width - 1)
					cout << "|";

			}

			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "|";
		cout << endl;

		cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
	}

	void Input()
	{
		ball->Move(); //Will also store the coordinates

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		if (_kbhit())
		{
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					player1->moveUp();
			if (current == up2)
				if (player2y > 0)
					player2->moveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();
			if (current == down2)
			if (player2y + 4 < height)
				player2->moveDown();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (current = 'esc')
				quit == true;

				
		}
	}

	void Logic()
	{
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		//Left Paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));

		//Right Paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		//Bottom wall
		if (bally == height - 1) //Bounce of the wall
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		//Top wall
		if (bally == 0) //Bounce of the wall
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		//Right wall
		if (ballx == width - 1)
			ScoreUp(player1);

		//Left wall
		if (ballx == 0)
			ScoreUp(player2);
	}

	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};

		int main()

		{
			GameManager c(40, 20);
			c.Run();
			return 0;
			
		} 