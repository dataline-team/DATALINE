#ifndef VARIANT_H_
#define VARIANT_H_

#include <iostream>
#include "boost/lexical_cast.hpp"


using boost::lexical_cast;
using boost::bad_lexical_cast;


enum class DataTypes
{
    NULL_T, BOOL, INT, DOUBLE, STRING
};


class Variant
{
public:
    Variant() :                  b_(nullptr),     i_(nullptr), d_(nullptr), s_(nullptr), datatype(DataTypes::NULL_T)   {}
    explicit Variant(bool b) :   b_(new bool(b)), i_(nullptr), d_(nullptr), s_(nullptr), datatype(DataTypes::BOOL)     {}
    explicit Variant(int i) :    b_(nullptr), i_(new int(i)),  d_(nullptr), s_(nullptr), datatype(DataTypes::INT)      {}
    explicit Variant(double d) : b_(nullptr), i_(nullptr), d_(new double(d)), s_(nullptr), datatype(DataTypes::DOUBLE) {}
    explicit Variant(const std::string& s) : b_(nullptr), i_(nullptr), d_(nullptr), s_(new std::string(s)), datatype(DataTypes::STRING) {}

    Variant(const Variant& variant);
    Variant& operator=(const Variant& variant);
    ~Variant();

    bool toBool() const;
    int toInt() const;
    double toDouble() const;
    std::string toString() const;

    void setData(bool b);
    void setData(int i);
    void setData(double d);
    void setData(const std::string& s);

    DataTypes getDatatype() const;

private:
    DataTypes datatype;

    bool *b_;
    int *i_;
    double *d_;
    std::string *s_;
};


#endif  // VARIANT_H_