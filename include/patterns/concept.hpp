#ifndef PATTERNS_CONCEPT_HPP
#define PATTERNS_CONCEPT_HPP

#include <utility>
#include <type_traits>

namespace patterns {

template <typename A, typename E = void>
constexpr bool is_node = false;

template <typename T>
concept Node = requires(T a)
{
  { next(a) };
  { is_type(a, std::type_identity<typename std::remove_reference<T>::type>{}) } -> std::convertible_to<bool>;
  //  { is_type(a, std::type_identity<decltype(next(a))>{}) } -> std::convertible_to<bool>;
} && is_node<typename std::remove_reference<T>::type>;

}

#endif
