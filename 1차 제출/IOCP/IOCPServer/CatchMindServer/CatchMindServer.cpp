#include "IOCompletionPort.h"
#include "..\..\Common\NetworkManager.h"
#include "WordManager.h"
#include <crtdbg.h>

#define WORDLIST_DIR "WordList\\WorldList.txt"

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_db(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

int main()
{
	//�޸� ��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(157);

	srand(GetTickCount());
	WordManager::GetInstance()->Init();
	WordManager::GetInstance()->LoadWords(WORDLIST_DIR);

	NetworkManager::GetInstance()->Init();
	if (IOCompletionPort::GetInstance()->Init())
	{
		IOCompletionPort::GetInstance()->StartServer();
	}

	NetworkManager::GetInstance()->Release();
	NetworkManager::FreeInstance();
	WordManager::GetInstance()->Release();
	WordManager::FreeInstance();
	IOCompletionPort::FreeInstance();

	return 0;
}