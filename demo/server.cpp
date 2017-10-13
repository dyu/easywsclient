#include <uWS.h>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "1st arg (port) is required." << std::endl;
        return 1;
    }
    
    int port = std::stoi(argv[1]);
    if (0 >= port)
    {
        std::cerr << "Not a valid port." << std::endl;
        return 1;
    }
    
    uWS::Hub h;

    h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        std::cout << std::string(message, length) << std::endl;
        ws->send(message, length, opCode);
    });

    h.listen("127.0.0.1", port);
    h.run();
    
    return 0;
}
