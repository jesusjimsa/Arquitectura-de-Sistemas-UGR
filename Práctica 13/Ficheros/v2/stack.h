#ifndef stack_h
#define stack_h 1

#include <exception>
#include <mutex>

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
		std::lock_guard<std::mutex> l(m);
		head = new node(head, t);
	}

	T pop()
	{
		std::lock_guard<std::mutex> l(m);
		if (!head)
			throw empty();
		node* n = head;
		head = head->next;
		T t = n->data;
		delete n;
		return t;
	}

private:
	std::mutex m;
	node* head;
};

#endif // stack_h

