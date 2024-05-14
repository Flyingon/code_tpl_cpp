
# include "../../util/string.cc"
# include <vector>

void useIterator() {
    std::cout << "使用 Iterator" << std::endl;
    std::vector<std::string> attrs = {
            "user_id",
            "name",
            "avatar"
    };
    auto begin = attrs.begin();
    auto end = attrs.end();
//    for (; begin != end; ++begin)
//        std::cout << *begin << std::endl;
    std::string res = joinIterator(attrs.begin(), attrs.end(), ",");
    std::cout << "使用 Iterator 返回: " << res << std::endl;
}

void useVector() {
    std::cout << "使用 Vector" << std::endl;
    std::vector<std::string> attrs = {
            "user_id",
            "name",
            "avatar"
    };
    auto begin = attrs.begin();
    auto end = attrs.end();
    std::string res = joinVector(attrs, ",");
    std::cout << "使用 Vector 返回: " << res << std::endl;
}

void useArray() {
    std::cout << "使用 Array" << std::endl;
    std::string arrs[3] = {
            "user_id",
            "name",
            "avatar",
    };
    std::string res = joinArray(arrs, ",");
    std::cout << "使用 Array 返回: " << res << std::endl;
}

int main() {
    useIterator();
    useVector();
    useArray();
}