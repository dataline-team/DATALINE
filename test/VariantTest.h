#include "gtest/gtest.h"
#include "Variant.h"
#include "boost/lexical_cast.hpp"



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


TEST(toBool, float_cast)
{
    float f = 115.12345;
    Variant f_variant(f);

    EXPECT_EQ(f_variant.toBool(), static_cast<bool>(f));
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


TEST(toInt, float_cast)
{
    float f = 115.12345;
    Variant f_variant(f);

    EXPECT_EQ(f_variant.toInt(), static_cast<int>(f));
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

TEST(toFloat, null_cast)
{
    Variant variant;
    EXPECT_NO_THROW(variant.toFloat());

    EXPECT_EQ(variant.toFloat(), float());
}


TEST(toFloat, bool_cast)
{
    bool is_true = true;
    Variant b_variant(is_true);

    EXPECT_EQ(b_variant.toFloat(), static_cast<float>(is_true));
}


TEST(toFloat, int_cast)
{
    int n = 1155;
    Variant i_variant(n);

    EXPECT_EQ(i_variant.toFloat(), static_cast<float>(n));
}


TEST(toFloat, float_cast)
{
    float f = 115.12345;
    Variant f_variant(f);

    EXPECT_EQ(f_variant.toFloat(), f);
}


TEST(toFloat, success_string_cast)
{
    std::string str = "123.45";
    Variant str_variant(str);

    EXPECT_EQ(str_variant.toFloat(), boost::lexical_cast<float>(str));
}


TEST(toFloat, bad_string_cast)
{
    std::string str2 = "12..3";
    Variant str_variant(str2);

    EXPECT_NO_THROW(str_variant.toFloat());

    EXPECT_EQ(str_variant.toFloat(), float());
}



// ----------------------- Variant::toString() -----------------------

TEST(toString, null_cast)
{
    Variant variant;
    EXPECT_NO_THROW(variant.toFloat());

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


TEST(toString, float_cast)
{
    float f = 115.12345;
    Variant f_variant(f);

    EXPECT_EQ(f_variant.toString(), lexical_cast<std::string>(f));
}


TEST(toString, string_cast)
{
    std::string str = "abcd";
    Variant str_variant(str);

    EXPECT_EQ(str_variant.toString(), str);
}
