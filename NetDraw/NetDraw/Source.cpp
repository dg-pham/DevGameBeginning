#include<iostream>
#include"some.h"

using namespace std;

#define length 120
#define width 30

void emptyNet();
void ascii();
void chessboard();
void chessboardColor();
void piece(int i, int j, int character);
void pieceColor(int iConsole, int jConsole, int color);
void color();
int main() {
	//ascii();
	//emptyNet();
	//chessboard();
	chessboardColor();
	//color();
	_getch();
}

void emptyNet() {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 9; j++) {
			if (i % 2 == 0 && j < 8) {
				cout << (char)197 << (char)196 << (char)196 << (char)196;
			}
			else if (i % 2 == 0) {
				cout << (char)197;
			}
			else {
				cout << (char)179 << "   ";
			}
		}
		cout << endl;
	}
}

void ascii() {
	for (int i = 0; i < 256; i++) {
		cout << i << ":" << char(i) << endl;
	}
}

void chessboard() {
	int row = 8;
	int col = 8;
	//1st way
	/*for (int iConsole = 0; iConsole < 8 * 3; iConsole++) {
		for (int jConsole = 0; jConsole < 8 * 6; jConsole++) {
			int i = iConsole / 3;
			int j = j / 6;

			if (i + j) % 2 == 0) {
				cout << (char)176;
			}
			else {
				cout << (char)178;
			}
		}
		cout << endl;
	}*/

	//2nd way
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if ((i + j) % 2 == 0) {
				piece(i * 3, j * 6, 176);
			}
			else {
				piece(i * 3, j * 6, 178);
			}
		}
		cout << endl;
	}
}

void piece(int iConsole, int jConsole, int character) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			gotoXY(jConsole + j, iConsole + i);
			cout << (char)character;
		}
	}
}

void pieceColor(int iConsole, int jConsole, int color) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			setTextColor(color);
			gotoXY(jConsole + j, iConsole + i);
			cout << " ";
		}
	}
}
void chessboardColor() {
	int row = 8;
	int col = 8;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++){
			setTextColor(180);
			cout << " ";
		}
	}

	gotoXY(0, 0);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			pieceColor(i * 3, j * 6, 208 * ((i + j) % 2));
		}
		cout << endl;
	}
}

void color() {
	for (int i = 0; i < 256; i++)
	{
		setTextColor(i);
		cout << i << endl;
	}
}