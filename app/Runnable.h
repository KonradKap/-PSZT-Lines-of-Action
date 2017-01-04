#pragma once

template<class T>
class Runner;

template<class Ret, class Args>
class Runnable {
    public:
        Runnable(Runner<Runnable<Ret, Args>>& source);
        virtual ~Runnable();

        const Ret& get_value();
        void set_value(const Ret& new_val);
    private:
        Runner<Runnable<Ret, Args>>& source;
};
