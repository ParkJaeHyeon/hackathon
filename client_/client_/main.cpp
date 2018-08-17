#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Windows.h>
#include <thread>
#include "parse.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

void ErrorHandling(const char* message);

int main(int argc, char*argv[]) {
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	char message[50];
	char buff[1024];
	int strLen;
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	thread pid(get_pid);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		perror("에러가 나는 이유");
		ErrorHandling("connect() error!");
	}


	strLen = recv(hSocket, message, sizeof(message) - 1, 0);
	if (strLen == -1)
		ErrorHandling("read() error!");

	printf("Message from server: %s\n", message);
	int check = 0;
	while (true) {
		cin >> check;
		if (check == 2) 
			exit(1);

		send(hSocket, buff, sizeof(buff),0);
	}
	pid.join();
	closesocket(hSocket);
	WSACleanup();
	return 0;
}
void ErrorHandling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}