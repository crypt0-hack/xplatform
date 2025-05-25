#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2048
#define MAX_CLIENTS 10
#define BUF_SZ 1024


int main() {
      int serv_fd, new_sock, client_socks[MAX_CLIENTS];
      struct sockaddr_in address;
      int opt = 1, max_sd, activity;

      fd_set read_fs;
      char buf[BUF_SZ] = { 0 };
      for (int i = 0; i < MAX_CLIENTS; i++) {
            client_socks[i] = 0;
      }
      if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
      }
      if (setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
            perror("setsockopt failed");
            exit(EXIT_FAILURE);
      }

      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons(PORT);
      if (bind(serv_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            perror("bind error");
            exit(EXIT_FAILURE);
      }
      if (listen(serv_fd, 3) < 0) {
            perror("listen failed");
            exit(EXIT_FAILURE);
      }
      printf("Server is listening on port %d...\n", PORT);

      while (1) {
            FD_ZERO(&read_fs);
            FD_SET(serv_fd, &read_fs);
            max_sd = serv_fd;

            for (int i = 0; i < MAX_CLIENTS; i++) {
                  if (client_socks[i] > 0) {
                        FD_SET(client_socks[i], &read_fs);
                  }
                  if (client_socks[i] > max_sd) {
                        max_sd = client_socks[i];
                  }
            }
            activity = select(max_sd + 1, &read_fs, NULL, NULL, NULL);

            if (activity < 0) {
                  perror("select");
            }
            if (FD_ISSET(serv_fd, &read_fs)) {
                  if ((new_sock = accept(serv_fd, NULL, NULL)) < 0) {
                        perror("accept failed");
                        exit(EXIT_FAILURE);
                  }
                  for (int i = 0; i < MAX_CLIENTS; i++) {
                        if (client_socks[i] == 0) {
                              client_socks[i] = new_sock;
                              printf("new client connected\n");
                              break;
                        }
                  }
            }

            for (int i = 0; i < MAX_CLIENTS; i++) {
                  if (client_socks[i] > 0 && FD_ISSET(client_socks[i], &read_fs)) {
                        int val_read = read(client_socks[i], buf, BUF_SZ);
                        if (val_read == 0) {
                              close(client_socks[i]);
                              client_socks[i] = 0;
                              printf("client disconnected\n");
                        } else {
                              buf[val_read] = '\0';
                              for (int j = 0; j < MAX_CLIENTS; j++) {
                                    if (client_socks[j] > 0 && j != i) {
                                          send(client_socks[j], buf, strlen(buf), 0);
                                    }
                              }
                        }
                  }
            }
      }

      return 0;
}
