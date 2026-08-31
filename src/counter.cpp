#include "counter.h"

int Counter::value() const noexcept
{
    return m_value;
}

bool Counter::canIncrement() const noexcept
{
    return m_value < Maximum;
}

bool Counter::canDecrement() const noexcept
{
    return m_value > Minimum;
}

void Counter::increment() noexcept
{
    if (canIncrement()) {
        ++m_value;
    }
}

void Counter::decrement() noexcept
{
    if (canDecrement()) {
        --m_value;
    }
}

void Counter::reset() noexcept
{
    m_value = 0;
}
