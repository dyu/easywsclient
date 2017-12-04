#include <uWS.h>
#include <iostream>

const char DEFAULT_MSG[] = "hello";

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "1st arg (connect_url) is required." << std::endl;
        return 1;
    }
    
    auto msg = argc > 2 ? argv[2] : DEFAULT_MSG;
    auto msg_len = strlen(msg);
    
    uWS::Hub h;

    h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        std::cout << std::string(message, length) << std::endl;
        exit(0);
    });
    
    h.onConnection([msg, msg_len](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        ws->send(msg, msg_len, uWS::OpCode::TEXT);
    });

    h.connect(argv[1], nullptr);
    h.run();
    
    return 0;
}
