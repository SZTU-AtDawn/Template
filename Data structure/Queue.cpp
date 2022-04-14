// 手写队列 - 快速核心
#define QUE_T int
#define QUE_SZ 1000

int qH, qT;
QUE_T que[QUE_SZ];

inline void push(QUE_T x) {
	que[++qT >= QUE_SZ ? (qT = 0) : qT] = x;
}
inline QUE_T pop() {
	return que[++qH >= QUE_SZ ? (qH = 0) : qH];
}
inline bool isEmpty() {
	return qH != qT;
}
inline bool isFull() {
	return (qH + QUE_SZ - 1) % QUE_SZ == qT;
}

// 手写队列 - 模板类
template<class T>
struct Queue {
	int head, tail, size;
	T *que;
	Queue(int sz): head(0), tail(0), size(sz), que(new T[sz]) {}
	~Queue() {delete[] que;}
	void push(T x) {
		que[++tail >= size ? (tail = 0) : tail] = x;
	}
	T pop() {
		return que[++head >= size ? (head = 0) : head];
	}
	bool isEmpty() {
		return head != tail;
	}
	bool isFull() {
		return (head + size - 1) % size == tail;
	}
};
