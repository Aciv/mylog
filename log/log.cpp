#include "log.h"
#include <iostream>

namespace Aciv::utility{

        Log::Log(){
            m_is_Async = false;
            m_queue = nullptr;
            m_write_thread = nullptr;   
            
        }

        Log::~Log(){
            
            if(m_write_thread && m_write_thread->joinable()){
                
                while(!m_queue->empty()){
                    m_queue->flush();
                }
                std::cout << std::flush;
                m_queue->Close();
                m_write_thread->join();
            }
            // std::cout << std::flush;
            //std::lock_guard<std::mutex> locker(m_mtx);
            //std::cout << "what ?" << std::flush;
        }

        void Log::init(std::size_t _max_queue_size,
                            std::size_t _message_limit){

             m_message_limit = _message_limit;
            if(_max_queue_size > 0){
                m_is_Async = true;
                if(!m_queue){
                    std::unique_ptr<BlockDeque<Queue_item>> new_queue
                                (new BlockDeque<Queue_item>(_max_queue_size));
                    m_queue = std::move(new_queue);

                    std::unique_ptr<std::thread> new_thread
                                (new std::thread(&Log::write_func, this));
                    m_write_thread = std::move(new_thread);
                }
            }else{
                m_is_Async = false;
            }
            m_buffer.reset();
        }

        void Log::set_pattern(std::string_view _pattern){
            std::lock_guard<std::mutex> locker(m_mtx);
            m_pattern.set_pattern(_pattern);

        }   

        void Log::add_sender(std::unique_ptr<Sender> _sender){
            std::lock_guard<std::mutex> locker(m_mtx);
            m_senders.push_back(std::move(_sender));
        }

        void Log::write_func(){
            Queue_item item;
            while(m_queue->pop(item)) {
                //std::lock_guard<std::mutex> locker(m_mtx);
                for(auto& sender : m_senders){
                
                    if(sender->should_sink(item.log_level)){
                        
                        sender->send(item.log_msg);
                    }
                       
                }
            }
        }

        void Log::record(level _level, const std::string &_log_msg){
            {
                if(_log_msg.size() >= m_message_limit){
                    return;
                }
                
                std::lock_guard<std::mutex> locker(m_mtx);
                m_buffer.reset();

                m_pattern.genrate(_level, _log_msg.data(), m_buffer);

                if(m_is_Async){
                    m_queue->push_back({_level, 
                            std::move(m_buffer.retrieve_to_string(m_buffer.size()))} );
                }
                else{
                    std::cout << m_buffer.retrieve_to_string(m_buffer.size());
                }
            }
            
        }

        void Log::flush(){
            if(m_is_Async){
                m_queue->flush();
            }
            //std::cout << std::flush;
        }

}