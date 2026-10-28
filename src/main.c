#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>

int main() {
	int srv = socket(AF_INET, SOCK_STREAM, 0);  // 1. ask the kernel for a socket
	bind(srv, &addr, sizeof addr);              // 2. claim port 8080
	listen(srv, 128);                           // 3. kernel starts accepting connections for you
	int c = accept(srv, NULL, NULL);            // 4. block until a client connects
	read(c, buf, sizeof buf);                   // 5. get the request bytes
	const char *resp = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nhi";
	write(c, resp, strlen(resp));               // 6. send the response bytes
	close(c);

	return 0;
}

