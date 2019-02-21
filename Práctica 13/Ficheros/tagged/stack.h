#include <atomic>
#include "tagged.h"

template <class T> class stack
{
public:
	struct node
	{
		tagged::pointer<node> next;
		T data;
	};

	stack(): head(tagged::pointer<node>{nullptr}) {}

	void push(node* n)
	{
		do
			n->next = head;
		while (!head.compare_exchange_weak(n->next, 
		                                   tagged::pointer<node>(n, n->next.tag + 1)));
	}

	node* pop()
	{
/*		tagged::pointer<node> n;*/
/*		do*/
/*			n = head;*/
/*		while (n != nullptr && !head.compare_exchange_weak(n, n->next));*/
/*		return n.ptr;*/

		tagged::pointer<node> n;
		do
			n = head;
		while (n != nullptr && 
		       !head.compare_exchange_weak(n, 
		                                   tagged::pointer<node>(n->next.ptr, n->next.tag + 1)));
		return n;
	}

private:
	std::atomic<tagged::pointer<node>> head;
};
