#include "serverinstance.h"
namespace cppserver{
    serverInstance::serverInstance(){

    }

    std::future<bool> serverInstance::open(){
        isOpen = true;
    }

    std::future<bool> serverInstance::close(){
        isOpen = false;
    }

    std::future<void> handle_message(const std::wstring &message){
        m_messageQueue.emplace(message);
    }
   


}