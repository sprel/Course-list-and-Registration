#pragma once
#include <string>

using std::string;

enum Day {
	DEFAULT = 0,
	MON = 1,
	TUE = 2,
	WED = 3,
	THU = 4,
	FRI = 5
	//Mon / Tue / Wed / Thu / Fri
};

struct Course {
	char courseName[40];  //강의명
	char professorName[10];  //교수명
	bool major;  //major or liberal art
	int credit;  //학점
	Day day1;  //요일
	Day day2;  //주 2회 강의인 경우 사용
	int startTime;  //시작시각
	int endTime;  //마침시각
};

Course& cinCourseInfo(Course& c);
void fwriteCoureseInfo(Course& c);
void addCourse();