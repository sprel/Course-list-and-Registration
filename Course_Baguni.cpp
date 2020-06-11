#pragma once
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
	courseNum = selectCourse("(수강 바구니) 강의 번호 입력: ");

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
		fwriteCoureseInfo(filename, c[courseNum-1]);
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
