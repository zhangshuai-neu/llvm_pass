#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct useDef:public FunctionPass{
        static char ID;
        useDef():FunctionPass(ID){}  //实例化函数
        
        bool runOnFunction(Function &F) override{
            errs()<<"defuse: ";
            errs()<<F.getName()<<"\n";
            
            for(Function::iterator bbi=F.begin(),bbe=F.end(); bbi!=bbe; bbi++){
                //遍历基本块
                for(BasicBlock::iterator ii=bbi->begin(),ie=bbi->end(); ii!=ie; ii++){
                    //遍历指令
                    Instruction * inst = dyn_cast<Instruction>(ii);
                    if(inst->getOpcode() == Instruction::Add){
                        for(Use &U:inst->operands()){
                            Value *v = U.get();
                            errs()<<*v<<"\n";
                        }
                    }
                }
            }
            return false;
        }
    };
}

char useDef::ID = 0;
static RegisterPass<useDef> X("useDef", "count number of opcode of every type.");
