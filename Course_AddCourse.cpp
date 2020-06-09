#define _CRT_SECURE_NO_WARNINGS
#include "functionPrototype.h"
#include <iostream>

using std::cout;
using std::cin;
using std::to_string;

Course& cinCourseInfo(Course& c) {
	//강의명, 학점, 요일, 시간, 전공/교양, 교수명
	
	char cName[40];
	cout << "강의명: ";
	cin >> cName;
	strcpy(c.courseName, cName);

	char pName[10];
	cout << "교수명: ";
	cin >> pName;
	strcpy(c.professorName, pName);

	bool temp;
	cout << "전공/교양 여부 - (전공이면 0, 교양이면 1 입력): ";
	cin >> temp;
	c.major = temp;

	int credit;
	cout << "학점: ";
	cin >> credit;
	c.credit = credit;

	char twotimes;
	cout << "주 2회 강의 여부(y/n): ";
	cin >> twotimes;

	int day1 = 0;
	int day2 = 0;
	if (twotimes == 'y') {
		cout << "첫번째 요일 - 월화수목금(1~5): ";
		cin >> day1;
		cout << "두번째 요일 - 월화수목금(1~5): ";
		cin >> day2;
	}
	else if (twotimes == 'n') {
		cout << "요일 - 월화수목금(1~5): ";
		cin >> day1;
		c.day2 = DEFAULT;
	}
	switch (day1) {
		case 1:
			c.day1 = MON;
			break;
		case 2:
			c.day1 = TUE;
			break;
		case 3:
			c.day1 = WED;
			break;
		case 4:
			c.day1 = THU;
			break;
		case 5:
			c.day1 = FRI;
			break;
	}
	if (day2 != 0) {
		switch (day2) {
			case 1:
				c.day2 = MON;
				break;
			case 2:
				c.day2 = TUE;
				break;
			case 3:
				c.day2 = WED;
				break;
			case 4:
				c.day2 = THU;
				break;
			case 5:
				c.day2 = FRI;
				break;
		}
	}

	int start;
	cout << "시작시각: ";
	cin >> start;
	c.startTime = start;

	int end;
	cout << "마침시각: ";
	cin >> end;
	c.endTime = end;

	char room[20];
	cout << "강의실: ";
	cin >> room;
	strcpy(c.classroom, room);

	return c;
}

void fwriteCoureseInfo(const char* filename, Course& c) {
	FILE* fp;
	fp = fopen(filename, "a");
	if (fp == nullptr) {
		cout << "파일 열기 실패";
		return;
	}

	fputs(c.courseName, fp);
	fputs("|", fp);
	fputs(c.professorName, fp);
	fputs("|", fp);
	if (!c.major) {
		fputc(48, fp);
	}
	else {
		fputc(49, fp);
	}
	fputs("|", fp);
	fputc(c.credit + 48, fp);
	fputs("|", fp);
	switch (c.day1) {
		case MON:
			fputs("월", fp);
			break;
		case TUE:
			fputs("화", fp);
			break;
		case WED:
			fputs("수", fp);
			break;
		case THU:
			fputs("목", fp);
			break;
		case FRI:
			fputs("금", fp);
			break;
	}
	if (c.day2 != DEFAULT)
		fputs("&", fp);
	switch (c.day2) {
		case DEFAULT:
			break;
		case MON:
			fputs("월", fp);
			break;
		case TUE:
			fputs("화", fp);
			break;
		case WED:
			fputs("수", fp);
			break;
		case THU:
			fputs("목", fp);
			break;
		case FRI:
			fputs("금", fp);
			break;
	}
	fputs("|", fp);
	fputs(to_string(c.startTime).c_str(), fp);
	fputs("~", fp);
	fputs(to_string(c.endTime).c_str(), fp);
	fputs("|", fp);
	fputs(c.classroom, fp);
	fputs("\n", fp);

	fclose(fp);
}

void addCourse() {
	Course c;
	c = cinCourseInfo(c);
	const char* filename = "./courseList.txt";

	fwriteCoureseInfo(filename, c);

	cout << "강의 추가 성공" << '\n';
	system("pause");
	system("cls");
}
