#include<iostream>
#include "FreeTable_FreeArea.h"
#include "Function.h"
using namespace std;

int main() {
	int size;
	cout << "=============================" << endl;
	cout << "||     �����ҵ��Ĵ�С    ||" << endl;
	cout << "=============================" << endl;
	cin >> size;
	Job *job_table = new Job[size];
	FreeArea *area_table = new FreeArea[size];
	int choose;
	while (true) {
		cout << "1������ʼ������" << endl;
		cout << "2���������ڴ�" << endl;
		cout << "3����������ҵ" << endl;
		cout << "4�����˳�" << endl;
		cout << "5����������" << endl;
		cout << "�����������";
		cin >> choose;
		switch (choose) {
		case 1:
			/*
				������ҵ��Ϣ��
				���������˵����
			*/
			Input(job_table, area_table, size);
			Output(job_table, area_table, size);
			break;
		case 2:
			/*
				��ҵ�����ڴ�ռ�
			*/
			Allot(job_table, area_table, size);
			break;
		case 3:
			/*
				�ͷ��ڴ�ռ䣬������ҵ�ź�����ҵ�б��в��Ҷ�Ӧ����ҵ�ţ����ͷ���ҵ��ռ�ڴ�
			*/
			Repeal(job_table, area_table, size);
			break;
		case 4:
			exit(0);
			break;
		case 5:
			/*
				�����ҵ��Ϣ��
				���������˵����
			*/
			Output(job_table, area_table, size);
			break;
		default:
			cout << "�������" << endl;
			break;
		}
	}
	return 0;
}