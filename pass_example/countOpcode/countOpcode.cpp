#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct opcodeCounter:public FunctionPass{
        static char ID;
        opcodeCounter():FunctionPass(ID){}  //实例化函数
        
        bool runOnFunction(Function &F) override{
            std::map<std::string,int> opcode_map;
            errs()<<"opcodeCounter: ";
            errs()<<F.getName()<<"\n";
            
            for(Function::iterator bbi=F.begin(),bbe=F.end(); bbi!=bbe; bbi++){
                //遍历基本块
                for(BasicBlock::iterator ii=bbi->begin(),ie=bbi->end(); ii!=ie; ii++){
                    //遍历指令
                    if(opcode_map.find(ii->getOpcodeName())==opcode_map.end()){
                        opcode_map[ii->getOpcodeName()]=1;
                    } else {
                        opcode_map[ii->getOpcodeName()]+=1;
                    }
                }
            }
            
            std::map<std::string,int>::iterator i=opcode_map.begin();
            std::map<std::string,int>::iterator e=opcode_map.end();
            while(i!=e){
                errs()<< i->first << ":" << i->second << "\n";
                i++;
            }
        }
    };
}

char opcodeCounter::ID = 0;
static RegisterPass<opcodeCounter> X("opcodeCounter", "count number of opcode of every type.");
