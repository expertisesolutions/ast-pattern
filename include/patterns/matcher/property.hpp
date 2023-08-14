#ifndef PATTERNS_MATCHER_PROPERTY_HPP
#define PATTERNS_MATCHER_PROPERTY_HPP

#include <patterns/archetype/context.hpp>
#include <patterns/matcher/concept.hpp>
#include <patterns/matcher/children_matcher_terminal.hpp>
#include <patterns/concept.hpp>

#include <type_traits>

namespace patterns { namespace matcher {

namespace detail {

struct eq {
  template <typename T, typename Context, std::size_t N>
  static bool match(T l, std::array<char, N> r, Context const&) {
    return std::distance(l.begin(), l.end()) == std::distance(r.begin(), r.end())
      && std::equal(l.begin(), l.end(), r.begin());
  }

  template <int N, typename U, typename Context>
  static bool match(std::array<char, N> l, U r, Context const& c) {
    return match(r, l, c);
  }

  template <typename T, typename Context>
  static bool match(T l, T r, Context const&) {
    return l == r;
  }
};

struct ne {
  template <typename T, typename U, typename Context>
  static bool match(T l, U r, Context const&) {
    std::cout << "matching " << l << " with " << r << "\n";
    return l != r;
  }
};

}

template <typename P>
struct property_value {
  
};

template <typename V>
struct literal_constant_value {
  V v;

  friend std::ostream& operator<<(std::ostream& os, literal_constant_value<V> v) {
    os << "[literal_constant_value<" << typeid(V).name() << ">{";
    std::copy(v.v.begin(), v.v.end(), std::ostream_iterator<char>(std::cout));
    return os << "}]";
  }
};

template <typename V, typename U, typename Context>
V get_value(literal_constant_value<V> l, U const&, Context const&) {
  return l.v;
}

template <typename P, typename U>
bool get_value(property_value<P> const& p, U&& u) {
  return get_property_value(u, std::type_identity<P>{});
}
    
template <typename L, typename R, typename Op>
struct property_boolean_expression_matcher : children_matcher_terminal {
  L l;
  R r;

  template <Node U, typename Context = archetype::empty_context>
  bool match(U&& u, Context const& context = archetype::empty_context{}) const
  {
    return Op::match(get_value(l, u, context), get_value(r, u, context), context);
  }
};


template <typename P>
property_value<P> const property;

namespace detail {
template <std::size_t N, std::size_t ... Is>
constexpr std::array<char, N - 1>
to_array(const char (&a)[N], std::index_sequence<Is...>)
{
    return {{a[Is]...}};
}

template <std::size_t N>
constexpr std::array<char, N - 1> to_array(const char (&a)[N])
{
    return to_array(a, std::make_index_sequence<N - 1>());
}
}

template <typename P, int N>
property_boolean_expression_matcher<property_value<P>, literal_constant_value<std::array<char, N-1>>, matcher::detail::eq>
operator==(property_value<P> l, const char (&literal_string)[N]) {
  literal_constant_value<std::array<char, N-1>> literal{detail::to_array(literal_string)};
  return property_boolean_expression_matcher<property_value<P>, literal_constant_value<std::array<char, N-1>>, matcher::detail::eq>
    {{}, l, std::move(literal)};
}

namespace properties {

struct name;

}

}

template <typename L, typename R, typename Op>
constexpr bool is_matcher<matcher::property_boolean_expression_matcher<L, R, Op>> = true;
template <typename L, typename R, typename Op>
constexpr bool is_matcher<matcher::property_boolean_expression_matcher<L, R, Op>&> = true;

}

#endif
