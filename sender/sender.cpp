#include "sender.h"


namespace Aciv::utility{

    void Sender::set_level_filter(level _level_filter){
        std::lock_guard<std::mutex> locker(m_mtx);
        m_level_filter = _level_filter;
    }
            
    bool Sender::should_sink(level _log_level){
        std::lock_guard<std::mutex> locker(m_mtx);

        if(has_level(m_level_filter, level::all) || 
           has_level(m_level_filter, _log_level)){
            return true;
        }
        
        return false;
    }
}