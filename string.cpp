//
// string.cpp
//
// 字符串基本操作：查找字符；查找子串
//
// Created by jyh on 12月18日.
//

#include <string>
#include <iostream>
using namespace std;

int main() {
    string s = "122344";
    // find 查找字符
    for (char c = '0'; c <= '9'; c++) {
        cout << "find(" << c << "):";
        auto findIte = s.find(c);
        if (findIte == s.npos) {
            cout << "NPOS" << endl;
        } else {
            cout << findIte << endl;
        }
    }
    // find 查找子串
    cout << "find(11):" << ((s.find("11") == s.npos) ? "NPOS" : "FOUND") << endl;
    cout << "find(44):" << s.find("44") << endl;
    // substr 获取子串
    cout << "substr(2,2):" << s.substr(2, 2) << endl;
    return 0;
}
