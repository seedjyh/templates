// 线段树（添加key-value；求key区间最大value）
// 原题：https://leetcode.cn/contest/weekly-contest-310/problems/longest-increasing-subsequence-ii/

class RangeTree {
public:
    int begin;
    int end;
    int maxVal;
    RangeTree *left, *right;
    RangeTree(int b, int e): begin(b), end(e), maxVal(0), left(nullptr), right(nullptr){};
    // assurePos 确保pos节点存在。
    void assurePos(int pos) {
        if (begin == end) {
            return;
        }
        int mid = (begin + end) / 2;
        // left: [begin, mid]
        // right: [mid + 1, end]
        if (this->left == nullptr) {
            this->left = new RangeTree(begin, mid);
        }
        if (this->right == nullptr) {
            this->right = new RangeTree(mid + 1, end);
        }
        if (pos <= mid) {
            this->left->assurePos(pos);
        } else {
            this->right->assurePos(pos);
        }
    }
    // 仅修改pos节点的值，以及父节点、祖先节点等。
    void setMaxVal(int pos, int val) {
        if (begin == end) {
            this->maxVal = max(this->maxVal, val);
            return;
        }
        int mid = (begin + end) / 2;
        // left: [begin, mid]
        // right: [mid + 1, end]
        if (pos <= mid) {
            this->left->setMaxVal(pos, val);
        } else {
            this->right->setMaxVal(pos, val);
        }
        this->maxVal = max(this->left->maxVal, this->right->maxVal);
        return;
    }
    // findMaxVal 查找某区间里的最大值
    int findMaxVal(int from, int to) const {
        if (this->begin > to || this->end < from) {
            return 0;
        }
        if (left == nullptr) {
            return maxVal;
        }
        if (from <= this->begin && this->end <= to) {
            return maxVal;
        }
        int mid = (begin + end) / 2;
        if (from > mid) {
            return this->right->findMaxVal(from, to);
        } else if (to <= mid) {
            return this->left->findMaxVal(from, to);
        } else {
            return max(this->left->findMaxVal(from, mid), this->right->findMaxVal(mid + 1, to));
        }
    }
};
