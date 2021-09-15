#ifndef BOOL_CELL_H_
#define BOOL_CELL_H_

#include "boost/variant.hpp"
#include "boost/type_index.hpp"
#include "boost/blank.hpp"


using data_t     = boost::variant<boost::blank, bool, int, double, std::string>;
using datatype_t = boost::typeindex::type_index;


class Cell
{
public:
    explicit Cell(datatype_t dt);
    template<class T>
    explicit Cell(const T& data);
    ~Cell();

    const data_t& getData() const;
    datatype_t datatype() const;

    bool empty() const;

private:
    data_t data_;
    datatype_t datatype_;
};


#endif  // BOOL_CELL_H_