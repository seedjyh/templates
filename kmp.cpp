//
// Created by jyh on 2024/1/14.
//

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class KMP {
    vector<int> prefixFunction(const string &s) {
        int n = (int)s.length();
        vector<int> pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }
public:
    vector<int> findOccurrences(const string &text, const string &pattern) {
        string cur = pattern + '#' + text;
        int sz1 = text.size(), sz2 = pattern.size();
        vector<int> v;
        vector<int> lps = prefixFunction(cur);
        for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
            if (lps[i] == sz2) v.push_back(i - 2 * sz2);
        }
        return v;
    }
};

int main() {
    string s = "abccaabcabcac";
    string pattern = "abc";
    for (auto x : KMP().findOccurrences(s, pattern)) {
        cout << x << endl;
    }
    return 0;
}
