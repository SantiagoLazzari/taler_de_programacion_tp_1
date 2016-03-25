#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include "api_socket.h"

#include <string.h>

int socket_init(socket_t *self, char *port, char *host) {
  self->port = port;
  self->skt = 0;
  self->host = host;

  printf("port : %s, host : %s\n", port, host);

  int s = 0;

  struct addrinfo hints;
  struct addrinfo *addrinfo;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
  hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
  hints.ai_flags = 0;

  s = getaddrinfo(self->host, self->port, &hints, &addrinfo);

  if (s != 0) {
     printf("Error in getaddrinfo: %s\n", gai_strerror(s));
     return 1;
  }

  self->skt = socket(addrinfo->ai_family, addrinfo->ai_socktype, addrinfo->ai_protocol);

  if (self->skt == -1) {
     printf("Error: %s\n", strerror(errno));
     freeaddrinfo(addrinfo);
     return 1;
  }

  self->addrinfo = addrinfo;
  printf("llegue al get addrinfo");
  return 0;
}


int socket_destroy(socket_t *self) {
  puts("destroy");

  socket_shutdown(self);
  socket_close(self);

  return 0;
}

int socket_send(socket_t *self, char *buf, int size) {
  printf("send : %s, of size %d\n", buf, size);

  int sent = 0;
  int s = 0;
  bool is_the_socket_valid = true;

  while (sent < size && is_the_socket_valid) {
     s = send(self->skt, &buf[sent], size-sent, MSG_NOSIGNAL);

     if (s == 0) {
        is_the_socket_valid = false;
     }
     else if (s < 0) {
        is_the_socket_valid = false;
     }
     else {
        sent += s;
     }
  }

  if (is_the_socket_valid) {
     return sent;
  }
  else {
     return -1;
  }

  return 0;
}

int socket_receive(socket_t *self, char *buf, int size) {
   int received = 0;
   int s = 0;
   bool is_the_socket_valid = true;

   while (received < size && is_the_socket_valid) {
      s = recv(self->skt, &buf[received], size-received, MSG_NOSIGNAL);

      if (s == 0) { // nos cerraron el socket :(
         is_the_socket_valid = false;
      }
      else if (s < 0) { // hubo un error >(
         is_the_socket_valid = false;
      }
      else {
         received += s;
      }
   }

   if (is_the_socket_valid) {
      return received;
   }
   else {
      return -1;
   }

  return 0;
}

int socket_listen(socket_t *self, int listen_queue_size) {
  printf("listen : queue size %d\n", listen_queue_size);

  int s;

  s = listen(self->skt, listen_queue_size);
  if (s == -1) {
     printf("Error: %s\n", strerror(errno));
     close(self->skt);
     return 1;
  }

  puts("listen done");

  return 0;
}

int socket_accept(socket_t *self, socket_t *peerskt) {
  puts("accept begin");

  peerskt->skt = accept(self->skt, NULL, NULL);   // aceptamos un cliente

  if (peerskt->skt == -1) {
     printf("Error: %s\n", strerror(errno));
     return 1;
  }

  puts("accept done");

  return 0;
}

int socket_bind(socket_t *self) {
  puts("bind begin");

  int s;

  s = bind(self->skt, self->addrinfo->ai_addr, self->addrinfo->ai_addrlen);
  if (s == -1) {
     printf("Error: %s\n", strerror(errno));
     close(self->skt);
     freeaddrinfo(self->addrinfo);
     return 1;
  }

  freeaddrinfo(self->addrinfo);

  puts("bind done");

  return 0;
}

int socket_connect(socket_t *self) {
  puts("connect");

  struct addrinfo *ptr;
  bool are_we_connected = false;
  int s = 0;

  for (ptr = self->addrinfo; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {
     self->skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
     if (self->skt == -1) {
        printf("Error: %s\n", strerror(errno));
     }

     else {
        s = connect(self->skt, ptr->ai_addr, ptr->ai_addrlen);
        if (s == -1) {
           printf("Error: %s\n", strerror(errno));
           close(self->skt);
        }
        are_we_connected = (s != -1); // nos conectamos?
     }
  }

  freeaddrinfo(self->addrinfo);

  if (are_we_connected == false) {
    return 1;
  }

  return 0;
}

int socket_shutdown(socket_t *self) {
  puts("shotdown");
  shutdown(self->skt, SHUT_RDWR);

  return 0;
}

int socket_close(socket_t *self) {
  puts("close");

  close(self->skt);

  return 0;
}
