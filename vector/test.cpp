#include <iostream>
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

int main() {
    test_vector_operations();  // 调用测试函数
    return 0;
}
