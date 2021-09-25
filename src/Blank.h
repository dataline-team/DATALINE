//
// Created by voveex on 9/20/21.
//

#ifndef DATALINE_BLANK_H
#define DATALINE_BLANK_H


#include <boost/blank.hpp>

class Blank : public boost::blank
{
public:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {}
};


#endif //DATALINE_BLANK_H
