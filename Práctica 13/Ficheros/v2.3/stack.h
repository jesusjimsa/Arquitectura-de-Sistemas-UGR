#ifndef stack_h
#define stack_h 1

#include <chrono>
#include <exception>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

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
		std::chrono::duration<float, std::micro> delay = 50us;
		while (!m.try_lock())
			std::this_thread::sleep_for(delay *= 2);
		head = new node(head, t);
		m.unlock();
	}

	T pop()
	{
		std::chrono::duration<float, std::micro> delay = 50us;
		while (!m.try_lock())
			std::this_thread::sleep_for(delay *= 2);
		if (!head)
		{
			m.unlock();
			throw empty();
		}
		node* n = head;
		head = head->next;
		T t = n->data;
		delete n;
		m.unlock();
		return t;
	}

private:
	std::mutex m;
	node* head;
};

#endif // stack_h

