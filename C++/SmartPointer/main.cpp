#include <iostream>
#include <vector>
#include <memory> // shared_ptr, weak_ptr
#include "TestClass.h"
using namespace std;

int main()
{
	// auto_ptr<TestClass>(); ¿¾³¯²¨
	// unique_ptr<TestClass> uptr(new TestClass()); º¹»ç°¡ ÀÏ¾î³ª¸é ¾ÈµÊ
	// unique_ptr<TestClass> uptr2 = move(uptr);

	vector<shared_ptr<TestClass>> vec;
	vec.push_back(make_shared<TestClass>());

	//shared_ptr<TestClass> sptr1(new TestClass());
	shared_ptr<TestClass> sptr1 = make_shared<TestClass>();
	shared_ptr<TestClass> sptr2 = sptr1;
	cout << sptr1.use_count() << endl;

	weak_ptr<TestClass> wptr1 = sptr1;
	shared_ptr<TestClass> sptr3 = wptr1.lock();

	cout << sptr1.use_count() << endl;


	return 0;
}