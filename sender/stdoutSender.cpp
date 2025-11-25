#include "stdoutSender.h"
#include <iostream>
namespace Aciv::utility{

    Stdout_sender::Stdout_sender() : m_stream(stdout) {
        std::setvbuf(m_stream, nullptr, _IOFBF, 0);
    }
    /*
    Stdout_sender::~Stdout_sender(){

    }
    */

    void Stdout_sender::send(level _level, std::string_view message){
        if (m_stream != nullptr)
		{   
            std::string log_ = "[" + std::string(to_string(_level)) + "] " + std::string(message);
            
			std::fwrite(log_.data(), log_.size(), 1, m_stream);
			std::fflush(m_stream);
		}
    }


}