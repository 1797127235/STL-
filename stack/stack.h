#pragma once
#include<vector>
using std::vector;

template<typename T, typename Container = vector<T>>
class stack
{
public:
    void push(const T& value)
    {
        _con.push_back(value);
    }

    void pop()
    {
        _con.pop_back();
    }

    T& top()
    {
        return _con.back();
    }

    const T& top() const
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