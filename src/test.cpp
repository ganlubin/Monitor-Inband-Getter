#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

// 示例结构体
struct MyStruct {
    int id;
    std::string name;
    double value;
};

// 转换结构体为JSON格式的字符串
std::string struct_to_json(const MyStruct& myStruct) {
    json j;
    j["id"] = myStruct.id;
    j["name"] = myStruct.name;
    j["value"] = myStruct.value;
    return j.dump();
}

int main() {
    MyStruct myStruct = {123, "example", 3.14};
    std::string jsonString = struct_to_json(myStruct);
    std::cout << "JSON string: " << jsonString << std::endl;
    return 0;
}
