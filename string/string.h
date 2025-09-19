#pragma once
#include <cassert>
#include <cstring>
#include <algorithm> // std::max
#include <utility>   // std::swap
#include <memory>    // std::unique_ptr

namespace tiny {

    class string {
    public:
        using iterator = char*;
        using const_iterator = const char*;

        // 常量
        static constexpr size_t npos = static_cast<size_t>(-1);

        // 迭代器
        iterator begin() noexcept { return _data; }
        iterator end()   noexcept { return _data + _size; }
        const_iterator begin() const noexcept { return _data; }
        const_iterator end()   const noexcept { return _data + _size; }
        const_iterator cbegin() const noexcept { return _data; }
        const_iterator cend()   const noexcept { return _data + _size; }

        // 构造函数 / 析构函数
        string()
            : _data(new char[1]), _size(0), _capacity(0)
        { _data[0] = '\0'; }

        ~string() noexcept
        {
            delete[] _data;
            _data = nullptr;
            _size = 0;
            _capacity = 0;
        }

        string(const char* s)
        {
            assert(s);
            _size = std::strlen(s);
            _capacity = _size;
            _data = new char[_capacity + 1];
            std::memcpy(_data, s, _size);
            _data[_size] = '\0';
        }

        // 拷贝构造
        string(const string& s)
            : _size(s._size), _capacity(s._capacity)
        {
            _data = new char[_capacity + 1]; // 保证容量一致
            if (_size) std::memcpy(_data, s._data, _size);
            _data[_size] = '\0';
        }

        // 移动构造
        string(string&& s) noexcept
            : _data(s._data), _size(s._size), _capacity(s._capacity)
        {
            s._data = nullptr;
            s._size = 0;
            s._capacity = 0;
        }

        // 子串构造
        string(const string& str, size_t pos, size_t len = npos)
        {
            assert(pos <= str._size);
            if (len == npos || pos + len > str._size) len = str._size - pos;
            _size = len; _capacity = _size;
            _data = new char[_capacity + 1];
            if (_size) std::memcpy(_data, str._data + pos, _size);
            _data[_size] = '\0';
        }

        // 赋值运算符（copy-and-swap，既能处理拷贝也能处理移动）
        string& operator=(string s)
        {
            swap(s);
            return *this;
        }

        // 元素访问
        char& operator[](size_t pos)
        {
            assert(pos < _size);
            return _data[pos];
        }
        const char& operator[](size_t pos) const
        {
            assert(pos < _size);
            return _data[pos];
        }

        // 观察器
        const char* c_str() const noexcept { return _data; }
        bool   empty() const noexcept { return _size == 0; }
        size_t size()  const noexcept { return _size; }
        size_t capacity() const noexcept { return _capacity; }

        // 修改器
        void clear() noexcept
        {
            _size = 0;
            _data[0] = '\0';
        }

        void reserve(size_t new_cap)
        {
            if (new_cap <= _capacity) return;
            reallocate_(new_cap);
        }


        string& operator+=(const string& s)
        {
            if (s._size == 0) return *this;

            // const size_t needed = _size + s._size;
            // if (needed > _capacity) grow_(needed);

            // std::memcpy(_data + _size, s._data, s._size);
            // _size = needed;
            // _data[_size] = '\0';
            // return *this;
            push_back(s._data);
            return *this;
        }

        // 交换函数
        void swap(string& other) noexcept
        {
            std::swap(_data, other._data);
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
        }

        // 子串
        string substr(size_t pos = 0, size_t len = npos) const
        {
            assert(pos <= _size);
            if (len == npos || pos + len > _size) len = _size - pos;
            return string(*this, pos, len);
        }

        void push_back(char ch)
        {
            if (_size + 1 > _capacity) grow_(_size + 1);
            _data[_size++] = ch;
            _data[_size] = '\0';
        }

        void push_back(char* s)
        {
            if (!s) return;
            size_t len = std::strlen(s);
            if (len == 0) return;

            const size_t needed = _size + len;
            if (needed > _capacity) grow_(needed);

            std::memcpy(_data + _size, s, len);
            _size = needed;
            _data[_size] = '\0';
        }

        void push_back(const string& s)
        {
            if (s._size == 0) return;

            const size_t needed = _size + s._size;
            if (needed > _capacity) grow_(needed);

            std::memcpy(_data + _size, s._data, s._size);
            _size = needed;
            _data[_size] = '\0';
        }

        //扩容
        void reserve(size_t n)
        {
            if (n > _capacity) grow_(n);
        }

        void resize(size_t n, char ch = '\0')
        {
            if (n < _size) {
                _size = n;
                _data[_size] = '\0';
            }
            else if (n > _size) {
                if (n > _capacity) grow_(n);
                std::memset(_data + _size, ch, n - _size);
                _size = n;
                _data[_size] = '\0';
            }
        }

        void insert(size_t pos, const string& s)
        {
            assert(pos <= _size);
            if (s._size == 0) return;

            if (&s == this) {              // 自插入：先拷贝一份再调回
                string tmp(s);
                insert(pos, tmp);
                return;
            }

            const size_t needed = _size + s._size;
            if (needed > _capacity) grow_(needed);

            std::memmove(_data + pos + s._size, _data + pos, _size - pos);
            std::memcpy(_data + pos, s._data, s._size);
            _size = needed;
            _data[_size] = '\0';
        }

        void insert(size_t pos,char ch)
        {
            assert(pos <= _size);
            const size_t needed = _size + 1;
            if (needed > _capacity) grow_(needed);

            // 移动原有元素
            std::memmove(_data + pos + 1, _data + pos, _size - pos);
            // 插入新元素
            _data[pos] = ch;
            _size = needed;
            _data[_size] = '\0';
        }

        void insert(size_t pos, const char* s)
        {
            assert(pos <= _size);
            if (!s) return;

            size_t len = std::strlen(s);
            if (len == 0) return;

            // 检测 s 是否指向自身缓冲区（别名）
            const bool aliased = (s >= _data) && (s <= _data + _size);

            // 如有别名，先把内容拷到临时缓冲
            const char* src = s;
            std::unique_ptr<char[]> tmp;
            if (aliased) {
                tmp.reset(new char[len]);
                std::memcpy(tmp.get(), s, len);
                src = tmp.get();
            }

            const size_t needed = _size + len;
            if (needed > _capacity) grow_(needed);

            std::memmove(_data + pos + len, _data + pos, _size - pos);
            std::memcpy(_data + pos, src, len);
            _size = needed;
            _data[_size] = '\0';
        }


        void erase(size_t pos, size_t len = npos)
        {
            // 边界检查，确保 pos 是有效的
            assert(pos < _size);
            
            if (len == 0) return; // 不需要删除任何字符

            // 如果 len 是 npos，表示删除从 pos 到结尾的所有字符
            if (len == npos || pos + len >= _size) len = _size - pos;

            // 移动内存，删除指定范围的字符
            std::memmove(_data + pos, _data + pos + len, _size - (pos + len));

            // 更新大小并插入终止符
            _size -= len;
            _data[_size] = '\0';
        }



    private:
        // 扩容
        void grow_(size_t min_cap)
        {
            size_t new_cap = _capacity ? _capacity * 2 : 4;
            if (new_cap < min_cap) new_cap = min_cap;
            reallocate_(new_cap);
        }

        // 重新分配内存
        void reallocate_(size_t new_cap)
        {
            char* newdata = new char[new_cap + 1];
            if (_size) std::memcpy(newdata, _data, _size);
            newdata[_size] = '\0';
            delete[] _data;
            _data = newdata;
            _capacity = new_cap;
        }

    private:
        char*  _data = nullptr;  // 字符数组
        size_t _size = 0;        // 当前字符串长度
        size_t _capacity = 0;    // 当前容量
    };

    // 非成员运算符重载
    inline string operator+(const string& lhs, const string& rhs)
    {
        string result(lhs);
        result += rhs;
        return result;
    }

    inline string operator+(const string& lhs, const char* rhs)
    {
        return lhs + string(rhs);
    }

    inline string operator+(const char* lhs, const string& rhs)
    {
        return string(lhs) + rhs;
    }

}
