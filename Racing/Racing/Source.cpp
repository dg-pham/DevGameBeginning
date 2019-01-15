#include<iostream>
#include"some.h"
#include<ctime>

using namespace std;

#define length 120
#define width 30
#define roadWidth 25

struct Coordinate {
	int x, y;
};

struct Shape {
	char a[3][3];
};

struct Car {
	Coordinate c;
	Shape s;
};

struct Obstacle
{
	Coordinate c;
	Shape s;
};

struct Pieces {
	char character;
	int color;
};

Pieces buffer[roadWidth + 1][width];	//create buffer

Car car;
Obstacle obs;
int p = 0;
int t = 200;

void create();
void display();
void roadDraw();
void catchEvent();
void obstacle();
void handle();
void obsDisplay();
void obsShape();
bool hit();
void whenOver();
void piece(int col, int row, int character, int color);
void show();
int main() {
	create();
	obstacle();
	obsShape();

	while (1) {
		catchEvent();
		display();
		obsDisplay();
		handle();
		if (hit() == true) {
			break;
		}
		Sleep(t);
	}
	whenOver();
	setTextColor(12);
	system("pause");
}

void create() {
	//car
	car.c.x = roadWidth / 2;
	car.c.y = width - 2;

	car.s.a[0][0] = car.s.a[0][2] = car.s.a[2][0] = car.s.a[2][2] = 'o';	//wheels
	car.s.a[1][0] = '^';	//head
	car.s.a[0][1] = car.s.a[2][1] = '|';	//body
	car.s.a[1][1] = ' ';
	car.s.a[1][2] = '_';

	//in a piece
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < roadWidth; j++) {
			buffer[j][i].character = ' ';
			buffer[j][i].color = 7;
		}
	}
}

void display() {
	roadDraw();

	setTextColor(3);
	gotoXY(roadWidth + 1, 1);
	cout << "Your Scores: " << p;


	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int x = j + car.c.x;
			int y = i + car.c.y;

			piece(x, y, car.s.a[j + 1][i + 1], 13);
		}
	}

	show();
}

void roadDraw() {
	/*setTextColor(6);*/
	for (int i = 0; i < width; i++) {
		piece(0, i, 179, 6);
		piece(roadWidth, i, 179, 6);
	}
}

void catchEvent() {
	int key = inputKey();
	/*if (key == 'w' || key == 'W' || key == KEY_UP) {
		direct = 1;
	}*/
	/*else if (key == 's' || key == 'S' || key == KEY_DOWN) {
		direct = 2;
	}*/
	if ((key == 'a' || key == 'A' || key == KEY_LEFT) && car.c.x > 2)
	{
		car.c.x--;
	}
	else if ((key == 'd' || key == 'D' || key == KEY_RIGHT) && car.c.x < roadWidth - 2) {
		car.c.x++;
	}
}

void obstacle() {
	//obstacle course
	srand(time(NULL));
	obs.c.x = 2 + rand() % (roadWidth - 3);
	obs.c.y = -1;
}

void obsShape() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			obs.s.a[i][j] = 173;
		}
	}
}

void handle() {
	//obs go down
	obs.c.y++;

	//when evaded
	if (obs.c.y > width) {
		p++;
		obstacle();
		if (t > 30) {
			t -= 20;
		}
	}
}

void obsDisplay() {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int x = j + obs.c.x;
			int y = i + obs.c.y;

			if (y >= 0 && y < width) {
				piece(x, y, obs.s.a[j + 1][i + 1], 11);
			}
		}
	}
}

bool hit() {
	// when hit
	int dX = abs(car.c.x - obs.c.x);
	int dY = abs(car.c.y - obs.c.y);

	if (dX < 3 && dY < 3) {
		return true;
	}
}

void whenOver() {
	clrscr();
	Sleep(500);
	cout << "U r done, idiot!!" << endl;
	setTextColor(11);
	cout << "Your scores: " << p << endl;
}

void piece(int col, int row, int character, int color = 7) {
	buffer[col][row].character = character;
	buffer[col][row].color = color;
}

void show() {
	gotoXY(0, 0);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j <= roadWidth; j++) {
			setTextColor(buffer[j][i].color);
			cout << (char)buffer[j][i].character;

			buffer[j][i].character = ' ';
		}

		if (i < width - 1) {
			cout << endl;
		}
	}
}