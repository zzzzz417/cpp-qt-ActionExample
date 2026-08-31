#pragma once

class Counter
{
public:
    static constexpr int Minimum = -99;
    static constexpr int Maximum = 99;

    [[nodiscard]] int value() const noexcept;
    [[nodiscard]] bool canIncrement() const noexcept;
    [[nodiscard]] bool canDecrement() const noexcept;

    void increment() noexcept;
    void decrement() noexcept;
    void reset() noexcept;

private:
    int m_value = 0;
};
