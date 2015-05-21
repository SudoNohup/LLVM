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
//#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"

#include "llvm/Support/InstIterator.h"
#include "llvm/Support/CallSite.h"

#include "llvm/DebugInfo.h"
#include "llvm/IR/Metadata.h"
#include "llvm/Assembly/AssemblyAnnotationWriter.h"
#include "llvm/Support/FormattedStream.h"



#include <ostream>
#include <fstream>
#include <iostream>

using namespace llvm;

namespace {

class FunctionInfo : public FunctionPass {
public:
  static char ID;
  FunctionInfo() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) {
	errs() << "functionName: ";
	errs().write_escaped(F.getName());

	int argNum = 0;
	//llvm::Function::ArgumentListType args = F.getArgumentList();
	//errs() << F.getArgumentList();
	//for(arg_iterator AI = F.arg_begin(); AI != F.arg_end(); ++AI) {
	//	++argNum;
	//}
	//llvm::Function::arg_iterator AI;
	for (llvm::Function::arg_iterator AI = F.arg_begin(); AI != F.arg_end(); ++AI) {
		++argNum;
	}	
	errs() << ", arguments=" << argNum << "\n";

	/*
	for (llvm::Function::iterator i = (&F)->begin(), e = (&F)->end(); i != e; ++i) {
		errs() << "Basic block (name="<< i->getName() << ") has " << i->size() << " instructions.\n";
		for (llvm::BasicBlock::iterator ii = i->begin(), ie = i->end(); ii != ie; ++ii) {
			errs() << *ii << "\n";
		}
	}
	*/
	
	/*
	int blockNum = 0;
	llvm::BasicBlock BB;
	
	for (BB = F.front(); BB != F.back(); ++BB) {
		++blockNum;
	}
	errs() << "basic blocks=" << F.size() << "\n";
	*/

	//errs() << F.front();
	
	//errs() << "basic blocks=" << F.size() << "\n";
	int instNum = 0;
	for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
		//errs() << *I << "\n";
		++instNum;
	}
	errs() << ", instructions=" << instNum << "\n";


	/*
	int callsitesNum = 0;
	for (Value::use_iterator U = F.use_begin(); U != F.use_end(); ++U) {
		if (Instruction *use = dyn_cast<Instruction>(*U)) {
			CallSite CS(use);
			if (CS.getCalledValue() == &F) {
				callsitesNum++;
			}
		}
	}
	

	errs() << ", call sites=" << callsitesNum << "\n";
	*/

	int callCounter = 0;
	for (Function::iterator b = F.begin(), be = F.end(); b != be; ++b) {
		for (BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; ++i) {
			if (CallInst* callInst = dyn_cast<CallInst>(&*i)) {
				if (callInst->getCalledFunction() == &F) {
					++callCounter;
				}
			}
		}
	}
	errs() << ", call sites=" << callCounter << "\n";



    return false; } // We don't modify the program, so we preserve all analyses
  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
  }
};

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char FunctionInfo::ID = 0;

// Register this pass to be used by language front ends.
// This allows this pass to be called using the command:
//    clang -c -Xclang -load -Xclang ./FunctionInfo.so loop.c
static void registerMyPass(const PassManagerBuilder &,
                           PassManagerBase &PM) {
    PM.add(new FunctionInfo());
}
RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerMyPass);

// Register the pass name to allow it to be called with opt:
//    clang -c -emit-llvm loop.c
//    opt -load ./FunctionInfo.so -function-info loop.bc > /dev/null
// See http://llvm.org/releases/3.4/docs/WritingAnLLVMPass.html#running-a-pass-with-opt for more info.
RegisterPass<FunctionInfo> X("function-info", "Function Information");

}
