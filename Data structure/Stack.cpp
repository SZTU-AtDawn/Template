// 手写栈 - 快速核心
// Author：SNRainiar, from SZTU_AtDawn

#define MAX_N 100000
// 栈顶指针
int top;
// 栈主结构
int stk[MAX_N];

// 清空
inline void clear() {
	top = 0;
}
// 入栈
inline void push(int x) {
	stk[top++] = x;
}
// 出栈
inline int pop() {
	return stk[--top];
}
// 检测空栈
inline bool isEmpty() {
	return !top;
}
// 检测满栈
inline bool isFull() {
	return top >= MAX_N;
}
