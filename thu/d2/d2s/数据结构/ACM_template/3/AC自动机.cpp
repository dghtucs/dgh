#include <bits/stdc++.h>
typedef unsigned long long ull;
const int P = 1e9+7;
const int maxn = 5e5 + 200;
const int inf = 0x3f3f3f3f;
using namespace std;
struct trie
{
    trie *nxt[26];
    trie *fail;
    int cnt;
    int flag;
    trie()
    {
        cnt = 1;
        flag = 0;
        fail = NULL;
        memset(nxt,NULL,sizeof(nxt));
    }
};

trie *root;
int T,N,Q;
char S[maxn],s1[maxn],s2[maxn];

void Insert(char *s)
{
    trie *p = root;
    int len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        int id = s[i] - 'a';
        if(p->nxt[id] != NULL)
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
    p -> flag++;
}

void getFail()
{
    queue<trie*> q;
    q.push(root);
    trie *temp,*p;
    while(!q.empty())
    {
        p = q.front();
        q.pop();
        for(int i = 0; i < 26; ++i)
        {
            if(p -> nxt[i])
            {
                if(p == root)
                    p -> nxt[i] -> fail = root;
                else
                {
                    temp = p -> fail;
                    while(temp)
                    {
                        if(temp -> nxt[i])
                        {
                            p -> nxt[i] -> fail = temp -> nxt[i];
                            break;
                        }
                        temp = temp -> fail;
                    }
                    if(!temp) p -> nxt[i] -> fail = root;
                }
                q.push(p -> nxt[i]);
            }
        }
    }
}

int query(char* s)
{
    int i = 0,res = 0;
    trie *p = root;
    trie *temp;
    while(s[i])
    {
        int id = s[i] - 'a';
        while(!p -> nxt[id] && p != root) p = p -> fail;
        p = p -> nxt[id];
        if(p == NULL) p = root;
        temp = p;
        while(temp != root && temp -> flag != 0)
        {
            res += temp -> flag;
            temp -> flag = 0;
            temp = temp -> fail;
        }
        i++;
    }
    return res;
}

void Free(trie *p)
{
    for(int i = 0; i < 26; ++i)
    {
        if(p -> nxt[i] != NULL) Free(p->nxt[i]);
    }
    delete(p);
    p = NULL;
}

int main()
{
    scanf("%d",&T);
    while(T--){
        root = new trie;
        scanf("%d",&N);
        while(N--)
        {
            scanf("%s",S);
            Insert(S);
        }
        getFail();
        scanf("%s",s1);
        printf("%d\n",query(s1));
        Free(root);
    }
}
