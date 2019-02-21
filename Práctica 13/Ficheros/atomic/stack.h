#include <atomic>

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
		do
			n->next = head;
		while (!head.compare_exchange_weak(n->next, n));
	}

	node* pop()
	{
		node* n;
		do
			n = head;
		while (n != nullptr && !head.compare_exchange_weak(n, n->next));
		return n;
	}

private:
	std::atomic<node*> head;
};
