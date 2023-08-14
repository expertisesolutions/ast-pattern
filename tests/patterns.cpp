#define BOOST_TEST_MODULE patterns
#include <boost/test/included/unit_test.hpp>

#include <patterns/matcher/operators.hpp>
#include <patterns/archetype/node.hpp>

#include <iostream>

namespace pt = patterns;

struct type1 {};
struct type2 {};
struct type3 {};
struct type4 {};

type2 next (type1) { return {}; }
type3 next (type2) { return {}; }
type4 next (type3) { return {}; }
type4 next (type4) { return {}; }

constexpr bool is_type (type1, std::type_identity<type1>) { return true; }
template <typename U>
constexpr bool is_type (type1, std::type_identity<U>) { return false; }
constexpr bool is_type (type2, std::type_identity<type2>) { return true; }
template <typename U>
constexpr bool is_type (type2, std::type_identity<U>) { return false; }
constexpr bool is_type (type3, std::type_identity<type3>) { return true; }
template <typename U>
constexpr bool is_type (type3, std::type_identity<U>) { return false; }
constexpr bool is_type (type4, std::type_identity<type4>) { return true; }
template <typename U>
constexpr bool is_type (type4, std::type_identity<U>) { return false; }

namespace patterns {
template <> constexpr bool is_node< ::type1, void> = true;
template <> constexpr bool is_node< ::type2, void> = true;
template <> constexpr bool is_node< ::type3, void> = true;
template <> constexpr bool is_node< ::type4, void> = true;
}

BOOST_AUTO_TEST_SUITE(test_pattern_suite)

BOOST_AUTO_TEST_CASE( test_pattern1 )
{
  bool action_called = false;
  
  // static_assert(pt::is_pattern_v<decltype(pt::a<type1>)>, "");
  // static_assert(pt::is_pattern_v<decltype(pt::a<type2>)>, "");
  using pt::matcher::type;
  using pt::matcher::case_;
  static_assert(pt::Node<pt::archetype::tree_node>);
  static_assert(pt::Node<type1>);
  static_assert(pt::Node<type2>);
  static_assert(pt::Node<type3>);
  static_assert(pt::Node<type4>);
  BOOST_TEST(type<type1>.match(type1{}, 0));
  BOOST_TEST(! type<type2>.match(pt::archetype::tree_node{}, 0));
  BOOST_TEST(!(type<type1> >> type<type2>).match(pt::archetype::tree_node{}, 0));
  BOOST_TEST((type<type1> >> type<type2>).match(type1{}, 0));
  BOOST_TEST(!(type<type1> >> type<type2>, type<type4>).match(type1{}, 0));
  std::cout << "start test" << std::endl;
  //BOOST_TEST((type<type1> >> type<type2> >> type<type3> >> type<type4>).match(type1{}, 0));
  (type<type1>[type<type2>, type<type4>]).match(pt::archetype::tree_node{}, 0);
  (type<type1>([&action_called] (auto&&, auto&&) {std::cout << "this was called" << std::endl; action_called = true;})
   >> type<type2>[type<type2>, type<type4>]).match
    (
     pt::archetype::tree_node{}, 0

     );
  // auto x =
  //   case_[type<type1> >> type<type2>[type<type3> >> type<type1>, type<type4>]]
  //   (
  //    [] (auto&& t1, auto&& t2)
  //    {
  //      std::cout << "lambda called" << std::endl;
  //    }
  //   )
  //   ;
  //x.match(pt, 0);

  BOOST_TEST(action_called == true);
}

BOOST_AUTO_TEST_SUITE_END()

