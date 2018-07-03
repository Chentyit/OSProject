#include<iostream>
using namespace std;

/*
	输入作业内容
	用一个指针指向一个作业方便之后连成一个链表
*/
void Input(Work **work_arr, int n) {
	int len = n;
	for (int i = 0; i < len; i++) {
		work_arr[i] = new Work();
		cout << "请输入第" << i + 1 << "个作业的名字，优先级和时间：" << endl;
		cin >> work_arr[i][0].name;
		cin >> work_arr[i][0].priority_num;
		cin >> work_arr[i][0].time;
		work_arr[i][0].index = i + 1;
		work_arr[i][0].state = 'R';
		work_arr[i][0].next = NULL;
	}
}

/*
	输出作业内容
*/
void Output(Work *head) {
	Work *p = head->next;
	cout << endl;
	cout << "===========================================================================" << endl;
	cout << "||                               作业内容                                ||" << endl;
	cout << "===========================================================================" << endl;
	while (p != NULL) {
		cout << "||    名称：" << p->name << "||	工作时间：" << p->time << "||	优先级：" 
			<< p->priority_num << "||	作业状态：" << p->state << "||	作业索引" << p->index << "||" << endl;
		p = p->next;
	}
	cout << "===========================================================================" << endl;
	cout << endl;
}

/*
	创建作业链表
	方便修改，插入
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
	将修改过的头结点再插入链表中
	改进点：如果有相同优先级的作业，优先调用作业索引最大的作业
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
	执行优先级调用作业
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
	if (p->time == 0) {			//	如果作业工作时间为0则退出链表，并将状态改成E
		p->state = 'E';
		cout << "退出作业信息：" << endl;
		cout << "名称：" << p->name << "	作业状态：" << p->state << endl;
	}
	else {
		InsertByPriority(p, head);
	}
	return head;
}