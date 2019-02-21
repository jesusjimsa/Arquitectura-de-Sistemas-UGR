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
		__transaction_atomic
		{
			n->next = head;
			head = n;
		}
	}

	node* pop()
	{
		__transaction_atomic
		{
			node* ret = head;
			if (ret != nullptr)
				head = ret->next;
			return ret;
		}
	}

private:
	node* head;
};
