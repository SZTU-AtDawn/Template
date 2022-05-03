# 公共模板库
## 声明
本数据库对所有SZTU_AtDawn的现/前成员开放，也对前成员的队友们开放，欢迎现/前成员继续对仓库进行贡献

如果需要内容搬运，请注明来源为SZTU_AtDawn

届时SZTU_AtDawn正式退役后，本仓库的所有内容将全部贡献给SZTU-ACM，作为SZTU-ACM模板库的一部分
## 规则
1. 请尽量使用**标准**名称命名，首字母大写，用下划线代替空格，写算法全名，如：`Aho_Corasick_Automaton.cpp`、`Segment_Tree.cpp`、`Red_Black_Tree.cpp`
2. 除非是该模板的缩写名称更加常用/更加简明扼要，可以使用缩写，如：`KMP.cpp`、`FFT.cpp`、`SAM.cpp`
3. 如果是数据结构，则打包成结构体，如果是算法，则打包成函数或结构体（模块化）；两者都单独放在.cpp文件中，不需要添加相关上下文代码
4. **必须对引用的外部变量进行说明**，如：`// N为数组长度`
5. 尽可能在关键位置添加注释来解释模板的核心代码
6. 如果新增了模板分类，请创建子文件夹，如：`Graph`、`Math`、`Geometry`
7. 记得更新快速列表（按照字典序）
## 快速列表
按照此格式（md源码）更新表格：`|[这里填文件名](这里填文件的github网址)|这里填模板名|`
### 数据结构（Data structure）
|文件名|中文名称|
|:----|:----|
|[Binary_Index_Tree.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Data%20structure/Binary_Index_Tree.cpp)|树状数组|
|[Queue.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Data%20structure/Queue.cpp)|循环对列|
|[ST.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Data%20structure/ST.cpp)|ST表|
|[Segment_Tree.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Data%20structure/Segment_Tree.cpp)|普通线段树|
|[Stack.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Data%20structure/Stack.cpp)|手写栈|
|[Union_Find.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Data%20structure/Union_Find.cpp)|普通并查集|
|[Weighted_Union_Find.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Data%20structure/Weighted_Union_Find.cpp)|带权并查集|
### 图论（Graph theory）
|文件名|中文名称|
|:----|:----|
|[Dicnic.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Graph%20theory/Dicnic.cpp)|Dicnic算法|
|[Dijkstra.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Graph%20theory/Dijkstra.cpp)|Dijkstra算法|
|[EK.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Graph%20theory/EK.cpp)|EK算法|
|[Floyd.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Graph%20theory/Floyed.cpp)|Floyed算法|
|[Link_Cut_Tree.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Graph%20theory/Link_Cut_Tree.cpp)|动态树|
|[Min_Cost_Max_Flow.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Graph%20theory/Min_Cost_Max_Flow.cpp)|最小费用最大流|
|[Tarjan.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Graph%20theory/Tarjan.cpp)|Tarjan算法|
### 杂项（Misc）
|文件名|中文名称|
|:----|:----|
|[Discrete.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Misc/Discrete.cpp)|离散化|
|[Fast_Read.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/Misc/Fast_Read.cpp)|快读|
### 字符串（String）
|文件名|中文名称|
|:----|:----|
|[ACAM.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/ACAM.cpp)|AC自动机|
|[Extend_KMP.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/Extend_KMP.cpp)|扩展KMP|
|[KMP.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/KMP.cpp)|KMP算法|
|[Manacher.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/Manacher.cpp)|Manacher算法|
|[Minimum_Presentation.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/Minimum_Presentation.cpp)|最小表示法|
|[PAM.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/PAM.cpp)|回文自动机|
|[Persistent_01_Trie.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/Persistent_01_Trie.cpp)|可持久化01Trie|
|[SAM.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/SAM.cpp)|后缀自动机|
|[Sequence_Automaton.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/Sequence_Automaton.cpp)|序列自动机|
|[Trie.cpp](https://github.com/SZTU-AtDawn/Template/blob/main/String/Trie.cpp)|字典树|
