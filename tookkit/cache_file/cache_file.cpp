#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int set_data(const string &file_path, const string &data) {
    // 以写模式打开文件
    ofstream fwriter;
    fwriter.open(file_path);

    if (!fwriter.is_open()) {
        cout << "cannot open the file" << endl;
        return -3;
    }

    fwriter << data << endl;
    fwriter.close();
    return 0;
}

int read_data(const string &file_path) {
    // 以写模式打开文件
    ifstream fread;
    fread.open(file_path);

    if (!fread.is_open()) {
        cout << "cannot open the file" << endl;
        return -3;
    }

    std::stringstream buffer;
    buffer << fread.rdbuf();
    fread.close();

    std::string data(buffer.str());

    cout << data << endl;
    fread.close();
    return 0;
}

int main(int argc, char *argv[]) {
    string user_home = std::getenv("HOME");
    if (user_home.length() == 0) {
        cout << "user home is not valid" << endl;
        return -2;
    }
    const string file_path = user_home + "xxxxx";

    if (argc > 1) {
        string content;
        for (int i = 1; i < argc; i++) {
            string elem = argv[i];
            if (content.length() > 0)
                content += " ";
            content += elem;
        }
        cout << content << endl;
        return set_data(file_path, content);
    }
    return read_data(file_path);
}