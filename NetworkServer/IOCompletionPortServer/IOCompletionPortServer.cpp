#include "IOCompletionPort.h"

int main()
{
	IOCompletionPort iocp_server;
	if (iocp_server.Init())
	{
		iocp_server.StartServer();
	}
	return 0;
}