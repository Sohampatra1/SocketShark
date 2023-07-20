#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>

#define PORT 8080

std::vector<int> client_sockets;

void *handle_client(void *arg)
{
    int new_socket = *((int *)arg);
    char buffer[1024] = {0};

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(new_socket, buffer, 1024);
        std::cout << "Client: " << buffer << std::endl;

        for (auto &client_sock : client_sockets)
        {
            if (client_sock != new_socket)
            {
                send(client_sock, buffer, strlen(buffer), 0);
            }
        }
    }

    return NULL;
}

int main()
{
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        std::cout << "Connected with client" << std::endl;
        client_sockets.push_back(new_socket);

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void *)&new_socket);
    }

    return 0;
}
