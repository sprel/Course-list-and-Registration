#pragma once
#include "functionPrototype.h"
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

int selectCourse(const char* message) {
	gotoxy(0, 25);
	cout << "                                                   ";
	cout << "                                                   ";
	gotoxy(0, 26);
	cout << "                                                   ";
	cout << "                                                   ";
	gotoxy(0, 27);
	cout << "                                                   ";
	cout << "                                                   ";

	gotoxy(3, 26);
	int courseNum = 0;
	cout << message;
	cin >> courseNum;
	
	return 0;
}


void registration(vector<Course>& c) {

	int courseNum = 0;
	courseNum = selectCourse("(수강 신청) 강의 번호 입력: ");

	const char* filename = "./timetable.txt";
	//내 시간표랑 겹치는지 체크

	int num_myCourse = lineCounter(filename);
	vector<Course> myC;
	myC.resize(num_myCourse);

	freadCourse(filename, myC, num_myCourse);

	bool dupl = 0;
	for (int i = 0; i < num_myCourse; i++) {
		if (c[courseNum].day1 == myC[i].day1 || c[courseNum].day1 == myC[i].day2 || c[courseNum].day2 == myC[i].day1 || c[courseNum].day2 == myC[i].day2) {
			if (!(c[courseNum].endTime <= myC[i].startTime || c[courseNum].startTime >= myC[i].endTime)) {
				dupl = 1;
				break;
			}
		}
	}

	gotoxy(3, 27);
	if (dupl) {
		cout << "※ 이미 수강 신청한 강의와 중복되는 시간대의 강의는 수강 신청할 수 없습니다." << '\n';
		system("pause");
		system("cls");
	}
	else {
		fwriteCoureseInfo(filename, c[courseNum]);
		coutCourse(c[courseNum], 12);
		gotoxy(2, 27);
		cout << "  ";
		gotoxy(3, 28);
		cout << "해당 강의 수강 신청 성공";
		system("pause");
		system("cls");
	}

}
