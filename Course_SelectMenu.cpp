#pragma once
#include "functionPrototype.h"

#include <Windows.h>
#include <conio.h>
#include <iostream>

using std::cout;

int moveCursor(int posY) {
	int pos = 0;
	int key = 0;

	pos = 1;
	gotoxy(pos, posY);
	printf("▶");
	while (1)
	{
		Sleep(200);
		if (_kbhit())
		{
			key = _getch();
			if (key == 224)
			{
				key = _getch();
				switch (key)
				{
					case LEFT:
						if (pos > 1)
						{
							gotoxy(pos, posY);
							printf("  ");
							pos = pos - 21;
							gotoxy(pos, posY);
							printf("▶");
						}
						break;
					case RIGHT:
						if (pos < 85)
						{
							gotoxy(pos, posY);
							printf("  ");
							pos = pos + 21;
							gotoxy(pos, posY);
							printf("▶");
						}
						break;
				}
			}
			if (key == 13)
				break;
		}
	}

	return (pos - 1) / 21 + 1;
}

int selectMenu(int& pageNum, int& endPage) {

	gotoxy(3, 25);
	printf("┌--------------┐");
	gotoxy(3, 26);
	printf("│  이전 페이지 │");
	gotoxy(3, 27);
	printf("└--------------┘");
	gotoxy(24, 25);
	printf("┌--------------┐");
	gotoxy(24, 26);
	printf("│  다음 페이지 │");
	gotoxy(24, 27);
	printf("└--------------┘");
	gotoxy(45, 25);
	printf("┌--------------┐");
	gotoxy(45, 26);
	printf("│   수강 신청  │");
	gotoxy(45, 27);
	printf("└--------------┘");
	gotoxy(66, 25);
	printf("┌----------------┐");
	gotoxy(66, 26);
	printf("│  바구니에 담기 │");
	gotoxy(66, 27);
	printf("└----------------┘");
	gotoxy(87, 25);
	printf("┌-----------┐");
	gotoxy(87, 26);
	printf("│  뒤로가기 │");
	gotoxy(87, 27);
	printf("└-----------┘");

	int menu = moveCursor(26);

	if (menu == 1) {
		if (pageNum == 1) {
			system("cls");
			cout << "더 이상 조회할 강의가 없습니다.";
			system("pause");
			return 0;
		}
		else {
			return 1;
		}
	}
	if (menu == 2) {
		if (pageNum == endPage) {
			system("cls");
			cout << "더 이상 조회할 강의가 없습니다.";
			system("pause");
			return 0;
		}
		else {
			return 2;
		}
	}
	if (menu == 3)
		return 3;
	if (menu == 4)
		return 4;
	if (menu == 5)
		return 5;
}
