#ifndef stack_h
#define stack_h 1

#include <atomic>
#include <chrono>
#include <exception>
#include <thread>

using namespace std::chrono_literals;

class cerrojo
{
public:
    cerrojo(): cerrado(false) {}

    void adquirir()
    {
        auto delay = 50us;
        while (cerrado.exchange(true))
            std::this_thread::sleep_for(delay *= 2);
    }

    void liberar()
    {
        cerrado = false;
    }

private:
    std::atomic<bool> cerrado;
};

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
		c.adquirir();
		head = new node(head, t);
		c.liberar();
	}

	T pop()
	{
		c.adquirir();
		if (!head)
		{
			c.liberar();
			throw empty();
		}
		node* n = head;
		head = head->next;
		T t = n->data;
		delete n;
		c.liberar();
		return t;
	}

private:
	cerrojo c;
	node* head;
};

#endif // stack_h

