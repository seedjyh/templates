# templates

用 C++写的各种 stl 和代码模板。

## C++ STL 用法

代码文件               | 功能
------------------ | --------------------------------------------------
lower_bound.cpp    | `lower_bound`和`upper_bound` 的用法。
map.cpp            | 自定义比较函数的 `map` 和 `multimap`。
priority_queue.cpp | 自定义比较函数的优先队列。
set.cpp            | 自定义比较函数的 `set` 和`multiset`。
sort.cpp           | 自定义比较函数的 `sort`。
string.cpp         | 字符串查找字符、查找子串。
unordered_map.cpp  | 自定义散列函数和判重函数的`unordered_map`和`unordered_multimap`。
unordered_set.cpp  | 自定义散列函数和判重函数的`unordered_set`和`unordered_multiset`。

## 算法模板

代码文件                 | 功能
-------------------- | -------------------------------------------------
combination.cpp      | 组合数计算。包含四种方法：传统加法、朴素乘除、逆元（可取素数模）、阶乘逆元（大素数模，常数时间）。
dijkstra.cpp         | 有向图单源最短路径（Dijkstra）算法。
manacher.cpp         | 最长回文子串（Manacher，马拉车）算法。
topological_sort.cpp | 拓扑排序。
union_find_set.cpp   | 并查集。
top_n.cpp            | 获取第 n 大的数。
bit_tree.cpp         | 树状数组。有两种：单点修改区间查询（不带模和带模）；区间修改单点查询。
segment_tree.cpp     | 线段树（只能添加元素；查询区间最大值）。
segment_tree_2.cpp   | 线段树（查询区间的元素数量和元素和）。
prime.cpp            | 欧拉素数筛。
kruskal.cpp          | 最小生成树（Kruskal算法）。
kmp.cpp | KMP 字符串查找算法。
