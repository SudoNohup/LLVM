// CS380C S14 Assignment 4: dce.cpp
// 
// Based on code from Todd C. Mowry
// Modified by Arthur Peters
// Modified by Jianyu Huang (UT EID: jh57266)
////////////////////////////////////////////////////////////////////////////////

#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Assembly/AssemblyAnnotationWriter.h"

#include "dceAnalysis.h"

#include <ostream>
#include <fstream>
#include <iostream>

using namespace llvm;

namespace {
	class DCE : public FunctionPass {
		public:
			static char ID;
			bool isChanged;
			DCE() : FunctionPass(ID) {}
			virtual bool runOnFunction(Function &F) {
				std::vector<Value *> domain;
				for (Function::arg_iterator arg = F.arg_begin(); arg != F.arg_end(); ++arg) {
					domain.push_back(arg);
				}
				for (inst_iterator ii = inst_begin(F), ie = inst_end(F); ii != ie; ++ii) {
					if (!ii->getName().empty() && !isa<CallInst>(&*ii)) {
						domain.push_back(&*ii);
					}
				}
				ValueMap<const BasicBlock *, idfaInfo *> *BBtoInfo = new ValueMap<const BasicBlock *, idfaInfo *>();		
				ValueMap<const Instruction *, idfaInfo *> *InstToInfo = new ValueMap<const Instruction *, idfaInfo *>();
				DCEAnalysis<llvm::Value *> *dceAnly = new DCEAnalysis<llvm::Value *>();
				dceAnly->analysis(domain, F, false, *BBtoInfo, *InstToInfo);

				/*
				Annotator<Value *> annot(*BBtoInfo, *InstToInfo, domain);
				F.print(errs(), &annot);
				*/

				BitVector *toErase = new BitVector(*((*BBtoInfo)[&(F.front())]->in)); 
				delete BBtoInfo; 
				delete InstToInfo;
				delete dceAnly;

				eraseDCE(domain, *toErase);
				return isChanged;
			}

			// erase the dead code in IR
			bool eraseDCE(std::vector<Value *> domain, BitVector &bv) {
				isChanged = false;
				for (int i = (bv.size()) - 1; i >= 0; --i) {
				//for (int i = 0; i < bv.size(); ++i) {
					if (!bv[i]) continue;
					if (Instruction *ii = dyn_cast<Instruction>(domain[i])) {
						if (ii->hasNUsesOrMore(1)) {
							Value *val = UndefValue::get(ii->getType());
							if (val != NULL) {	
								ii->replaceAllUsesWith(val);
							}
						}
						if (ii->getParent()) {
							ii->eraseFromParent();
							isChanged = true;
						}
					}
				}
				return isChanged;
			}

			// We don't modify the program, so we preserve all analyses
			virtual void getAnalysisUsage(AnalysisUsage &AU) const {
				AU.setPreservesAll();
			}

	};

	// LLVM uses the address of this static member to identify the pass, so the
	// initialization value is unimportant.
	char DCE::ID = 0;

	// Register this pass to be used by language front ends.
	// This allows this pass to be called using the command:
	//    clang -c -Xclang -load -Xclang ./FunctionInfo.so loop.c
	static void registerMyPass(const PassManagerBuilder &,
			PassManagerBase &PM) {
		PM.add(new DCE());
	}
	RegisterStandardPasses
		RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
				registerMyPass);

	// Register the pass name to allow it to be called with opt:
	//    clang -c -emit-llvm loop.c
	//    opt -load ./FunctionInfo.so -function-info loop.bc > /dev/null
	// See http://llvm.org/releases/3.4/docs/WritingAnLLVMPass.html#running-a-pass-with-opt for more info.
	RegisterPass<DCE> X("dce-pass", "dce-pass");

}
