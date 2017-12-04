#include <uWS.h>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "1st arg (connect_url) is required." << std::endl;
        return 1;
    }
    
    uWS::Hub h;

    h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        std::cout << std::string(message, length) << std::endl;
        exit(0);
    });
    
    h.onConnection([](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        ws->send("hello", 5, uWS::OpCode::TEXT);
    });

    h.connect(argv[1], nullptr);
    h.run();
    
    return 0;
}
