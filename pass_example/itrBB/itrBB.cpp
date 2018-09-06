#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct itrBB:public FunctionPass{
        static char ID;
        itrBB():FunctionPass(ID){}
        
        bool runOnFunction(Function &F) override{
            errs()<<"hello: ";
            errs()<<F.getName()<<"\n";
            
            for(Function::iterator bb = F.begin(), e = F.end(); bb!=e; bb++ ){
                errs()<<"BasicBlock name="<< bb->getName()<<"\n";
                errs()<<"BasicBlock size="<< bb->size()<<"\n";
            }
        }
    };
}

char itrBB::ID = 0;
static RegisterPass<itrBB> X("itrBB", "Iterate over basicblocks of function");
