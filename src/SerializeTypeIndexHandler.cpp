//
// Created by voveex on 9/20/21.
//

#include "SerializeTypeIndexHandler.h"


SerializeTypeIndexHandler::SerializeTypeIndexHandler()
{
    // pass
}


std::vector<named_typeindex> SerializeTypeIndexHandler::name_register =
        {
                { typeid(Blank).name(), typeid(Blank) },
                { typeid(bool).name(), typeid(bool) },
                { typeid(int).name(), typeid(int) },
                { typeid(double).name(), typeid(double) },
                { typeid(std::string).name(), typeid(std::string) }
        };


std::type_index SerializeTypeIndexHandler::type_for_name(const std::string& name)
{
    auto i = std::find_if(std::begin(name_register), std::end(name_register),
                          [&name](const auto& entry) { return std::get<std::string>(entry) == name; } );
    if (i == std::end(name_register))
        return typeid(Blank);
    return std::get<std::type_index>(*i);
}



std::string const& SerializeTypeIndexHandler::name_for_type(std::type_index type)
{
    auto i = std::find_if(std::begin(name_register), std::end(name_register),[type](const auto& entry)
    {
        return std::get<std::type_index>(entry) == type;
    });

    using namespace std::string_literals;

    if (i == std::end(name_register))
    {
        throw std::logic_error("unregistered type "s + type.name());
    }

    return std::get<std::string>(*i);
}
