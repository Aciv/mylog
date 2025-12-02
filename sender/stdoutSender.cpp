#include "stdoutSender.h"

namespace Aciv::utility{

    Stdout_sender::Stdout_sender() : m_stream(stdout) {
        std::setvbuf(m_stream, nullptr, _IOFBF, 0);
    }


    void Stdout_sender::send(std::string_view _message){
        if (m_stream != nullptr)
		{   
            
			std::fwrite(_message.data(), _message.size(), 1, m_stream);
			std::fflush(m_stream);
		}
    }


}