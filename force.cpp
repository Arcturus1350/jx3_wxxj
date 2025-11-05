#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

int n;
vector<int> p, q;

// 计算环上距离
long long ringDist(int a, int b) {
    long long d = abs(a - b);
    return min(d, 2LL * n - d);
}

int main() {
    n = 4; // 固定n=4
    p.resize(n);
    
    // 读取不带空格的字符串，例如"1234"
    string input;
    cin >> input;
    
    vector<bool> used(2 * n + 1, false);
    for (int i = 0; i < n; i++) {
        p[i] = input[i] - '0'; // 将字符转为数字
        used[p[i]] = true;
    }
    
    // 构建q集合
    for (int i = 1; i <= 2 * n; i++) {
        if (!used[i]) {
            q.push_back(i);
        }
    }
    
    // 暴力枚举所有排列
    vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    
    long long minCost = LLONG_MAX;
    vector<int> bestMatch(n);
    
    do {
        long long currentCost = 0;
        for (int i = 0; i < n; i++) {
            long long dist = ringDist(p[i], q[perm[i]]);
            currentCost += dist * dist;
        }
        
        if (currentCost < minCost) {
            minCost = currentCost;
            bestMatch = perm;
        }
    } while (next_permutation(perm.begin(), perm.end()));
    
    // 输出结果
    cout << minCost << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i] << " -> " << q[bestMatch[i]] << endl;
    }
    
    return 0;
}

