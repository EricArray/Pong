#pragma once

#include <cassert>
#include <functional>
#include <variant>

template<typename Data, typename... Args>
class Lazy {
public:
    using Func = std::function<Data(Args...)>;

    explicit Lazy(Func func) : data(func) {}

    Lazy(Lazy&& other) noexcept : data(std::move(other.data)) {}

    Lazy& operator=(Lazy&& other) noexcept {
        this->data = std::move(other.data);
        return *this;
    }

    Data& get(Args... args) {
        if (auto funcPtr = std::get_if<Func>(&this->data)) {
            this->data = (*funcPtr)(args...);
        }
        return std::get<Data>(this->data);
    }

private:
    std::variant<Func, Data> data;
};

namespace test::lazy {
    inline void should_not_init_until_get_is_called() {
        bool called = false;
        Lazy<int> lazy([&called]() {
            called = true;
            return 123;
        });

        assert(!called);
        assert(lazy.get() == 123);
        assert(called);
    }

    inline void should_only_call_once() {
        int callCount = 0;
        Lazy<int> lazy([&callCount]() {
            callCount += 1;
            return 123;
        });

        assert(callCount == 0);
        assert(lazy.get() == 123);
        assert(callCount == 1);
        assert(lazy.get() == 123);
        assert(callCount == 1);
    }

    inline void should_accept_arguments() {
        Lazy<int, int> lazy([](int x) {
            return x * 2;
        });

        assert(lazy.get(10) == 20);
        assert(lazy.get(100) == 20);
    }

}
