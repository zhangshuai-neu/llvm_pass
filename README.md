# LLVM Pass

This project is mainly used to save some practices of writing llvm pass, which is helpful for people who are unfamiliar with LLVM.

### Directory Info

Introduce some information about several directories.

    pass_example: there are some llvm pass example, like iterate BasicBlocks
    test_program: there are some C program, which is used to

    Notice: More information you can see in dir's doc file

### How to Use These LLVM Pass

1) You should compile the LLVM for your platform

2) Select a LLVM Pass example, and copy it in LLVM

    cp -R pass_example/${LLVM_PASS} ${LLVM_HOME}/lib/Transforms
    cd ${LLVM_BUILD}
    make

3) Test the LLVM Pass

    clang -emit-llvm -S -o ${TEST_FILE}.ll test_program/${TEST_FILE}.c
    opt -load ${LLVM_BUILD}/lib/LLVM${LLVM_PASS}.so -${LLVM_PASS} ${TEST_FILE}.ll

Notice: </br>
  LLVM_HOME: llvm's home dir </br>
  LLVM_BUILD: the dir which is uesd to build llvm </br>
  LLVM_PASS: the llvm pass which you want to test </br>
  TEST_FILE: test C file </br>
