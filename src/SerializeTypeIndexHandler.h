//
// Created by voveex on 9/20/21.
//

#ifndef DATALINE_SERIALIZETYPEINDEXHANDLER_H
#define DATALINE_SERIALIZETYPEINDEXHANDLER_H


#include "Blank.h"

#include <tuple>
#include <string>
#include <typeindex>
#include <vector>
#include <algorithm>
#include <stdexcept>


using named_typeindex = std::tuple<std::string, std::type_index>;


class SerializeTypeIndexHandler
{
public:
    [[nodiscard]] static std::type_index type_for_name(const std::string& name);
    [[nodiscard]] static std::string const& name_for_type(std::type_index type);

protected:
    SerializeTypeIndexHandler();
    static std::vector<named_typeindex> name_register;
};


#endif //DATALINE_SERIALIZETYPEINDEXHANDLER_H
