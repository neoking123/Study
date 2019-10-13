#include "IOCompletionPort.h"
#include "..\..\Common\NetworkManager.h"
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_db(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

int main()
{
	//메모리 릭
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();

	NetworkManager::GetInstance()->Init();
	if (IOCompletionPort::GetInstance()->Init())
	{
		IOCompletionPort::GetInstance()->StartServer();
	}
	NetworkManager::GetInstance()->Release();
	NetworkManager::FreeInstance();

	return 0;
}