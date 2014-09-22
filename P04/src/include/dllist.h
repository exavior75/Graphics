struct List
{
	List();
	List(List const& from);
	List& operator=(List const& from);
	~List();
	void push_back(int x);
	void pop_back();
	int back();
	void push_front(int x);
	void pop_front();
	int front();

	struct Node
	{
	public:
		int value;
		Node* next;
		Node* prev;

		Node() {};

		Node(int v, Node* prev, Node* next)
		{
			this->value = v;
			this->next = next;
			this->prev = prev;
		}
	};

	Node head, tail;

	struct iterator 
	{
		Node* node_ptr;

		iterator(){};

		iterator(Node* i)
		{
			this->node_ptr = i;
		}

		int& operator*() const
		{
			return node_ptr->value;
		}

		void operator++()
		{
			this->node_ptr = &(*node_ptr->next);
		}

		iterator operator++(int)
		{
			return iterator(node_ptr->next);
		}

		void operator--()
		{
			this->node_ptr = &(*node_ptr->prev);
		}

		iterator operator--(int)
		{
			return iterator(node_ptr->prev);
		}
	};

	struct iterator;

	iterator begin;
	iterator end;
	void erase(Node* what);
	iterator insert(Node* before, int x);
};