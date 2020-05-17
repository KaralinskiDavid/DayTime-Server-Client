#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

int main() {

	time_t itime;
	char* tstr;
	char node[128], service[16];

	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		printf("Error");
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(13);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)& addr, sizeof(addr));
	listen(sListen, SOMAXCONN);


	while (1) {
		SOCKET newConnection;
		newConnection = accept(sListen, (SOCKADDR*)& addr, &sizeofaddr);

		if (newConnection == 0) {
			printf("Error #2\n");
		}
		else {
			itime = time(NULL);
			tstr = ctime(&itime);
			printf("%s\tRequest recieved from ", tstr);
			getnameinfo((SOCKADDR*)& addr, sizeof(addr), node, 128, service, 16, 0);
			printf("%s:%s\n", node, service);
			send(newConnection, tstr, 26, NULL);
		}


	
		closesocket(newConnection);
	}
	return 0;
}