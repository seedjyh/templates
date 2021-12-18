//
// manacher.cpp
//
// 马拉车（manacher）算法：最长回文子串
//
// Created by jyh on 12月19日.
//

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// 使用方法
// auto ss = Manacher::addSharp(raw);
// auto p = Manacher::calcP(ss);
class Manacher {
public:
    // addSharp在raw的开头、末尾、每一个字符之间，都加入一个'#'。目的是将字符串的长度确定为奇数。
    static string addSharp(const string &raw) {
        stringstream ss;
        ss << '#';
        for (auto c : raw) {
            ss << c << '#';
        }
        return ss.str();
    }
    // calcP返回一个s.size()的数组，保存着从s[i]为中心开始扩展的最大回文串半径（中心本身不算在半径里）。
    // 例如s="abac"，返回数组是{0, 1, 0, 0}。
    static vector<int> calcP(const string &s) {
        vector<int> p(s.size());
        int bestCenter = 0; // bestCenter是从j=0~i-1的所有中心里，最大回文串的右侧`j+p[j]`最靠右的那个中心。
        p[0] = 0;
        for (int i = 1; i < s.size(); i++) {
            if (i < bestCenter + p[bestCenter]) {
                int right = min(
                        bestCenter + p[bestCenter],
                        i + p[bestCenter - (i - bestCenter)]
                );
                p[i] = right - i;
            }
            p[i] = expand(i, p[i], s);
            if (bestCenter + p[bestCenter] < i + p[i]) {
                bestCenter = i;
            }
        }
        return p;
    }
    static int expand(int center, int nowRadius, const string &s) {
        for (int left = center - nowRadius, right = center + nowRadius;
             left >= 0 && right < s.size() && s[left] == s[right];
             nowRadius++, left--, right++);
        return nowRadius - 1;
    }
};

int main() {
    string raw = "1123631";
    Manacher m;
    auto sharped = m.addSharp(raw);
    cout << sharped << endl;
    for (auto x : m.calcP(sharped)) {
        cout << x << endl;
    }
    return 0;
}
