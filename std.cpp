#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;

const int MAXN = 1005;
const long long INF = 1e18;

int n;
vector<int> p, q;
long long cost[MAXN][MAXN];
long long lx[MAXN], ly[MAXN];
int match[MAXN]; // match[j] 表示q[j]匹配到p中的哪个点
bool visx[MAXN], visy[MAXN];
long long slack[MAXN];
int pre[MAXN];

// 计算环上距离
long long ringDist(int a, int b) {
    long long d = abs(a - b);
    return min(d, 2LL * n - d);
}

// BFS增广
bool bfs(int s) {
    memset(visx, false, sizeof(visx));
    memset(visy, false, sizeof(visy));
    memset(pre, -1, sizeof(pre));
    for (int i = 0; i < n; i++) {
        slack[i] = INF;
    }
    
    int queue[MAXN];
    int head = 0, tail = 0;
    queue[tail++] = s;
    visx[s] = true;
    
    while (true) {
        // 扩展相等子图
        while (head < tail) {
            int x = queue[head++];
            for (int y = 0; y < n; y++) {
                if (visy[y]) continue;
                
                long long delta = lx[x] + ly[y] - cost[x][y];
                
                if (delta == 0) {
                    visy[y] = true;
                    pre[y] = x;
                    
                    if (match[y] == -1) {
                        // 找到增广路
                        while (y != -1) {
                            int last_x = pre[y];
                            int last_y = -1;
                            if (last_x != -1) {
                                for (int j = 0; j < n; j++) {
                                    if (match[j] == last_x) {
                                        last_y = j;
                                        break;
                                    }
                                }
                            }
                            match[y] = pre[y];
                            y = last_y;
                        }
                        return true;
                    } else {
                        int next_x = match[y];
                        visx[next_x] = true;
                        queue[tail++] = next_x;
                    }
                } else if (slack[y] > delta) {
                    slack[y] = delta;
                    pre[y] = x;
                }
            }
        }
        
        // 调整顶标
        long long delta = INF;
        for (int y = 0; y < n; y++) {
            if (!visy[y] && slack[y] < delta) {
                delta = slack[y];
            }
        }
        
        if (delta == INF) return false;
        
        for (int x = 0; x < n; x++) {
            if (visx[x]) lx[x] -= delta;
        }
        for (int y = 0; y < n; y++) {
            if (visy[y]) ly[y] += delta;
            else slack[y] -= delta;
        }
        
        // 将新加入相等子图的边加入
        head = 0;
        tail = 0;
        for (int y = 0; y < n; y++) {
            if (!visy[y] && slack[y] == 0) {
                visy[y] = true;
                
                if (match[y] == -1) {
                    // 找到增广路
                    while (y != -1) {
                        int last_x = pre[y];
                        int last_y = -1;
                        if (last_x != -1) {
                            for (int j = 0; j < n; j++) {
                                if (match[j] == last_x) {
                                    last_y = j;
                                    break;
                                }
                            }
                        }
                        match[y] = pre[y];
                        y = last_y;
                    }
                    return true;
                } else {
                    int next_x = match[y];
                    if (!visx[next_x]) {
                        visx[next_x] = true;
                        queue[tail++] = next_x;
                    }
                }
            }
        }
    }
}

void KM() {
    // 初始化顶标 - 对于最小权匹配，使用负权重
    for (int i = 0; i < n; i++) {
        lx[i] = -INF;
        for (int j = 0; j < n; j++) {
            lx[i] = max(lx[i], cost[i][j]);
        }
    }
    memset(ly, 0, sizeof(ly));
    memset(match, -1, sizeof(match));
    
    // 为每个p[i]寻找匹配
    for (int i = 0; i < n; i++) {
        bfs(i);
    }
}

// 计算点x的对面（环上相距n的点）
int getOpposite(int x) {
    int opposite = x + n;
    if (opposite > 2 * n) {
        opposite -= 2 * n;
    }
    return opposite;
}

// 在环上获取与点x相距dist的点
int getPointAtDistance(int x, int dist) {
    int result = x + dist;
    if (result > 2 * n) result -= 2 * n;
    if (result < 1) result += 2 * n;
    return result;
}

int main() {
    n = 4; // 固定n=4
    
    // 第一行读取m
    int m;
    cin >> m;
    cin.ignore(); // 忽略第一行末尾的换行符
    
    // 第二行读取p，可能带空格也可能不带空格
    string line;
    getline(cin, line);
    
    p.resize(n);
    vector<bool> used(2 * n + 1, false);
    vector<bool> inP(2 * n + 1, false);
    
    // 从字符串中提取所有数字字符
    int idx = 0;
    for (char ch : line) {
        if (ch >= '1' && ch <= '8' && idx < n) {
            p[idx] = ch - '0';
            used[p[idx]] = true;
            inP[p[idx]] = true;
            idx++;
        }
    }
    
    // 构建q集合
    for (int i = 1; i <= 2 * n; i++) {
        if (!used[i]) {
            q.push_back(i);
        }
    }
    
    // 构建代价矩阵（使用负数，因为KM算法求最大权匹配）
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long dist = ringDist(p[i], q[j]);
            cost[i][j] = -(dist * dist); // 负数转换为求最小
        }
    }
    
    // 运行KM算法
    KM();
    
    // 计算总花费
    long long totalCost = 0;
    vector<int> result(n);
    for (int j = 0; j < n; j++) {
        int i = match[j];
        if (i != -1) {
            result[i] = j;
            long long dist = ringDist(p[i], q[j]);
            totalCost += dist * dist;
        }
    }
    
    // 输出最优匹配
    for (int i = 0; i < n; i++) {
        cout << p[i] << " -> " << q[result[i]] << endl;
    }
    cout << endl;
    
    // 构建q的标记数组
    vector<bool> inQ(2 * n + 1, false);
    for (int i = 0; i < n; i++) {
        inQ[q[i]] = true;
    }
    
    // 寻找安全点k
    // k必须在q中，且k的对面必须在p中
    int k = -1;
    
    // 首先检查m是否满足条件
    int m_opposite = getOpposite(m);
    if (inQ[m] && inP[m_opposite]) {
        k = m;
    } else {
        // 在m附近找最近的满足条件的点
        // 按距离从小到大搜索
        for (int dist = 1; dist <= n; dist++) {
            // 尝试顺时针方向
            int candidate1 = getPointAtDistance(m, dist);
            if (inQ[candidate1] && inP[getOpposite(candidate1)]) {
                k = candidate1;
                break;
            }
            
            // 尝试逆时针方向
            int candidate2 = getPointAtDistance(m, -dist);
            if (inQ[candidate2] && inP[getOpposite(candidate2)]) {
                k = candidate2;
                break;
            }
        }
    }
    
    // 输出安全点
    if (k != -1) {
        cout << "安全点:" << k << endl;
    }
    
    return 0;
}

