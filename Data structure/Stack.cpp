// 手写栈 - 快速核心
#define STK_T int
#define STK_SZ 1000

int top;
STK_T stk[STK_SZ];

inline void clr() {
	top = 0;
}
inline void push(STK_T x) {
	stk[top++] = x;
}
inline STK_T pop() {
	return stk[--top];
}
inline bool isFull() {
	return top >= STK_SZ;
}
inline bool isEmpty() {
	return !top;
}

// 手写栈 - 模板类
template<class T>
struct Stack {
	int top, size;
	T *stk;
	Stack(int sz): top(0), size(sz), stk(new T[sz]) {}
	~Stack() {delete[] stk;}
	void clear() {
		top = 0;
	}
	void push(T x) {
		stk[top++] = x;
	}
	T pop() {
		return stk[--top];
	}
	bool isFull() {
		return top >= size;
	}
	bool isEmpty() {
		return !top;
	}
};
