#include<iostream>
#include "FreeTable_FreeArea.h"
#include "Function.h"
using namespace std;

int main() {
	int size;
	cout << "=============================" << endl;
	cout << "||     输出作业表的大小    ||" << endl;
	cout << "=============================" << endl;
	cin >> size;
	Job *job_table = new Job[size];
	FreeArea *area_table = new FreeArea[size];
	int choose;
	while (true) {
		cout << "1——初始化数据" << endl;
		cout << "2——申请内存" << endl;
		cout << "3——撤销作业" << endl;
		cout << "4——退出" << endl;
		cout << "5——输出结果" << endl;
		cout << "请输入操作：";
		cin >> choose;
		switch (choose) {
		case 1:
			/*
				输入作业信息表
				输入空闲区说明表
			*/
			Input(job_table, area_table, size);
			Output(job_table, area_table, size);
			break;
		case 2:
			/*
				作业申请内存空间
			*/
			Allot(job_table, area_table, size);
			break;
		case 3:
			/*
				释放内存空间，输入作业号后，在作业列表中查找对应的作业号，并释放作业所占内存
			*/
			Repeal(job_table, area_table, size);
			break;
		case 4:
			exit(0);
			break;
		case 5:
			/*
				输出作业信息表
				输出空闲区说明表
			*/
			Output(job_table, area_table, size);
			break;
		default:
			cout << "输入错误！" << endl;
			break;
		}
	}
	return 0;
}