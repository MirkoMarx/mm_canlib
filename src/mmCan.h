#ifndef mmCan_h
#define mmCan_h

#include <functional>

namespace mm {

class receive_filter
{
public:
    receive_filter(const uint32_t& min_can_id, const uint32_t& max_can_id);
    uint32_t min_can_id();
    uint32_t max_can_id();
private:
    uint32_t m_min_can_id;
    uint32_t m_max_can_id;
};

class can
{
public:
    can(const std::string& interface_name);

    void init();
    void deinit();

    template<class Arg, class F>
    void set_receive_callback(Arg&& arg, F&& f);

    void error_counters(uint8_t& rx, uint8_t& tx);

    void add_receive_filter(const receive_filter& filter);

    void transmit_can_message(const uint32_t& can_id, const uint8_t& frame_type, const uint8_t& dlc, const uint8_t* data);

    static void availiable_interface_names();
    static std::string version();

private:
    std::function<void(uint32_t, uint8_t, uint8_t, const uint8_t*)> m_receive_callback;
};

template<class Arg, class F>
void can::set_receive_callback(Arg&& arg, F&& f)
{
    m_receive_callback = std::bind(f, arg, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

    const uint8_t data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    m_receive_callback(0x100, 8, 2, data);
}

}

#endif
