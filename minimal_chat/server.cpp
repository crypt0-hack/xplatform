#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 


int main() {
    int ss = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = INADDR_ANY;


    bind(ss, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(ss, 5);

    int cs = accept(ss, nullptr, nullptr);

    char buf[1024] = {0};
    while (1) {
        recv(cs, buf, sizeof(buf), 0);
        std::cout << "Message from client:  " << buf << std::endl;
    }

    close(ss);
    return 0;
}
