#include <iostream>
#include <string>
using namespace std;

int main()
{
	std::string str;
	str.reserve(256); // �ݺ����� �����Ҵ��� �����ϱ� ���� ���


	str = "slkdjfsak";



	cout << str[2];

	return 0;
}