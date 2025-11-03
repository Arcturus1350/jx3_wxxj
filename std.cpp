#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    vector<int> p(4);
    
    // 读入4个选中的点
    for (int i = 0; i < 4; i++) {
        cin >> p[i];
    }
    
    // 使用set记录已选中的点，方便查找剩余的点
    set<int> selected(p.begin(), p.end());
    
    // 找出剩余的4个点
    vector<int> q;
    for (int i = 1; i <= 8; i++) {
        if (selected.find(i) == selected.end()) {
            q.push_back(i);
        }
    }
    
    // 对p和q数组排序
    sort(p.begin(), p.end());
    sort(q.begin(), q.end());
    
    // 按顺序输出配对结果
    for (int i = 0; i < 4; i++) {
        cout << p[i] << " -> " << q[i] << endl;
    }
    
    return 0;
}

