#include<iostream>
using namespace std;

/*
	������ҵ��Ϣ��
	���������˵����
*/
void Input(Job *job_table, FreeArea *area_table, int size) {
	cout << "=============================" << endl;
	cout << "||        ��ҵ����Ϣ       ||" << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < size; i++) {
		cout << "�������" << i + 1 << "����ҵ����Ϣ�����|��ַ|���ȣ���" << endl;
		cin >> job_table[i].jno >> job_table[i].jstart >> job_table[i].jlen;
	}
	cout << "=============================" << endl;
	cout << "||       ������˵����      ||" << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < size; i++) {
		cout << "�������" << i + 1 << "���������Ϣ����ַ|����|��־����" << endl;
		cin >> area_table[i].fstart >> area_table[i].flen >> area_table[i].fstatus;
	}
	cout << "=============================" << endl;
	cout << "||         �������        ||" << endl;
	cout << "=============================" << endl;
}

/*
	�����ҵ��Ϣ��
	���������˵����
*/
void Output(Job *job_table, FreeArea *area_table, int size) {
	cout << "=============================" << endl;
	cout << "||        ��ҵ����Ϣ       ||" << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < size; i++) {
		cout << job_table[i].jno << '\t' << job_table[i].jstart << '\t' << job_table[i].jlen << endl;
	}
	cout << "=============================" << endl;
	cout << "||       ������˵����      ||" << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < size; i++) {
		cout << area_table[i].fstart << '\t' << area_table[i].flen << '\t' << area_table[i].fstatus << endl;
	}
}

/*
	��ҵ�����ڴ�ռ�
*/
void Allot(Job *job_table, FreeArea *area_table, int size) {
	int jno, jlen;
	cin >> jno >> jlen;
	bool flag = false;
	for (int i = 0; i < size; i++) {
		if (area_table[i].fstatus == 'F' && area_table[i].flen >= jlen) {
			/*
				Ѱ���Ƿ���ڿ��õĿռ�
				����ҵ��ͷ��벢��flag��ֵΪtrue
				����Ҳ����ͽ�flag��ֵΪfalse
			*/
			for (int j = 0; j < size; j++) {
				if (!job_table[j].jno) {
					job_table[j].jno = jno;
					job_table[j].jstart = area_table[i].fstart;
					job_table[j].jlen = jlen;
					break;
				}
			}
			area_table[i].fstart += jlen;
			area_table[i].flen -= jlen;
			if (area_table[i].flen == 0) {
				area_table[i].fstart = 0;
				area_table[i].fstatus = ' ';
			}
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "�����ڴ�ɹ���" << endl;
	}
	else {
		cout << "�����ڴ�ʧ�ܣ�" << endl;
	}
}

/*
	����ҵ����ڴ�ռ�����ʹ��ҵ���ڴ�ռ��ǰ��ս������У�����֮���ͷ��ڴ�ռ�
*/
void Sort(Job *job_table, FreeArea *area_table, int size) {
	Job job_buf;
	FreeArea area_buf;
	for (int i = 0; i < size; i++) {
		if (job_table[i].jno == 0) {
			job_table[i].jno = 65535;
		}
		if (area_table[i].fstart == 0) {
			area_table[i].fstart = 65535;
		}
	}
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (job_table[i].jno > job_table[j].jno) {
				job_buf = job_table[i];
				job_table[i] = job_table[j];
				job_table[j] = job_buf;
			}
			if (area_table[i].fstart > area_table[j].fstart) {
				area_buf = area_table[i];
				area_table[i] = area_table[j];
				area_table[j] = area_buf;
			}
		}
	}
	for (int i = 0; i < size; i++) {
		if (job_table[i].jno == 65535) {
			job_table[i].jno = 0;
		}
		if (area_table[i].fstart == 65535) {
			area_table[i].fstart = 0;
		}
	}
}

/*
	�ͷ��ڴ�ռ䣬������ҵ�ź�����ҵ�б��в��Ҷ�Ӧ����ҵ�ţ����ͷ���ҵ��ռ�ڴ�
	���������
		��1����ҵ�Ľ���λ������һ���ڴ����ʼλ����ͬ
		��2����ҵ����ʼλ������һ���ڴ�Ľ���λ����ͬ��������һ���ڴ����ʼλ�ò�ͬ
		��3����ҵ����ʼλ������һ���ڴ�Ľ���λ����ͬ��������һ���ڴ����ʼλ����ͬ
		��4����ҵ����ʼλ���������������ڴ�ռ䶼������
*/
void Repeal(Job *job_table, FreeArea *area_table, int size) {
	int jno;
	Output(job_table, area_table, size);
	cout << "������Ҫ��������ҵ��:";
	cin >> jno;
	if (jno == 0) {
		cout << "�������";
	}
	else {
		for (int i = 0; i < size; i++) {
			if (job_table[i].jno == jno) {
				int jend = job_table[i].jstart + job_table[i].jlen;
				bool flag = false;
				for (int j = 0; j < size; j++) {
					//	���1
					if (area_table[j].fstart == jend) {
						area_table[j].fstart -= job_table[i].jlen;
						area_table[j].flen += job_table[i].jlen;
						flag = true;
						break;
					}
					//	���2
					else if ((area_table[j].fstart + area_table[j].flen == job_table[i].jstart) && area_table[j + 1].flen != 0 && (area_table[j + 1].fstart != jend)) {
						area_table[j].flen += job_table[i].jlen;
						flag = true;
						break;
					}
					//	���3
					else if ((area_table[j].fstart + area_table[j].flen == job_table[i].jstart) && area_table[j + 1].flen != 0 && (area_table[j + 1].fstart == jend)) {
						area_table[j].flen += (job_table[i].jlen + area_table[j + 1].flen);
						area_table[j + 1].fstart = area_table[j + 1].flen = 0;
						area_table[j + 1].fstatus = 'N';
						flag = true;
						break;
					}
				}
				if (!flag) {
					//	���4
					for (int j = 0; j < size; j++) {
						if (area_table[j].fstart == 0) {
							area_table[j].fstart = job_table[i].jstart;
							area_table[j].flen = job_table[i].jlen;
							area_table[j].fstatus = 'F';
							break;
						}
					}
				}
				//	�����ͷŵ���ҵ��������
				job_table[i].jno = 0;
				job_table[i].jlen = 0;
				job_table[i].jstart = 0;
			}
		}
	}
	Sort(job_table, area_table, size);
}