﻿#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 6385)
#pragma once

#include "functionPrototype.h"
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

void freadCourse(const char* filename, vector<Course>& c, int& lines) {
	FILE* fp;
	fp = fopen(filename, "r");
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
			fgetc(fp);
		}
		else {
			c[j].day2 = DEFAULT;
		}


		char time[10] = "";
		i = 0;
		do {
			time[i++] = fgetc(fp);
		} while (time[i - 1] != '|');

		if (time[1] == '~') {
			c[j].startTime = time[0] - 48;
			if (time[3] == '|') {
				c[j].endTime = time[2] - 48;
			}
			else {
				c[j].endTime = 10 + (time[3] - 48);
			}
		}
		else {
			c[j].startTime = 10 + (time[0] - 48);
			if (time[4] == '|') {
				c[j].endTime = time[3] - 48;
			}
			else {
				c[j].endTime = 10 + (time[4] - 48);
			}
		}

		char room[20] = "";
		i = 0;
		while (true) {
			temp = fgetc(fp);
			if (temp == '\n')
				break;
			room[i++] = temp;
		}
		strcpy(c[j].classroom, room);

	}

}

int lineCounter(const char* filename) {
	FILE* fp;
	fp = fopen(filename, "r");
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

	int pos = cNum * 2 + 3;

	gotoxy(2, pos);
	cout << cNum;
	gotoxy(5, pos);
	cout << c.courseName;
	gotoxy(30, pos);
	cout << c.professorName;
	gotoxy(45, pos);
	if (!c.major) {
		cout << "전공";
	}
	else {
		cout << "교양";
	}
	gotoxy(60, pos);
	cout << c.credit;
	gotoxy(70, pos);
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

	if (c.day2 != DEFAULT) {
		cout << "&";
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

	gotoxy(80, pos);
	cout << c.startTime << "~" << c.endTime;
	gotoxy(90, pos);
	cout << c.classroom;
}

void coutItemname(const char* title) {
	gotoxy(40, 1);
	cout << title;

	gotoxy(5, 3);
	cout << "강의명";
	gotoxy(30, 3);
	cout << "교수명";
	gotoxy(45, 3);
	cout << "전공/교양";
	gotoxy(60, 3);
	cout << "학점";
	gotoxy(70, 3);
	cout << "요일";
	gotoxy(80, 3);
	cout << "강의시간";
	gotoxy(90, 3);
	cout << "강의실";
	cout << '\n';
}

void courseList() {

	const char* filename = "./courseList.txt";

	int num_course;
	num_course = lineCounter(filename);

	vector<Course> c;
	c.resize(num_course);

	freadCourse(filename, c, num_course);

	int menu = 0;
	int start = 0;
	bool flag = 1;
	int pageNum = 1;
	int endPage = ((num_course - 1) / 10) + 1;
	while (flag) {
		start = (pageNum - 1) * 10;
		coutItemname("<강의 시간표 조회>");
		for (int i = start; i < start + 10; i++) {
			if (i < num_course) {
				coutCourse(c[i], i + 1);
			}
		}

		menu = selectMenu(pageNum, endPage);
		switch (menu) {
			case 1:
				pageNum++;
				break;
			case 2:
				pageNum--;
				break;
			case 3:
				//수강신청
				registration(c, 26);
				break;
			case 4:
				//바구니에 담기
				putinBaguni(c);
				system("cls");
				break;
			case 5:
				flag = 0;
				break;
		}


	}
	system("cls");
}

