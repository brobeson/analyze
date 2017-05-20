#include <QtTest/QtTest>
#include "bounding_box.h"

// this allows bounding_box<int> objects to be added to the data table
Q_DECLARE_METATYPE(analyzer::integer_box)

namespace QTest
{
    template <>
        char* toString(const analyzer::integer_box& box)
        {
            QByteArray a = "(";
            a.append(QByteArray::number(box.left()))
             .append(", ")
             .append(QByteArray::number(box.right()))
             .append(", ")
             .append(QByteArray::number(box.top()))
             .append(", ")
             .append(QByteArray::number(box.bottom()))
             .append(")");
            return qstrdup(a.data());
        }
}

namespace analyzer
{
    bool operator==(const integer_box& a, const integer_box& b)
    {
        return a.left()   == b.left()  &&
               a.right()  == b.right() &&
               a.top()    == b.top()   &&
               a.bottom() == b.bottom();
    }

    /// A set of unit tests for the analyzer::bounding_box class and associated functions.
    class bounding_box_test final: public QObject
    {
        Q_OBJECT
        public:
            /**
             * \brief   Construct a set of bounding box unit tests.
             * \throws  None
             */
            bounding_box_test() = default;

            /**
             * \brief   Copy a set of bounding box unit tests.
             * \throws  None
             */
            bounding_box_test(const bounding_box_test&) = default;

            /**
             * \brief   Move a set of bounding box unit tests.
             * \throws  None
             */
            bounding_box_test(bounding_box_test&&) = default;

            /**
             * \brief   Destroy a bounding box test.
             * \throws  None
             */
            ~bounding_box_test() noexcept = default;

            /**
             * \brief   Copy a set of bounding box unit tests.
             * \return  A reference to this set of unit tests.
             * \throws  None
             */
            bounding_box_test& operator=(const bounding_box_test&) = default;

            /**
             * \brief   Move a set of bounding box unit tests.
             * \return  A reference to this set of unit tests.
             * \throws  None
             */
            bounding_box_test& operator=(bounding_box_test&&) = default;

        private slots:
            /**
             * \brief       Verify that the bounding box default constructor works as described.
             * \throws      None
             */
            void test_default_construction() noexcept
            {
                integer_box b;
                QCOMPARE(b.left(),   0);
                QCOMPARE(b.right(),  0);
                QCOMPARE(b.top(),    0);
                QCOMPARE(b.bottom(), 0);
            }

            /**
             * \brief   Generate test data for testing bounding box construction.
             * \throws  None
             */
            void test_construction_data() noexcept
            {
                // input data
                QTest::addColumn<integer_box::value_type>("column_1");
                QTest::addColumn<integer_box::value_type>("column_2");
                QTest::addColumn<integer_box::value_type>("row_1");
                QTest::addColumn<integer_box::value_type>("row_2");

                // expected data
                QTest::addColumn<integer_box::value_type>("left");
                QTest::addColumn<integer_box::value_type>("right");
                QTest::addColumn<integer_box::value_type>("top");
                QTest::addColumn<integer_box::value_type>("bottom");

                QTest::newRow("0 area")              <<  10 <<  10 <<  10 <<  10 <<  10 << 10 <<  10 << 10;
                QTest::newRow("column 1 < column 2") << -10 <<  10 <<   0 <<   0 << -10 << 10 <<   0 <<  0;
                QTest::newRow("column 2 < column 1") <<  10 << -10 <<   0 <<   0 << -10 << 10 <<   0 <<  0;
                QTest::newRow("row 1 < row 2")       <<   0 <<   0 << -10 <<  10 <<   0 <<  0 << -10 << 10;
                QTest::newRow("row 2 < row 1")       <<   0 <<   0 <<  10 << -10 <<   0 <<  0 << -10 << 10;
            }

            /**
             * \brief       Verify that the bounding box constructor works as described.
             * \throws      None
             */
            void test_construction() noexcept
            {
                QFETCH(integer_box::value_type, column_1);
                QFETCH(integer_box::value_type, column_2);
                QFETCH(integer_box::value_type, row_1);
                QFETCH(integer_box::value_type, row_2);
                try
                {
                    integer_box b(column_1, column_2, row_1, row_2);
                    QTEST(b.left(),   "left");
                    QTEST(b.right(),  "right");
                    QTEST(b.top(),    "top");
                    QTEST(b.bottom(), "bottom");
                }
                catch (std::exception& e)
                {
                    std::string message("caught an exception: ");
                    message.append(e.what());
                    QFAIL(message.c_str());
                }
                catch (...)
                {
                    QFAIL("caught an unknown exception");
                }
            }

            /**
             * \brief   Generate test data for testing bounding box area.
             * \throws  None
             */
            void test_area_data() noexcept
            {
                QTest::addColumn<integer_box>("box");
                QTest::addColumn<integer_box::value_type>("area");

                QTest::newRow("0 area")       << integer_box( 10,   10,   10,  10) <<     0;
                QTest::newRow("all positive") << integer_box( 10,  110,   10, 110) << 10000;
                QTest::newRow("all negative") << integer_box(-10, -110, -110, -10) << 10000;
            }

            /**
             * \brief       Verify that the area function for bounding boxes works as described.
             * \throws      None
             */
            void test_area() noexcept
            {
                QFETCH(integer_box, box);
                QTEST(area(box), "area");
            }

            /**
             * \brief   Generate test data for testing bounding box intersection.
             * \throws  None
             */
            void test_intersection_data()
            {
                QTest::addColumn<integer_box>("a");
                QTest::addColumn<integer_box>("b");
                QTest::addColumn<integer_box>("intersection");

                QTest::newRow("a has 0 area") << integer_box()
                                              << integer_box(0, 10, 0, 10)
                                              << integer_box();
                QTest::newRow("b has 0 area") << integer_box(0, 10, 0, 10)
                                              << integer_box()
                                              << integer_box();
                QTest::newRow("half overlap on the right") << integer_box( 0, 100, 0, 100)
                                                           << integer_box(50, 150, 0, 100)
                                                           << integer_box(50, 100, 0, 100);
                QTest::newRow("half overlap on the left") << integer_box(  0, 100, 0, 100)
                                                          << integer_box(-50,  50, 0, 100)
                                                          << integer_box(  0,  50, 0, 100);
                QTest::newRow("half overlap on the top") << integer_box(0, 100,   0, 100)
                                                         << integer_box(0, 100, -50,  50)
                                                         << integer_box(0, 100,   0,  50);
                QTest::newRow("half overlap on the bottom") << integer_box(0, 100,  0, 100)
                                                            << integer_box(0, 100, 50, 150)
                                                            << integer_box(0, 100, 50, 100);
                QTest::newRow("equal boxes") << integer_box(0, 100, 0, 100)
                                             << integer_box(0, 100, 0, 100)
                                             << integer_box(0, 100, 0, 100);
                QTest::newRow("upper left quarter") << integer_box(0, 100, 0, 100)
                                                    << integer_box(0,  50, 0,  50)
                                                    << integer_box(0,  50, 0,  50);
                QTest::newRow("centered, quarter size") << integer_box( 0, 100,  0, 100)
                                                        << integer_box(25,  75, 25,  75)
                                                        << integer_box(25,  75, 25,  75);
                QTest::newRow("a left of b") << integer_box( 0,  20, 0, 100)
                                             << integer_box(50, 100, 0, 100)
                                             << integer_box( 0,   0, 0,   0);
                QTest::newRow("a right of b") << integer_box(50, 100, 0, 100)
                                              << integer_box( 0,  20, 0, 100)
                                              << integer_box( 0,   0, 0,   0);
                QTest::newRow("a top of b") << integer_box(0, 100,  0,  20)
                                            << integer_box(0, 100, 50, 100)
                                            << integer_box(0,   0,  0,   0);
                QTest::newRow("a bottom of b") << integer_box(0, 100, 50, 100)
                                               << integer_box(0, 100,  0,  20)
                                               << integer_box(0,   0,  0,   0);
            }

            /**
             * \brief   Verify that the intersection function for bounding boxes works as described.
             * \throws  None
             */
            void test_intersection()
            {
                QFETCH(integer_box, a);
                QFETCH(integer_box, b);
                QTEST(intersection(a, b), "intersection");
            }

            /**
             * \brief   Generate test data for testing bounding box union area.
             * \throws  None
             */
            void test_union_data()
            {
                QTest::addColumn<integer_box>("a");
                QTest::addColumn<integer_box>("b");
                QTest::addColumn<int>("union_area");

                QTest::newRow("a has 0 area") << integer_box()
                                              << integer_box(0, 10, 0, 10)
                                              << 100;
                QTest::newRow("b has 0 area") << integer_box(0, 10, 0, 10)
                                              << integer_box()
                                              << 100;
                QTest::newRow("a and b have 0 area") << integer_box()
                                                     << integer_box()
                                                     << 0;
                QTest::newRow("half overlap on the right") << integer_box( 0, 100, 0, 100)
                                                           << integer_box(50, 150, 0, 100)
                                                           << 15'000;
                QTest::newRow("half overlap on the left") << integer_box(  0, 100, 0, 100)
                                                          << integer_box(-50,  50, 0, 100)
                                                          << 15'000;
                QTest::newRow("half overlap on the top") << integer_box(0, 100,   0, 100)
                                                         << integer_box(0, 100, -50,  50)
                                                         << 15'000;
                QTest::newRow("half overlap on the bottom") << integer_box(0, 100,  0, 100)
                                                            << integer_box(0, 100, 50, 150)
                                                            << 15'000;
                QTest::newRow("equal boxes") << integer_box(0, 100, 0, 100)
                                             << integer_box(0, 100, 0, 100)
                                             << 10'000;
                QTest::newRow("upper left quarter") << integer_box(0, 100, 0, 100)
                                                    << integer_box(0,  50, 0,  50)
                                                    << 10'000;
                QTest::newRow("centered, quarter size") << integer_box( 0, 100,  0, 100)
                                                        << integer_box(25,  75, 25,  75)
                                                        << 10000;
            }

            /**
             * \brief   Verify that the union function for bounding boxes works as described.
             * \throws  None
             */
            void test_union()
            {
                QFETCH(integer_box, a);
                QFETCH(integer_box, b);
                QTEST(box_union(a, b), "union_area");
            }
    };
}

QTEST_MAIN(analyzer::bounding_box_test);
#include "bounding_box_test.moc"
