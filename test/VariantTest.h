#include "gtest/gtest.h"
#include "Variant.h"
#include "boost/lexical_cast.hpp"



// ----------------------- Object copy -----------------------

TEST(constructorOfCopy, objectCopy)
{
    int n = 5;
    Variant v(n);
    Variant v2 = v;

    EXPECT_EQ(v2.toInt(), n);
}

TEST(assignmentOperatorOverloading, objectAssignment)
{
    std::string str = "hello world";
    Variant v(str);
    Variant v2;
    v2 = v;

    EXPECT_EQ(v2.toString(), str);
}



// ----------------------- Variant::toBool() -----------------------

TEST(toBool, null_cast)
{
    Variant variant;
    EXPECT_NO_THROW(variant.toBool());

    EXPECT_EQ(variant.toBool(), bool());
}


TEST(toBool, bool_cast)
{
    bool is_true = true;
    Variant b_variant(is_true);

    EXPECT_EQ(b_variant.toInt(), is_true);
}


TEST(toBool, int_cast)
{
    int n = 1155;
    Variant i_variant(n);

    EXPECT_EQ(i_variant.toBool(), static_cast<bool>(n));
}


TEST(toBool, double_cast)
{
    double d = 115.12345;
    Variant d_variant(d);

    EXPECT_EQ(d_variant.toBool(), static_cast<bool>(d));
}


TEST(toBool, string_cast)
{
    std::string str = "abcd";
    Variant str_variant(str);

    EXPECT_EQ(str_variant.toBool(), !str.empty());
}



// ----------------------- Variant::toInt() -----------------------

TEST(toInt, null_cast)
{
    Variant variant;
    EXPECT_NO_THROW(variant.toInt());

    EXPECT_EQ(variant.toInt(), int());
}


TEST(toInt, bool_cast)
{
    bool is_true = true;
    Variant b_variant(is_true);

    EXPECT_EQ(b_variant.toInt(), static_cast<int>(is_true));
}


TEST(toInt, int_cast)
{
    int n = 1155;
    Variant i_variant(n);

    EXPECT_EQ(i_variant.toInt(), n);
}


TEST(toInt, double_cast)
{
    double d = 115.12345;
    Variant d_variant(d);

    EXPECT_EQ(d_variant.toInt(), static_cast<int>(d));
}


TEST(toInt, success_string_cast)
{
    std::string str = "12345";
    Variant str_variant(str);

    EXPECT_EQ(str_variant.toInt(), boost::lexical_cast<int>(str));
}


TEST(toInt, bad_string_cast)
{
    std::string str2 = "123abc";
    Variant str_variant(str2);

    EXPECT_NO_THROW(str_variant.toInt());

    EXPECT_EQ(str_variant.toInt(), int());
}



// ----------------------- Variant::toFloat() -----------------------

TEST(toDouble, null_cast)
{
    Variant variant;
    EXPECT_NO_THROW(variant.toDouble());

    EXPECT_EQ(variant.toDouble(), float());
}


TEST(toDouble, bool_cast)
{
    bool is_true = true;
    Variant b_variant(is_true);

    EXPECT_EQ(b_variant.toDouble(), static_cast<double>(is_true));
}


TEST(toDouble, int_cast)
{
    int n = 1155;
    Variant i_variant(n);

    EXPECT_EQ(i_variant.toDouble(), static_cast<double>(n));
}


TEST(toDouble, double_cast)
{
    double d = 115.12345;
    Variant d_variant(d);

    EXPECT_EQ(d_variant.toDouble(), d);
}


TEST(toDouble, success_string_cast)
{
    std::string str = "123.45";
    Variant str_variant(str);

    EXPECT_EQ(str_variant.toDouble(), boost::lexical_cast<double>(str));
}


TEST(toDouble, bad_string_cast)
{
    std::string str2 = "12..3";
    Variant str_variant(str2);

    EXPECT_NO_THROW(str_variant.toDouble());

    EXPECT_EQ(str_variant.toDouble(), float());
}



// ----------------------- Variant::toString() -----------------------

TEST(toString, null_cast)
{
    Variant variant;
    EXPECT_NO_THROW(variant.toDouble());

    EXPECT_EQ(variant.toString(), std::string());
}


TEST(toString, bool_cast)
{
    bool is_true = true;
    Variant b_variant(is_true);

    EXPECT_EQ(b_variant.toString(), lexical_cast<std::string>(is_true));
}


TEST(toString, int_cast)
{
    int n = 1155;
    Variant i_variant(n);

    EXPECT_EQ(i_variant.toString(), lexical_cast<std::string>(n));
}


TEST(toString, double_cast)
{
    double d = 115.12345;
    Variant d_variant(d);

    EXPECT_EQ(d_variant.toString(), lexical_cast<std::string>(d));
}


TEST(toString, string_cast)
{
    std::string str = "abcd";
    Variant str_variant(str);

    EXPECT_EQ(str_variant.toString(), str);
}
