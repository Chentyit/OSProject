#include<iostream>
#include "Work.h"
#include "Function.h"
using namespace std;

int main() {
	int n;
	cout << "��������ҵ����:";
	cin >> n;
	Work **work_arr = new Work*[n];		//	����һ����СΪn��ָ�����飬��ָ������ָ��ÿһ����ҵ������֮��Ĳ���
	Input(work_arr, n);
	Work *head = new Work();			//	����ͷָ��
	head = Create_Work_Queue(head, work_arr, n);
	Output(head);
	while (head->next) {
		head = Do(head);				//	ִ�����ȼ�������ҵ
		Output(head);
	}
	return 0;
}