template<class Ret, class... Args>
bool Runner<Ret, Args...>::can_continue() {
    const std::lock_guard<std::mutex> guard(cont_lock);
    return continuation;
}

template<class Ret, class... Args>
void Runner<Ret, Args...>::do_running(Args... args) {
    while(can_continue()) {
        run(args...);
    }
}

template<class Ret, class... Args>
std::thread Runner<Ret, Args...>::start(Args... args) {
    continuation = true;
    return std::thread(std::bind(&Runner<Ret, Args...>::do_running, this, args...));
}

//template<class Ret, class... Args>
//void Runner<Ret, Args...>::stop(std::thread& thread) {
template<class Ret, class... Args>
void Runner<Ret, Args...>::stop() {
    {
        const std::lock_guard<std::mutex> guard(cont_lock);
        continuation = false;
    }
    //thread.detach();
}

template<class Ret, class... Args>
const Ret& Runner<Ret, Args...>::get_value() {
    const std::lock_guard<std::mutex> guard(value_lock);
    return value;
}

template<class Ret, class... Args>
void Runner<Ret, Args...>::set_value(const Ret& new_val) {
    const std::lock_guard<std::mutex> guard(value_lock);
    value = new_val;
}

template<class Ret, class... Args>
Ret Runner<Ret, Args...>::run_for(std::chrono::milliseconds duration, Args... args) {
    auto thread = start(args...);
    std::this_thread::sleep_for(duration);
    //stop(thread);
    stop();
    thread.join(); //new
    return get_value();
}
