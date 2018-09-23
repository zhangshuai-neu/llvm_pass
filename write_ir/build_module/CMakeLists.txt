set(LLVM_LINK_COMPONENTS
  Core
  ExecutionEngine
  Interpreter
  MC
  Support
  nativecodegen
  )

add_llvm_example(build_module
  build_module.cpp
  )
