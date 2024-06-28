#include <iostream>
using namespace std;

#define delimiter "\n--------------------------\n"

class String
{
	int size;
	char* str;
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}

	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char str[])
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++) this->str[i] = str[i];
		cout << "Constructor:\t" << this << endl;
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	String(String&& other)noexcept
	{
		this->size = other.size;
		this->str = other.str;

		//resert other;
		other.size = 0;
		other.str = nullptr;
		cout << "MoveConstructor:" << this << endl;
	}

	~String()
	{
		delete[] str;
		cout << "Destructor:\t" << this << endl;
	}

	String& operator=(const String& other)
	{
		if (this == &other) return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++) this->str[i] = other.str[i];
		cout << "CopyAssignment:" << this << endl;
		return *this;
	}
	String& operator=(String&& other)noexcept
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.size = 0;
		other.str = nullptr;
		cout << "MoveAssignment:" << this << endl;
		return *this;
	}

	const char& operator[](int i)const
	{
		return str[i];
	}
	char& operator[](int i)
	{
		return str[i];
	}

	void print()const
	{
		cout << "Obj:\t\t" << this << endl;
		cout << "Size:\t\t" << size << endl;
		cout << "Addr:\t\t" << &str << endl;
		cout << "STR:\t\t" << str << endl;
		cout << delimiter << endl;
	}
};

String operator+(const String& left, const String& right)
{
	//cout << delimiter << endl;
	cout << "Operator +" << endl;
	String buffer(left.get_size() + right.get_size() - 1);
	//buffer.print();
	for (int i = 0; i < left.get_size(); i++)
		buffer[i] = left[i];
	//buffer.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		buffer[i + left.get_size() - 1] = right[i];
	//buffer.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return buffer;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//#define CONSTRUCTORS_CHECK
#define MOVE_ASSIGNMENT_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK 
	String str1;
	str1.print();

	String str2(8);
	str2.print();

	String str3 = "Hello";
	str3 = str3;
	str3.print();

	String str4 = "World";
	str4.print();

	String str5;
	str5 = str3 + str4;
	str5.print();
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef MOVE_ASSIGNMENT_CHECK
	String str1 = "Hello", str2 = "World";
	String str3 = str1 + str2;
	String str4;
	str4 = std::move(str3);
	cout << delimiter << endl;
	cout << str4 << endl;
	cout << delimiter << endl;
#endif // MOVE_ASSIGNMENT_CHECK


}