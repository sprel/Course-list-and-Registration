#pragma
#include "functionPrototype.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

void coutTable(string (*table)[5]) {
	gotoxy(20, 1);
	cout << "<내 시간표 보기>";

	for (size_t i = 0; i < 10; i++) {
		if (i >= 1 && i <= 3) {
			gotoxy(4, 5 + 2 * (i + 1));
		}
		else {
			gotoxy(5, 5 + 2 * (i + 1));
		}
		
		if (i <= 3) {
			cout << i + 9;
		}
		else {
			cout << i - 3;
		}

		gotoxy(7, 5 + 2 * (i + 1));
		cout << "--------------------------------------------------";

		if (i == 9)
			continue;
		for (size_t j = 0; j < 5; j++) {
			gotoxy(1 + 10 * (j + 1), 5);
			switch (j + 1) {
				case MON:
					cout << "월";
					break;
				case TUE:
					cout << "화";
					break;
				case WED:
					cout << "수";
					break;
				case THU:
					cout << "목";
					break;
				case FRI:
					cout << "금";
					break;
			}
			if (table[i][j] != "") {
				gotoxy(8 + 10 * (j), 5 + 2 * (i + 1) + 1);
				cout << table[i][j];
			}
		}
	}
}

int selectMenu_T() {

	gotoxy(3, 27);
	printf("┌----------------┐");
	gotoxy(3, 28);
	printf("│   수강 바구니  │");
	gotoxy(3, 29);
	printf("└----------------┘");
	gotoxy(24, 27);
	printf("┌---------------┐");
	gotoxy(24, 28);
	printf("│ 수강 신청 취소│");
	gotoxy(24, 29);
	printf("└---------------┘");
	gotoxy(45, 27);
	printf("┌------------┐");
	gotoxy(45, 28);
	printf("│  뒤로가기  │");
	gotoxy(45, 29);
	printf("└------------┘");

	int menu = moveCursor(28);

	return menu;
}

void noContent(const char* message) {
	gotoxy(0, 28 - 1);
	cout << "                                                   ";
	cout << "                                                   ";
	gotoxy(0, 28);
	cout << "                                                   ";
	cout << "                                                   ";
	gotoxy(0, 28 + 1);
	cout << "                                                   ";
	cout << "                                                   ";
	gotoxy(3, 28);
	cout << message;

	gotoxy(3, 29);
	system("pause");
	system("cls");
}

void myTable() {
	
	bool flag = 1;
	while (flag) {

		const char* filenameT = "./timetable.txt";

		int num_myCourse;
		num_myCourse = lineCounter(filenameT);

		vector<Course> c;
		c.resize(num_myCourse);

		freadCourse(filenameT, c, num_myCourse);

		string table[9][5];

		int start = -1;
		int end = -1;

		for (vector<Course>::iterator it = c.begin(); it != c.end(); ++it) {
			if ((*it).startTime >= 9)
				start = (*it).startTime - 9;
			else
				start = (*it).startTime + 3;
			if ((*it).endTime >= 9)
				end = (*it).endTime - 9;
			else
				end = (*it).endTime + 3;

			for (size_t i = start; i < end; i++) {
				table[i][(*it).day1 - 1] = (*it).courseName;
			}
			if ((*it).day2 != DEFAULT) {
				for (size_t i = start; i < end; i++) {
					table[i][(*it).day2 - 1] = (*it).courseName;
				}
			}
		}

		coutTable(table);

		int menu = selectMenu_T();

		const char* filenameB = "./baguni.txt";

		int num_baguni = 0;
		num_baguni = lineCounter(filenameB);

		int courseNum = 0;
		
		switch (menu) {
			case 1:
				if (num_baguni == 0) {
					noContent("※ 수강 바구니에 담긴 강의가 없습니다.");
				}
				else {
					system("cls");
					openBaguni();
				}
				break;
			case 2:
				
				break;
			case 3:
				flag = 0;
				break;
		}
	}

	system("cls");
}
