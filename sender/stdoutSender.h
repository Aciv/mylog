#pragma once

#include "sender.h"
#include <filesystem>

namespace Aciv::utility{
    class Stdout_sender: public Sender {
        private:
        
        public:
            Stdout_sender();
            ~Stdout_sender() override = default ;
            void send(level _level, std::string_view message) override;

        private:

            std::FILE* m_stream{ nullptr };
    };
}