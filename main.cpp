#include<iostream>
#include<time.h>
#include <iomanip>
#include <limits>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include<windows.h>

using namespace std;

bool TurnOn;
const int FieldW = 20, FieldL = 20;
int field[FieldW][FieldL];

void ShowScreen();
void OneStep(int GX, int GY, int Len);
void FillDots();


void game()	
{
	system("cls");
	srand(time(0));
	cout << "GAME STARTS...";
	Sleep(1000);
	system("cls");

	int k2;
	int counter=10;		//clock frequency (can be used for difficulty up), tick
	int FieldW = 20, FieldL = 20;
	int direction=1, HeadX=10, HeadY=5, YY=rand()%19, YX=rand()%19;
	field[YX][YY] = -1;
	int Len = 5;
	Sleep(1000);
	FillDots();
	field[YX][YY] = -1;
	bool Ingame = 1;
	while (Ingame == 1)
	{		
			//waiting for key button hit or keep the direction
			srand(time(0));
			counter = 10;
			for (int i = 10; (i > 0) && (!_kbhit()); i--)
			{
				Sleep(50);
				counter--;
			}
			Sleep(counter*50);	//remaining tick time
			//

			//controls
			while (_kbhit())
			{
				k2 = _getch();
				if (k2 == 'a' && direction != 1) direction = 3;	//left
				if (k2 == 'w' && direction != 4) direction = 2;	//up
				if (k2 == 'd' && direction != 3) direction = 1;	//right	
				if (k2 == 's' && direction != 2) direction = 4;	//down
			}

			//if not kbhi'tted direction is constant

			if (direction == 1)
				HeadY++;
			if (direction == 2)
				HeadX--;
			if (direction == 3)
				HeadY--;
			if (direction == 4)
				HeadX++;


			//processing apple spawn and eating
			if (field[HeadX][HeadY] == -1)
			{
				Len++;
				bool Yok=0;
				srand(time(0));
				while (Yok==0)
				{
					YX = rand() % 19;
					YY = rand() % 19;
					if (field[YX][YY] == 1)
					{
						field[YX][YY] = -1;
						Yok = 1;
					}
				}
				//tail grow imideately after eating
				for (int j = 0; j <= FieldL; j++)
				{
					for (int i = 0; i <= FieldW; i++)
					{
						if (field[j][i]>1)
						field[j][i] ++;
					}
				}
			}

			//win condition
			if (Len==400)
			{
				Ingame = 0;
				Sleep(500);
				system("cls");
				cout << "CONGRATULATIONS!!!";
				Sleep(2000);
				system("cls");
			}

			// loose condition
			if (HeadX > 20 || HeadX < 1 || HeadY > 20 || HeadY < 1 || field[HeadX][HeadY] >1)
			{
				Ingame = 0;

				Sleep(500);
				system("cls");
				cout << "Failed";

				Sleep(1000);
				system("cls");
			}
			OneStep(HeadX, HeadY, Len);//calling rendering and next step
	}
}

void OneStep(int GX, int GY, int Zlen)
{
	field[GX][GY] = 0;		//present head position
	ShowScreen();			//rendering
	field[GX][GY] = Zlen;	//present head becomes body cell with int (Len) lifetime
}

//printing function
void ShowScreen()
{
	system("cls");
	for (int X = 1; X <= FieldL; X++)
	{
		for (int Y = 1; Y <= FieldW; Y++)
		{
			//empty cell 1, head 0, apple <0, body >1
			if (field[X][Y] == 1)						//dot code 1
				cout << ". ";
			if (field[X][Y] == 0)
				printf("\033[1;104;30m  \033[0m");	//head code 0
			if (field[X][Y] < 0)
				cout << "\033[2;103;30m  \033[0m";	//apple code <0
			if (field[X][Y] > 1)
			{
				printf("\033[3;47;35m  \033[0m");	//body code >1
				field[X][Y]--;
			}
			//after 1 tick body cell lifetime decreases by 1


		}
		cout << "\n";
	}
}

//filling all cells with dot code
void FillDots()
{
	for (int X = 0; X <= FieldL; X++)
	{
		for (int Y = 0; Y <= FieldW; Y++)
		{
			field[X][Y] = 1;//dot code - 1
		}
	}
}


int main()
{
	TurnOn = 1;
	while (TurnOn==1)
	{
		int MenuNumber;
		Menu:
		system("cls");
		cout << "ZMEIKA 1.0 \n 1.Igra \n 2.Info \n 3.Quit " << endl;
	Mistake:
		Sleep(500);
		MenuNumber=_getch();
		if (MenuNumber == '1')
		{
			game();
			goto Menu;
		}
		if (MenuNumber == '2')
		{
			system("cls");
			cout << "VERSION 1.0\nWASD for control\nOnly english \n 1. Any key to menu";
			int Menu;
			Menu = _getch();
				goto Menu;
		}
		if (MenuNumber == '3')
			TurnOn = 0;
		else
		{
			goto Mistake;
			break;
		}

	}
	return 0;
}