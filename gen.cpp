#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
    // 使用当前时间作为随机种子
    random_device rd;
    mt19937 gen(rd());
    
    // 固定n=4
    int n = 4;
    
    // 生成集合s = {1, 2, ..., 2n} = {1, 2, 3, 4, 5, 6, 7, 8}
    vector<int> s(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        s[i] = i + 1;
    }
    
    // 随机打乱
    shuffle(s.begin(), s.end(), gen);
    
    // 前n个作为集合p
    vector<int> p(s.begin(), s.begin() + n);
    
    // 输出不带空格的格式，例如"1234"
    for (int i = 0; i < n; i++) {
        cout << p[i];
    }
    cout << endl;
    
    return 0;
}

