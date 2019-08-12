#include <iostream>
#include <string>
using namespace std;

int main()
{
	std::string str;
	str.reserve(256); // 반복적인 동적할당을 방지하기 위해 사용


	str = "slkdjfsak";



	cout << str[2];

	return 0;
}