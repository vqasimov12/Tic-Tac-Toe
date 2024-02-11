#include <iostream>
#include <conio.h>
#include <Windows.h>
#define red "\x1B[31m"
#define white "\x1B[0m"
using namespace std;

void cursor(char a[5][5], int row, int col, int turn)
{
	if (turn % 2)
	{
		system("cls");
		cout << "Player 1 -> X" << endl << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == row && j == col)
					cout << red << "X " << white;
				else
					cout << a[i][j] << " ";
			}
			cout << endl;
		}
	}
	else
	{
		system("cls");
		cout << "Player 2 -> O" << endl << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == row && j == col)
					cout << red << "O " << white;
				else
					cout << a[i][j] << " ";
			}
			cout << endl;
		}
	}
}
int change(char a[5][5], int row, int col, bool check = false, int turn = 1)
{
	if (a[row][col] == ' ')
	{
		a[row][col] = (turn % 2 == 1 ? 'X' : 'O');
		return true;
	}
	else
	{
		cout << endl << red << "Please choose another spot." << white << endl;
		Sleep(1002);
		return false;
	}
}
int check_array(char a[5][5])
{
	int check = 3;
	for (int i = 0, j = 0; j < 5; j += 2)
	{
		if (a[i][j] == 'X' && a[i + 2][j] == 'X' && a[i + 4][j] == 'X')
			return 1;
		else if (a[j][i] == 'X' && a[j][i + 2] == 'X' && a[j][i + 4] == 'X')
			return 1;
		else if (a[i][j] == 'O' && a[i + 2][j] == 'O' && a[i + 4][j] == 'O')
			return 2;
		else if (a[j][i] == 'O' && a[j][i + 2] == 'O' && a[j][i + 4] == 'O')
			return 2;
	}
	if (a[0][0] == 'X' && a[2][2] == 'X' && a[4][4] == 'X' || a[0][4] == 'X' && a[2][2] == 'X' && a[4][0] == 'X')
		return 1;
	else if (a[0][0] == 'O' && a[2][2] == 'O' && a[4][4] == 'O' || a[0][4] == 'O' && a[2][2] == 'O' && a[4][0] == 'O')
		return 2;
	for (int i = 0; i < 5; i += 2)
	{
		for (int j = 0; j < 5; j += 2)
		{
			if (a[i][j] == ' ')
			{
				check = 0;
				break;
			}
		}
	}
	return check;
}
void main()
{
	char a[5][5]{};
	int turn = 1;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i % 2)
				a[i][j] = 196;
			else if (j % 2)
				a[i][j] = '|';
			else
				a[i][j] = ' ';
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	int move = 0;
	int row = 0, col = 0;
	cursor(a, row, col, 1);
	while (true)
	{
		bool check = false;
		move = _getch();
		if (move == 77 || move == 68 || move == 100)
		{
			col += 2;
			if (row == 4 && col == 6)
				col = 4;
			if (col >= 6 && row < 6)
			{
				col = 0;
				row += 2;
			}
		}
		else if (move == 75 || move == 65 || move == 97)
		{
			if (col != 0)
				col -= 2;
			else if (col == 0 && row > 0)
			{
				col = 4;
				row -= 2;
			}
		}
		else if (move == 72 || move == 119 || move == 87)
		{
			if (row > 0)
				row -= 2;
		}
		else if (move == 80 || move == 115 || move == 83)
		{
			if (row != 4)
				row += 2;
		}
		else if (move == 13)
		{
			bool check = 1;
			if (change(a, row, col, check, turn))
				turn++;
		}
		cursor(a, row, col, turn);
		if (check_array(a) == 1)
		{
			system("cls");
			cout << "\nWinner -> Player 1\n";
			break;
		}
		else if (check_array(a) == 2)
		{
			system("cls");
			cout << "\nWinner -> Player 2\n";
			break;
		}
		else if (check_array(a) == 3)
		{
			system("cls");
			cout << "\nDraw \n";
			break;
		}
	}
}
