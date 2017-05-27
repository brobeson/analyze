#include "iou.h"

namespace analyze
{
    //-------------------------------------------------------
    //                                     iou class methods
    //-------------------------------------------------------
    iou::iou(const float& value) noexcept:
        m_value(value)
    {}

    iou::value_type iou::value() const noexcept
    {
        return m_value;
    }

    //-------------------------------------------------------
    //                                 iou related functions
    //-------------------------------------------------------
    bool operator==(const iou& a, const iou& b) noexcept
    {
        return a.value() == b.value();
    }

    bool operator!=(const iou& a, const iou& b) noexcept
    {
        return !(a == b);
    }

    bool operator<(const iou& a, const iou& b) noexcept
    {
        return a.value() < b.value();
    }

    bool operator<=(const iou& a, const iou& b) noexcept
    {
        return a.value() <= b.value();
    }

    bool operator>(const iou& a, const iou& b) noexcept
    {
        return a.value() > b.value();
    }

    bool operator>=(const iou& a, const iou& b) noexcept
    {
        return a.value() >= b.value();
    }

    iou operator+(const iou& a, const iou& b) noexcept
    {
        return iou(a.value() + b.value());
    }

    iou operator+(const iou& a, const iou::value_type b) noexcept
    {
        return iou(a.value() + b);
    }

    iou operator+(const iou::value_type a, const iou& b) noexcept
    {
        return iou(a + b.value());
    }

    iou operator-(const iou& a, const iou& b) noexcept
    {
        return iou(a.value() - b.value());
    }

    iou operator-(const iou& a, const iou::value_type b) noexcept
    {
        return iou(a.value() - b);
    }

    iou operator-(const iou::value_type a, const iou& b) noexcept
    {
        return iou(a - b.value());
    }

    iou operator*(const iou& a, const iou& b) noexcept
    {
        return iou(a.value() * b.value());
    }

    iou operator*(const iou& a, const iou::value_type b) noexcept
    {
        return iou(a.value() * b);
    }

    iou operator*(const iou::value_type a, const iou& b) noexcept
    {
        return iou(a * b.value());
    }

    iou operator/(const iou& a, const iou& b) noexcept
    {
        return iou(a.value() / b.value());
    }

    iou operator/(const iou& a, const iou::value_type b) noexcept
    {
        return iou(a.value() / b);
    }

    iou operator/(const iou::value_type a, const iou& b) noexcept
    {
        return iou(a / b.value());
    }
}

