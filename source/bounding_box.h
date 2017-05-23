#ifndef ANALYZER_BOUNDING_BOX_H
#define ANALYZER_BOUNDING_BOX_H

#include <algorithm>
#include <cmath>

namespace analyzer
{
    /**
     * \brief       Represents a bounding box on an image.
     * \tparam      T   The data type representing the box coordinates.
     * \details     The bounding box assumes image coordinates increase left to right, and top to
     *              bottom.
     */
    template <class T>
    class bounding_box final
    {
        public:
            /// The data type representing the bounding box coordinates.
            using value_type = T;

            /**
             * \brief       Construct a default bounding box.
             * \throws      None
             * \details     The box coordinates are all set to 0.
             */
            bounding_box() = default;

            /**
             * \brief       Construct a bounding box.
             * \param[in]   column_1,column_2   The numbers which define the bounding box columns.
             *                                  The smaller of the two values is designated as the
             *                                  left(), and the larger is designated as the right().
             * \param[in]   row_1,row_2         The numbers which define the bounding box rows. The
             *                                  smaller of the two values is designated as the
             *                                  top(), and the larger is designated as the right().
             * \throws      None
             */
            bounding_box(const value_type& column_1,
                         const value_type& column_2,
                         const value_type& row_1,
                         const value_type& row_2) noexcept:
                m_left(std::min(column_1, column_2)),
                m_right(std::max(column_1, column_2)),
                m_top(std::min(row_1, row_2)),
                m_bottom(std::max(row_1, row_2))
                {}

            /**
             * \brief   Copy a bounding box.
             * \throws  None
             */
            bounding_box(const bounding_box&) = default;

            /**
             * \brief   Move a bounding box.
             * \throws  None
             */
            bounding_box(bounding_box&&) = default;

            /**
             * \brief   Destroy a bounding box.
             * \throws  None
             */
            ~bounding_box() noexcept = default;

            /**
             * \brief   Copy a bounding box.
             * \return  A reference to this bounding box.
             * \throws  None
             */
            bounding_box& operator=(const bounding_box&) = default;

            /**
             * \brief   Move a bounding box.
             * \return  A reference to this bounding box.
             * \throws  None
             */
            bounding_box& operator=(bounding_box&&) = default;

            /**
             * \brief   Query the box's left side coordinate.
             * \return  The coordinate of the left side of the box.
             * \throws  None
             */
            value_type left() const noexcept { return m_left; }

            /**
             * \brief   Query the box's right side coordinate.
             * \return  The coordinate of the right side of the box.
             * \throws  None
             */
            value_type right() const noexcept { return m_right; }

            /**
             * \brief   Query the box's top side coordinate.
             * \return  The coordinate of the top side of the box.
             * \throws  None
             */
            value_type top() const noexcept { return m_top; }

            /**
             * \brief   Query the box's bottom side coordinate.
             * \return  The coordinate of the bottom side of the box.
             * \throws  None
             */
            value_type bottom() const noexcept { return m_bottom; }

        private:
            value_type m_left   = 0, ///< The coordinate for the box's left side.
                       m_right  = 0, ///< The coordinate for the box's right side.
                       m_top    = 0, ///< The coordinate for the box's top.
                       m_bottom = 0; ///< The coordinate for the box's bottom.
    };

    /// Alias a bounding box type based on integer data.
    using integer_box = bounding_box<int>;

    /**
     * \brief       Calculate the area of a bounding box.
     * \tparam      T       The data type of the bounding box coordinates.
     * \param[in]   box     The bounding box for which to calculate the area.
     * \return      The area of the bounding box, measured in pixel coordinates.
     * \throws      None
     * \related     bounding_box
     */
    template <class T>
        T area(const bounding_box<T>& box) noexcept
        {
            return std::fabs(box.left() - box.right()) * std::fabs(box.top() - box.bottom());
        }

    /**
     * \brief       Calculate the intersection of two bounding boxes.
     * \tparam      T     The data type of the bounding box coordinates.
     * \param[in]   a,b   The boxes for which to calculate an intersection.
     * \return      A bounding box which represents the intersection of \a a and \a b.
     * \retval      bounding_box<T>(0, 0, 0, 0)   This indicates that \a a and \a b do not
     *                                            intersect.
     * \throws      None
     * \related     bounding_box
     */
    template <class T>
        bounding_box<T> intersection(const bounding_box<T>& a, const bounding_box<T>& b) noexcept
        {
            if ((a.bottom() < b.top())  ||
                (b.bottom() < a.top())  ||
                (a.right()  < b.left()) ||
                (b.right()  < a.left()))
            {
                return bounding_box<T>();
            }

            return bounding_box<T>(std::max(a.left(),   b.left()),
                                   std::min(a.right(),  b.right()),
                                   std::max(a.top(),    b.top()),
                                   std::min(a.bottom(), b.bottom()));
        }

    /**
     * \brief       Calculate the area of the union of two bounding boxes.
     * \tparam      T     The data type of the bounding box coordinates.
     * \param[in]   a,b   The boxes for which to calculate the union.
     * \return      The area of the union of the two boxes. Note that the union is not guaranteed to
     *              be a box, so only the area is available.
     * \throws      None
     * \related     bounding_box
     * \details     The union area is calculated as
     *              \f$ A_{\cup}(a,b) = A(a) + A(b) - A(a \cap b) \f$
     */
    template <class T>
        T box_union(const bounding_box<T>& a, const bounding_box<T>& b) noexcept
        {
            return area(a) + area(b) - area(intersection(a, b));
        }
}

#endif

