/*
 * @Description: 
 * @Version: 
 * @Author: LotusIR
 * @Date: 2020-07-31 14:11:12
 * @LastEditors: LotusIR
 * @LastEditTime: 2020-07-31 14:11:31
 */ 
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5;

char mp[55][55];
int R,C,ans,lnum,rnum,match[maxn],a[55][55],b[55][55];
bool vis[maxn];
vector<int> E[maxn];

bool dfs(int u){
    for(int i = 0; i < E[u].size(); ++i){
        int v = E[u][i];
        if(!vis[v]){
            vis[v]=1;
            if(match[v]==-1 || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int xyl(){
    memset(match,-1,sizeof(match));
    ans = 0;
    for(int i = 0; i < lnum; ++i){
        memset(vis,0,sizeof(vis));
        ans += dfs(i);
    }
    return ans;
}