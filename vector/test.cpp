#include <iostream>
#include<string>
#include <cassert>
#include "vector.h"  // 包含你的 vector 类头文件

void test_vector_operations() {
    // 测试1：默认构造和 push_back
    tiny::vector<int> vec;
    assert(vec.empty());  // 初始时，vector 应该是空的
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    assert(vec.size() == 3);  // 向 vector 添加了 3 个元素，大小应该是 3
    assert(vec.capacity() >= 3);  // 容量应该至少为 3
    // 测试2：访问元素
    assert(vec.begin() != vec.end());  // vector 中应该有元素
    assert(*vec.begin() == 10);  // 第一个元素应该是 10
    assert(*(vec.begin() + 1) == 20);  // 第二个元素应该是 20

    // 测试3：在指定位置插入元素
    vec.insert(vec.begin() + 1, 15);  // 在索引 1 处插入元素 15
    assert(vec.size() == 4);  // 大小应该变为 4
    assert(*(vec.begin() + 1) == 15);  // 索引 1 处的元素应该是 15  [10,15,20,30]

    // 测试4：pop_back 操作
    vec.pop_back();  // 移除最后一个元素（30）
    assert(vec.size() == 3);  // 大小应该变为 3
    assert(*(vec.end() - 1) == 20);  // 最后一个元素应该是 20  [10,15,20]

    // 测试5：删除元素
    vec.erase(vec.begin() + 1);  // 删除索引 1 处的元素（15）
    assert(vec.size() == 2);  // 大小应该变为 2
    assert(*(vec.begin() + 1) == 20);  // 第二个元素应该是 20  [10,20]

    // 测试6：调整大小
    vec.resize(5, 50);  // 将 vector 调整为 5 个元素，填充默认值 50
    assert(vec.size() == 5);  // 大小应该变为 5
    assert(*(vec.end() - 1) == 50);  // 最后一个元素应该是 50  [10,20,50,50,50]

    // 测试7：拷贝构造函数
    tiny::vector<int> vec_copy = vec;  // 拷贝构造一个新的 vector
    assert(vec_copy.size() == 5);  // 拷贝的 vector 应该和原来的大小相同
    assert(*(vec_copy.begin() + 2) == 50);  // 检查拷贝 vector 中的某个元素  


    // 测试8：赋值运算符
    tiny::vector<int> vec_assigned;
    vec_assigned = vec;  // 将一个 vector 赋值给另一个
    assert(vec_assigned.size() == 5);  // 大小应该相同
    assert(*(vec_assigned.begin() + 4) == 50);  // 最后一个元素应该是 50

    // 测试9：reserve 操作
    vec.reserve(10);  // 增加容量
    assert(vec.capacity() >= 10);  // 容量应该至少为 10

    std::cout << "all test is win！" << std::endl;
}

void test_string()
{
        // 测试1：构造和初始化
    tiny::vector<std::string> vec;
    vec.push_back("Hello");
    vec.push_back("World");
    vec.push_back("Test");

    assert(vec.size() == 3);  // 大小应该是 3
    assert(vec[0] == "Hello");  // 第一个元素应该是 "Hello"
    assert(vec[1] == "World");  // 第二个元素应该是 "World"
    assert(vec[2] == "Test");   // 第三个元素应该是 "Test"

    // 测试2：添加元素
    vec.push_back("C++");
    vec.push_back("Programming");

    assert(vec.size() == 5);  // 大小应该是 5
    assert(vec[3] == "C++");  // 第四个元素应该是 "C++"
    assert(vec[4] == "Programming");  // 第五个元素应该是 "Programming"   ["Hello", "World", "Test", "C++", "Programming"]

    // 测试3：插入元素
    vec.insert(vec.begin() + 1, "Inserted");

    assert(vec.size() == 6);  // 大小应该是 6
    assert(vec[1] == "Inserted");  // 第二个元素应该是 "Inserted" ["Hello", "Inserted", "World", "Test", "C++", "Programming"]

    for(auto s : vec)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    // 测试4：删除元素
    vec.erase(vec.begin() + 2);  // 删除索引 2 处的元素

    assert(vec.size() == 5);  // 大小应该是 5
    assert(vec[2] == "Test");  // ["Hello", "Inserted",  "Test", "C++", "Programming"]

    // 测试5：访问元素
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "Element at index " << i << ": " << vec[i] << std::endl;
    }
    // 输出:
    // Element at index 0: Hello
    // Element at index 1: Inserted
    // Element at index 2: Test
    // Element at index 3: C++
    // Element at index 4: Programming

    // 测试6：清空 vector
    vec.resize(0);
    assert(vec.empty());  // 清空后，vector 应该为空

    // 测试7：重新填充 vector
    vec.push_back("Apple");
    vec.push_back("Banana");
    vec.push_back("Cherry");

    assert(vec.size() == 3);  // 大小应该是 3
    assert(vec[0] == "Apple");  // 第一个元素应该是 "Apple"
    assert(vec[1] == "Banana");  // 第二个元素应该是 "Banana"
    assert(vec[2] == "Cherry");  // 第三个元素应该是 "Cherry"

    // 测试8：使用迭代器遍历
    std::cout << "Iterating through vector:" << std::endl;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << std::endl;  // 输出每个字符串
    }
    // 输出:
    // Apple
    // Banana 
    // Cherry

    // 测试9：查找特定元素
    auto it = std::find(vec.begin(), vec.end(), "Banana");
    assert(it != vec.end());  // 应该找到 "Banana"
    assert(*it == "Banana");  // 确认找到的元素是 "Banana"

    // 测试10：使用范围 for 循环
    std::cout << "Range-based for loop output:" << std::endl;
    for (const auto& str : vec) {
        std::cout << str << std::endl;
    }
    // 输出:
    // Apple
    // Banana
    // Cherry

    std::cout << "所有 tiny::vector<std::string> 测试通过！" << std::endl;
}

int main() {
    //test_vector_operations();  // 调用测试函数
    test_string();
    return 0;
}
