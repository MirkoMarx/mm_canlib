#include "mmCan.h"

mm::receive_filter::receive_filter(const uint32_t& min_can_id, const uint32_t& max_can_id)
    : m_min_can_id(min_can_id)
    , m_max_can_id(max_can_id)
{
}

uint32_t mm::receive_filter::min_can_id()
{
    return m_min_can_id;
}

uint32_t mm::receive_filter::max_can_id()
{
    return m_max_can_id;
}

mm::can::can(const std::string& interface_name)
{

}
