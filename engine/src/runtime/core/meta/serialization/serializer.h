#pragma once
#include <string>
#include <type_traits>
#include <memory>
#include <iostream>

#include <yaml-cpp/yaml.h>

#include "core/meta/reflection/reflection.h"

namespace Untitled
{
    template <typename TClass>
    class Serializer
    {
    public:
        void serialize(const TClass& object, YAML::Node& root)
        {
            auto refl_tuple = object.reflect();
        }

        void deserialize(TClass& object, YAML::Node& root)
        {
            auto refl_tuple = object.reflect();
            auto object_node = root[Reflection::getClassName(refl_tuple)];

            Reflection::processFields(refl_tuple, [&object_node](auto&& tp)
                {
                    if constexpr(std::is_same_v<std::decay_t<decltype(*std::get<1>(tp))>, int>)
                        *std::get<1>(tp) = object_node[std::get<0>(tp)].as<int>();      
                    else if constexpr(std::is_same_v<std::decay_t<decltype(*std::get<1>(tp))>, std::string>)
                        *std::get<1>(tp) = object_node[std::get<0>(tp)].as<std::string>();
                });
        }
    };
}
