#ifndef ANALYZE_IOU_H
#define ANALYZE_IOU_H

#include "bounding_box.h"
#include <iostream>

namespace analyze
{
    /**
     * \brief       Represents an intersection-over-union (IoU) metric between two bounding boxes.
     * \details     The formula for an IoU is:
     *              \f$ IoU(B,G) = \frac{B \cap G}{B \cup G} \f$
     *              This is implemented as
     *              \f$ IoU(B,G) = \frac{A(B \cap G)}{A(B) + A(G) - A(B \cap G)} \f$
     *              where \f$ A(\dot) \f$ is the area of \f$ \dot \f$.
     */
    class iou final
    {
    public:
        /// The type of the IoU value.
        using value_type = float;

        /**
         * \brief   Construct a default IoU.
         * \throws  None
         * \details The IoU value is 0.
         */
        iou() = default;

        /**
         * \brief       Construct an IoU object with the specified value.
         * \param[in]   value   The value to assign to the IoU. \f$value \in [0, 1]\f$
         * \throws      None
         */
        explicit iou(const float& value) noexcept;

        /**
         * \brief   Copy an IoU object.
         * \throws  None
         */
        iou(const iou&) = default;

        /**
         * \brief   Move an IoU object.
         * \throws  None
         */
        iou(iou&&) = default;

        /**
         * \brief   Destroy an IoU object.
         * \throws  None
         */
        ~iou() noexcept = default;

        /**
         * \brief   Copy an IoU object.
         * \return  A reference to this IoU object.
         * \throws  None
         */
        iou& operator=(const iou&) = default;

        /**
         * \brief   Move an IoU object.
         * \return  A reference to this IoU object.
         * \throws  None
         */
        iou& operator=(iou&&) = default;

        /**
         * \brief       Set the IoU value.
         * \param[in]   v   The new value to set.
         * \throws      None
         */
        iou& operator=(const iou::value_type v) noexcept;

        /**
         * \brief   Query the IoU value.
         * \return  The IoU value. This is a proportion, on [0, 1].
         * \throws  None
         */
        value_type value() const noexcept;

        /**
         * \brief       Add an IoU value to this IoU.
         * \param[in]   a   The IoU value to add to this IoU.
         * \throws      None
         */
        iou& operator+=(const iou& a) noexcept;

        /// \copydoc    operator+=(const iou&)
        iou& operator+=(const iou::value_type a) noexcept;

        /**
         * \brief       Subtract an IoU value from this IoU.
         * \param[in]   a   The IoU value to subtract from this IoU.
         * \throws      None
         */
        iou& operator-=(const iou& a) noexcept;

        /// \copydoc    operator-=(const iou&)
        iou& operator-=(const iou::value_type a) noexcept;

        /**
         * \brief       Multiply an IoU value with this IoU.
         * \param[in]   a   The IoU value to multiply with this IoU.
         * \throws      None
         */
        iou& operator*=(const iou& a) noexcept;

        /// \copydoc    operator*=(const iou&)
        iou& operator*=(const iou::value_type a) noexcept;

        /**
         * \brief       Divide this IoU by another IoU value.
         * \param[in]   a   The IoU value by which to divide this.
         * \throws      None
         * \warning     This operator does not guard against division by zero.
         */
        iou& operator/=(const iou& a) noexcept;

        /// \copydoc    operator/=(const iou&)
        iou& operator/=(const iou::value_type a) noexcept;

        /**
         * \brief       Divide this IoU by another IoU value.
         * \param[in]   a   The IoU value by which to divide this.
         * \throws      None
         * \warning     This operator does not guard against division by zero.
         */
        iou& operator%=(const iou& a) noexcept;

        /// \copydoc    operator/=(const iou&)
        iou& operator%=(const iou::value_type a) noexcept;

        /**
         * \brief   Negate this IoU value.
         * \throws  None
         */
        iou operator-() noexcept;

    private:
        float m_value = 0.0f; ///< The value of the IoU.
    };

    /// \name Comparison
    /// \{

    /**
     * \brief       Compare two IoU objects for equality.
     * \param[in]   a,b     The two IoU objects to compare.
     * \retval      true    \a a is equivalent to \a b.
     * \retval      false   \a a is not equivalent to \a b.
     * \throws      None
     * \details     This function uses a fuzzy comparison since iou::value_type is a floating point
     *              type. This allows for IoU values very close to each other to be considered
     *              equivalent.
     */
    bool operator==(const iou& a, const iou& b) noexcept;

    /**
     * \brief       Compare two IoU objects for inequality.
     * \param[in]   a,b     The two IoU objects to compare.
     * \retval      true    \a a is not equivalent to \a b.
     * \retval      false   \a a is equivalent to \a b.
     * \throws      None
     * \details     This function uses a fuzzy comparison since iou::value_type is a floating point
     *              type. This allows for IoU values very close to each other to be considered
     *              equivalent.
     */
    bool operator!=(const iou& a, const iou& b) noexcept;

    /**
     * \brief       Query if one IoU is less than another.
     * \param[in]   a,b     The two IoU objects to compare.
     * \retval      true    \a a is less than \a b.
     * \retval      false   \a a is greater than, or equal to, \a b.
     * \throws      None
     */
    bool operator<(const iou& a, const iou& b) noexcept;

    /**
     * \brief       Query if one IoU is less than, or equal to, another.
     * \param[in]   a,b     The two IoU objects to compare.
     * \retval      true    \a a is less than, or equal to, \a b.
     * \retval      false   \a a is greater than \a b.
     * \throws      None
     * \details     This function uses a fuzzy comparison since iou::value_type is a floating point
     *              type. This allows for IoU values very close to each other to be considered
     *              equivalent.
     */
    bool operator<=(const iou& a, const iou& b) noexcept;

    /**
     * \brief       Query if one IoU is greater than another.
     * \param[in]   a,b     The two IoU objects to compare.
     * \retval      true    \a a is greater than \a b.
     * \retval      false   \a a is less than, or equal to, \a b.
     * \throws      None
     */
    bool operator>(const iou& a, const iou& b) noexcept;

    /**
     * \brief       Query if one IoU is greater than, or equal to, another.
     * \param[in]   a,b     The two IoU objects to compare.
     * \retval      true    \a a is greater than, or equal to, \a b.
     * \retval      false   \a a is less than \a b.
     * \throws      None
     * \details     This function uses a fuzzy comparison since iou::value_type is a floating point
     *              type. This allows for IoU values very close to each other to be considered
     *              equivalent.
     */
    bool operator>=(const iou& a, const iou& b) noexcept;
    /// \}

    /// \name Arithmetic
    /// \{

    /**
     * \brief       Add two IoU objects.
     * \param[in]   a,b     The two objects to add.
     * \return      \f$ f(a,b) = a + b \f$
     * \throws      None
     */
    iou operator+(const iou& a, const iou& b) noexcept;

    /// copydoc operator+(const iou&, const iou&)
    iou operator+(const iou& a, const iou::value_type b) noexcept;

    /// copydoc operator+(const iou&, const iou&)
    iou operator+(const iou::value_type a, const iou& b) noexcept;

    /**
     * \brief       Subtract one IoU value from another.
     * \param[in]   a,b     The two IoU's to subtract.
     * \return      \f$ f(a,b) = a - b \f$
     * \throws      None
     */
    iou operator-(const iou& a, const iou& b) noexcept;

    /// copydoc operator-(const iou&, const iou&)
    iou operator-(const iou& a, const iou::value_type b) noexcept;

    /// copydoc operator-(const iou&, const iou&)
    iou operator-(const iou::value_type a, const iou& b) noexcept;

    /**
     * \brief       Multiply two IoU values.
     * \param[in]   a,b     The two IoU's to multiply.
     * \return      The product of two IoU values.
     * \return      \f$ f(a,b) = a \times b \f$
     * \throws      None
     */
    iou operator*(const iou& a, const iou& b) noexcept;

    /// copydoc operator*(const iou&, const iou&)
    iou operator*(const iou& a, const iou::value_type b) noexcept;

    /// copydoc operator*(const iou&, const iou&)
    iou operator*(const iou::value_type a, const iou& b) noexcept;

    /**
     * \brief       Divide two IoU values.
     * \param[in]   a,b     The two Iou's to divide.
     * \return      \f$ f(a,b) = \frac{a}{b} \f$
     * \throws      None
     * \warning     This operator does not check for division by zero.
     */
    iou operator/(const iou& a, const iou& b) noexcept;

    /// copydoc operator/(const iou&, const iou&)
    iou operator/(const iou& a, const iou::value_type b) noexcept;

    /// copydoc operator/(const iou&, const iou&)
    iou operator/(const iou::value_type a, const iou& b) noexcept;

    /**
     * \brief       Modulo two IoU values.
     * \param[in]   a,b     The two Iou's to modulo.
     * \return      std::fmod(a.value(), b.value())
     * \throws      None
     * \warning     This operator does not check for division by zero.
     */
    iou operator%(const iou& a, const iou& b) noexcept;

    /// copydoc operator/(const iou&, const iou&)
    iou operator%(const iou& a, const iou::value_type b) noexcept;

    /// copydoc operator/(const iou&, const iou&)
    iou operator%(const iou::value_type a, const iou& b) noexcept;

    /// \}

    /**
     * \brief       Construct an IoU for two bounding boxes.
     * \tparam      T           The data type of the bounding box coordinates.
     * \param[in]   box1,box2   The two bounding boxes for which to calculate the IoU.
     * \throws      None
     * \todo        Handle the case of division by 0
     */
    template <class T>
    iou make_iou(const bounding_box<T>& box1, const bounding_box<T>& box2) noexcept
    {
        try
        {
            const float intersection_area = area(intersection(box1, box2));
            const float area1             = area(box1);
            const float area2             = area(box2);
            return iou(intersection_area / (area1 + area2 - intersection_area));
        }
        catch (...)
        {
            return iou();
        }
    }

    /**
     * \brief           Write an IoU value to an output stream.
     * \tparam          CharT   See [std::basic_ostream](http://en.cppreference.com/w/cpp/io/basic_ostream).
     * \tparam          Traits  See [std::basic_ostream](http://en.cppreference.com/w/cpp/io/basic_ostream).
     * \param[in,out]   output  The output stream to which to write the IoU.
     * \param[in]       i       The IoU to write.
     * \throws          None
     */
    template <class CharT, class Traits>
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& output,
                                                  const iou& i) noexcept
    {
        return output << i.value();
    }
}

#endif
