#include "Variant.h"



bool Variant::toBool() const
{
    switch (datatype)
    {
        case DataTypes::NULL_T:
            return bool();
        case DataTypes::BOOL:
            return b_;
        case DataTypes::INT:
            return static_cast<bool>(i_);
        case DataTypes::FLOAT:
            return static_cast<bool>(f_);
        case DataTypes::STRING:
            return !s_.empty();
    }
}


int Variant::toInt() const
{
    switch (datatype)
    {
        case DataTypes::NULL_T:
            return int();
        case DataTypes::BOOL:
            return static_cast<int>(b_);
        case DataTypes::INT:
            return i_;
        case DataTypes::FLOAT:
            return static_cast<int>(f_);
        case DataTypes::STRING:
            try
            {
                return lexical_cast<int>(s_);
            }
            catch (const bad_lexical_cast& blc)
            {
                return int();
            }
    }
}


float Variant::toFloat() const
{
    switch (datatype)
    {
        case DataTypes::NULL_T:
            return float();
        case DataTypes::BOOL:
            return static_cast<float>(b_);
        case DataTypes::INT:
            return static_cast<float>(i_);
        case DataTypes::FLOAT:
            return f_;
        case DataTypes::STRING:
            try
            {
                return lexical_cast<float>(s_);
            }
            catch (const bad_lexical_cast& blc)
            {
                return float();
            }
    }
}


std::string Variant::toString() const
{
    switch (datatype)
    {
        case DataTypes::NULL_T:
            return std::string();
        case DataTypes::BOOL:
            return lexical_cast<std::string>(b_);
        case DataTypes::INT:
            return lexical_cast<std::string>(i_);
        case DataTypes::FLOAT:
            return lexical_cast<std::string>(f_);
        case DataTypes::STRING:
            return s_;
    }
}


DataTypes Variant::getDatatype() const
{
    return datatype;
}
