#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// 包含你的 list 实现头文件
#include "list.h"

// 一个简单的测试框架，用于打印测试结果
void run_test(void (*test_func)(), const std::string& test_name) {
    std::cout << "Running test: " << test_name << "..." << std::endl;
    try {
        test_func();
        std::cout << "  [PASSED] " << test_name << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  [FAILED] " << test_name << " with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "  [FAILED] " << test_name << " with unknown exception." << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

// 1. 测试构造函数和赋值操作
void test_constructors_and_assignment() {
    // a. 默认构造函数
    tiny::list<int> l1;
    assert(l1.size() == 0);
    assert(l1.empty());

    // b. 拷贝构造函数
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);
    tiny::list<int> l2 = l1; // 使用拷贝构造
    assert(l2.size() == 3);
    assert(l2.front() == 10);
    assert(l2.back() == 30);

    // 验证深拷贝：修改 l1 不应影响 l2
    l1.front() = 99;
    assert(l1.front() == 99);
    assert(l2.front() == 10);

    // c. 拷贝赋值运算符
    tiny::list<int> l3;
    l3.push_back(5);
    l3 = l2; // 使用拷贝赋值
    assert(l3.size() == 3);
    assert(l3.front() == 10);
    
    // 验证深拷贝：修改 l2 不应影响 l3
    l2.pop_front();
    assert(l2.size() == 2);
    assert(l3.size() == 3);

    // d. 自我赋值
    l3 = l3;
    assert(l3.size() == 3);
    assert(l3.front() == 10);
}

// 2. 测试元素的添加和删除
void test_push_pop_front_back() {
    tiny::list<int> l;
    
    // a. push_back
    l.push_back(1);
    assert(l.size() == 1);
    assert(l.front() == 1 && l.back() == 1);
    l.push_back(2);
    assert(l.size() == 2);
    assert(l.front() == 1 && l.back() == 2);
    
    // b. push_front
    l.push_front(0);
    assert(l.size() == 3);
    assert(l.front() == 0 && l.back() == 2); // 列表内容: 0, 1, 2

    // c. pop_back
    l.pop_back(); // 列表内容: 0, 1
    assert(l.size() == 2);
    assert(l.front() == 0 && l.back() == 1);
    
    // d. pop_front
    l.pop_front(); // 列表内容: 1
    assert(l.size() == 1);
    assert(l.front() == 1 && l.back() == 1);

    // e. 清空列表
    l.pop_back();
    assert(l.empty());
}

// 3. 测试迭代器
void test_iterators() {
    tiny::list<int> l;
    for (int i = 0; i < 5; ++i) {
        l.push_back(i * 10); // {0, 10, 20, 30, 40}
    }

    // a. 正向遍历
    int expected_value = 0;
    for (tiny::list<int>::iterator it = l.begin(); it != l.end(); ++it) {
        assert(*it == expected_value);
        expected_value += 10;
    }
    
    // b. C++11 范围 for 循环
    expected_value = 0;
    for (int val : l) {
        assert(val == expected_value);
        expected_value += 10;
    }

    // c. 反向遍历
    expected_value = 40;
    for (auto it = --l.end();; --it) {
        assert(*it == expected_value);
        expected_value -= 10;
        if (it == l.begin()) break;
    }

    // d. 通过迭代器修改值
    auto it = l.begin();
    ++it; // 指向 10
    *it = 99;
    assert(l.front() == 0);
    ++it; // 指向 20
    assert(*--it == 99); // 验证 --it 能回到修改后的值
}

// 4. 测试 insert 和 erase
void test_insert_and_erase() {
    tiny::list<int> l;
    l.push_back(10);
    l.push_back(30);

    // a. 在 begin() 处 insert
    auto it = l.insert(l.begin(), 0);
    assert(*it == 0);
    assert(l.size() == 3); // {0, 10, 30}
    assert(l.front() == 0);

    // b. 在 end() 处 insert (等同于 push_back)
    it = l.insert(l.end(), 40);
    assert(*it == 40);
    assert(l.size() == 4); // {0, 10, 30, 40}
    assert(l.back() == 40);

    // c. 在中间 insert
    it = l.begin();
    ++it; ++it; // it 指向 30
    it = l.insert(it, 20);
    assert(*it == 20);
    assert(l.size() == 5); // {0, 10, 20, 30, 40}

    // d. 验证插入后的顺序
    int expected_value = 0;
    for (int val : l) {
        assert(val == expected_value);
        expected_value += 10;
    }

    // e. erase begin()
    it = l.erase(l.begin()); // 删除 0
    assert(*it == 10);
    assert(l.size() == 4);
    assert(l.front() == 10);

    // f. erase 最后一个元素
    it = l.erase(--l.end()); // 删除 40
    assert(it == l.end());
    assert(l.size() == 3);
    assert(l.back() == 30);

    // g. erase 中间元素
    it = l.begin();
    ++it; // it 指向 20
    it = l.erase(it); // 删除 20
    assert(*it == 30);
    assert(l.size() == 2); // {10, 30}
    assert(l.front() == 10 && l.back() == 30);
}

// 5. 测试 const 正确性
void test_const_correctness() {
    tiny::list<int> l;
    l.push_back(100);
    l.push_back(200);

    const tiny::list<int>& const_l = l;

    // a. 调用 const 成员函数
    assert(const_l.size() == 2);
    assert(!const_l.empty());
    assert(const_l.front() == 100);
    assert(const_l.back() == 200);

    // b. 使用 const_iterator 遍历
    int expected_value = 100;
    for (tiny::list<int>::const_iterator it = const_l.cbegin(); it != const_l.cend(); ++it) {
        assert(*it == expected_value);
        expected_value += 100;
    }
    
    // c. 范围 for 循环遍历 const list
    expected_value = 100;
    for (auto val : const_l) {
        assert(val == expected_value);
        expected_value += 100;
    }

    // 以下代码如果取消注释，应该会导致编译失败，证明 const 保护有效
    // const_l.push_back(300);
    // const_l.front() = 999;
    // *const_l.cbegin() = 999;
}

// 6. 测试复杂类型 (std::string)
void test_with_complex_type() {
    tiny::list<std::string> l;
    l.push_back("hello");
    l.push_front("tiny");
    l.push_back("world");

    assert(l.size() == 3);
    assert(l.front() == "tiny");
    assert(l.back() == "world");

    l.pop_front();
    assert(l.front() == "hello");

    tiny::list<std::string> l2 = l;
    l2.front() = "你好";
    assert(l.front() == "hello");
    assert(l2.front() == "你好");
}

int main() {
    run_test(test_constructors_and_assignment, "Constructors and Assignment");
    run_test(test_push_pop_front_back, "Push, Pop, Front, Back");
    run_test(test_iterators, "Iterators");
    run_test(test_insert_and_erase, "Insert and Erase");
    run_test(test_const_correctness, "Const Correctness");
    run_test(test_with_complex_type, "Complex Type (std::string)");

    std::cout << "========================================" << std::endl;
    std::cout << "      All tests completed successfully! " << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}