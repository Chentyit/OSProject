#include<string>
using namespace std;

struct Work {
	string name;		//	作业名
	Work *next;			//	指向下一个作业的指针
	int time;			//	作业工作时间
	int priority_num;	//	作业优先级
	char state;			//	作业装态
	int index;			//	作业索引
};