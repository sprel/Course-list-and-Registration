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

	int x = 10;
	int y = 3;
	gotoxy(x, y);
	cout << "메뉴 선택";
	gotoxy(x, y + 2);
	cout << "강의 시간표 조회";
	gotoxy(x, y + 4);
	cout << "강의 추가";
	gotoxy(x, y + 6);
	cout << "내 시간표 보기";
	gotoxy(x, y + 8);
	cout << "종료";

	int key = 0;
	int pos = y + 2;
	int menu = 0;

	while (true) {
		gotoxy(x - 2, pos);
		Sleep(200);
		if (_kbhit()) {
			key = _getch();
			if (key == 13) {
				menu = (pos - 3) / 2;
				return menu;
			}
			if (key == 224) {
				key = _getch();
				switch (key) {
					case 72:
						if (pos > y) {
							pos -= 2;
						}
						break;
					case 80:
						if (pos < y + 8) {
							pos += 2;
						}
						break;
				}
			}
		}
	}
}

int main() {

	int menu = 1;
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