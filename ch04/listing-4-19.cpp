// Listing 4-19. Rewriting casts declaratively with a Transformer rule
// Run: clang++ -I$LLVM_DIR/include -I . -std=c++17 -fsyntax-only listing-4-19.cpp

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/FixIt.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/Transformer/RangeSelector.h"
#include "clang/Tooling/Transformer/RewriteRule.h"
#include "clang/Tooling/Transformer/Stencil.h"
#include "clang/Tooling/Transformer/Transformer.h"
using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::transformer;

// Define the rewrite rule
RewriteRule Rule = makeRule(
    cStyleCastExpr(hasSourceExpression(expr().bind("castedExpr"))).bind("cStyleCast"),
    changeTo(
        node("cStyleCast"),
        run([](const ast_matchers::MatchFinder::MatchResult &Result)
                -> llvm::Expected<std::string> {
            const auto *CastExpr = Result.Nodes.getNodeAs<CStyleCastExpr>("cStyleCast");
            const auto *CastedExpr = Result.Nodes.getNodeAs<Expr>("castedExpr");
            std::string CastType = CastExpr->getTypeAsWritten().getAsString();
            return ("static_cast<" + CastType + ">(" +
                    clang::tooling::fixit::getText(*CastedExpr, *Result.Context) + ")")
                .str();
        })));

// Create a tool that applies the transformer
MatchFinder Finder;
clang::tooling::Transformer Xfmr(
    Rule, [](llvm::Expected<llvm::MutableArrayRef<tooling::AtomicChange>>) {});
std::unique_ptr<tooling::FrontendActionFactory> Tool =
    (Xfmr.registerMatchers(&Finder), tooling::newFrontendActionFactory(&Finder));
