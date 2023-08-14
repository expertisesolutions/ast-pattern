#define BOOST_TEST_MODULE clang_ast
#include <boost/test/included/unit_test.hpp>

#include <patterns/matcher/operators.hpp>
#include <patterns/matcher/property.hpp>
#include <patterns/matcher/boolean_expression.hpp>
#include <patterns/archetype/node.hpp>
#include <patterns/clang/clang.hpp>

#include <iostream>

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace pt = patterns;

BOOST_AUTO_TEST_SUITE(test_clang_suite)

static llvm::cl::OptionCategory PandaToolsCompilerCategory("my-tool options");

template <typename T>
struct frontend_factory_for_consumer : clang::tooling::FrontendActionFactory {
    std::unique_ptr<T> consumer;

    template <typename... Args>
    frontend_factory_for_consumer(Args &&...args)
    {
        consumer = std::make_unique<T>(std::forward<Args>(args)...);
    }

    frontend_factory_for_consumer()
    {
        consumer = std::make_unique<T>();
    }

    struct frontend : clang::SyntaxOnlyAction {
        std::unique_ptr<T> consumer;

        frontend(std::unique_ptr<T> consumer)
            : consumer(std::move(consumer))
        {
        }

        std::unique_ptr<clang::ASTConsumer>
        CreateASTConsumer(clang::CompilerInstance &ci,
                          ::llvm::StringRef InFile) override
        {
            return std::move(consumer);
        }
    };

    std::unique_ptr<clang::FrontendAction> create() override
    {
        return std::make_unique<frontend>(std::move(consumer));
    }
};

struct metadata_record_consumer : public clang::ASTConsumer, clang::RecursiveASTVisitor<metadata_record_consumer> {
  bool VisitNamedDecl(clang::NamedDecl *named_decl)
  {
    using ::patterns::matcher::type;
    using ::patterns::matcher::property;
    using ::patterns::matcher::properties::name;

    if (auto function = (type<clang::FunctionDecl> and property<name> == "foo").match(named_decl)) {
      std::cout << "It matched ! " << std::endl;
      //this->TraverseStmt(body);
    }

    return true;
  }

  void HandleTranslationUnit(clang::ASTContext &ast_context) final
  {
    this->ast_context = &ast_context;
    TraverseDecl(ast_context.getTranslationUnitDecl());
  }
  clang::ASTContext* ast_context;
};

BOOST_AUTO_TEST_CASE( clang_pattern1 )
{
  int argc = 2;
  const char* argv[] = {"program", "tests/clang-test.c"};
  
  llvm::Expected<clang::tooling::CommonOptionsParser> OptionsParser =
    clang::tooling::CommonOptionsParser::create(argc, argv,
                                                PandaToolsCompilerCategory);

  clang::tooling::ClangTool Tool(OptionsParser->getCompilations(),
                                 OptionsParser->getSourcePathList(),
                                 std::make_shared<clang::PCHContainerOperations>());

  frontend_factory_for_consumer<metadata_record_consumer> factory;
  Tool.run(&factory);

  BOOST_TEST(false == true);
}

BOOST_AUTO_TEST_SUITE_END()
