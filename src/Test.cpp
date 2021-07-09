#include "mmCan.h"

#include <iostream>

class Test
{
public:
    void receive(uint32_t canid, uint8_t dlc, uint8_t frame_type, const uint8_t* data)
    {
        std::cout << "receive()\n";
        std::cout << "canid: " << static_cast<uint32_t>(canid) << '\n';
        std::cout << "dlc: " << static_cast<uint32_t>(dlc) << '\n';
        std::cout << "frame_type: " << static_cast<uint32_t>(frame_type) << '\n';
        std::cout << "data: ";
        for( uint8_t i = 0; i < dlc; ++i ) {
            std::cout << std::hex << static_cast<uint32_t>(data[i]) << ' ';
        }
        std::cout << '\n';
    }
};

int main()
{
    Test test;

    mm::can c("can0");
    c.register_receive_callback( &Test::receive, &test );

    return 0;
}
