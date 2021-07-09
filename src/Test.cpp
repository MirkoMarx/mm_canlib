#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>

#include <signal.h>

#include "mmCan.h"

static volatile bool running = true;
static volatile int transmission_interval_usecs = -1;

void sigterm([[maybe_unused]] int signo)
{
    running = 0;
}

class Test
{
private:
    struct ThreadData {
        void* hContext;
    };

public:
    void Init();
    void DeInit();

private:
    void OnReceiveMessage(uint32_t canid, uint8_t dlc, uint8_t frame_type, const uint8_t* data);
    bool OnErrorOccured(void* hContext, unsigned char bChannel, bool fErrorIsActive, unsigned short CanError);
//    static void* TransmitThread(void *args);

private:
    pthread_t m_RxThread;
    ThreadData m_ThreadData;
    std::vector<void*> m_Filter;
    mm::can* m_can;
};

void Test::Init()
{
    m_can = new mm::can("can0");
    m_can->set_receive_callback(this, &Test::OnReceiveMessage);

//    unsigned short retval;

//    m_ThreadData.hContext = MOBA_MCAN_New( Test::OnReceiveMessage, Test::OnErrorOccured, this, &retval );
//    if( retval ) {
//        std::cout << "error: " << std::dec << retval << std::endl;
//    }

//    void* tmp;

//    tmp = MOBA_MCAN_RegisterMsg( m_ThreadData.hContext, MCW_ALL_CHANNELS, 0x0, 0x7FF, 0, FT_Standard, &retval );
//    if( retval ) {
//        std::cout << "error: " << std::dec << retval << std::endl;
//    }
//    else {
//        m_Filter.push_back( tmp );
//    }

//    tmp = MOBA_MCAN_RegisterMsg( m_ThreadData.hContext, MCW_ALL_CHANNELS, 0x09FD0200, 0x09FD02FF, 0, FT_Extended, &retval );
//    if( retval ) {
//        std::cout << "error: " << std::dec << retval << std::endl;
//    }
//    else {
//        m_Filter.push_back( tmp );
//    }

//    tmp = MOBA_MCAN_RegisterMsg( m_ThreadData.hContext, MCW_ALL_CHANNELS, 0x15FD0700, 0x15FD07FF, 0, FT_Extended, &retval );
//    if( retval ) {
//        std::cout << "error: " << std::dec << retval << std::endl;
//    }
//    else {
//        m_Filter.push_back( tmp );
//    }

    // Sende-Thread starten
//    pthread_create( &m_RxThread, NULL, Test::TransmitThread, (void*)&m_ThreadData );
}

void Test::DeInit()
{
    unsigned short retval;

    // Warte auf die Beendigung des Sende-Threads
//    pthread_join( m_RxThread, NULL );

//    for(void* handle : m_Filter) {
//        retval = MOBA_MCAN_UnRegisterMsg( m_ThreadData.hContext, 0, handle );
//        if( retval ) {
//            std::cout << "error: " << std::dec << retval << std::endl;
//        }
//    }
//    m_Filter.clear();

//    retval = MOBA_MCAN_Delete( m_ThreadData.hContext, 0 );
//    if( retval ) {
//        std::cout << "error: " << std::dec << retval << std::endl;
//    }

    delete m_can;
}

void Test::OnReceiveMessage(uint32_t canid, uint8_t dlc, uint8_t frame_type, const uint8_t* data)
{
    std::cout << std::hex << std::setw(9) << canid << "  ";
    std::cout << static_cast<int>( dlc ) << " " << std::setw(19);
    switch( frame_type ) {
//        case FT_Standard: std::cout << "FT_Standard  "; break;
//        case FT_Standard_Remote: std::cout << "FT_Standard_Remote  "; break;
//        case FT_Extended: std::cout << "FT_Extended  "; break;
//        case FT_Extended_Remote: std::cout << "FT_Extended_Remote  "; break;
//        case FT_Error: std::cout << "FT_Error  "; break;
        default: std::cout << "FT_Unknown  "; break;
    }
    for( unsigned char i = 0; i < dlc; ++i ) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)data[i] << " ";
    }
    std::cout << std::endl;
}

bool Test::OnErrorOccured(void* hContext, unsigned char bChannel, bool fErrorIsActive, unsigned short CanError)
{
    std::cout << "on_error " << std::dec << CanError << " " << fErrorIsActive << std::endl;

    return false;
}


//void* Test::TransmitThread(void *args)
//{
//    ThreadData* thread_data = (ThreadData*)args;

//    unsigned char dlc = 8;
//    unsigned char txData[dlc];

//    unsigned int can_id;

//    if( transmission_interval_usecs < 0 ) {
//        return 0;
//    }

//    srand (time (NULL));

//    while( running ) {
//        if( rand() % 2 == 0 ) {
//            can_id = rand() % 0x800;
//            MOBA_MCAN_TransmitMsg( thread_data->hContext, 0, can_id, dlc, FT_Standard, txData );
//        }
//        else {
//            can_id = static_cast<unsigned int>( rand() * rand() + rand() ) % 0x20000000;
//            MOBA_MCAN_TransmitMsg( thread_data->hContext, 0, can_id, dlc, FT_Extended, txData );
//        }

//#if _WIN32
//        SleepForMicroseconds( transmission_interval_usecs );
//#else
//        usleep( transmission_interval_usecs );
//#endif
//    }

//    return 0;
//}

int main(int argc, char **argv)
{
    signal( SIGTERM, sigterm );
    signal( SIGINT, sigterm );

    if( argc > 1 ) {
        transmission_interval_usecs = std::stoi( argv[1] );
        std::cout << "transmission inverval (usec): " << transmission_interval_usecs << std::endl;
    }

    Test test;

    test.Init();

    while( running ) {
        sleep( 1 );
    }

    test.DeInit();

    std::cout << "Main thread ended" << std::endl;

    return 0;
}

