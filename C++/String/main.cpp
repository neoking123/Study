#include "Student.h"
#include "StudentManager.h"

int main()
{
	StudentManager manager;
	Student st(1, "���ٿ�", 20, 30, 40);

	manager.insertStudent(st);
	manager.printScoreBoard();

	return 0;
}