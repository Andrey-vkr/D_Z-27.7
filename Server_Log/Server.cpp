#include "Server.h"



void Server::createSocket()
{
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Winsock initialization error " << WSAGetLastError() << std::endl;
        exit(1);
    }

    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == INVALID_SOCKET)
    {
        std::cout << "Creation of Socket failed!" << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(1);
    }
    else
    {
        std::cout << "Socket creation was successful.!" << std::endl;
    }
#else
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == -1)
    {
        perror("Creation of Socket failed!");
        exit(1);
    }
    else
    {
        std::cout << "Socket creation was successful.!" << std::endl;
    }
#endif
}

void Server::bindSocket()
{
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;

#ifdef _WIN32
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (bind_status == SOCKET_ERROR)
    {
        std::cout << "Socket binding failed.!" << WSAGetLastError() << std::endl;
        exit(1);
    }
#else
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (bind_status == -1)
    {
        perror("Socket binding failed.!");
        exit(1);
    }
#endif

    std::cout << "The socket binding was successful!" << std::endl;
}

void Server::closeSocket()
{
#ifdef _WIN32
    closesocket(sockert_file_descriptor);
    WSACleanup();
#else
    close(sockert_file_descriptor);
#endif 
}

void Server::dataReceivingServer()
{
    connection_status = listen(sockert_file_descriptor, 5);

    if (connection_status == -1)
    {
#ifdef _WIN32
        std::cout << "Socket is unable to listen for new connections.!" << WSAGetLastError() << std::endl;
#else
        perror("Socket is unable to listen for new connections.!");
#endif
        exit(1);
    }
    else
    {
        std::cout << "Server is listening for new connection: " << std::endl;
    }

    length = sizeof(client);
    connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);

    if (connection == -1)
    {
#ifdef _WIN32
        std::cout << "Server is unable to accept the data from client.!" << WSAGetLastError() << std::endl;
#else
        perror("Server is unable to accept the data from client.!");
#endif
        exit(1);
    }
    else
    {
        std::cout << "The client has joined!" << std::endl;
    }
}

char* Server::readData()
{

#ifdef _WIN32
    memset(message, '\0', MESSAGE_LENGTH);

    int bytesReceived = recv(connection, message, sizeof(message), 0);
    if (bytesReceived == SOCKET_ERROR)
    {
        std::cout << "Error when reading data from the client.! " << WSAGetLastError() << std::endl;
        exit(1);
    }
#else
    bzero(message, MESSAGE_LENGTH);

    int bytesRead = read(connection, message, sizeof(message));
    if (bytesRead == -1)
    {
        perror("Error when reading data from the client.! ");
        exit(1);
    }
#endif

    std::cout << "Data received from client: " << message << std::endl;
    return message;
}

void Server::writeData(std::string serverMessage)
{
#ifdef _WIN32
    memset(message, '\0', MESSAGE_LENGTH);
    strcpy_s(message, serverMessage.c_str());

    int bytesSent = send(connection, message, sizeof(message), 0);

    if (bytesSent == SOCKET_ERROR)
    {
        std::cout << "Sending data to the client failed.!" << WSAGetLastError() << std::endl;
        closesocket(connection);
        WSACleanup();
        exit(1);
    }
    else
    {
        std::cout << "Data successfully sent to the client.!" << message << std::endl;
    }
#else
    bzero(message, MESSAGE_LENGTH);
    strncpy(message, serverMessage.c_str(), MESSAGE_LENGTH - 1);

    ssize_t bytes = write(connection, message, sizeof(message));

    if (bytes == -1)
    {
        perror("Sending data to the client failed.!");
        close(connection);
        exit(1);
    }
    else
    {
        std::cout << "Data successfully sent to the client.!" << message << std::endl;
    }
#endif
}