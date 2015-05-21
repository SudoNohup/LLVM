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

#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
//#include "llvm/Analysis/InstructionSimplify.h"
#include "./InstructionSimplify1.h"

#include "llvm/ADT/SetVector.h"


#include <ostream>
#include <fstream>
#include <iostream>

using namespace llvm;

namespace {


	class LocalOpts : public FunctionPass {
		public:
			static char ID;
			LocalOpts() : FunctionPass(ID) {}

			void replaceAndErase(Value *val, BasicBlock::iterator &ii) {
				if (val != NULL) {
					ii->replaceAllUsesWith(val);
				}
				BasicBlock::iterator tmp = ii;
				++ii;
				tmp->eraseFromParent();
			}



			virtual bool runOnFunction(Function &F) {
				for (Function::iterator BB = F.begin(), Be = F.end(); BB != Be; ++BB) {
					SmallSetVector<Instruction *, 8> Worklist;
					for (BasicBlock::iterator ii = BB->begin(), ie = BB->end(); ii != ie; ++ii) {
						Worklist.insert(ii);
					}

					for (unsigned Idx = 0; Idx != Worklist.size(); ++Idx) {
						recursivelySimplifyInstruction(Worklist[Idx]);
					}
					//BasicBlock::iterator ii = BB->begin(), ie = BB->end();
					//while (ii != ie) {}
						//if (Value *V = SimplifyInstruction(ii)) 
						//if (Value *V = recursivelySimplifyInstruction(ii)) 
						//recursivelySimplifyInstruction(ii);
							//ii->replaceAllUsesWith(V);
							//replaceAndErase(V, ii);
					//}
				}
				return false;
			}

			// We don't modify the program, so we preserve all analyses
			virtual void getAnalysisUsage(AnalysisUsage &AU) const {
				AU.setPreservesAll();
			}
	};

	// LLVM uses the address of this static member to identify the pass, so the
	// initialization value is unimportant.
			char LocalOpts::ID = 0;

			// Register this pass to be used by language front ends.
			// This allows this pass to be called using the command:
			//    clang -c -Xclang -load -Xclang ./FunctionInfo.so loop.c
			static void registerMyPass(const PassManagerBuilder &,
					PassManagerBase &PM) {
				PM.add(new LocalOpts());
			}
			RegisterStandardPasses
				RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
						registerMyPass);

			// Register the pass name to allow it to be called with opt:
			//    clang -c -emit-llvm loop.c
			//    opt -load ./FunctionInfo.so -function-info loop.bc > /dev/null
			// See http://llvm.org/releases/3.4/docs/WritingAnLLVMPass.html#running-a-pass-with-opt for more info.
			RegisterPass<LocalOpts> X("my-local-opts", "my-local-opts");

	}
