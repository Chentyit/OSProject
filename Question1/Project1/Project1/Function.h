#include<iostream>
using namespace std;

/*
	������ҵ����
	��һ��ָ��ָ��һ����ҵ����֮������һ������
*/
void Input(Work **work_arr, int n) {
	int len = n;
	for (int i = 0; i < len; i++) {
		work_arr[i] = new Work();
		cout << "�������" << i + 1 << "����ҵ�����֣����ȼ���ʱ�䣺" << endl;
		cin >> work_arr[i][0].name;
		cin >> work_arr[i][0].priority_num;
		cin >> work_arr[i][0].time;
		work_arr[i][0].index = i + 1;
		work_arr[i][0].state = 'R';
		work_arr[i][0].next = NULL;
	}
}

/*
	�����ҵ����
*/
void Output(Work *head) {
	Work *p = head->next;
	cout << endl;
	cout << "===========================================================================" << endl;
	cout << "||                               ��ҵ����                                ||" << endl;
	cout << "===========================================================================" << endl;
	while (p != NULL) {
		cout << "||    ���ƣ�" << p->name << "||	����ʱ�䣺" << p->time << "||	���ȼ���" 
			<< p->priority_num << "||	��ҵ״̬��" << p->state << "||	��ҵ����" << p->index << "||" << endl;
		p = p->next;
	}
	cout << "===========================================================================" << endl;
	cout << endl;
}

/*
	������ҵ����
	�����޸ģ�����
*/
Work* Create_Work_Queue(Work *head, Work **work_arr, int n) {
	Work *buf, *p = new Work();
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((work_arr[i][0].priority_num < work_arr[j][0].priority_num) || (work_arr[i][0].priority_num == work_arr[j][0].priority_num && work_arr[i][0].index < work_arr[j][0].index)) {
				buf = work_arr[i];
				work_arr[i] = work_arr[j];
				work_arr[j] = buf;
			}
		}
	}
	p = head->next = work_arr[0];
	for (int i = 1; i < n; i++) {
		p->next = work_arr[i];
		p = p->next;
	}
	return head;
}

/*
	���޸Ĺ���ͷ����ٲ���������
	�Ľ��㣺�������ͬ���ȼ�����ҵ�����ȵ�����ҵ����������ҵ
*/
void InsertByPriority(Work *work, Work *head) {
	Work *p = head;
	Work *n = head->next;
	while (n && n->next && (n->priority_num > work->priority_num || (n->priority_num == work->priority_num && n->index > work->index))) {
		p = n;
		n = n->next;
	}
	work->next = n;
	p->next = work;
}

/*
	ִ�����ȼ�������ҵ
*/
Work* Do(Work *head) {
	head->next->priority_num--;
	head->next->time--;
	if (head->next->priority_num == 0) {
		head->next->priority_num = 5;
	}
	Work *p = head->next;
	head = new Work();
	head->next = p->next;
	if (p->time == 0) {			//	�����ҵ����ʱ��Ϊ0���˳���������״̬�ĳ�E
		p->state = 'E';
		cout << "�˳���ҵ��Ϣ��" << endl;
		cout << "���ƣ�" << p->name << "	��ҵ״̬��" << p->state << endl;
	}
	else {
		InsertByPriority(p, head);
	}
	return head;
}