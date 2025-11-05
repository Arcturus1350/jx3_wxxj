#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int main() {
    int qwq = 100; // 对拍次数
    
    cout << "开始对拍，共 " << qwq << " 次..." << endl;
    cout << "固定n=4，输入格式为不带空格的4位数字" << endl;
    cout << endl;
    
    for (int test = 1; test <= qwq; test++) {
        cout << "测试点 " << test << " / " << qwq << " ... ";
        
        // 生成数据
        system("gen.exe > 1.in");
        
        // 运行std.exe
        system("std.exe < 1.in > 1.out");
        
        // 运行force.exe
        system("force.exe < 1.in > 1.ans");
        
        // 读取结果并比较第一行（总花费）
        ifstream fout("1.out");
        ifstream fans("1.ans");
        
        if (!fout.is_open() || !fans.is_open()) {
            cout << "错误: 无法打开输出文件!" << endl;
            return 1;
        }
        
        long long cost_std, cost_force;
        fout >> cost_std;
        fans >> cost_force;
        
        fout.close();
        fans.close();
        
        if (cost_std != cost_force) {
            cout << "错误!" << endl;
            cout << "std.exe 输出总花费: " << cost_std << endl;
            cout << "force.exe 输出总花费: " << cost_force << endl;
            cout << "测试数据已保存在 1.in" << endl;
            cout << "std.exe 输出保存在 1.out" << endl;
            cout << "force.exe 输出保存在 1.ans" << endl;
            return 1;
        }
        
        cout << "通过! (总花费 = " << cost_std << ")" << endl;
    }
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "所有测试点均通过! 对拍成功!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}

