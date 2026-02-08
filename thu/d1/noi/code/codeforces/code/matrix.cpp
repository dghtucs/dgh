#include <iostream>

using namespace std;



int main()
{
    int i, j, val;
    int x, y;
    for(i = 1; i <= 5; i++)
        for(j = 1; j <= 5; j++)
        {
            scanf("%d", &val);
            if(val)
                x = i, y = j;
        }
    printf("%d\n", abs(x - 3) + abs(y - 3));
}