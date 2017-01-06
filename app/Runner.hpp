template<class Ret, class... Args>
Ret Runner<Ret, Args...>::run_for(duration_t duration, Args... args) {
    start(duration);
    do_running(args...);
    return get_value();
}

template<class Ret, class... Args>
const Ret& Runner<Ret, Args...>::get_value() const {
    return value;
}

template<class Ret, class... Args>
void Runner<Ret, Args...>::set_value(const Ret& new_val) {
    value = new_val;
}

template<class Ret, class... Args>
void Runner<Ret, Args...>::start(duration_t duration) {
    requested_duration = duration;
    start_time = std::chrono::system_clock::now();
}

template<class Ret, class... Args>
bool Runner<Ret, Args...>::can_continue() const {
    const auto now = std::chrono::system_clock::now();
    const auto period = now - start_time;
    return requested_duration > period;
}

template<class Ret, class... Args>
void Runner<Ret, Args...>::do_running(Args... args) {
    while(can_continue()) {
        run(args...);
    }
}
