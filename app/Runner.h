#pragma once

#include <chrono> 

template<class Ret, class... Args>
class Runner {
    public:
        typedef decltype(std::chrono::system_clock::now()) time_t;
        typedef decltype(time_t() - time_t()) duration_t;

        Ret run_for(duration_t duration, Args... args);

    protected:
        const Ret& get_value() const;
        void set_value(const Ret& new_val);
    private:
        virtual void run(Args... args) = 0;

        void start(duration_t);
        bool can_continue() const;
        void do_running(Args... args);

        time_t start_time;
        duration_t requested_duration;
        Ret value;
};

#include "Runner.hpp"
