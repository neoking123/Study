#include "IOCompletionPort.h"
#include "..\..\Common\NetworkManager.h"

int main()
{
	NetworkManager::GetInstance()->Init();
	if (IOCompletionPort::GetInstance()->Init())
	{
		IOCompletionPort::GetInstance()->StartServer();
	}
	return 0;
}