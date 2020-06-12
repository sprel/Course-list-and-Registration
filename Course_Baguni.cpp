#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "functionPrototype.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cin;
using std::cout;

void putinBaguni(vector<Course>& c) {
	vector<Course> baguniC(10);
	const char* filename = "./baguni.txt";

	int num_baguni = 0;
	num_baguni = lineCounter(filename);

	freadCourse(filename, baguniC, num_baguni);

	int courseNum = 0;
	courseNum = selectCourse("(수강 바구니) 강의 ", 26);

	bool dupl = 0;
	for (int i = 0; i < num_baguni; i++) {
		if (strcmp(c.at(courseNum-1).courseName, baguniC.at(i).courseName) == 0) {
			dupl = 1;
		}
	}

	gotoxy(3, 27);
	if (dupl) {
		cout << "※(실패) 이미 수강 바구니에 담겨 있는 강의입니다.";
	}
	else {
		fwriteCoureseInfo(filename, c[courseNum-1], "a");
		coutCourse(c[courseNum-1], 12);
		gotoxy(2, 27);
		cout << "  ";
		gotoxy(3, 28);
		cout << "해당 강의 수강 바구니에 담기 성공";
	}
	gotoxy(3, 29);
	system("pause");
	system("cls");

}

int selectMenu_B() {

	gotoxy(3, 27);
	printf("┌--------------┐");
	gotoxy(3, 28);
	printf("│   수강 신청  │");
	gotoxy(3, 29);
	printf("└--------------┘");
	gotoxy(24, 27);
	printf("┌--------------┐");
	gotoxy(24, 28);
	printf("│   항목 삭제  │");
	gotoxy(24, 29);
	printf("└--------------┘");
	gotoxy(45, 27);
	printf("┌-----------┐");
	gotoxy(45, 28);
	printf("│  뒤로가기 │");
	gotoxy(45, 29);
	printf("└-----------┘");

	int menu = moveCursor(28);

	return menu;
}

void openBaguni() {
	vector<Course> baguniC(10);
	const char* filename = "./baguni.txt";



	bool flag = 1;
	while (flag) {

		int num_baguni = 0;
		num_baguni = lineCounter(filename);
		baguniC.resize(num_baguni);

		freadCourse(filename, baguniC, num_baguni);
		coutItemname("<수강 바구니 목록>");
		for (int i = 0; i < num_baguni; i++) {
			coutCourse(baguniC[i], i + 1);
		}

		int menu = selectMenu_B();
		int courseNum = 0;
		switch (menu) {
			case 1:
				courseNum = registration(baguniC, 26);
				if (courseNum != -1) {
					deleteCourse(baguniC, num_baguni, filename, courseNum);
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


void deleteCourse(vector<Course>& c, int& num_course, const char* filename, int& courseNum) {

	if (1 <= courseNum && courseNum <= num_course) {
		c.erase(c.begin() + (courseNum - 1));
	}
	if (c.size() == 0) {
		FILE* fp;
		fp = fopen(filename, "w");
		if (fp == nullptr) {
			cout << "파일 열기 실패";
			return;
		}
		fclose(fp);
	}
	else {
		vector<Course>::iterator it = c.begin();
		fwriteCoureseInfo(filename, *it, "w");
		for (it = c.begin() + 1; it != c.end(); ++it) {
			fwriteCoureseInfo(filename, *it, "a");
		}
	}

}
