#include<iostream>
#include"some.h"
#include<ctime>

using namespace std;

#define piece 254
#define up 1
#define down 2
#define left 3
#define right 4
#define top_wall 3
#define bottom_wall 23
#define left_wall 10
#define right_wall 100 

struct Coordinate
{
	int x;
	int y;
};

Coordinate snake[100];
int cP = 3;		//count pieces
int p = 0;		//count points

void create();
void display(Coordinate old_last_piece);
Coordinate move(int direct);
void catchEvent(int &direct);
void wall_draw();
bool isOver();
void whenOver();
Coordinate bait();
bool isEaten(Coordinate b);
void addPiece();
int main() {
	int direct = right;	//direction
	int t = 250;

	create();
	wall_draw();
	Coordinate b = bait(); //random a bait
	//game loop
	while (1) {
		Coordinate old_last_piece = move(direct);
		catchEvent(direct);
		display(old_last_piece);
		if (isEaten(b) == true) {
			b = bait(); //random a new bait
			addPiece();
			if (t > 30) {
				t -= 20;
			}
			p++;
		}
		if (isOver() == true) {
			break;
		}
		Sleep(t);
	}
	whenOver();
	setTextColor(10);
	cout << "Your scores: " << p << endl;
	setTextColor(7);
	system("pause"); //pause
}

void create() {
	snake[0].x = 17; snake[1].x = 16; snake[2].x = 15;
	snake[0].y = snake[1].y = snake[2].y = 10;
}

void display(Coordinate old_last_piece) {
	setTextColor(13);
	gotoXY(right_wall + 3, top_wall);
	cout << "Your Scores: " << p;
	gotoXY(snake[0].x, snake[0].y);
	cout << (char)2;
	for (int i = 1; i < cP; i++) {
		gotoXY(snake[i].x, snake[i].y);
		cout << (char)piece;
	}
	gotoXY(old_last_piece.x, old_last_piece.y);
	cout << " ";
}

Coordinate move(int direct) {
	Coordinate old_last_piece = snake[cP - 1];

	for (int i = cP - 1; i >= 1; i--) {
		snake[i] = snake[i - 1];
	}
	switch (direct) {
	case up:
		snake[0].y--;
		break;
	case down:
		snake[0].y++;
		break;
	case left:
		snake[0].x--;
		break;
	case right:
		snake[0].x++;
		break;
	}
	return old_last_piece;
}

void catchEvent(int &direct) {
	int key = inputKey();
	if (key == 'w' || key == 'W' || key == KEY_UP) {
		direct = 1;
	}
	else if (key == 's' || key == 'S' || key == KEY_DOWN) {
		direct = 2;
	}
	else if (key == 'a' || key == 'A' || key == KEY_LEFT)
	{
		direct = 3;
	}
	else if (key == 'd' || key == 'D' || key == KEY_RIGHT) {
		direct = 4;
	}
}

void wall_draw() {
	for (int i = left_wall; i <= right_wall; i++) {
		setTextColor(6);
		gotoXY(i, top_wall);
		cout << (char)220;
	}
	for (int i = top_wall + 1; i <= bottom_wall; i++) {
		setTextColor(14);
		gotoXY(left_wall, i);
		cout << (char)221;
	}
	for (int i = left_wall; i <= right_wall; i++) {
		setTextColor(6);
		gotoXY(i, bottom_wall);
		cout << (char)223;
	}
	for (int i = top_wall + 1; i <= bottom_wall - 1; i++) {
		setTextColor(14);
		gotoXY(right_wall, i);
		cout << (char)222;
	}
	cout << endl << endl;

}

bool isOver() {
	if (snake[0].x == left_wall || snake[0].y == top_wall || snake[0].x == right_wall || snake[0].y == bottom_wall) {
		return true;
	}
	for (int i = 1; i < cP; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			return true;
		}
	}
}

void whenOver() {
	Sleep(500);
	clrscr();
	setTextColor(9);
	cout << "U r f*cking bad at this game" << endl;
}

Coordinate bait() {
	srand(time(NULL)); //when use rand()
	int x = left_wall + 1 + rand() % (right_wall - 1 - (left_wall + 1) + 1);
	int y = top_wall + 1 + rand() % (bottom_wall - 1 - (top_wall + 1) + 1);
	int _b = 1 + rand() % 6;
	gotoXY(x, y);
	setTextColor(11);
	cout << (char) _b;
	return Coordinate{ x, y };
}

bool isEaten(Coordinate b) {
	if (snake[0].x == b.x && snake[0].y == b.y)
	{
		return true;
	}
	else {
		return false;
	}
}

void addPiece() {
	snake[cP] = snake[cP - 1];
	cP++;
}