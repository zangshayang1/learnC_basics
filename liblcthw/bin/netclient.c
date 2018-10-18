#undef NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h> // ref: man fcntl

#include "../src/lcthw/ringbuffer.h"
#include "../src/lcthw/dbg.h"

int nonblock(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  check(flags > 0, "Invalid flags on nonblock.");

  int rc = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  check(rc == 0, "Can't set nonblocking.");
  return 0;
error:
  return -1;
}

int client_connect(char* host, char* port) {
  int rc = -1;

  // ref <netdb.h>
  struct addrinfo* addr = NULL;
  rc = getaddrinfo(host, port, NULL, &addr);
  check(rc == 0, "Failed to lookup %s:%s", host, port);

  // ref: man socket
  // sock_fd = socket(domain, type, protocol)
  // AF_INET -> IPv4; AF_INET6 -> IPv6;
  // SOCKET_STREAM -> TCP; SOCKET_DGRAM -> UDP;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  check(sock >= 0, "Can't create a socket.");

  rc = connect(sock, addr->ai_addr, addr->ai_addrlen);
  check(rc == 0, "Failed to connect.");

  rc = nonblock(sock);
  check(rc == 0, "Failed to set the sock nonblock.");

  freeaddrinfo(addr);
  return sock;
error:
  return -1;
}

int recv_from(RingBuffer* buffer, int fd, int is_socket) {
  int rc = -1;

  if (RingBuffer_available_data(buffer) == 0) {
    buffer->start = buffer->end = 0;
  }

  if (is_socket) {
    // recv(sockt, buffer, length, flags);
    rc = recv(fd, RingBuffer_starts_at(buffer), RingBuffer_available_space(buffer), 0);
  } else {
    // read(fd, buffer, lenth) ref: <unistd.h>
    // invoke ACTION: taking from stdin 
    rc = read(fd, RingBuffer_starts_at(buffer), RingBuffer_available_space(buffer));
  }
  check(rc >= 0, "Failed to read from file descriptor: %d", fd);

  RingBuffer_commit_write(buffer, rc);

  return rc;

error:
  return -1;
}

int send_to(int fd, RingBuffer* buffer, int is_socket) {
  int rc = -1;
  int amount = RingBuffer_available_data(buffer);

  char* data = calloc(1, amount + 1);
  RingBuffer_read(buffer, data, amount);

  if (is_socket) {
    rc = send(fd, buffer, amount, 0);
  } else {
    rc = write(fd, buffer, amount);
  }

  check(rc == amount, "Failed to write everything to file descriptor: %d", fd);

  free(data);
  return rc;

error:
  return -1;
}

int main(int argc, char const *argv[]) {
  // fd_set defines a set of "selectable" file descriptor subject to select()
  // which allows the program to monitor multiple file descriptors in terms of
  // when a file is ready for some IO operation.
  fd_set allreads;
  fd_set readmask;

  int socket = 0;
  int rc = -1;
  RingBuffer* in_rb = RingBuffer_create(1024 * 10);
  RingBuffer* so_rb = RingBuffer_create(1024 * 10);

  check(argc == 3, "USAGE: netclient host port.");

  socket = client_connect(argv[1], argv[2]);

  FD_ZERO(&allreads); // MACRO clear the set
  FD_SET(socket, &allreads); // MACRO add to the set
  FD_SET(0, &allreads);

  // listen?
  while (1) {
    readmask = allreads;
    // socket + 1 makes the ceiling value
    rc = select(socket + 1, &readmask, NULL, NULL, NULL);
    check(rc >= 0, "Failed to select.");

    if (FD_ISSET(0, &readmask)) {
      rc = recv_from(in_rb, 0, 0);
    }
    if (FD_ISSET(socket, &readmask)) {
      rc = recv_from(in_rb, socket, 1);
    }

    while (!RingBuffer_empty(so_rb)) {
      rc = send_to(0, so_rb, 0);
    }
    while (!RingBuffer_empty(in_rb)) {
      rc = send_to(socket, in_rb, 1);
    }
  }

  return 0;

error:
  return -1;
}
























// #
