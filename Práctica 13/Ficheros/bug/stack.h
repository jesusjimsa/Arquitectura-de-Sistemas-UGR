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
		n->next = head;
		head = n;
	}

	node* pop()
	{
		node* n = head;
		if (head)
			head = head->next;
		return n;
	}

private:
	node* head;
};
