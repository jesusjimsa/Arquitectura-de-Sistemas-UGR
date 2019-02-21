template <typename T> class stack
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
		do {
			n->next = head;
		} while (!__sync_bool_compare_and_swap(&head, n->next, n));
	}

	node* pop()
	{
		node* n;
		do
			n = head;
		while (n != nullptr && !__sync_bool_compare_and_swap(&head, n, n->next));
		return n;
	}

private:
	node* head;
};

