#ifndef mmCan_h
#define mmCan_h

#include <functional>

namespace mm {

class can
{
public:
    can(const std::string& interface_name);

    template< class F, class Arg>
    void register_receive_callback(F&& f, Arg&& arg);

    void error_counters(uint8_t& rx, uint8_t& tx);

private:
    std::function<void(uint32_t, uint8_t, uint8_t, const uint8_t*)> m_receive_callback;
};

template< class F, class Arg>
void can::register_receive_callback(F&& f, Arg&& arg)
{
    m_receive_callback = std::bind(f, arg, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

    const uint8_t data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    m_receive_callback(0x100, 8, 2, data);
}

}

#endif
