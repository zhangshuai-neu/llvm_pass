#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct defuse:public FunctionPass{
        static char ID;
        defuse():FunctionPass(ID){}  //实例化函数
        
        bool runOnFunction(Function &F) override{
            errs()<<"defuse: ";
            errs()<<F.getName()<<"\n";
            
            for(Function::iterator bbi=F.begin(),bbe=F.end(); bbi!=bbe; bbi++){
                //遍历基本块
                for(BasicBlock::iterator ii=bbi->begin(),ie=bbi->end(); ii!=ie; ii++){
                    //遍历指令
                    Instruction * inst = dyn_cast<Instruction>(ii);
                    if(inst->getOpcode() == Instruction::Add){
                        for(User *U:inst->users()){
                            if(Instruction *temp_i=dyn_cast<Instruction>(U)){
                                errs()<<"Instruction used in ::";
                                errs()<<*temp_i<<"\n";
                            }
                        }
                    }
                    
                }
            }
            return false;
        }
    };
}

char defuse::ID = 0;
static RegisterPass<defuse> X("defuse", "count number of opcode of every type.");
