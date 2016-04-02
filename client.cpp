#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>

using namespace std;

// char message[] = "Hello there!\n";
// char buf[sizeof(message)];

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3426); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    string message;
    std::cout << "Введите сообщение..." << std::endl;
    while (1) {
        std::getline (std::cin, message);
        char *message_chars = new char[message.length() + 1];
        strcpy(message_chars, message.c_str());
        char buf[sizeof(message_chars)];

        send(sock, message_chars, sizeof(message_chars), 0);
        recv(sock, buf, sizeof(message_chars), 0);
        cout << "От сервера пришло сообщение: ";
        
        printf(buf);
        cout << endl;

    }
    close(sock);

    return 0;
}