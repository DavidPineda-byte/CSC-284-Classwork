#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif
#include <thread>

/*
 * main
 *
 * Initializes networking support on Windows, creates a TCP listening socket,
 * binds it to port 54000 on all interfaces, and enters a loop accepting a
 * single client connection.
 *
 * For each accepted client:
 *   - convert the client's IP address from binary form to a human-readable
 *     C string using inet_ntop
 *   - print the client's IP and port
 *   - receive data and echo it back until the client disconnects or an error
 *     occurs
 *
 * Cleans up sockets and networking resources before exiting.
 *
 * Note: inet_ntop converts the client's IP address from binary form
 * (stored in clientAddr.sin_addr) to a null-terminated C string
 * stored in clientIp.
 */

class ClientHandler
{
private:
    std::string ipAddress;
    int port;
    std::string clientName;
    int clientSocket;

public:
    // Constructor
    ClientHandler(const std::string &ip, int p, const std::string &name, int &socket)
        : ipAddress(ip), port(p), clientName(name), clientSocket(socket) {}

    // Getters
    std::string getIpAddress() const { return ipAddress; }
    int getPort() const { return port; }
    std::string getClientName() const { return clientName; }

    // Setters
    void setClientName(const std::string &name) { clientName = name; }
    void setClientSocket(int socket) { clientSocket = socket; }
    int getClientSocket() const { return clientSocket; }
};

int main()
{
#ifdef _WIN32
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
#endif

    int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket < 0)
    {
        std::cerr << "Cannot create socket\n";
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    std::vector<ClientHandler> clients;

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Bind failed\n";
        closesocket(listenSocket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }


// SERVER MAIN LOOP 
/*
 
Inside this loop the server listens for incoming Client Connections []

*/





    while (true)
    {

        std::cout << "Waiting for a client to connect...\n" << std::endl;
        
        // LISTENS FOR INCOMING CONNECTIONS 
        // SOMAXCONN is a constant that specifies the maximum number of pending connections
        if (listen(listenSocket, SOMAXCONN) < 0)
        {
            std::cerr << "Listen failed\n";
            closesocket(listenSocket);
#ifdef _WIN32
            WSACleanup();
#endif
            return 1;
        }

        sockaddr_in clientAddr{};
        socklen_t clientSize = sizeof(clientAddr);
        // clientSocket represents the socket file descriptor for the accepted client connection
        
        int clientSocket = accept(listenSocket, (sockaddr *)&clientAddr, &clientSize);

        // HANDLES FAILED ACCEPTS
        if (clientSocket < 0)
        {
            std::cerr << "Accept failed\n";
            closesocket(listenSocket);
#ifdef _WIN32
            WSACleanup();
#endif
            return 1;
        }
        
        
        char clientIp[INET_ADDRSTRLEN];
        // cleans array might not need it
        std::memset(clientIp, 0, sizeof(clientIp));
        // inet_ntop is a function that converts an IP address from binary form to text form
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, sizeof(clientIp));
        // We create a ClientHandler object for the connected client and store it in a vector
        ClientHandler client(clientIp, ntohs(clientAddr.sin_port), "Unknown", clientSocket);
        clients.push_back(client);
        // We print the client's IP address and port number to the console
        std::cout << "Client connected from "
                  // We use ntohs to convert the client's port number from network byte order to host byte order
                  << clientIp << ":" << ntohs(clientAddr.sin_port) << '\n';

                  
// CLIENT HANDLING LOGIC IN A NEW THREAD FOR EACH CONNECTED CLIENT =========================================================
        std::thread clientThread([client, &clients]()
                                 {
        while(true){
        // THIS SECTION WILL HOLD EACH CLIENDS THREAD LOGIC FOR HANDLING CHAT MESSAGES AND RESPONSES =========================================================
        // Buffer to hold incoming messages from the client
        char buffer[4096];

        int bytesReceived = recv(client.getClientSocket(), buffer, sizeof(buffer), 0);
        if (bytesReceived > 0)
        {
            std::string message(buffer, bytesReceived);
            std::cout << "Client: " << message << '\n';

            



            for(ClientHandler &c : clients){
                if (c.getClientSocket() == client.getClientSocket())
        continue;
                // *** ECHO BACK THE RECEIVED MESSAGE TO THE CLIENT ***
            if (send(c.getClientSocket(), buffer, bytesReceived, 0) < 0)
            {
                std::cerr << "Send failed\n";
                break;
            }
            }
        }
        else if (bytesReceived == 0)
        {
            std::cout << "Client disconnected\n";
            // We break the loop and close the client's socket when the client disconnects
            closesocket(client.getClientSocket());

            break;
        }
        else
        {
            std::cerr << "Receive failed\n";
            break;
        }
        // END OF CLIENT MESSAGE HANDLING AND RESPONSE LOGIC =========================================================
    } });

        clientThread.detach();
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}