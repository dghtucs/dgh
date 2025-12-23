#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>


using namespace std;
int k;
int longestCommonSubsequence(const char* str1,const char* str2, int m, int n) {
    
    int dp[2][n + 1];
    memset(dp, 0, sizeof(dp));
    

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if(j-i > k)
            break;
            if(i - j > k)
                j = i-k;
            else{
                if (str1[i - 1] == str2[j - 1]) {
                dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1; 
                } else {
                dp[i % 2][j] = max(dp[(i - 1) % 2][j], dp[i % 2][j - 1]);
            }
            }
        }
    }
   
    return dp[m % 2][n];
}


int main() {
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    
    int n,m;
    // cin >> m >> n >> k;
    scanf("%d %d %d",&m,&n,&k);
    const char* str1 = new char[m];
    const char *str2 =new char[n];
    // cout << "Enter the first string: ";
    // cin >> str1;
    scanf("%s",str1);
    // cout << "Enter the second string: ";
    // cin >> str2;
    scanf("%s",str2);

    int lcs = longestCommonSubsequence(str1, str2,m,n);
    int dis1 = strlen(str1) - lcs;
    int dis2 = strlen(str2) - lcs;
    // cout << lcs.size() << endl;
    // cout << dis1 << endl;
    // cout << dis2 << endl;
    int res = abs(dis1) + abs(dis2) ;
    if(res <= k)
        printf("%d\n",res);
    else
        printf("%d\n",-1);

    return 0;
}

