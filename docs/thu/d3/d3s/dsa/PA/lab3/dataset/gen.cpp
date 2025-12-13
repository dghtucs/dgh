#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace std;

struct Entry {
    string name;
    int val;
};

int main(int argc, char* argv[]) {
    if (argc < 4) return 0;

    int INS = atoi(argv[2]);
    int QRY = atoi(argv[3]);

    vector<Entry> all;

    // 读取 poj.txt
    freopen(argv[1], "r", stdin);

    int id, rank, solved;
    string name;
    while (cin >> id >> name >> rank >> solved) {
        Entry e;
        e.name = name;
        e.val = rank;
        all.push_back(e);
    }

    // 随机打乱
    srand((unsigned)time(NULL));
    random_shuffle(all.begin(), all.end());

    int n = INS;
    if (n > (int)all.size()) n = all.size();

    // 插入操作
    for (int i = 0; i < n; ++i) {
        cout << "0 " << all[i].name << " " << all[i].val << "\n";
    }

    // 查询
    for (int i = 0; i < QRY; ++i) {
        if ((rand() & 1) && n > 0) {
            int idx = rand() % n;
            cout << "1 " << all[idx].name << "\n";
        } else {
            cout << "1 not_exist_" << rand() << "\n";
        }
    }

    cout << "2\n";
    return 0;
}
