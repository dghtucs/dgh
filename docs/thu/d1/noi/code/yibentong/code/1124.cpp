#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int A[100][100], B[100][100], C[100][100];

    // 输入矩阵A
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> A[i][j];
        }
    }

    // 输入矩阵B
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> B[i][j];
        }
    }

    // 计算矩阵A + B
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // 输出结果矩阵C
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << C[i][j];
            if (j != m - 1) cout << " "; // 控制行内空格
        }
        cout << endl; // 换行
    }

    return 0;
}
