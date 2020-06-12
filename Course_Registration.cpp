#pragma once
#include "functionPrototype.h"
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

int selectCourse(const char* message, int posY) {

	for (int i = posY - 1; i <= posY + 4; i++) {
		gotoxy(0, i);
		cout << "                                                   ";
		cout << "                                                   ";
	}
	
	gotoxy(3, posY);
	int courseNum = 0;
	cout << message << "번호 입력: ";
	cin >> courseNum;
	
	return courseNum;
}


int registration(vector<Course>& c, int posY) {

	int courseNum = 0;
	courseNum = selectCourse("(수강 신청) 강의 ", posY);

	const char* filename = "./timetable.txt";
	//내 시간표랑 겹치는지 체크

	int num_myCourse = lineCounter(filename);
	vector<Course> myC;
	myC.resize(num_myCourse);

	freadCourse(filename, myC, num_myCourse);

	bool duplName = 0;
	bool duplTime = 0;
	for (int i = 0; i < num_myCourse; i++) {
		if (strcmp(c[courseNum-1].courseName, myC[i].courseName) == 0) {
			duplName = 1;
			break;
		}
		if (c[courseNum-1].day1 == myC[i].day1 || c[courseNum-1].day1 == myC[i].day2 || c[courseNum-1].day2 == myC[i].day1 || c[courseNum-1].day2 == myC[i].day2) {
			if (!(c[courseNum-1].endTime <= myC[i].startTime || c[courseNum-1].startTime >= myC[i].endTime)) {
				duplTime = 1;
				break;
			}
		}
	}

	gotoxy(3, posY + 1);
	if (duplName) {
		cout << "※(실패) 이미 수강 신청한 강의입니다." << '\n';
	}
	if (duplTime) {
		cout << "※(실패) 이미 수강 신청한 강의와 중복되는 시간대의 강의입니다." << '\n';
	}
	else {
		fwriteCoureseInfo(filename, c[courseNum-1], "a");
		coutCourse(c[courseNum-1], posY-14);
		gotoxy(2, posY + 1);
		cout << "  ";
		gotoxy(3, posY + 2);
		cout << "해당 강의 수강 신청 성공";
	}
	gotoxy(3, posY+3);
	system("pause");
	system("cls");

}
