#include "log/log.h"
#include <vector>
#include "sender/stdoutSender.h"
#include "sender/fileSender.h"

int main(){
    {
        Aciv::utility::Log& logger = Aciv::utility::Log::get_Instance();
        logger.init(1024);
        
        
        logger.add_sender(std::make_unique<Aciv::utility::Stdout_sender>());
        logger.add_sender(std::make_unique<Aciv::utility::File_sender>("logs/log.txt"));
        
        logger.m_senders[1]->set_level_filter(Aciv::utility::level::warning | Aciv::utility::level::critical);
        logger.m_senders[0]->set_level_filter(Aciv::utility::level::info );

        logger.set_pattern("[%l] [%y] [%m] [%d] [%w] [%T] [%t]: %v\n");

        std::vector<std::unique_ptr<std::thread>> threads;
        for(int i = 0; i < 5; ++i){
            threads.emplace_back(new std::thread([&logger, i](){
                for(int j = 0; j < 20; ++j){
                    std::string msg = "Log message from thread " + std::to_string(i) + 
                                      ", message number " + std::to_string(j);
                    Aciv::utility::level tmp_level = (j % 2 == 0) ?
                                    Aciv::utility::level::info : Aciv::utility::level::warning;
                    logger.record(tmp_level, "wcnm");
                }
            }));
        } 
        
        for(auto& t : threads){ 
            if(t->joinable()){
                t->join();
            }
        }
    }
    return 0;

}