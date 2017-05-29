#include <sstream>
#include <QtTest/QtTest>
#include "iou.h"

// this allows iou objects to be added to the data table
Q_DECLARE_METATYPE(analyze::iou)

namespace QTest
{
    template <>
        char* toString(const std::string& s)
        {
            QByteArray a = s.c_str();
            return qstrdup(a);
        }

    template <>
        char* toString(const analyze::iou& i)
        {
            QByteArray a = QByteArray::number(i.value());
            return qstrdup(a);
        }
}

namespace analyze
{
    void make_comparison_table(const bool less_result, const bool equal_result, const bool greater_result)
    {
        QTest::addColumn<iou> ("a");
        QTest::addColumn<iou> ("b");
        QTest::addColumn<bool>("expected_result");

        QTest::newRow("a < b") << iou(0.1f) << iou(0.2f) << less_result;
        QTest::newRow("a = b") << iou(0.2f) << iou(0.2f) << equal_result;
        QTest::newRow("a > b") << iou(1.0f) << iou(0.4f) << greater_result;
    }

    /// A set of unit tests for the analyze::iou class and associated functions.
    class iou_test final: public QObject
    {
        Q_OBJECT
        public:
            /**
             * \brief   Construct a set of IoU unit tests.
             * \throws  None
             */
            iou_test() = default;

            /**
             * \brief   Copy a set of IoU unit tests.
             * \throws  None
             */
            iou_test(const iou_test&) = default;

            /**
             * \brief   Move a set of IoU unit tests.
             * \throws  None
             */
            iou_test(iou_test&&) = default;

            /**
             * \brief   Destroy a IoU test.
             * \throws  None
             */
            ~iou_test() noexcept = default;

            /**
             * \brief   Copy a set of IoU unit tests.
             * \return  A reference to this set of unit tests.
             * \throws  None
             */
            iou_test& operator=(const iou_test&) = default;

            /**
             * \brief   Move a set of IoU unit tests.
             * \return  A reference to this set of unit tests.
             * \throws  None
             */
            iou_test& operator=(iou_test&&) = default;

        private slots:
            /**
             * \brief       Verify that the IoU default constructor works as described.
             * \throws      None
             */
            void test_default_construction() noexcept
            {
                iou i;
                QCOMPARE(i.value(), static_cast<iou::value_type>(0));
            }

            /**
             * \brief   Generate test data for testing IoU construction with an IoU value.
             * \throws  None
             */
            void test_value_construction_data() noexcept
            {
                QTest::addColumn<iou::value_type>("value");

                QTest::newRow("negative")  << -1.0f;
                QTest::newRow("zero")      <<  0.0f;
                QTest::newRow("one half")  <<  0.5f;
                QTest::newRow("one")       <<  1.0f;
                QTest::newRow("excessive") <<  1.1f;
            }

            /**
             * \brief       Verify that the IoU constructor works as described.
             * \throws      None
             */
            void test_value_construction() noexcept
            {
                QFETCH(iou::value_type, value);
                try
                {
                    iou i(value);
                    QTEST(i.value(), "value");
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

            void test_operator_assign() noexcept
            {
                iou a(4.0f);
                a = 5.0f;
                QCOMPARE(a.value(), 5.0f);
            }

            void test_operator_add_assign() noexcept
            {
                iou a(4.0f);
                a += iou(5.0f);
                QCOMPARE(a.value(), 9.0f);

                a += 5.0f;
                QCOMPARE(a.value(), 14.0f);
            }

            void test_operator_subtract_assign() noexcept
            {
                iou a(4.0f);
                a -= iou(5.0f);
                QCOMPARE(a.value(), -1.0f);

                a -= 5.0f;
                QCOMPARE(a.value(), -6.0f);
            }

            void test_operator_multiply_assign() noexcept
            {
                iou a(4.0f);
                a *= iou(5.0f);
                QCOMPARE(a.value(), 20.0f);

                a *= 5.0f;
                QCOMPARE(a.value(), 100.0f);
            }

            void test_operator_divide_assign() noexcept
            {
                iou a(4.0f);
                a /= iou(5.0f);
                QCOMPARE(a.value(), 4.0f / 5.0f);

                a /= 5.0f;
                QCOMPARE(a.value(), 4.0f / 5.0f / 5.0f);
            }

            void test_operator_modulo_assign() noexcept
            {
                iou a(23.0f);
                a %= iou(5.0f);
                QCOMPARE(a.value(), std::fmod(23.0f, 5.0f));

                a %= 2.0f;
                QCOMPARE(a.value(), std::fmod(std::fmod(23.0f, 5.0f), 2.0f));
            }

            void test_operator_negate() noexcept
            {
                iou a(4.0f);
                QCOMPARE(-a, iou(-4.0f));

                a = 0.0f;
                QCOMPARE(-a, iou(0.0f));
            }

            void test_operator_equal_data() noexcept
            {
                make_comparison_table(false, true, false);
            }

            void test_operator_equal() noexcept
            {
                QFETCH(iou, a);
                QFETCH(iou, b);
                QTEST(a == b, "expected_result");
            }

            void test_operator_not_equal_data() noexcept
            {
                make_comparison_table(true, false, true);
            }

            void test_operator_not_equal() noexcept
            {
                QFETCH(iou, a);
                QFETCH(iou, b);
                QTEST(a != b, "expected_result");
            }

            void test_operator_less_data() noexcept
            {
                make_comparison_table(true, false, false);
            }

            void test_operator_less() noexcept
            {
                QFETCH(iou, a);
                QFETCH(iou, b);
                QTEST(a < b, "expected_result");
            }

            void test_operator_less_or_equal_data() noexcept
            {
                make_comparison_table(true, true, false);
            }

            void test_operator_less_or_equal() noexcept
            {
                QFETCH(iou, a);
                QFETCH(iou, b);
                QTEST(a <= b, "expected_result");
            }

            void test_operator_greater_data() noexcept
            {
                make_comparison_table(false, false, true);
            }

            void test_operator_greater() noexcept
            {
                QFETCH(iou, a);
                QFETCH(iou, b);
                QTEST(a > b, "expected_result");
            }

            void test_operator_greater_or_equal_data() noexcept
            {
                make_comparison_table(false, true, true);
            }

            void test_operator_greater_or_equal() noexcept
            {
                QFETCH(iou, a);
                QFETCH(iou, b);
                QTEST(a >= b, "expected_result");
            }

            void test_operator_stream_insertion() noexcept
            {
                std::ostringstream s;
                const iou i(4.5f);
                s << i;
                QCOMPARE(s.str(), std::string("4.5"));
            }

            void test_operator_add_data() noexcept
            {
                QTest::addColumn<iou::value_type>("a");
                QTest::addColumn<iou::value_type>("b");
                QTest::addColumn<iou>            ("expected_result");

                QTest::newRow(" 0.0 +  0.0 =  0.0") <<  0.0f <<  0.0f << iou( 0.0f);
                QTest::newRow(" 0.0 +  0.4 =  0.4") <<  0.0f <<  0.4f << iou( 0.4f);
                QTest::newRow(" 0.4 +  0.0 =  0.4") <<  0.4f <<  0.0f << iou( 0.4f);
                QTest::newRow(" 1.0 + -0.3 =  0.7") <<  1.0f << -0.3f << iou( 0.7f);
                QTest::newRow("-0.3 +  1.0 =  0.7") << -0.3f <<  1.0f << iou( 0.7f);
                QTest::newRow("-0.3 + -0.7 = -1.0") << -0.3f << -0.7f << iou(-1.0f);
                QTest::newRow("-0.7 + -0.3 = -1.0") << -0.7f << -0.3f << iou(-1.0f);
            }

            void test_operator_add() noexcept
            {
                QFETCH(iou::value_type, a);
                QFETCH(iou::value_type, b);

                QTEST(iou(a) + iou(b), "expected_result");
                QTEST(iou(a) +     b , "expected_result");
                QTEST(    a  + iou(b), "expected_result");
            }

            void test_operator_subtract_data() noexcept
            {
                QTest::addColumn<iou::value_type>("a");
                QTest::addColumn<iou::value_type>("b");
                QTest::addColumn<iou>("expected_result");

                QTest::newRow(" 0.0 -  0.0 =  0.0") <<  0.0f <<  0.0f << iou( 0.0f);
                QTest::newRow(" 0.0 -  0.4 = -0.4") <<  0.0f <<  0.4f << iou(-0.4f);
                QTest::newRow(" 0.4 -  0.0 =  0.4") <<  0.4f <<  0.0f << iou( 0.4f);
                QTest::newRow(" 1.0 - -0.3 =  1.3") <<  1.0f << -0.3f << iou( 1.3f);
                QTest::newRow("-0.3 -  1.0 = -1.3") << -0.3f <<  1.0f << iou(-1.3f);
                QTest::newRow("-0.3 - -0.7 =  0.4") << -0.3f << -0.7f << iou( 0.4f);
                QTest::newRow("-0.7 - -0.3 = -0.4") << -0.7f << -0.3f << iou(-0.4f);
            }

            void test_operator_subtract() noexcept
            {
                QFETCH(iou::value_type, a);
                QFETCH(iou::value_type, b);

                QTEST(iou(a) - iou(b), "expected_result");
                QTEST(iou(a) -     b , "expected_result");
                QTEST(    a  - iou(b), "expected_result");
            }

            void test_operator_multiply_data() noexcept
            {
                QTest::addColumn<iou::value_type>("a");
                QTest::addColumn<iou::value_type>("b");
                QTest::addColumn<iou>            ("expected_result");

                QTest::newRow(" 0.0 *  0.0 =  0.0 ") <<  0.0f <<  0.0f << iou( 0.0f);
                QTest::newRow(" 0.0 *  0.4 =  0.0 ") <<  0.0f <<  0.4f << iou( 0.0f);
                QTest::newRow(" 0.4 *  0.0 =  0.0 ") <<  0.4f <<  0.0f << iou( 0.0f);
                QTest::newRow(" 1.0 * -0.3 = -0.3 ") <<  1.0f << -0.3f << iou(-0.3f);
                QTest::newRow("-0.3 *  1.0 = -0.3 ") << -0.3f <<  1.0f << iou(-0.3f);
                QTest::newRow("-0.3 * -0.7 =  0.21") << -0.3f << -0.7f << iou( 0.21f);
                QTest::newRow("-0.7 * -0.3 =  0.21") << -0.7f << -0.3f << iou( 0.21f);
                QTest::newRow(" 0.7 *  0.3 =  0.21") <<  0.7f <<  0.3f << iou( 0.21f);
            }

            void test_operator_multiply() noexcept
            {
                QFETCH(iou::value_type, a);
                QFETCH(iou::value_type, b);

                QTEST(iou(a) * iou(b), "expected_result");
                QTEST(iou(a) *     b , "expected_result");
                QTEST(    a  * iou(b), "expected_result");
            }

            void test_operator_divide_data() noexcept
            {
                QTest::addColumn<iou::value_type>("a");
                QTest::addColumn<iou::value_type>("b");
                QTest::addColumn<iou>            ("expected_result");

                QTest::newRow(" 0.0 /  0.4 =  0.0 ") <<  0.0f <<  0.4f << iou( 0.0f);
                QTest::newRow(" 1.0 / -0.3 = -3.33") <<  1.0f << -0.3f << iou( 1.0f / -0.3f);
                QTest::newRow("-0.3 /  1.0 = -0.3 ") << -0.3f <<  1.0f << iou(-0.3f);
                QTest::newRow("-0.3 / -0.7 =  0.43") << -0.3f << -0.7f << iou(-0.3f / -0.7f);
                QTest::newRow("-0.7 / -0.3 =  2.33") << -0.7f << -0.3f << iou(-0.7f / -0.3f);
                QTest::newRow(" 0.7 /  0.3 =  2.33") <<  0.7f <<  0.3f << iou( 0.7f /  0.3f);
            }

            void test_operator_divide() noexcept
            {
                QFETCH(iou::value_type, a);
                QFETCH(iou::value_type, b);

                QTEST(iou(a) / iou(b), "expected_result");
                QTEST(iou(a) /     b , "expected_result");
                QTEST(    a  / iou(b), "expected_result");
            }

            void test_operator_modulo_data() noexcept
            {
                QTest::addColumn<iou::value_type>("a");
                QTest::addColumn<iou::value_type>("b");
                QTest::addColumn<iou>            ("expected_result");

                QTest::newRow(" 0.0 /  0.4 =  0.0 ") <<  0.0f <<  0.4f << iou(std::fmod( 0.0f,  0.4f));
                QTest::newRow(" 1.0 / -0.3 = -3.33") <<  1.0f << -0.3f << iou(std::fmod( 1.0f, -0.3f));
                QTest::newRow("-0.3 /  1.0 = -0.3 ") << -0.3f <<  1.0f << iou(std::fmod(-0.3f,  1.0f));
                QTest::newRow("-0.3 / -0.7 =  0.43") << -0.3f << -0.7f << iou(std::fmod(-0.3f, -0.7f));
                QTest::newRow("-0.7 / -0.3 =  2.33") << -0.7f << -0.3f << iou(std::fmod(-0.7f, -0.3f));
                QTest::newRow(" 0.7 /  0.3 =  2.33") <<  0.7f <<  0.3f << iou(std::fmod( 0.7f,  0.3f));
            }

            void test_operator_modulo() noexcept
            {
                QFETCH(iou::value_type, a);
                QFETCH(iou::value_type, b);

                QTEST(iou(a) % iou(b), "expected_result");
                QTEST(iou(a) %     b , "expected_result");
                QTEST(    a  % iou(b), "expected_result");
            }
    };
}

QTEST_MAIN(analyze::iou_test)
#include "iou_test.moc"
