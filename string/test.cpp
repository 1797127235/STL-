#include <iostream>
#include "string.h"  // or whatever your custom string header file is named

void test_string_class() {
    // 1. 构造函数测试
    tiny::string s1("Hello");
    tiny::string s2(" World!");
    std::cout << "s1: " << s1.c_str() << ", s2: " << s2.c_str() << std::endl;

    // 2. 运算符重载 + 测试
    tiny::string s3 = s1 + s2;
    std::cout << "s3 (s1 + s2): " << s3.c_str() << std::endl;

    // 3. += 运算符测试
    s1 += s2;
    std::cout << "s1 after += s2: " << s1.c_str() << std::endl;

    // 4. 子字符串测试
    tiny::string s4 = s1.substr(6, 5);  // 从位置 6 开始，长度为 5
    std::cout << "s4 (substring): " << s4.c_str() << std::endl;

    // 5. push_back 测试
    s1.push_back('!');
    std::cout << "s1 after push_back '!': " << s1.c_str() << std::endl;

    // 6. insert 测试
    s1.insert(5, " inserted");
    std::cout << "s1 after insert: " << s1.c_str() << std::endl;

    // 7. erase 测试
    s1.erase(5, 9);  // 删除从位置 5 开始，长度为 9 的部分
    std::cout << "s1 after erase: " << s1.c_str() << std::endl;

    // 8. resize 测试
    s1.resize(8, '-');  // 调整大小到 8，空白部分填充 '-'
    std::cout << "s1 after resize(8, '-'): " << s1.c_str() << std::endl;

    // 9. clear 测试
    s1.clear();
    std::cout << "s1 after clear: " << s1.c_str() << std::endl;

    // 10. empty 测试
    std::cout << "Is s1 empty? " << (s1.empty() ? "Yes" : "No") << std::endl;

    // 11. reserve 测试
    s2.reserve(50);  // 提前为 s2 分配更大的内存
    std::cout << "s2 after reserve(50): " << s2.c_str() << std::endl;
}

int main() {
    test_string_class();
    return 0;
}
