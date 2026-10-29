#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <err.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <unistd.h>

int main() {
	int srv = socket(AF_INET, SOCK_STREAM, 0);  // 1. ask the kernel for a socket
	int port = 8080;
	int client, running = 1;

	printf("[*] Server setup and running on %d\n", port);

	struct sockaddr_in addr = {0}; // Zero-initialize the memory
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;


	if (bind(srv, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		err(EXIT_FAILURE, "\n[!] bind");

	if (listen(srv, 128) == -1)
		err(EXIT_FAILURE, "\n[!] listen");

	while (running) {
		client = accept(srv, NULL, NULL);
		printf("[*] Client found!\n");
		char buf[500] = {0}; // flush buffer

		if (read(client, buf, sizeof(buf)) < 0)
			err(EXIT_FAILURE, "\n[!] read");

		// parse
		char method[16], path[2048], protocol[16];
		sscanf(buf, "%15s %2047s %15s", method, path, protocol);
		//printf("Method: %s\nPath: %s\nProtocol: %s\n", method, path, protocol);

		char *body = strstr(buf, "\r\n\r\n");
		if (body) {
		    body += 4;
		    printf("Body: %s\n", body);

				if (strcmp(body, "close") == 0) {
					printf("[*] Close requested\n");
					running = 0;
					}
		}

		// respond
		const char *resp = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nGot message!";
		write(client, resp, strlen(resp));

		close(client);
	}

	printf("[*] Server shutting down...\n");
	close(srv);
	
	return 0;
}
