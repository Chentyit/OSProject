#include<iostream>
using namespace std;

/*
	输入作业信息表
	输入空闲区说明表
*/
void Input(Job *job_table, FreeArea *area_table, int size) {
	cout << "=============================" << endl;
	cout << "||        作业表信息       ||" << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < size; i++) {
		cout << "请输入第" << i + 1 << "个作业的信息（编号|起址|长度）：" << endl;
		cin >> job_table[i].jno >> job_table[i].jstart >> job_table[i].jlen;
	}
	cout << "=============================" << endl;
	cout << "||       空闲区说明表      ||" << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < size; i++) {
		cout << "请输入第" << i + 1 << "个区域的信息（起址|长度|标志）：" << endl;
		cin >> area_table[i].fstart >> area_table[i].flen >> area_table[i].fstatus;
	}
	cout << "=============================" << endl;
	cout << "||         输入完成        ||" << endl;
	cout << "=============================" << endl;
}

/*
	输出作业信息表
	输出空闲区说明表
*/
void Output(Job *job_table, FreeArea *area_table, int size) {
	cout << "=============================" << endl;
	cout << "||        作业表信息       ||" << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < size; i++) {
		cout << job_table[i].jno << '\t' << job_table[i].jstart << '\t' << job_table[i].jlen << endl;
	}
	cout << "=============================" << endl;
	cout << "||       空闲区说明表      ||" << endl;
	cout << "=============================" << endl;
	for (int i = 0; i < size; i++) {
		cout << area_table[i].fstart << '\t' << area_table[i].flen << '\t' << area_table[i].fstatus << endl;
	}
}

/*
	作业申请内存空间
*/
void Allot(Job *job_table, FreeArea *area_table, int size) {
	int jno, jlen;
	cin >> jno >> jlen;
	bool flag = false;
	for (int i = 0; i < size; i++) {
		if (area_table[i].fstatus == 'F' && area_table[i].flen >= jlen) {
			/*
				寻找是否存在可用的空间
				如果找到就放入并将flag赋值为true
				如果找不到就将flag赋值为false
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
		cout << "申请内存成功！" << endl;
	}
	else {
		cout << "申请内存失败！" << endl;
	}
}

/*
	将作业表和内存空间排序，使作业和内存空间是按照降序排列，方便之后释放内存空间
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
	释放内存空间，输入作业号后，在作业列表中查找对应的作业号，并释放作业所占内存
	所分情况：
		（1）作业的结束位置与下一个内存的起始位置相同
		（2）作业的起始位置与上一个内存的结束位置相同，且与下一个内存的起始位置不同
		（3）作业的起始位置与上一个内存的结束位置相同，且与下一个内存的起始位置相同
		（4）作业的起始位置与上下两部分内存空间都不相邻
*/
void Repeal(Job *job_table, FreeArea *area_table, int size) {
	int jno;
	Output(job_table, area_table, size);
	cout << "请输入要撤销的作业号:";
	cin >> jno;
	if (jno == 0) {
		cout << "输入错误！";
	}
	else {
		for (int i = 0; i < size; i++) {
			if (job_table[i].jno == jno) {
				int jend = job_table[i].jstart + job_table[i].jlen;
				bool flag = false;
				for (int j = 0; j < size; j++) {
					//	情况1
					if (area_table[j].fstart == jend) {
						area_table[j].fstart -= job_table[i].jlen;
						area_table[j].flen += job_table[i].jlen;
						flag = true;
						break;
					}
					//	情况2
					else if ((area_table[j].fstart + area_table[j].flen == job_table[i].jstart) && area_table[j + 1].flen != 0 && (area_table[j + 1].fstart != jend)) {
						area_table[j].flen += job_table[i].jlen;
						flag = true;
						break;
					}
					//	情况3
					else if ((area_table[j].fstart + area_table[j].flen == job_table[i].jstart) && area_table[j + 1].flen != 0 && (area_table[j + 1].fstart == jend)) {
						area_table[j].flen += (job_table[i].jlen + area_table[j + 1].flen);
						area_table[j + 1].fstart = area_table[j + 1].flen = 0;
						area_table[j + 1].fstatus = 'N';
						flag = true;
						break;
					}
				}
				if (!flag) {
					//	情况4
					for (int j = 0; j < size; j++) {
						if (area_table[j].fstart == 0) {
							area_table[j].fstart = job_table[i].jstart;
							area_table[j].flen = job_table[i].jlen;
							area_table[j].fstatus = 'F';
							break;
						}
					}
				}
				//	将被释放的作业进行清零
				job_table[i].jno = 0;
				job_table[i].jlen = 0;
				job_table[i].jstart = 0;
			}
		}
	}
	Sort(job_table, area_table, size);
}