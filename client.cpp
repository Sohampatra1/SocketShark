#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080

void *receive_message(void *arg)
{
    int sock = *((int *)arg);
    char buffer[1024] = {0};

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(sock, buffer, 1024);
        std::cout << "Server: " << buffer << std::endl;
    }

    return NULL;
}

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "Connection Failed" << std::endl;
        return -1;
    }

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, receive_message, (void *)&sock);

    while (true)
    {
        std::string message;
        std::cout << "Client: ";
        std::getline(std::cin, message);
        send(sock, message.c_str(), message.length(), 0);
    }

    return 0;
}
