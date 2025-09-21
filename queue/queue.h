#pragma once
#include<deque>
using std::deque;

template<typename T, typename Container = deque<T>>
class queue
{
pubblic:
    void push(const T& value)
    {
        _con.push_back(value);
    }

    void pop()
    {
        _con.pop_front();
    }

    T& front()
    {
        return _con.front();
    }

    const T& front() const
    {
        return _con.front();
    }

    T& back()
    {
        return _con.back();
    }

    const T& back() const
    {
        return _con.back();
    }

    bool empty() const
    {
        return _con.empty();
    }

    size_t size() const
    {
        return _con.size();
    }
private:
    Container _con;
};