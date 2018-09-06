#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct itrBBInFunction:public FunctionPass{
        static char ID;
        itrBBInFunction():FunctionPass(ID){}
        
        bool runOnFunction(Function &F) override{
            errs()<<"hello: ";
            errs()<<F.getName()<<"\n";
            
            for(Function::iterator bb = F.begin(), e = F.end(); bb!=e; bb++ ){
                errs()<<"BasicBlock name="<< bb->getName()<<"\n";
                errs()<<"BasicBlock size="<< bb->size()<<"\n";
                
                for(BasicBlock::iterator i=bb->begin(),ie=bb->end(); i!=ie; i++){
                    errs()<<"    "<<*i<<"\n";
                } 
                errs()<<"\n";
            }
        }
    };
}

char itrBBInFunction::ID = 0;
static RegisterPass<itrBBInFunction> X("itrBBInFunction", "Iterate over basicblocks inside a function");
