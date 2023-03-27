# include <iostream>

class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = 0;
	}

	/*
	// 不允许拷贝
	String(const String& other) = delete;

	// 默认的 拷贝构造函数，浅拷贝
	String(const String& other)
		: m_Buffer(other.m_Buffer), m_Size(other.m_Size)
	{}
	*/

	// 深拷贝
	String(const String& other)
		:m_Size(other.m_Size)
	{
		std::cout << "Copied String!" << std::endl;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}

	/*
	String(const String& other)
	{
		memcpy(this, &other, sizeof(String));
	}
	*/

	

	~String()
	{
		delete[] m_Buffer;
	}

	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}

// 基本情况下就用"const引用" 传递参数，避免导出复制
// 需要的话可以在函数中复制
void PrintString(const String& string) {
	std::cout << string << std::endl;
}

int main() {
	String string = "joeyuan";
	String second = string;

	second[1] = 'a';

	PrintString(string);
	PrintString(second);

	std::cin.get();
}