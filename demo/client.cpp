#include <easywsclient.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "1st arg (port) is required." << std::endl;
        return 1;
    }
    
    if (0 >= std::stoi(argv[1]))
    {
        std::cerr << "Not a valid port." << std::endl;
        return 1;
    }
    
    std::string connect_url;
    connect_url += "ws://127.0.0.1:";
    connect_url += argv[1];
    
    auto ws = easywsclient::WebSocket::from_url(connect_url);
    if (ws == nullptr)
    {
        std::cerr << "Could not connect to " << connect_url << std::endl;
        return 1;
    }
    
    auto handler = [ws](const std::string& message) {
        std::cout << message << std::endl;
        if (message == "hello")
            ws->close();
    };
    
    ws->send("hello");
    
    while (ws->getReadyState() != easywsclient::WebSocket::CLOSED)
    {
        ws->poll();
        ws->dispatch(handler);
    }
    
    delete ws;
    return 0;
}
