#ifndef PATTERNS_MATCHER_AST_STMT_NODE_HPP
#define PATTERNS_MATCHER_AST_STMT_NODE_HPP

#include <patterns/concept.hpp>
#include <patterns/matcher/concept.hpp>
#include <patterns/matcher/property.hpp>

#include <clang/AST/Stmt.h>
#include <clang/AST/Decl.h>

#include <type_traits>

namespace patterns {

template <typename T>
constexpr bool is_node<T*, std::enable_if_t<std::is_base_of_v<::clang::Stmt, T>>> = true;
template <>
constexpr bool is_node<::clang::Stmt*> = true;
template <typename T>
constexpr bool is_node<T*, std::enable_if_t<std::is_base_of_v<::clang::Decl, T>>> = true;
template <>
constexpr bool is_node<::clang::Decl*> = true;

}

namespace clang {

inline ::clang::Stmt* next(::clang::Stmt* stmt) { return nullptr; }
template <typename T>
bool is_type(::clang::Stmt* stmt, std::type_identity<T>)
{
  return llvm::dyn_cast<T>(stmt);
}

inline ::clang::Decl* next(::clang::Decl* decl) { return nullptr; }
template <typename T>
bool is_type(::clang::Decl* decl, std::type_identity<T>)
{
  return llvm::dyn_cast<T>(decl);
}

template <typename Context>
std::string get_value(patterns::matcher::property_value<patterns::matcher::properties::name> const& p
                      , ::clang::NamedDecl* decl, Context const& context) {
  return decl->getNameAsString();
}

}

static_assert( patterns::Node< ::clang::Stmt*>);
static_assert( patterns::Node< ::clang::Decl*>);
static_assert( patterns::Node< ::clang::NamedDecl*>);

#endif
