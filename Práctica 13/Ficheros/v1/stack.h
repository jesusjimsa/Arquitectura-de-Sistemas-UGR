#ifndef stack_h
#define stack_h 1

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
/*		node* n = new node(head, t);*/
/*		head = n;*/
		head = new node(head, t);
	}

	T pop()
	{
		if (!head)
			throw empty();
		node* n = head;
		head = head->next;
		T t = n->data;
		delete n;
		return t;
	}

private:
	node* head;
};

#endif // stack_h

