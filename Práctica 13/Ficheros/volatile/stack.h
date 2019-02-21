template <typename T> class stack
{
public:
	struct node
	{
		volatile node* next;
		T data;
	};

	stack(): head(nullptr) {}

	void push(node* n)
	{
		n->next = head;
		head = n;
	}

	node* pop()
	{
		node* ret = const_cast<node*>(head);
		if (ret != nullptr)
			head = ret->next;
		return ret;
	}

private:
	volatile node* head;
};

