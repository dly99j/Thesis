#include <vector>
#include <utility>

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "llvm/Support/CommandLine.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "llvm/Support/raw_ostream.h"

static llvm::cl::OptionCategory optionCategory("Tool options");
//static std::vector<std::variant<clang::Decl*, clang::Type*, clang::Stmt*>> ASTVector;

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
public:
    explicit MyASTVisitor(clang::ASTContext* context) : m_context(context) {}

    bool VisitDecl(clang::Decl *D) {
        if (D) {
            //ASTVector.push_back(D);
        }
        return true;
    }

    bool VisitType(clang::Type *TL) {
        if (TL) {
            //ASTVector.push_back(TL);
        }
        return true;
    }

    bool VisitStmt(clang::Stmt *S) {
        if (S) {
            //ASTVector.push_back(S);
        }
        return true;
    }

private:

    clang::ASTContext* m_context;
};

class MyASTConsumer : public clang::ASTConsumer {
public:
    virtual void HandleTranslationUnit(clang::ASTContext &Context) {
        clang::Decl *D = Context.getTranslationUnitDecl();

        MyASTVisitor astVisitor(&Context);
        astVisitor.TraverseDecl(D);
    }
};

class MyFrontendAction : public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance& CI, clang::StringRef) final {
        //CI.getInvocation().getLangOpts()->CPlusPlus11 = 1;
        return std::make_unique<MyASTConsumer>();
    }
};


void handleASTTraversal(int argc, const char **argv) {
    auto expectedOptionsParser = clang::tooling::CommonOptionsParser::create(argc,
                                                                             const_cast<const char**>(argv),
                                                                             optionCategory);
    if (!expectedOptionsParser) {
        llvm::errs() << llvm::format("Unable to create option parser ({}).\n",
                                    llvm::toString(expectedOptionsParser.takeError()));
    }
    clang::tooling::CommonOptionsParser& optionsParser = *expectedOptionsParser;
    clang::tooling::ClangTool tool(optionsParser.getCompilations(),
                                   optionsParser.getSourcePathList());

    tool.run(clang::tooling::newFrontendActionFactory<MyFrontendAction>().get());
}


int main(int argc, const char **argv) {

    handleASTTraversal(argc, argv);
    /*
    auto expectedOptionsParser = clang::tooling::CommonOptionsParser::create(argc,
                                                                             const_cast<const char**>(argv),
                                                                             optionCategory);
    if (!expectedOptionsParser) {
        llvm::errs() << std::format("Unable to create option parser ({}).\n",
                                    llvm::toString(expectedOptionsParser.takeError()));
    }
    clang::tooling::CommonOptionsParser& optionsParser = *expectedOptionsParser;
    clang::tooling::ClangTool tool(optionsParser.getCompilations(),
                                   optionsParser.getSourcePathList());

    std::vector<std::unique_ptr<clang::ASTUnit>> vec;
    tool.buildASTs(vec);
    for (auto& i : vec) {
        i->getASTContext();
    }
     */

    return 0;
}
