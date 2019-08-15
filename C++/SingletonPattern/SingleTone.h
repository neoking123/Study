#pragma once

//extern int currentMap[20];

class SingleTone
{
private:
	static SingleTone* pThis;

public:
	int map[20];

	static SingleTone* GetInstance()
	{
		if (pThis == nullptr)
			pThis = new SingleTone();

		return pThis;
	}

	void Release()
	{
		if (pThis)
			delete pThis;
	}

public:
	SingleTone();
	~SingleTone();
};

