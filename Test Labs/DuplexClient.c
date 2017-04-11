#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>

int socketFD = 0, connectFlag = 0, pid = 0;
struct sockaddr_in serverAddress, clientAddress;
char buffer[50];
void createSocket();
void connectToServer();
void doSend();
void doRecieve();
void quit();
int main() {
	createSocket();
	if (socketFD == -1) {
		printf("Socket creation error\n");
	}

	connectToServer();
	if (connectFlag == -1) {
		printf("Connection error\n");
	}

	printf("Client ready. \n");
	pid = fork();
	while (1) {
		if (pid > 0) {
			doSend();
		}

		if (pid == 0) {
			doRecieve();
		}
	}
}

void createSocket() {
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
}

void connectToServer() {
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(3388);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	connectFlag = connect(socketFD, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
}

void doSend() {
	printf("Send:");
	scanf("%[^\n]%*c", buffer);
	int sendFlag = send(socketFD, buffer, sizeof(buffer), 0);
	if (sendFlag == -1) {
		printf("Sending error\n");
	}
	if (strcmp(buffer, "exit") == 0) {
		quit();
	}
}

void doRecieve() {
	int recieveFlag = recv(socketFD, buffer, sizeof(buffer), 0);
	if (recieveFlag == -1) {
		printf("Recieveing error\n");
	}
	printf("%s\n", buffer);
	if (strcmp(buffer, "exit") == 0) {
		quit();
	}
}

void quit() {
	if (pid == 0) {
		kill(getppid(), SIGKILL);
	}
	if (socketFD != -1) {
		close(socketFD);
	}
	if (pid > 0) {
		kill(pid, SIGKILL);
	}
	exit(1);
}