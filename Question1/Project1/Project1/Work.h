#include<string>
using namespace std;

struct Work {
	string name;		//	��ҵ��
	Work *next;			//	ָ����һ����ҵ��ָ��
	int time;			//	��ҵ����ʱ��
	int priority_num;	//	��ҵ���ȼ�
	char state;			//	��ҵװ̬
	int index;			//	��ҵ����
};