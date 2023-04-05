#ifndef PATTERNS_CONCEPT_HPP
#define PATTERNS_CONCEPT_HPP

#include <utility>
#include <type_traits>

namespace patterns {

template <typename A, typename E = void>
constexpr bool is_ast_node = false;

struct ast_node_archetype
{
};

template <typename T>
concept AST_Node = requires(T a)
{
  { next(a) };
  { is_type(a, std::type_identity<ast_node_archetype>{}) } -> std::convertible_to<bool>;
} && is_ast_node<T>;

inline ast_node_archetype next(ast_node_archetype x) { return x; }
template <typename T>
bool is_type(ast_node_archetype x, std::type_identity<T>) { return false; }
  
template <>
constexpr bool is_ast_node<ast_node_archetype> = true;
template <>
constexpr bool is_ast_node<ast_node_archetype&> = true;

static_assert(AST_Node<ast_node_archetype>);
static_assert(AST_Node<ast_node_archetype&>);

// concept for tree

template <typename T, typename E = void>
struct node_tag;

template <typename Tag>
constexpr bool is_tree_tag = false;

// template <typename T>
// concept Tree

}

#endif
