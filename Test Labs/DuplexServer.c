#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int socketFD = 0, bindFlag = 0, listenFlag = 0, newSocketFD_AfterListen, newSocket, pid;
struct sockaddr_in serverAddress, clientAddress;
char buffer[50];
void createSocket();
void bindSocket();
void startListening();
void startAccepting();
void doSend();
void doRecieve();
void quit();
int main() {
	createSocket();
	if (socketFD == -1) printf("Socket creation error\n");

	bindSocket();
	if (bindFlag == -1) printf("Binding error\n");

	startListening();
	if (listenFlag == -1) printf("Listening error\n");

	startAccepting();
	if (newSocketFD_AfterListen == -1) printf("Accepting error\n");

	printf("Server v0.57. Do not send more than 50 characters at a time \n \n \n");
	printf("Waiting for client ... \n");
	pid = fork();
	while (1) {
		if (pid > 0) {
			doSend();
		}
		else {
			doRecieve();
		}
	}

}

void createSocket() {
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
}

void bindSocket() {
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(3333);
	serverAddress.sin_addr.s_addr = htons(INADDR_ANY);

	bindFlag = bind(socketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
}

void startListening() {
	listenFlag = listen(socketFD, 1);
}

void startAccepting() {
	socklen_t tempLength = sizeof(clientAddress);
	newSocketFD_AfterListen = accept(socketFD, (struct sockaddr *) &clientAddress, &(tempLength));
}

void doSend() {
	printf("Send:");
	scanf("%[^\n]%*c", buffer);
	int sendFlag = send(newSocketFD_AfterListen, buffer, sizeof(buffer), 0);
	if (sendFlag == -1) {
		printf("Sending error\n");
	}
	if (strcmp(buffer, "exit") == 0) {
		quit();
	}
}

void doRecieve() {
	int recieveFlag = recv(newSocketFD_AfterListen, buffer, sizeof(buffer), 0);
	if (recieveFlag == -1) {
		printf("Recieve error\n");
	}
	printf("Client:%s\n" , buffer);
	if (strcmp(buffer, "exit") == 0) {
		quit();
	}
}

void quit() {
	if (pid > 0) {
		kill(pid, SIGKILL);
	}
	else if ( pid == 0) {
		kill(getppid() , SIGKILL);
	}
	if (socketFD != -1) {
		close(socketFD);
	}
	if (newSocketFD_AfterListen != -1) {
		close(newSocketFD_AfterListen);
	}
}