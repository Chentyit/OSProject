#include<iostream>
#include "Work.h"
#include "Function.h"
using namespace std;

int main() {
	int n;
	cout << "请输入作业数量:";
	cin >> n;
	Work **work_arr = new Work*[n];		//	申请一个大小为n的指针数组，用指针数组指向每一个作业，方便之后的操作
	Input(work_arr, n);
	Work *head = new Work();			//	创建头指针
	head = Create_Work_Queue(head, work_arr, n);
	Output(head);
	while (head->next) {
		head = Do(head);				//	执行优先级调度作业
		Output(head);
	}
	return 0;
}