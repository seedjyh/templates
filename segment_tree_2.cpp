// 线段树（添加key-value；求key区间的节点数量和总和）
// 原题：https://atcoder.jp/contests/jsc2021/tasks/jsc2021_f

// RangeTree 线段树。同一个位置可以插入多个值。
template<typename VALUE>
class RangeTree {
    class Node {
    public:
        Node(VALUE _left, VALUE _right) : left(_left), right(_right), count(0), sum(0), leftChild(nullptr),
                                      rightChild(nullptr) {};

        Node(VALUE _left, VALUE _right, VALUE _count, VALUE _sum) : left(_left), right(_right), count(_count), sum(_sum),
                                                            leftChild(nullptr), rightChild(nullptr) {};
        VALUE left, right, count;
        VALUE sum;
        Node *leftChild, *rightChild;
    };

    Node *root;
public:
    explicit RangeTree(VALUE left = 0, VALUE right = 1e9) : root(new Node(left, right)) {};

    // insert 在位置 pos 插入一个值 value。
    void insert(VALUE pos, VALUE value) {
        insert(root, pos, value);
    }

    // remove 移除位置 pos 值为 value 的点
    void remove(VALUE pos, VALUE value) {
        remove(root, pos, value);
    }

    // count 计算区间 [left, right] 的点的个数。
    VALUE count(VALUE left, VALUE right) const {
        return count(root, left, right);
    }

    // sum 计算区间 [left, right] 的点的值的和。
    VALUE sum(VALUE left, VALUE right) const {
        return sum(root, left, right);
    }

private:
    static void insert(Node *root, VALUE pos, VALUE value) {
        if (root->left == pos && root->right == pos) {
            root->count++;
            root->sum += value;
            return;
        }
        VALUE mid = (root->left + root->right) / 2;
        if (root->leftChild == nullptr) {
            root->leftChild = new Node(root->left, mid);
        }
        if (root->rightChild == nullptr) {
            root->rightChild = new Node(mid + 1, root->right);
        }
        if (pos <= mid) {
            insert(root->leftChild, pos, value);
            root->count++;
            root->sum += value;
        } else {
            insert(root->rightChild, pos, value);
            root->count++;
            root->sum += value;
        }
    }

    // remove 移除 root为树根的子树里，位置pos，值为value的点。并返回被移除的值的value。需要保证pos有值。
    static void remove(Node *root, VALUE pos, LL value) {
        if (root->count == 0) {
            throw -1;
        }
        if (root->left == pos && root->right == pos) {
            root->count--;
            root->sum -= value;
            return;
        }
        VALUE mid = (root->left + root->right) / 2;
        if (pos <= mid) {
            remove(root->leftChild, pos, value);
            root->sum -= value;
            root->count--;
            return;
        } else {
            remove(root->rightChild, pos, value);
            root->sum -= value;
            root->count--;
            return;
        }
    }

    static VALUE count(const Node *root, VALUE left, VALUE right) {
        if (root == nullptr) {
            return 0;
        }
        if (left > root->right || right < root->left) {
            return 0;
        }
        if (left <= root->left && right >= root->right) {
            return root->count;
        }
        return count(root->leftChild, max(root->left, left), min(root->right, right)) +
               count(root->rightChild, max(root->left, left), min(root->right, right));
    }

    static VALUE sum(const Node *root, VALUE left, VALUE right) {
        if (root == nullptr) {
            return 0;
        }
        if (left > root->right || right < root->left) {
            return 0;
        }
        if (left <= root->left && right >= root->right) {
            return root->sum;
        }
        return sum(root->leftChild, max(root->left, left), min(root->right, right)) +
               sum(root->rightChild, max(root->left, left), min(root->right, right));
    }
};
