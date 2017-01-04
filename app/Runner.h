#pragma once

#include <chrono> 
#include <thread>
#include <mutex>

template<class Ret, class... Args>
class Runner {
    public:
        Ret run_for(std::chrono::milliseconds duration, Args... args);

    protected:
        const Ret& get_value();
        void set_value(const Ret& new_val);
    private:
        virtual void run(Args... args) = 0;

        std::thread start(Args... args);
        //void stop(std::thread& thread);
        void stop();
        void do_running(Args... args);
        bool can_continue();

        bool continuation;
        std::mutex cont_lock;
        std::mutex value_lock;
        Ret value;
};

#include "Runner.hpp"
