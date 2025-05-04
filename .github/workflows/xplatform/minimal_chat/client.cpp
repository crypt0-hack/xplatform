// #include "./cls.h"


// int main() {
//     int cs = socket(AF_INET, SOCK_STREAM, 0);

//     sockaddr_in serv_addr;
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(8080);
//     serv_addr.sin_addr.s_addr = INADDR_ANY;

//     connect(cs, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

//     const char *msg = "Hello, server! Are you Anton?";
//     send(cs, msg, strlen(msg), 0);

//     close(cs);
//     return 0;
// }
