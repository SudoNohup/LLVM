// CS380C S14 Assignment 4: licm.cpp
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

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"

#include "llvm/Analysis/Dominators.h"
#include "llvm/Support/CFG.h"
#include "llvm/Transforms/Scalar.h"

//#include "llvm/Analysis/ValueTracking.h"

//#include "licmAnalysis.h"


#include "domAnalysis.h"
//#include "reachAnalysis.h"

#include <ostream>
#include <fstream>
#include <iostream>

using namespace llvm;

namespace {
	class LICM : public LoopPass {
		public:
			static char ID;

			BasicBlock *preheader;
			Loop *myloop;
			LoopInfo *LI;
			DominatorTree *DT;
			bool isChanged;
			std::vector<Value *> *LIset;

			std::vector<BasicBlock *> domain;
			ValueMap<BasicBlock *, unsigned> domainToIdx;
			ValueMap<const BasicBlock *, idfaInfo *> BBtoInfo;		

			LICM() : LoopPass(ID) {
				initializeLICMPass(*PassRegistry::getPassRegistry());
			}

			// runOnLoop function, similar to runOnFunction
			virtual bool runOnLoop(Loop *L, LPPassManager &LPM) {
				isChanged = false;
				LI = &getAnalysis<LoopInfo>();
 				DT = &getAnalysis<DominatorTree>();
				myloop = L;
				preheader = L->getLoopPreheader();

				/*
				errs() << *preheader << "\n";
				errs() << *(L->getHeader()) << "\n";
				errs() << "Exit\n";
				SmallVector<BasicBlock*, 8> ExitBlocks;
				myloop->getExitBlocks(ExitBlocks);

				for (unsigned i = 0, e = ExitBlocks.size(); i != e; ++i) {
					errs() << *ExitBlocks[i] << "\n";
				}
				*/

				Function *F = preheader->getParent();
				for (Function::iterator Bi = F->begin(), Be = F->end(); Bi != Be; ++Bi) {
					domain.push_back(&*Bi);
				}
				for (int i = 0; i < domain.size(); ++i) {
					domainToIdx[domain[i]] = i;
				}



				DomAnalysis<BasicBlock *> *domAnly = new DomAnalysis<BasicBlock *>();
				domAnly->analysisBB(domain, *F, true, BBtoInfo);

				AnnotatorBB<BasicBlock *> annot(BBtoInfo, domain);
				F->print(errs(), &annot);

				//print the result....
				


				/*
				std::vector<Value *> domain;
				for (Function::arg_iterator arg = F->arg_begin(); arg != F->arg_end(); ++arg) {
					domain.push_back(arg);
				}
				for (inst_iterator ii = inst_begin(F), ie = inst_end(F); ii != ie; ++ii) {
					if (!ii->getName().empty()) {
						domain.push_back(&*ii);
					}
				}
				ValueMap<const BasicBlock *, idfaInfo *> BBtoInfo;		
				ValueMap<const Instruction *, idfaInfo *> InstToInfo;
				ReachAnalysis<llvm::Value *> *reachAnly = new ReachAnalysis<llvm::Value *>();
				reachAnly->analysis(domain, *F, true, BBtoInfo, InstToInfo);
				*/


				//replace isLoopInvariant with the ReachDef definition.........................
				if (preheader)
					putAboveHandler(DT->getNode(L->getHeader()));
				/*
				genLIset(L);
				modifyLI();
				*/

				return isChanged;
			}

			/*
			 * generate the Loop Invariant Set
			 */
			void genLIset(Loop *L) {
				LIset = new std::vector<Value *>(); 
				bool setChanged = true;
				while(setChanged) {
					setChanged = false;
					for (unsigned i = 0, e = L->getBlocks().size(); i != e; ++i) {
						BasicBlock *BB = L->getBlocks()[i];

						if (!myloop->contains(BB)) continue;
						if (LI->getLoopFor(BB) != myloop) continue;
						for (BasicBlock::iterator II = BB->begin(), E = BB->end(); II != E; ++II) {
							//	Value *V = I->getOperand(i);

							//Phi...Node we cannot move it into preheader
							//if (isLoopInvariantOperands(II) && (LIset->find(II) == LIset->end()) && isSafeInst(II)) {
							//Notice......II cannot be a argument....
							if (isLoopInvariantOperands(II) && std::find(LIset->begin(), LIset->end(), II) == LIset->end() && isSafeInst(II)) {
								LIset->push_back(II);
								//errs() << *II << "\n";
								setChanged = true;
							}
						}
					}
				}
			}

			/* 
			 * move the loop invariant instructions to the preheader as long as it satisifies four conditions
			 */
			void modifyLI() {
				bool hoistChanged = true;
				while (hoistChanged) {
					hoistChanged = false;
					for (std::vector<Value *>::iterator it = LIset->begin(); it != LIset->end(); ) {
						Value *val = *it;
						if (Instruction *Inst = dyn_cast<Instruction>(val)) {
							if (isLoopInvariantOprInloop(Inst) && dominateExits(Inst) && dominateUses(Inst) && isSafeInst(Inst)) {
								putAboveInst(Inst);
								//how to erase the elements from the vector with iterator...
								it = LIset->erase(it);
								hoistChanged = true;
							} else {
								it++;
							}
						} else {
							it++;
						}
					}
				}
			}

			/*
			 * The candidate is in a block that dominates all uses of variable x.
			 */
			bool dominateUses(Instruction *I) {				
				for (Value::use_iterator UI = I->use_begin(), UE = I->use_end(); UI != UE; ++UI) {
					if (Instruction *useI = dyn_cast<Instruction>(*UI)) {
						//if (!(DT->dominates(I, useI))) {
						if (!(DT->dominates(I, useI))) {
							return false;
						}
					}
				}
				return true;	
			}

			/*
			 * the instruction that is safe to move outside of the loop.
			 */
			bool isSafeInst(Instruction *I) {
				//if (I->getName().empty() || isa<PHINode>(I)) {
				if (isa<PHINode>(I)) {
					return false;
				}	
				//if (!isa<StoreInst>(I) && !isa<BinaryOperator>(I) && !isa<CastInst>(I) && !isa<SelectInst>(I) && !isa<GetElementPtrInst>(I) &&
				if (!isa<BinaryOperator>(I) && !isa<CastInst>(I) && !isa<SelectInst>(I) && !isa<GetElementPtrInst>(I) &&
						!isa<CmpInst>(I) && !isa<InsertElementInst>(I) && !isa<ExtractElementInst>(I) && !isa<ShuffleVectorInst>(I) &&
						!isa<ExtractValueInst>(I) && !isa<InsertValueInst>(I))
					return false;
			
				return true;
			}

			/* to delete
			bool isSafePutAboveInst(Instruction  &I) {
			//if( !isa<BasicBlock>(&**op_it)
				if (!isa<BinaryOperator>(I) && !isa<CastInst>(I) && !isa<SelectInst>(I) && !isa<GetElementPtrInst>(I) &&
						!isa<CmpInst>(I) && !isa<InsertElementInst>(I) && !isa<ExtractElementInst>(I) && !isa<ShuffleVectorInst>(I) &&
						!isa<ExtractValueInst>(I) && !isa<InsertValueInst>(I))
					return false;
				return safeToMove(I);
			}
			*/


			/* 
			 * depth-first order traverse on the dominatorTree
			 */
			void putAboveHandler(DomTreeNode *N) {
				BasicBlock *BB = N->getBlock();
				//BB should be the immediately withnin L
				if (!myloop->contains(BB)) return;
				if (!(LI->getLoopFor(BB) != myloop)) {
					for (BasicBlock::iterator II = BB->begin(), E = BB->end(); II != E; ) {
						Instruction *I = II++;
						//constant folding the instruction????....TO DO....
						//if (isLoopInvariantOprInloop(&I) && isSafePutAboveInst(I) && safeToMove(I)) {
						if (isLoopInvariantOprInloop(I) && dominateExits(I) && dominateUses(I) && isSafeInst(I)) {
						//if (isLoopInvariantOprInloop(&I) && safeToMove(I)) {}
							//errs() << "to be moved into the preheader\n";
							//errs() << I << "\n";
							putAboveInst(I);
						}
					}
				}
				const std::vector<DomTreeNode*> &Children = N->getChildren();
				for (unsigned i = 0, e = Children.size(); i != e; ++i) {
					putAboveHandler(Children[i]);
				}	
			}

			/*
			 * the computation is loop invariant, plus its operands have all be moved outside the loop
			 */
			bool isLoopInvariantOperands(Instruction *I) {
				for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i) {
					if (!isLI(I->getOperand(i)) && std::find(LIset->begin(), LIset->end(), I->getOperand(i)) == LIset->end() )
						return false;
				}
				return true;
			}

			/*
			 * the computation is loop invariant or not
			 */
			bool isLoopInvariantOprInloop(Instruction *I) {
				for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i) {
					if (!isLI(I->getOperand(i)) )
						return false;
				}
				return true;
			}

			//we might need to change it to the "reach def" style...
			/*
			 * the instrution is outside the loop or not
			 */
			bool isLI(Value *V) {
				if (Instruction *I = dyn_cast<Instruction>(V)) {
					return !myloop->contains(I);
				}
				return true;
			}

			/* 
			 * The candidate is in a basic block that dominates all uses of variable x
			 */
			bool dominateExits(Instruction *I) {
				if (I->getParent() == myloop->getHeader()) {
					return true;
				}
				SmallVector<BasicBlock*, 8> ExitBlocks;
				myloop->getExitBlocks(ExitBlocks);
				for (unsigned i = 0, e = ExitBlocks.size(); i != e; ++i) {
					//if (!DT->dominates(I->getParent(), ExitBlocks[i]))
					if (!DT->dominates(I->getParent(), ExitBlocks[i]))
						return false;
				}
				if (ExitBlocks.empty())
					return false;
				return true;
			}

			
			/* to delete...
			bool safeToMove(Instruction &Inst) {
				if (isSafeToSpeculativelyExecute(&Inst)) {
					errs() << "isSafeToSpeculatively\n";
					errs() << Inst << "\n";
					return true;
				}
	
				if (Inst.getParent() == myloop->getHeader()) {
					//errs() << "getHeader...\n";
					//errs() << Inst << "\n";
					return true;
				}

				SmallVector<BasicBlock*, 8> ExitBlocks;
				myloop->getExitBlocks(ExitBlocks);
				for (unsigned i = 0, e = ExitBlocks.size(); i != e; ++i) {
					if (!DT->dominates(Inst.getParent(), ExitBlocks[i]))
						return false;
				}

				if (ExitBlocks.empty())
					return false;

				return true;
			}
			*/

			/* to delete...
			bool isSafePutAboveInst(Instruction  &I) {
				if (!isa<BinaryOperator>(I) && !isa<CastInst>(I) && !isa<SelectInst>(I) && !isa<GetElementPtrInst>(I) &&
						!isa<CmpInst>(I) && !isa<InsertElementInst>(I) && !isa<ExtractElementInst>(I) && !isa<ShuffleVectorInst>(I) &&
						!isa<ExtractValueInst>(I) && !isa<InsertValueInst>(I))
					return false;
				return safeToMove(I);
			}
			*/

			void putAboveInst(Instruction *I) {
				I->moveBefore(preheader->getTerminator());
				isChanged = true;
			}

			// We don't modify the program, so we preserve all analyses
			virtual void getAnalysisUsage(AnalysisUsage &AU) const {
				AU.setPreservesCFG();
				AU.addRequired<LoopInfo>();
				AU.addRequired<DominatorTree>();
			}

	};

	// LLVM uses the address of this static member to identify the pass, so the
	// initialization value is unimportant.
	char LICM::ID = 0;

	// Register this pass to be used by language front ends.
	// This allows this pass to be called using the command:
	//    clang -c -Xclang -load -Xclang ./FunctionInfo.so loop.c
	static void registerMyPass(const PassManagerBuilder &,
			PassManagerBase &PM) {
		PM.add(new LICM());
	}
	RegisterStandardPasses
		RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
				registerMyPass);

	// Register the pass name to allow it to be called with opt:
	//    clang -c -emit-llvm loop.c
	//    opt -load ./FunctionInfo.so -function-info loop.bc > /dev/null
	// See http://llvm.org/releases/3.4/docs/WritingAnLLVMPass.html#running-a-pass-with-opt for more info.
	RegisterPass<LICM> X("licm-pass", "licm-pass");

}
