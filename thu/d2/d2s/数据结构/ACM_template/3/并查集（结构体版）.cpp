#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <queue>
const int inf = 0x3f3f3f3f;
using namespace std;


struct node{
    //����
    int id;
    //���ڵ�
    node *father = NULL;
}no[100050];

//Ѱ�Ҹ��ڵ�+·��ѹ��
node* FindRoot(node *a){
    if(a->father == NULL) return a;
    else return a->father = FindRoot(a->father);
}

//�ϲ���
void Union(node *from,node *to){
    node *f1 = FindRoot(from),*f2 = FindRoot(to);
    if(f1 == f2) return;
    f2->father=f1;
}



int main()
{

}
