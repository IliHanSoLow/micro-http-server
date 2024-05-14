#include "netinet/in.h"
#include <fcntl.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
  int my_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in sockaddr = {AF_INET, htons(8080), 0};
  bind(my_socket, &sockaddr, sizeof(sockaddr));
  listen(my_socket, 10);
  int client_sock = accept(my_socket, 0, 0);
  char buffer[256] = {0};
  recv(client_sock, buffer, 256, 0);
  // Get /file.html
  char *file = buffer + 5;
  *strchr(file, ' ') = 0;
  int filedesc = open(file, O_RDONLY);
  sendfile(client_sock, filedesc, 0, 256);
  close(filedesc);
  close(client_sock);
  close(my_socket);
  return 0;
}
