#include<iostream>
using namespace std;

int fib(int n,int& prev)
{
    if(n == 0)
    {
        prev = 1;
        return 0;
    }
    else{
        int prePrev;prev = fib(n-1,prePrev);
        return prePrev + prev;
    }
}

int main()
{
    int n = 3000;
    int prev;
    cout<<fib(n,prev)<<endl;
    return 0;
}