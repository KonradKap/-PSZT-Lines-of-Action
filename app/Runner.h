#pragma once

#include <chrono> 
#include <thread>
#include <mutex>

template<class Ret, class... Args>
class Runner {
    public:
        Ret run_for(std::chrono::milliseconds duration, Args... args);

    protected:
        const Ret& get_value() const;
        void set_value(const Ret& new_val);
    private:
        virtual void run(Args... args) = 0;

        std::thread start(Args... args);
        void stop(std::thread& thread);
        void do_running(Args... args);
        bool can_continue();

        bool continuation;
        std::mutex lock;
        Ret value;
};

#include "Runner.hpp"
