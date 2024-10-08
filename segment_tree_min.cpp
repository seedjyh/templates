
typedef long long LL;

class RangeTree {
public:
    int begin;
    int end;
    LL minVal;
    RangeTree *left, *right;
    RangeTree(int b, int e): begin(b), end(e), minVal(INT_MAX), left(nullptr), right(nullptr){};
    // assurePos 确保pos节点存在。
    void assurePos(int pos) {
        if (begin == end) {
            return;
        }
        int mid = calcMid(begin, end);
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
    void setMinVal(int pos, LL val) {
        this->minVal = min(this->minVal, val);
        if (begin == end) {
            this->minVal = min(this->minVal, val);
            return;
        }
        int mid = calcMid(begin, end);
        // left: [begin, mid]
        // right: [mid + 1, end]
        if (this->left == nullptr) {
            this->left = new RangeTree(begin, mid);
            this->right = new RangeTree(mid + 1, end);
        }
        if (pos <= mid) {
            this->left->setMinVal(pos, val);
        } else {
            this->right->setMinVal(pos, val);
        }
        return;
    }
    // findMinVal 查找某区间里的最大值
    LL findMinVal(int from, int to) const {
        if (this->begin > to || this->end < from) {
            return 0;
        }
        if (left == nullptr) {
            return minVal;
        }
        if (from <= this->begin && this->end <= to) {
            return minVal;
        }
        int mid = calcMid(begin, end);
        if (from > mid) {
            return this->right->findMinVal(from, to);
        } else if (to <= mid) {
            return this->left->findMinVal(from, to);
        } else {
            return min(this->left->findMinVal(from, mid), this->right->findMinVal(mid + 1, to));
        }
    }
    int calcMid(int lo, int hi) const {
        if (lo + hi >= 0) return (lo + hi) / 2;
        else return (lo + hi - 1) / 2;
    }
};
