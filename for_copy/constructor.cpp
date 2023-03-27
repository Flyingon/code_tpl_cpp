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
	// ��������
	String(const String& other) = delete;

	// Ĭ�ϵ� �������캯����ǳ����
	String(const String& other)
		: m_Buffer(other.m_Buffer), m_Size(other.m_Size)
	{}
	*/

	// ���
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

// ��������¾���"const����" ���ݲ��������⵼������
// ��Ҫ�Ļ������ں����и���
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