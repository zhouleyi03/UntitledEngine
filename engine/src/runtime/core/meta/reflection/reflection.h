#pragma once
#include <type_traits>
#include <utility>
#include <functional>

#define REFLECTION_START(CLASS_NAME, ...) \
    inline decltype(auto) reflect(){ \
        return std::make_tuple(#CLASS_NAME, __VA_ARGS__); \
    }

#define REFLECTION_FIELD_DEF(FIELD_TYPE, FIELD_NAME) \
    std::make_tuple(#FIELD_NAME, &FIELD_NAME)

namespace Untitled
{
    namespace Reflection
    {
        template <typename ReflTuple>
        std::string getClassName(const ReflTuple& t)
        {
            return std::get<0>(t);
        }

        template <typename Tuple, typename Functor>
        constexpr void processFieldTuple(Tuple& t, Functor&& f)
        {
            if constexpr (!std::is_same_v<Tuple, const char*>)
                f(t);
        }

        template <typename Tuple, typename Functor, std::size_t... Is>
        constexpr void processFields_impl(Tuple& t, Functor&& f, std::index_sequence<Is...>)
        {
            (processFieldTuple(std::get<Is>(t), std::forward<Functor>(f)), ...);
        }

        template <typename Tuple, typename Functor>
        constexpr void processFields(Tuple& t, Functor&& f)
        {
            processFields_impl(t, std::forward<Functor>(f), std::make_index_sequence<std::tuple_size_v<Tuple>>());
        }
    }
}
