#include "fileSender.h"

namespace Aciv::utility{

    File_sender::File_sender(std::string_view _file_path): m_file_path(_file_path) {
		if (!std::filesystem::exists(m_file_path.parent_path()))
		{
			std::filesystem::create_directory(m_file_path.parent_path());
		}

		m_stream = std::fopen(m_file_path.string().data(), "a");

		if (m_stream != nullptr)
		{
            // without buffer
			std::setvbuf(m_stream, nullptr, _IOFBF, 0);
		}
    }
    
    File_sender::~File_sender(){
        if (!m_file_path.empty() && m_stream != nullptr)
		{
			std::fclose(m_stream);
			m_stream = nullptr;
		}

    }
    
    void File_sender::send(level _level, std::string_view message){
        if (m_stream != nullptr)
		{   
            std::string log_ = "[" + std::string(to_string(_level)) + "] " + std::string(message);
            
			std::fwrite(log_.data(), log_.size(), 1, m_stream);
			std::fflush(m_stream);
		}
    }


}