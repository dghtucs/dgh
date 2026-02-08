/*
 * @Description: 
 * @Version: 
 * @Author: LotusIR
 * @Date: 2019-07-01 22:18:36
 * @LastEditors: LotusIR
 * @LastEditTime: 2020-05-23 14:52:10
 */ 
#include <stdio.h>
#include <iostream>
#include <cstring>
typedef unsigned long long ull;
const int maxn = 11;
const int inf = 0x3f3f3f3f;
using namespace std;
struct trie
{
    trie *nxt[26];
    int cnt;
    trie()
    {
        cnt = 1;
        memset(nxt,0,sizeof(nxt));
    }
};

trie *root;
string S,s1;

void Insert(string s)
{
    trie *p = root;
    for(int i = 0; i < s.length(); ++i){
        int id = s[i] - 'a';
        if(p->nxt[id])
        {
            p = p->nxt[id];
            p -> cnt++;
        }
        else
        {
            p -> nxt[id] = new trie;
            p = p -> nxt[id];
        }
    }
}


int query(string s)
{
    trie *p = root;
    for(int i = 0 ; i < s.length(); ++i)
    {
        id = s[i] - 'a';
        if(p -> nxt[id]) p = p -> nxt[id];
        else return 0;
    }
    return p -> cnt;
}

void Free(trie *p)
{
    for(int i = 0; i < 26; ++i) if(p -> nxt[i] != NULL) Free(p->nxt[i]);
    delete(p);
    p = NULL;
}

int main()
{
    root = new trie;
    while(cin >> S){
        Insert(S);
        cin.get();
        if(cin.peek() == '\n') break;
    }
    while(cin >> s1){
        cout << query(s1) << endl;
    }
    return 0;
}
