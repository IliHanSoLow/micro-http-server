#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main() {
  int tcp_socket;
  struct sockaddr_in server_address;
  if ((tcp_socket = socket(AF_INET, SOCK_STREAM, 0) < 0)) {
    printf("socket failed");
    exit(EXIT_FAILURE);
  }
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;

  return 0;
}

int test() {}
