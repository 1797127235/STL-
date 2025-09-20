#pragma once
#include <cstddef>   
#include <algorithm>   

namespace tiny {
    template<typename T>
    class vector
    {
    public:
        using Iterator = T*;
        using ConstIterator = const T*;

        Iterator begin() { return _start; }
        Iterator end() { return _finish; }
        ConstIterator cbegin() const { return _start; }
        ConstIterator cend() const { return _finish; }

        vector() = default;

        vector(const vector<T>& v)
        {
            size_t n = v.size();
            if (n > 0)
            {
                reserve(n);
                for (size_t i = 0; i < n; ++i)
                {
                    new (_start + i) T(v._start[i]);  // 使用 placement new 构造元素
                }
                _finish = _start + n;
                _endorstorage = _start + n;
            }
        }

        ~vector()
        {
            // 手动调用每个元素的析构函数
            for (Iterator ptr = _start; ptr != _finish; ++ptr) {
                ptr->~T();  // 显式调用析构函数
            }
            delete[] _start;  // 释放内存
            _start = _finish = _endorstorage = nullptr;
        }


        size_t size() const
        {
            return _finish - _start;
        }

        size_t capacity() const
        {
            return _endorstorage - _start;
        }


        //不要在用傻逼memcpy了
        void reserve(size_t n)
        {
            if (n > capacity())
            {
                T* tmp = new T[n];  // 分配新的内存

                if (_start != nullptr) {
                    // 使用 std::copy 来正确拷贝元素
                    std::copy(_start, _finish, tmp);  // 拷贝现有元素
                }

                size_t oldsize = size();
                
                for(size_t i = 0; i < oldsize; ++i)
                {
                    _start[i].~T();  // 显式调用析构函数
                }


                delete[] _start;  // 释放原内存

                _start = tmp;  // 更新 _start 指针
                _finish = _start + oldsize;  // 更新 _finish 指针
                _endorstorage = _start + n;  // 更新 _endorstorage 指针
            }
        }


        void resize(size_t n, const T& value = T())
        {
            if(n > size())
            {
                reserve(n);
                while(_finish < _start + n)
                {
                    *_finish = value;
                    ++_finish;
                }
            }
            else //删除
            {
                _finish = _start + n;
            }
        }

        void push_back(const T& value)
        {
            if(_finish == nullptr)
            {
                size_t newcapacity = 4;
                _start = new T[newcapacity];
                _finish = _start;
                _endorstorage = _start + newcapacity;
            }

            if(_finish == _endorstorage)
            {
                size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
                reserve(newcapacity);
            }
            *_finish = value;
            ++_finish;
        }

        void insert(Iterator pos, const T& value)
        {
            assert(pos >= _start && pos <= _finish);  // 确保 pos 在有效范围内

            size_t offset = pos - _start;

            if (_finish == _endorstorage)
            {
                reserve(capacity() == 0 ? 4 : capacity() * 2);
            }

            Iterator it = _finish;

            while (it != _start + offset)
            {
                *it = *(it - 1);
                --it;
            }

            *(_start + offset) = value;
            ++_finish;
        }

        bool empty() const
        {
            return _start == _finish;
        }

        void pop_back()
        {
            assert(!empty());
            --_finish;
        }

        Iterator erase(Iterator pos)
        {
            assert(pos >= _start && pos < _finish);

            Iterator it = pos;
            while (it != _finish - 1)
            {
                *it = *(it + 1);
                ++it;
            }

            --_finish;
            return pos;
        }

        vector<T>& operator=(vector<T> v)
        {
            swap(v);
            return *this;
        }

        void swap(vector<T>& v)
        {
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_endorstorage, v._endorstorage);
        }

        template<typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            size_t n = std::distance(first, last);  // 计算输入范围的元素数量
            reserve(n);

            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }

        vector(size_t n, const T& value = T())
        {
            reserve(n);
            for (size_t i = 0; i < n; ++i)
            {
                new (_start + i) T(value);  
            }
            _finish = _start + n;
            _endorstorage = _start + n;
        }

        T& operator[](size_t index)
        {
            assert(index < size());
            return _start[index];
        }

    private:
        Iterator _start = nullptr;
        Iterator _finish = nullptr;
        Iterator _endorstorage = nullptr;
    };
}
