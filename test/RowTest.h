#include "Row.h"



// test input data
int n = 5;
std::string str = "hello";
bool b = true;
float f = 5.123;


Row createExampleOfRow(int i_t, const std::string& s_t, bool b_t, float f_t)
{
    Variant v(i_t), v2(s_t), v3(b_t), v4(f_t);
    std::vector<Variant> cells{v, v2, v3, v4};
    Row row(cells);

    return row;
}


TEST(rowConstructor, createRow)
{
    Row row = createExampleOfRow(n, str, b, f);

    EXPECT_EQ(row.getItem(0).toInt(), n);
    EXPECT_EQ(row.getItem(1).toString(), str);
    EXPECT_EQ(row.getItem(2).toBool(), b);
    EXPECT_EQ(row.getItem(3).toFloat(), f);
}


TEST(setItem, successfulSetItem)  // data type of cell has being checked
{
    Row row = createExampleOfRow(n, str, b, f);

    std::string str2 = "world";
    Variant vv(str2);
    row.setItem(vv, 1);

    EXPECT_EQ(row.getItem(1).toString(), str2);
}


TEST(setItem, badSetItem)
{
    Row row = createExampleOfRow(n, str, b, f);

    std::string str2 = "world";
    Variant vv(str2);
    row.setItem(vv, 3);

    EXPECT_NO_THROW(row.getItem(3));
    EXPECT_NE(row.getItem(3).toString(), str2);
}


TEST(setRow, useSetRow)
{
    Row row = createExampleOfRow(n, str, b, f);

    EXPECT_EQ(row.getItem(0).toInt(), n);
    EXPECT_EQ(row.getItem(1).toString(), str);

    Variant v(str), v2(n), v3(b), v4(f);
    std::vector<Variant> cells{v, v2, v3, v4};

    row.setRow(cells);

    EXPECT_EQ(row.getItem(0).toString(), str);
    EXPECT_EQ(row.getItem(1).toInt(), n);
}