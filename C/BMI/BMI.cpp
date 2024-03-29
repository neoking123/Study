// BMI.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	float weight = 0.f;
	float height = 0.f;
	float bmi = 0.f;
	bool quit = true;

	while (quit)
	{
		cout << "몸무게를 입력하세요 : ";
		cin >> weight;
		cout << "키를 입력하세요 : ";
		cin >> height;

		height /= 100;
		bmi = weight / (height * height);

		if (bmi >= 40)
		{
			cout << "BMI 지수 " << bmi << endl;
			cout << "고도 비만입니다" << endl;
		}
		else if (bmi >= 35)
		{
			cout << "BMI 지수 " << bmi << endl;
			cout << "중등도 비만입니다" << endl;
		}
		else if (bmi >= 30)
		{
			cout << "BMI 지수 " << bmi << endl;
			cout << "경도 비만입니다" << endl;
		}
		else if (bmi >= 25)
		{
			cout << "BMI 지수 " << bmi << endl;
			cout << "과체중입니다" << endl;
		}
		else if (bmi >= 18.5)
		{
			cout << "BMI 지수 " << bmi << endl;
			cout << "정상입니다" << endl;
		}
		else if (bmi < 18.5)
		{
			cout << "BMI 지수 " << bmi << endl;
			cout << "저체중입니다" << endl;
		}

		cout << endl;
	}
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
