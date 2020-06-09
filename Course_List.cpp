#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 6385)
#include <iostream>
#include "functionPrototype.h"

using std::cout;

void freadCourse(Course* c, int& lines) {
	FILE* fp;
	fp = fopen("./courseList.txt", "r");
	if (fp == nullptr) {
		cout << "파일 열기 실패";
		return;
	}

	for (size_t j = 0; j < lines; j++) {
		int i = 0;

		char cName[40] = "";
		char temp;
		while (true) {
			temp = fgetc(fp);
			if (temp == '|')
				break;
			cName[i++] = temp;
		}
		strcpy(c[j].courseName, cName);

		char pName[10] = "";
		i = 0;
		while (true) {
			temp = fgetc(fp);
			if (temp == '|')
				break;
			pName[i++] = temp;
		}
		strcpy(c[j].professorName, pName);

		c[j].major = fgetc(fp) - 48;
		fgetc(fp);
		c[j].credit = fgetc(fp) - 48;
		fgetc(fp);

		char day[3] = "";

		fgets(day, 3, fp);
		if (strcmp(day, "월") == 0) {
			c[j].day1 = MON;
		}
		if (strcmp(day, "화") == 0) {
			c[j].day1 = TUE;
		}
		if (strcmp(day, "수") == 0) {
			c[j].day1 = WED;
		}
		if (strcmp(day, "목") == 0) {
			c[j].day1 = THU;
		}
		if (strcmp(day, "금") == 0) {
			c[j].day1 = FRI;
		}
		temp = fgetc(fp);
		if (temp == '&') {
			fgets(day, 3, fp);
			if (strcmp(day, "월") == 0) {
				c[j].day2 = MON;
			}
			if (strcmp(day, "화") == 0) {
				c[j].day2 = TUE;
			}
			if (strcmp(day, "수") == 0) {
				c[j].day2 = WED;
			}
			if (strcmp(day, "목") == 0) {
				c[j].day2 = THU;
			}
			if (strcmp(day, "금") == 0) {
				c[j].day2 = FRI;
			}
		}
		else {
			c[j].day2 = DEFAULT;
		}

		char time[10];
		i = 0;
		do {
			time[i++] = fgetc(fp);
		} while (time[i - 1] != '\n');

		if (time[1] == '~') {
			c[j].startTime = time[0] - 48;
			if (time[3] == '\n') {
				c[j].endTime = time[2] - 48;
			}
			else {
				c[j].endTime = 10 + (time[3] - 48);
			}
		}
		else {
			c[j].startTime = 10 + (time[0] - 48);
			if (time[4] == '\n') {
				c[j].endTime = time[3] - 48;
			}
			else {
				c[j].endTime = 10 + (time[4] - 48);
			}
		}

	}

}

int lineCounter() {
	FILE* fp;
	fp = fopen("./courseList.txt", "r");
	if (fp == nullptr) {
		cout << "파일 열기 실패";
		return -1;
	}

	int count = 0;
	char temp;
	do {
		temp = fgetc(fp);
		if (temp == '\n')
			count++;
	} while (!feof(fp));

	return count;
}

void coutCourse(Course& c, const int& cNum) {

	gotoxy(5, 3 + cNum);
	cout << c.courseName << " ";
	gotoxy(26, 3 + cNum);
	cout << c.professorName << " ";
	gotoxy(37, 3 + cNum);
	if (!c.major) {
		cout << "전공 ";
	}
	else {
		cout << "교양 ";
	}
	gotoxy(47, 3 + cNum);
	cout << c.credit << " ";
	gotoxy(52, 3 + cNum);
	switch (c.day1) {
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
	cout << " ";
	if (c.day2 != DEFAULT) {
		cout << "&" << c.day2 << " ";
	}
	else {
		switch (c.day2) {
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
	}
	gotoxy(58, 3 + cNum);
	cout << c.startTime << "~" << c.endTime << '\n';
}

void courseList() {
	Course* c;

	int courseNum;
	courseNum = lineCounter();

	c = new Course[courseNum];

	freadCourse(c, courseNum);

	gotoxy(20, 1);
	cout << "<강의 시간표 조회>";

	gotoxy(5, 3);
	cout << "강의명  ";
	gotoxy(26, 3);
	cout << "교수명  ";
	gotoxy(37, 3);
	cout << "전공/교양  ";
	gotoxy(47, 3);
	cout << "학점  ";
	gotoxy(52, 3);
	cout << "요일  ";
	gotoxy(58, 3);
	cout << "강의시간  ";
	cout << '\n';

	for (int i = 0; i < courseNum; i++) {
		coutCourse(c[i], i + 1);
	}

	system("pause");
	system("cls");

	delete[] c;
}
