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

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		printf("Error");
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("132.163.97.1");
	addr.sin_port = htons(13);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)& addr, sizeof(addr)) != 0) {
		printf("Error: failed connect to server.\n");
		return 1;
	}
	char tstr[26];
	recv(Connection, tstr, 25, NULL);
	tstr[25] = '\0';
	printf("%s",tstr);

	closesocket(Connection);
	return 0;
}
	

	
