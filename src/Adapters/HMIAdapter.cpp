#include "HMIAdapter.h"
std::shared_ptr<HMIAdapter> HMIAdapter::mIntanceHMI = nullptr;

void HMIAdapter::handleReceivedCommand ()
{
    char buffer[1024] = { 0 };
    int valread       = recv (mClientSocket, buffer, sizeof (buffer) - 1, 0);

    if (valread > 0)
    {
        std::lock_guard<std::mutex> lock (mCommandMutex);
        mSocketCommand = std::string (buffer);
        printLog_I ("Receive command from client: %s", mSocketCommand.c_str ());
        json parsedData = json::parse (mSocketCommand);
        if (parsedData.contains ("command"))
        {
            mSocketCommand = parsedData["command"].get<std::string> ();
            printLog_I ("Parsed command: %s", mSocketCommand.c_str ());
        }
        else
        {
            printLog_I ("Invalid JSON format: 'command' field missing");
        }
    }
    else if (valread == 0)
    {
        printLog_I ("Client closed connection. Please reconnect!");
        {
            std::lock_guard<std::mutex> lock (mSocketMutex);
            close (mClientSocket);
            mClientSocket = -1;
        }
    }
    else
    {
        perror ("Error receiving data from client");
    }
}
const std::string HMIAdapter::getSocketCommand ()
{
    std::lock_guard<std::mutex> lock (mCommandMutex);
    return mSocketCommand;
}
void HMIAdapter::clearSocketCommand ()
{
    std::lock_guard<std::mutex> lock (mCommandMutex);
    mSocketCommand.clear ();
}
json HMIAdapter::stringCommand (const std::string &command)
{
    json response;
    json command_json          = json::parse (command);
    std::string actual_command = command_json["command"];
    if (actual_command == "ON")
    {
        response["status"]  = "success";
        response["message"] = "LED turned on!";
    }
    else if (actual_command == "OFF")
    {
        response["status"]  = "success";
        response["message"] = "LED turned off!";
    }
    else
    {
        response["status"]  = "error";
        response["message"] = "Unknown command!";
    }
    return response;
}
void HMIAdapter::onHMIScreen (const std::string &response)
{
    printLog_I ("Preparing to send response to client.");

    // std::lock_guard<std::mutex> lock (mSocketMutex);

    if (mClientSocket <= 0)
    {
        printLog_E ("Invalid or closed socket. Cannot send response.");
        return;
    }

    ssize_t bytes_sent = send (mClientSocket, response.c_str (), response.size (), 0);
    if (bytes_sent == -1)
    {
        perror ("Send response failed!!");
    }
    else
    {
        printLog_I ("Send response to client: %s", response.c_str ());
    }
}

void HMIAdapter::initSocket ()
{
    if ((server_fd = socket (AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror ("Socket failed");
        exit (EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt (server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof (opt)))
    {
        perror ("setsockopt");
        close (server_fd);
        exit (EXIT_FAILURE);
    }

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons (SOCKET_PORT);

    if (bind (server_fd, (struct sockaddr *)&address, sizeof (address)) < 0)
    {
        perror ("Bind failed");
        close (server_fd);
        exit (EXIT_FAILURE);
    }

    if (listen (server_fd, 3) < 0)
    {
        perror ("Listen");
        close (server_fd);
        exit (EXIT_FAILURE);
    }
}

void HMIAdapter::runServerSocketHMI ()
{
    while (true)
    {
        printLog_I ("Server running on port: %d", SOCKET_PORT);

        {
            std::lock_guard<std::mutex> lock (mSocketMutex);
            mClientSocket = accept (server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
            if (mClientSocket < 0)
            {
                perror ("Accept failed");
                continue;
            }
        }

        printLog_I ("Client connected. Waiting for commands.");
        while (true)
        {
            handleReceivedCommand ();

            {
                std::lock_guard<std::mutex> lock (mSocketMutex);
                if (mClientSocket <= 0)
                {
                    printLog_I ("Client disconnected. Closing socket.");
                    break;
                }
            }
        }
        {
            std::lock_guard<std::mutex> lock (mSocketMutex);
            close (mClientSocket);
            mClientSocket = -1;
        }
    }

    close (server_fd);
}

void HMIAdapter::handleDataFromMQTT (const std::string &data)
{
    printLog_I ("Get data from MQTT: %s", data.c_str ());

    {
        std::lock_guard<std::mutex> lock (mSocketMutex);
        if (mClientSocket <= 0)
        {
            printLog_E ("Invalid or closed socket. Cannot send MQTT data to client.");
            return;
        }

        onHMIScreen (data);
    }
}
HMIAdapter *HMIAdapter::getInstance ()
{
    if (mIntanceHMI == nullptr)
    {
        mIntanceHMI = std::make_shared<HMIAdapter> ();
    }
    return mIntanceHMI.get ();
}