#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <queue>
const int inf = 0x3f3f3f3f;
using namespace std;


struct node{
    //数据
    int id;
    //父节点
    node *father = NULL;
}no[100050];

//寻找根节点+路径压缩
node* FindRoot(node *a){
    if(a->father == NULL) return a;
    else return a->father = FindRoot(a->father);
}

//合并树
void Union(node *from,node *to){
    node *f1 = FindRoot(from),*f2 = FindRoot(to);
    if(f1 == f2) return;
    f2->father=f1;
}



int main()
{

}
