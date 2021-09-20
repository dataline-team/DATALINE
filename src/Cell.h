#ifndef BOOL_CELL_H_
#define BOOL_CELL_H_

#include "SerializeTypeIndexHandler.h"


#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <typeindex>
#include <stdexcept>
#include <string_view>

#include <boost/variant.hpp>
#include <boost/log/trivial.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>


using data_t     = boost::variant<Blank, bool, int, double, std::string>;
using datatype_t = std::type_index;


class Cell
{
public:
    Cell();
    explicit Cell(datatype_t dt);
    template<class T>
    explicit Cell(const T& data);
    ~Cell();

    [[nodiscard]] data_t const& getData() const;
    [[nodiscard]] datatype_t datatype() const;

    [[nodiscard]] bool empty() const;


    template<class Archive>
    void save(Archive & ar, const unsigned int version);

    template<class Archive>
    void load(Archive & ar, const unsigned int version);

    BOOST_SERIALIZATION_SPLIT_MEMBER();
private:
    data_t data_;
    datatype_t datatype_;
};


#endif  // BOOL_CELL_H_