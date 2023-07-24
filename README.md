
# Server-Client Communication Project

This project is a simple implementation of server-client communication using sockets in C++. It's a basic chat application where the server and client can send and receive messages.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

You need to have a C++ compiler (like g++) installed on your machine.

### Installing

Clone the repository to your local machine:

```bash
git clone https://github.com/Sohampatra1/SocketShark.git
```

Navigate to the project directory:

```bash
cd SocketShark
```

Compile the server and client files:

```bash
g++ -std=c++11 -o server server.cpp -lpthread
g++ -std=c++11 -o client client.cpp -lpthread
```

## Usage

First, run the server:

```bash
./server
```

Then, in a new terminal window, run the client:

```bash
./client
```

start multiple client-server like client1 client2 etc,
You can now start sending messages from one client to another client, and all messages will show in the server section.

## Result
![Loading](https://github.com/Sohampatra1/SocketShark/blob/main/ss_AdobeExpress.gif)




## Contributing

Contributions are welcome. Please open an issue to discuss your idea or submit a Pull Request.

## License

This project is licensed under the MIT License

## Contact

If you have any questions, feel free to reach out me
