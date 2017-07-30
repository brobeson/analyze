#include "iou.h"
#include <QtGlobal>

namespace analyze
{
    //-------------------------------------------------------
    //                                     iou class methods
    //-------------------------------------------------------
    iou::iou(const float& value) noexcept : m_value(value) {}

    iou& iou::operator=(const iou::value_type v) noexcept
    {
        m_value = v;
        return *this;
    }

    iou::value_type iou::value() const noexcept
    {
        return m_value;
    }

    iou& iou::operator+=(const iou& a) noexcept
    {
        m_value += a.m_value;
        return *this;
    }

    iou& iou::operator+=(const iou::value_type a) noexcept
    {
        m_value += a;
        return *this;
    }

    iou& iou::operator-=(const iou& a) noexcept
    {
        m_value -= a.m_value;
        return *this;
    }

    iou& iou::operator-=(const iou::value_type a) noexcept
    {
        m_value -= a;
        return *this;
    }

    iou& iou::operator*=(const iou& a) noexcept
    {
        m_value *= a.m_value;
        return *this;
    }

    iou& iou::operator*=(const iou::value_type a) noexcept
    {
        m_value *= a;
        return *this;
    }

    iou& iou::operator/=(const iou& a) noexcept
    {
        m_value /= a.m_value;
        return *this;
    }

    iou& iou::operator/=(const iou::value_type a) noexcept
    {
        m_value /= a;
        return *this;
    }

    iou& iou::operator%=(const iou& a) noexcept
    {
        m_value = std::fmod(m_value, a.m_value);
        return *this;
    }

    iou& iou::operator%=(const iou::value_type a) noexcept
    {
        m_value = std::fmod(m_value, a);
        return *this;
    }

    iou iou::operator-() noexcept
    {
        return iou(-m_value);
    }

    //-------------------------------------------------------
    //                                        iou comparison
    //-------------------------------------------------------
    bool operator==(const iou& a, const iou& b) noexcept
    {
        return qFuzzyCompare(a.value(), b.value());
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
        // need to take advantage of fuzzy equality here
        return (a < b) || (a == b);
    }

    bool operator>(const iou& a, const iou& b) noexcept
    {
        return a.value() > b.value();
    }

    bool operator>=(const iou& a, const iou& b) noexcept
    {
        // need to take advantage of fuzzy equality here
        return (a > b) || (a == b);
    }

    //-------------------------------------------------------
    //                                        iou arithmetic
    //-------------------------------------------------------
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

    iou operator%(const iou& a, const iou& b) noexcept
    {
        return iou(std::fmod(a.value(), b.value()));
    }

    iou operator%(const iou& a, const iou::value_type b) noexcept
    {
        return iou(std::fmod(a.value(), b));
    }

    iou operator%(const iou::value_type a, const iou& b) noexcept
    {
        return iou(std::fmod(a, b.value()));
    }
}
