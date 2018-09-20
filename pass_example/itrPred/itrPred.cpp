#include "llvm/IR/Function.h"
#include "llvm/IR/CFG.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;

namespace {
    struct itrPred:public FunctionPass{
        static char ID;
        itrPred():FunctionPass(ID){}  //实例化函数
        
        bool runOnFunction(Function &F) override{
            errs()<<"itrPred: ";
            errs()<<F.getName()<<"\n";
            
            BasicBlock *target;
            int basicblock_count=0;
            
            for(Function::iterator bbi=F.begin(),bbe=F.end(); bbi!=bbe; bbi++){
                //遍历基本块
                basicblock_count++;
                if(basicblock_count==4){
                    target = &*bbi;
                    break;
                }
                
            }
            for(pred_iterator pi=pred_begin(target), pe=pred_end(target); pi!=pe; pi++){
                BasicBlock *pred = *pi;
                errs()<<"BasicBlock Name "<<pred->getName()<<"\n";
            }
            return false;
        }
    };
}

char itrPred::ID = 0;
static RegisterPass<itrPred> X("itrPred", "count number of opcode of every type.");
