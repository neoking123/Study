#include "StudentManager.h"

int main()
{
	StudentManager manager;

	ScienceStudent st(0, 0, "���ٿ�", 70, 80, 90, 100);
	HumanityStudent st1(1, 1, "������", 60, 50, 10, 90);
	HumanityStudent st2(2, 1, "������", 30, 40, 20, 80);
	ScienceStudent st3(3, 0, "�̰���", 60, 70, 80, 90);

	manager.insertStudent(&st);
	manager.insertStudent(&st1);
	manager.insertStudent(&st2);
	manager.insertStudent(&st3);
	manager.printScoreBoard();

	/*Student st(1, 0, "���ٿ�", 90, 70, 80);
	Student st1(2, 1, "�Ƿη�", 50, 30, 10);
	Student st2(3, 1, "��ī��", 60, 60, 40);
	Student st3(4, 0, "�Ʊ���", 10, 50, 40);*/

	/*manager.insertStudent(&st);
	manager.insertStudent(&st1);
	manager.insertStudent(&st2);
	manager.insertStudent(&st3);
	manager.printScoreBoard();*/

	return 0;
}