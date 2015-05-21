// 15-745 S13 Assignment 1: FunctionInfo.cpp
// 
// Based on code from Todd C. Mowry
// Modified by Arthur Peters
////////////////////////////////////////////////////////////////////////////////

#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/DebugInfo.h"
//#include "llvm/Constants.h"
#include "llvm/IR/Metadata.h"
#include "llvm/Assembly/AssemblyAnnotationWriter.h"
#include "llvm/Support/FormattedStream.h"


#include <ostream>
#include <fstream>
#include <iostream>

using namespace llvm;

namespace {


class AAWriter : public AssemblyAnnotationWriter {
public:
	AAWriter(): AssemblyAnnotationWriter() {}
	void emitInstructionAnnot(const Instruction * I, formatted_raw_ostream & stream) {
		if (MDNode *N = I->getMetadata("dbg")) {
			  DILocation Loc(N);
			  unsigned Line = Loc.getLineNumber();
			  StringRef File = Loc.getFilename();
			  StringRef Dir = Loc.getDirectory();
			  stream << Dir << "/" << File << ": " << Line << ": ";
			  //errs() << Dir << ": " << File << ": " << Line << ": ";
		  } else {
			  //errs() << "----";
		  }
		  //stream << *I << "\n";	
	}
};

class assignment1 : public ModulePass {
public:
  static char ID;
  assignment1() : ModulePass(ID) {}

  bool runOnModule(Module &M) {
	  AAWriter *aww = new AAWriter();
	  M.print(errs(), aww);
    return false;
  }



  // We don't modify the program, so we preserve all analyses
  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
  }
};

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char assignment1::ID = 0;

// Register this pass to be used by language front ends.
// This allows this pass to be called using the command:
//    clang -c -Xclang -load -Xclang ./FunctionInfo.so loop.c
static void registerMyPass(const PassManagerBuilder &,
                           PassManagerBase &PM) {
    PM.add(new assignment1());
}
RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerMyPass);

// Register the pass name to allow it to be called with opt:
//    clang -c -emit-llvm loop.c
//    opt -load ./FunctionInfo.so -function-info loop.bc > /dev/null
// See http://llvm.org/releases/3.4/docs/WritingAnLLVMPass.html#running-a-pass-with-opt for more info.
RegisterPass<assignment1> X("assignment1", "assignment1");

}
