#include <coroutine>
#include <iostream>
// The caller-level type
struct Generator {
    // The coroutine level type
    struct promise_type {
        using Handle = std::coroutine_handle<promise_type>;
        Generator get_return_object() {
            return Generator{Handle::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
        void unhandled_exception() { }
        int current_value;
    };
    explicit Generator(promise_type::Handle coro) : coro_(coro) {}
    ~Generator() {
        if (coro_) coro_.destroy();
    }
    // Make move-only
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& t) noexcept : coro_(t.coro_) { 
        t.coro_ = {};
    }
    Generator& operator=(Generator&& t) noexcept {
        if (this == &t) return *this;
        if (coro_) coro_.destroy();
        coro_ = t.coro_;
        t.coro_ = {};
        return *this;
    }
    int get_next() {
        coro_.resume();
        return coro_.promise().current_value;
    }
private:
    promise_type::Handle coro_;
};

Generator evenCoroutine() {
    int x = 0;
    while (true) {
        co_yield x+=2;
    }
}

Generator factorialCoroutine() {
    int x = 1;
    int c = 1;
    while (true) {
        c*=x;
        x+=1;
        co_yield c;
        
    }
}

Generator primeCoroutine() {
    int x = -1;
    while (true) {
        x+=2;
        for (int i=3; i<x/2; i++) {
            if (x%i == 0) {goto outer;}
        }
        co_yield x;
    outer:
    }
}
int main() {
    auto c = evenCoroutine();
    //int x = 0;
    for (int i = 0; i<10; i++) {
        std::cout << c.get_next() << "\n";
    }
}