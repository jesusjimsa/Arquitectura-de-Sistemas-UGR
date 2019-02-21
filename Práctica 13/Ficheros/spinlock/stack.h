#include <mutex>
#include <ostream>
#include "spinlock.h"

template<class T> class stack
{
public:
	struct node
	{
		node* next;
		T data;
	};

	stack(): head(nullptr) {}

	void push(node* n)
	{
		std::lock_guard<spinlock> l(s);
		n->next = head;
		head = n;
	}

	node* pop()
	{
		std::lock_guard<spinlock> l(s);
		node* ret = head;
		if (ret != nullptr)
			head = ret->next;
		return ret;
	}

private:
	spinlock s;
	node* head;
};
