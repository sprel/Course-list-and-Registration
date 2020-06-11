#pragma once
#include <string>
#include <vector>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

using std::string;
using std::vector;

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
	char classroom[20];  //강의실
};

//Common
void gotoxy(int x, int y);

//Course_AddCourse.cpp
Course& cinCourseInfo(Course& c);
void fwriteCoureseInfo(const char* filename, Course& c);
void addCourse();

//Course_List.cpp
void courseList();
void freadCourse(const char* filename, vector<Course>& c, int& lines);
void coutCourse(Course& c, const int& cNum);
int lineCounter(const char* filename);

//Course_SelecMenu.cpp
int selectMenu(int& pageNum, int& endPage);

//Course_Registration.cpp
void registration(vector<Course>& c);
int selectCourse(const char* message);