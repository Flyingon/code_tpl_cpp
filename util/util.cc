
std::string NumToAlphabets(int number) {
    std::string res;
    if (number > 702) {
        return "";  // 不支持
    }
    if (number <= 26) {
        char temp = static_cast<char>( 64 + number);
        res = temp;
        return res;
    }
    int countAlphabet = number / 26;
    int overNumber = number % 26;

    char fist = static_cast<char>( 64 + (countAlphabet <= 26 ? countAlphabet : 26));
    res = fist;
    char second = static_cast<char>(64 + (overNumber > 0 ? overNumber : 26));
    res += second;
    return res;
}
