#pragma once
#include "functionPrototype.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>

using std::cout;

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int selectMenu_Main() {

	int x = 30;
	int y = 7;
	
	gotoxy(x + 2, y - 3);
	printf("<강의 시간표 조회 및 수강 신청 서비스>");
	gotoxy(x + 12, y - 1);
	printf("201811286 임종민");

	gotoxy(x, y + 1);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	gotoxy(x, y + 2);
	printf("┃                                      ┃\n");
	gotoxy(x, y + 3);
	printf("┃                                      ┃\n");
	gotoxy(x, y + 4);
	printf("┃      ┏━━━━━━━━━━━━━━━━━━━━━━━━┓      ┃\n");
	gotoxy(x, y + 5);
	printf("┃      ┃        강의 추가       ┃      ┃\n");
	gotoxy(x, y + 6);
	printf("┃      ┗━━━━━━━━━━━━━━━━━━━━━━━━┛      ┃\n");
	gotoxy(x, y + 7);
	printf("┃                                      ┃\n");
	gotoxy(x, y + 8);
	printf("┃      ┏━━━━━━━━━━━━━━━━━━━━━━━━┓      ┃\n");
	gotoxy(x, y + 9);
	printf("┃      ┃    강의 시간표 조회    ┃      ┃\n");
	gotoxy(x, y + 10);
	printf("┃      ┗━━━━━━━━━━━━━━━━━━━━━━━━┛      ┃\n");
	gotoxy(x, y + 11);
	printf("┃                                      ┃\n");
	gotoxy(x, y + 12);
	printf("┃      ┏━━━━━━━━━━━━━━━━━━━━━━━━┓      ┃\n");
	gotoxy(x, y + 13);
	printf("┃      ┃     내 시간표 보기     ┃      ┃\n");
	gotoxy(x, y + 14);
	printf("┃      ┗━━━━━━━━━━━━━━━━━━━━━━━━┛      ┃\n");
	gotoxy(x, y + 15);
	printf("┃                                      ┃\n");
	gotoxy(x, y + 16);
	printf("┃      ┏━━━━━━━━━━━━━━━━━━━━━━━━┓      ┃\n");
	gotoxy(x, y + 17);
	printf("┃      ┃          종료          ┃      ┃\n");
	gotoxy(x, y + 18);
	printf("┃      ┗━━━━━━━━━━━━━━━━━━━━━━━━┛      ┃\n");
	gotoxy(x, y + 19);
	printf("┃                                      ┃\n");
	gotoxy(x, y + 20);
	printf("┃                                      ┃\n");
	gotoxy(x, y + 21);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");


	//gotoxy(x, y);
	//cout << "메뉴 선택";
	//gotoxy(x, y + 2);
	//cout << "강의 시간표 조회";
	//gotoxy(x, y + 4);
	//cout << "강의 추가";
	//gotoxy(x, y + 6);
	//cout << "내 시간표 보기";
	//gotoxy(x, y + 8);
	//cout << "종료";

	int key = 0;
	int posY = y + 5;
	int menu = 0;

	while (true) {
		gotoxy(x + 4, posY);
		printf("▶");
		Sleep(200);
		if (_kbhit()) {
			key = _getch();
			if (key == 13) {
				menu = posY / 4 - 2;
				return menu;
			}
			if (key == 224) {
				key = _getch();
				switch (key) {
					case UP:
						if (posY > y + 5) {
							gotoxy(x + 4, posY);
							printf("  ");
							posY = posY - 4;
							gotoxy(x + 4, posY);
							printf("▶");
						}
						break;
					case DOWN:
						if (posY < y + 17) {
							gotoxy(x + 4, posY);
							printf("  ");
							posY = posY + 4;
							gotoxy(x + 4, posY);
							printf("▶");
						}
						break;
				}
			}
		}
	}
}

int main() {

	int menu = 0;
	bool flag = 1;
	while (flag) {
		menu = selectMenu_Main();
		system("cls");
		switch (menu) {
			case 1:
				courseList();
				break;
			case 2:
				addCourse();
				break;
			case 3:
				myTable();
				break;
			case 4:
				flag = 0;
				break;
		}
	}

	system("cls");
	cout << "프로그램 종료" << '\n';

	return 0;
}