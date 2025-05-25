#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 2048
#define BUF_SZ 1024

void* receive_msgs(void* socket_desc);


int main() {
      int sock = 0;
      struct sockaddr_in serv_addr;
      char buf[BUF_SZ];
      pthread_t thread_id;

      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
      }
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_port = htons(PORT);

      if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            perror("invalid address");
            exit(EXIT_FAILURE);
      }
      if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("connection failed");
            exit(EXIT_FAILURE);
      }

      printf("Connected to server\n");
      if (pthread_create(&thread_id, NULL, receive_msgs, (void*)&sock) < 0) {
            perror("thread creation failed");
            exit(EXIT_FAILURE);
      }

      while (1) {
            fgets(buf, BUF_SZ, stdin);
            send(sock, buf, strlen(buf), 0);
      }

      return 0;
}


void* receive_msgs(void* sock_desc) {
      int sock = *(int*)sock_desc;
      char buf[BUF_SZ];

      while (1) {
            int val_read = read(sock, buf, BUF_SZ);

            if (val_read <= 0) {
                  break;
            }
            buf[val_read] = '\0';
            printf("%s", buf);
      }

      return NULL;
}
