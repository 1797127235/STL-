#pragma once
#include<cassert>

namespace tiny{
    template<typename T>
    struct ListNode
    {
        ListNode() :prev(nullptr), next(nullptr), data(T()) {}
        ListNode(const T& value) :prev(nullptr), next(nullptr), data(value) {}
        ListNode<T>* prev;
        ListNode<T>* next;
        T data;
    };

    //原生指针不符合预期，直接重载运算符
    template<class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef ListNode<T> Node;

		typedef ListIterator<T, Ref, Ptr> Self;

		Node* _node;

		ListIterator(Node* node)
			:_node(node)
		{}

		// *it
		//T& operator*()
		Ref operator*()
		{
			return _node->data;
		}
		
		// it->
		//T* operator->()
		Ptr operator->()
		{
			return &_node->data;
		}

		// ++it
		Self& operator++()
		{
			_node = _node->next;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);
			_node = _node->next;

			return tmp;
		}

		Self& operator--()
		{
			_node = _node->prev;
			return *this;
		}

		Self operator--(int)
		{
			Self tmp(*this);
			_node = _node->prev;

			return tmp;
		}

        template<class T_other, class Ref_other, class Ptr_other>
        bool operator!=(const ListIterator<T_other, Ref_other, Ptr_other>& it) const
        {
            return _node != it._node;
        }

        template<class T_other, class Ref_other, class Ptr_other>
        bool operator==(const ListIterator<T_other, Ref_other, Ptr_other>& it) const
        {
            return _node == it._node;
        }
	};


    
    template<typename T>
    class list
    {
    public:
        using Node = ListNode<T>;
        using iterator = ListIterator<T, T&, T*>;
        using const_iterator = ListIterator<T, const T&, const T*>;

        list()
        {
            _head = new Node;
            _head->next = _head;
            _head->prev = _head;
            _head->data = T();
        }

        list(const list<T>& l)
        {
            _head = new Node;
            _head->next = _head;
            _head->prev = _head;
            _head->data = T();
            _size = 0;

            for (Node* cur = l._head->next; cur != l._head; cur = cur->next)
            {
                push_back(cur->data);
            }
        }

        list& operator=(const list<T>& other)
        {
            if(this != &other)
            {
                clear();

                for(const T& item : other)
                {
                    push_back(item);
                }
            }

            return *this;
        }

        ~list()
        {
            clear();
            delete _head;
            _head = nullptr;
        }

        void clear()
        {
            Node* cur = _head->next;
            while (cur != _head)
            {
                Node* next = cur->next;
                delete cur;
                cur = next;
            }
            _head->next = _head;
            _head->prev = _head;
            _size = 0;
        }
        
        iterator begin()
        {
            return iterator(_head->next);
        }

        iterator end()
        {
            return iterator(_head);
        }

        const_iterator begin() const
        {
            return const_iterator(_head->next);
        }

        const_iterator end() const
        {
            return const_iterator(_head);
        }

        const_iterator cbegin() const
        {
            return const_iterator(_head->next);
        }

        const_iterator cend() const
        {
            return const_iterator(_head);
        }

        iterator insert(iterator pos, const T& value)
        {
            assert(pos._node != nullptr);

            Node* newnode = new Node(value);
            Node* cur = pos._node;
            Node* prev = cur->prev;
            newnode->next = cur;
            newnode->prev = prev;
            prev->next = newnode;
            cur->prev = newnode;
            ++_size;
            
            return iterator(newnode);
        }


        iterator erase(iterator pos)
        {
            assert(pos._node != _head);

            Node* cur = pos._node;
            Node* prev = cur->prev;
            Node* next = cur->next;

            prev->next = next;
            next->prev = prev;
            delete cur;

            --_size;

            return iterator(next);
        }

        bool empty() const
        {
            return _size == 0;
        }

        size_t size() const
        {
            return _size;
        }

        T& front()
        {
            assert(!empty());
            return _head->next->data;
        }
        T& back()
        {
            assert(!empty());
            return _head->prev->data;
        }

        const T& front() const
        {
            assert(!empty());
            return _head->next->data;
        }

        const T& back() const
        {
            assert(!empty());
            return _head->prev->data;
        }



        void push_back(const T& value)
        {
            insert(end(), value);
        }

        void push_front(const T& value)
        {
            insert(begin(), value);
        }

        void pop_back()
        {
            assert(!empty());
            erase(--end());
        }

        void pop_front()
        {
            assert(!empty());
            erase(begin());
        }



    private:
        Node* _head;
        size_t _size = 0;

    };
}