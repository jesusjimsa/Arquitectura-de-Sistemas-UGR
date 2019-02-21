#include <mutex>
#include <ostream>

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
		std::lock_guard<std::mutex> l(m);
		n->next = head;
		head = n;
	}

	node* pop()
	{
		std::lock_guard<std::mutex> l(m);
		node* ret = head;
		if (ret != nullptr)
			head = ret->next;
		return ret;
	}

private:
	std::mutex m;
	node* head;
};
