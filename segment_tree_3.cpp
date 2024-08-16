// segment tree 3
// 用数组实现的、求区间最小值的线段树

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

typedef long long LL;

// SegmentTreeArrayMinValue 是用数组实现的、求区间最小值的线段树。
//  位置最小是 0
//
class SegmentTreeArrayMinValue {
    class Node {
    public:
        // 位置信息
        int leftChild; // 左儿子的 nodes 下标，-1 表示没有
        int rightChild; // 右儿子的 nodes 下标，-1 表示没有
        int parent; // 父节点的 nodes 下标，-1 表示没有
        int lo; // 左边界，最小是 0
        int hi; // 右边界
        // 业务信息
        bool hasValue; // 自己为根的子树是否有值
        LL minValue; // 自己为根的子树的最小值（仅当 hasValue 为真的时候有效）
        int minValuePos; // 自己为根的子树的最小值的位置（仅当 hasValue 为真的时候有效）
        int getMid() const {
            return (lo + hi) / 2;
        }
        Node(int _lo, int _hi, int _parent):
                leftChild(-1),
                rightChild(-1),
                parent(_parent),
                lo(_lo),
                hi(_hi),
                hasValue(false),
                minValue(0),
                minValuePos(-1){};
    };
    vector<Node> nodes; // 树根永远是 nodes[0]
    int rangeLength; // 线段树能表示的范围是 [0, rangeLength-1]
public:
    explicit SegmentTreeArrayMinValue(int _maxPos) {
        // 区间可以包含的点，最小是 0，最大是 n
        int maxBit = 0;
        for (int bit = 1; bit <= _maxPos; bit <<= 1) {
            if (_maxPos & bit) {
                maxBit = _maxPos;
            }
        }
        // 例如最大需要保存的范围是 0~14
        // 那么 rangeLength 就是 16 (大于 14 的最小的 2 的幂)
        // 节点数就是 32 (16 * 2 == 32)
        rangeLength = maxBit << 1;
        nodes.reserve(rangeLength << 1);
        nodes.emplace_back(0, rangeLength - 1, -1);
    }
    void setValue(int pos, LL value) {
        if (pos >= rangeLength) throw -1;
        int now = 0; // 树根
        while (nodes[now].hi > nodes[now].lo) { // 当前节点并非原子
            int mid = (nodes[now].lo + nodes[now].hi) / 2; // [lo, mid], [mid+1, hi]
            if (pos <= mid) {
                if (nodes[now].leftChild < 0) {
                    nodes[now].leftChild = nodes.size();
                    nodes.emplace_back(Node(nodes[now].lo, mid, now));
                }
                now = nodes[now].leftChild;
            } else {
                if (nodes[now].rightChild < 0) {
                    nodes[now].rightChild = nodes.size();
                    nodes.emplace_back(Node(mid + 1, nodes[now].hi, now));
                }
                now = nodes[now].rightChild;
            }
        }
        // now != pos
        // now 是节点号
        // pos 是原始数轴下标
        if (nodes[now].hasValue) {
            nodes[now].minValue = min(nodes[now].minValue, value);
        } else {
            nodes[now].hasValue = true;
            nodes[now].minValue = value;
            nodes[now].minValuePos = pos;
        }

        // 回溯
        for (LL nowMinValue = nodes[now].minValue, nowMinValuePos = pos; now >= 0; now = nodes[now].parent) {
            if (!nodes[now].hasValue) {
                nodes[now].hasValue = true;
                nodes[now].minValue = nowMinValue;
                nodes[now].minValuePos = nowMinValuePos;
            } else {
                if (nodes[now].minValue < nowMinValue) {
                    break;
                }
                nodes[now].minValue = nowMinValue;
                nodes[now].minValuePos = nowMinValuePos;
            }
        }
    }
    pair<LL, int> getMinValue(int lo, int hi) {
        return getMinValueNode(lo, hi, 0);
    }
private:
    pair<LL, int> getMinValueNode(int lo, int hi, int now) {
        // 获取节点 now 所属范围里，[lo, hi] 的最小值
        // 注：如果没有值，则返回 <LONG_LONG_MAX, -1>
        if (now < 0) return {LONG_LONG_MAX, -1};
        if (lo > hi) return {LONG_LONG_MAX, -1};
        if (nodes[now].hi < lo) return {LONG_LONG_MAX, -1};
        if (nodes[now].lo > hi) return {LONG_LONG_MAX, -1};
        if (nodes[now].lo >= lo && nodes[now].hi <= hi) return {nodes[now].minValue, nodes[now].minValuePos};
        int mid = nodes[now].getMid();
        auto leftResult = getMinValueNode(max(nodes[now].lo, lo), min(hi, mid), nodes[now].leftChild);
        auto rightResult = getMinValueNode((mid + 1, lo), min(hi, nodes[now].hi), nodes[now].rightChild);
        if (leftResult.second < 0 && rightResult.second < 0) return {LONG_LONG_MAX, -1};
        if (leftResult.second < 0) return rightResult;
        if (rightResult.second < 0) return leftResult;
        if (leftResult.first <= rightResult.first) return leftResult;
        return rightResult;
    }
};


bool test(pair<LL, int> actual, pair<LL, int> expect) {
    if (expect != actual) {
        cout << "ERROR! expect=" << expect.second << ", actual=" << actual.second << endl;
        return false;
    }
    return true;
}
int main() {
    SegmentTreeArrayMinValue st(14);
    if (!test(st.getMinValue(3,7), {LONG_LONG_MAX, -1})) return -1;
    if (!test(st.getMinValue(12,14), {LONG_LONG_MAX, -1})) return -1;
    st.setValue(3, 10);
    st.setValue(4, 9);
    st.setValue(6, 12);
    if (!test(st.getMinValue(2,7), {9, 4})) return -1;
    if (!test(st.getMinValue(2,3), {10, 3})) return -1;
    if (!test(st.getMinValue(2,4), {9, 4})) return -1;
    if (!test(st.getMinValue(5,8), {12, 6})) return -1;
}
