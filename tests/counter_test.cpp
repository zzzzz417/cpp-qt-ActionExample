#include "counter.h"

#include <iostream>

namespace {

bool expect(bool condition, const char *message)
{
    if (!condition) {
        std::cerr << "FAILED: " << message << '\n';
    }
    return condition;
}

} // namespace

int main()
{
    bool passed = true;
    Counter counter;

    passed &= expect(counter.value() == 0, "counter starts at zero");
    counter.increment();
    passed &= expect(counter.value() == 1, "increment adds one");
    counter.decrement();
    counter.decrement();
    passed &= expect(counter.value() == -1, "decrement subtracts one");
    counter.reset();
    passed &= expect(counter.value() == 0, "reset restores zero");

    for (int i = 0; i < Counter::Maximum + 10; ++i) {
        counter.increment();
    }
    passed &= expect(counter.value() == Counter::Maximum, "upper bound is enforced");
    passed &= expect(!counter.canIncrement(), "increment is disabled at upper bound");

    counter.reset();
    for (int i = 0; i < -Counter::Minimum + 10; ++i) {
        counter.decrement();
    }
    passed &= expect(counter.value() == Counter::Minimum, "lower bound is enforced");
    passed &= expect(!counter.canDecrement(), "decrement is disabled at lower bound");

    if (passed) {
        std::cout << "All counter tests passed.\n";
        return 0;
    }
    return 1;
}
