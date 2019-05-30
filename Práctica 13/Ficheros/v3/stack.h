#ifndef stack_h
#define stack_h 1

#include <atomic>
#include <exception>

template<class T> class stack
{
public:
	struct node
	{
		node(node* n, const T& d): next(n), data(d) {}
		node* next;
		T data;
	};

	stack(): head(nullptr) {}

	struct empty: std::exception {};

	void push(const T& t)
	{
		node* n = new node(head, t);
		while (!head.compare_exchange_weak(n->next, n))
			n->next = head;
	}

	T pop()
	{
		node* n;
		do {
			if (!head)
				throw empty();
			n = head;
		} while (!head.compare_exchange_weak(n, n->next));
		T t = n->data;
		delete n;
		return t;
	}

private:
	std::atomic<node*> head;
};

#endif // stack_h

