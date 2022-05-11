// 循环队列 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100000
// 队首指针、队尾指针
int qH, qT;
// 循环队列主结构
int que[MAX_N];

// 清空
inline void clear() {
	qH = qT = 0;
}
// 入队
inline void push(int x) {
	que[(++qT) %= MAX_N] = x;
}
// 出队
inline int pop() {
	return que[(++qH) %= MAX_N];
}
// 检测空队列
inline bool isEmpty() {
	return qH != qT;
}
// 检测满队列
inline bool isFull() {
	return (qT + 1) % MAX_N == qH;
}
