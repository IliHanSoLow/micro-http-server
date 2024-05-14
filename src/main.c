#include "netinet/in.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
  // define socket and accept connections
  int my_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in sockaddr = {AF_INET, htons(8080), 0};
  bind(my_socket, &sockaddr, sizeof(sockaddr));
  listen(my_socket, 10);
  int client_sock = accept(my_socket, 0, 0);
  char buffer[256] = {0};
  recv(client_sock, buffer, 256, 0);

  // Get http_request and response to work
  // Get /file.html
  char *file;
  if (buffer[5] == ' ') {
    file = "index.html";
  } else {
    file = buffer + 5;
    *strchr(file, ' ') = 0;
  }
  char ok_buf[256];
  int header_len =
      snprintf(ok_buf, sizeof(ok_buf),
               "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\n\n");

  // send file
  send(client_sock, ok_buf, header_len, 0);
  int filedesc = open(file, O_RDONLY);
  sendfile(client_sock, filedesc, 0, 256);

  // close all sockets
  close(filedesc);
  close(client_sock);
  close(my_socket);
  return 0;
}
