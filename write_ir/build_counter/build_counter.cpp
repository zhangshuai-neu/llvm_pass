//生成LLVM IR的框架类
#include "llvm/IR/Module.h"         //程序模块
#include "llvm/IR/LLVMContext.h"    //上下文
#include "llvm/IR/Function.h"       //函数
#include "llvm/IR/BasicBlock.h"     //基本块
#include "llvm/IR/IRBuilder.h"      //指令生成器
#include "llvm/IR/Constants.h"      //常量 int,string
#include "llvm/IR/DerivedTypes.h"   //导出类型定义-数组/函数
#include "llvm/IR/Type.h"           //标准类型，int8/16.. pointer
#include "llvm/IR/Verifier.h"

//字节码
#include "llvm/Bitcode/BitcodeWriter.h"

//c++标准库
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;
using namespace std;

//-----------------------------------------------
//全局变量
//-----------------------------------------------
static LLVMContext TheContext;                      // 上下文
static IRBuilder<> Builder(TheContext);             // IR生成器
static std::map<std::string, Value *> NamedValues;  // <名字,值>映射 用来记录一些参数表或者...

int main(){
//构建Module
    llvm::Module my_module("My_Module",TheContext);

//全局变量
    IntegerType * int32_type = Type::getInt32Ty(TheContext);
    ConstantInt * int32_zero = ConstantInt::get(int32_type,0);
    GlobalVariable  *global_counter = new llvm::GlobalVariable(my_module,int32_type, true, GlobalValue::CommonLinkage, int32_zero, "global_counter");
    global_counter->setAlignment(4);    // 继承自 global object
    
//添加 printf 函数声明
    //返回值类型 printf 返回int32类型
    vector<Type *> func_argu_type;
    func_argu_type.push_back(Type::getInt8PtrTy(TheContext));
    
    FunctionType * printf_func_type = FunctionType::get(Type::getInt32Ty(TheContext), func_argu_type, true);
    Function * printf_func = Function::Create(printf_func_type, GlobalValue::ExternalLinkage, "printf", &my_module);

//添加 main Function
    //返回值类型
    IntegerType * result_type = Type::getInt32Ty(TheContext);
    //参数类型列表
    
    //函数类型
    FunctionType * main_func_type = FunctionType::get(result_type,false);
        //notice:没有参数，只能用两个参数的 FunctionType::get 函数
        
    //创建function,并插入Module
    Function * main_func = Function::Create(main_func_type, GlobalValue::ExternalLinkage, "main", &my_module);

//添加basicblock
    //创建BasicBlock，并插入函数
    BasicBlock * main_bb = BasicBlock::Create(TheContext, "main_bb", main_func, nullptr);
    
    //设置插入点 main_bb末尾
    Builder.SetInsertPoint(main_bb);

//局部变量 char str[]="hello world!\n"
    Value * local_str = Builder.CreateGlobalStringPtr("Counter:%d\n","str");
    //从全局变量中读取数据
    Value * load_global_counter = Builder.CreateLoad(global_counter, "load_global_counter");

//添加 call printf 指令
    //参数
    vector<Value *> func_argu;
    func_argu.push_back(local_str);
    func_argu.push_back(load_global_counter);
    //插入 call printf 指令
    Builder.CreateCall(printf_func, func_argu);

//添加 ret int32 指令
    //插入 return int32 指令
    Builder.CreateRet(Builder.getInt32(0));

//确认
    verifyModule(my_module);
    
//打印IR，用来调试
    my_module.dump();
    //WriteBitcodeToFile(&my_module, outs());
}
