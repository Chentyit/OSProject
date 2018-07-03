#include<iostream>
using namespace std;

struct Job {
	int jno;		//作业号
	int jstart;		//作业起始位置
	int jlen;		//作业长度
};

struct FreeArea {
	int fstart;		//内存起始位置
	int flen;		//内存长度
	char fstatus;	//内存表示符
};