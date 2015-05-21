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

#include "llvm/Support/PatternMatch.h"


#include <ostream>
#include <fstream>
#include <iostream>

using namespace llvm;
using namespace llvm::PatternMatch;

namespace {

	class OptSummary {
		public:
			int algbraicIdent;
			int constantFold;
			int strengthReduce;
			int deleteUnused;
			int consecutiveUnion;
			OptSummary(): algbraicIdent(0), constantFold(0), strengthReduce(0), deleteUnused(0), consecutiveUnion(0) {}
	};

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


			/*
			bool LocalOptimize() {

			}
			*/



			virtual bool runOnFunction(Function &F) {
				OptSummary *ops = new OptSummary();
				bool funcchanged = false;

				for (Function::iterator BB = F.begin(), Be = F.end(); BB != Be; ++BB) {
					//for (BasicBlock::iterator ii = BB->begin(), ie = BB->end(); ii != ie; ++ii) {


					bool bbchanged = true;

					while (bbchanged) {

						bbchanged = false;

						BasicBlock::iterator ii = BB->begin(), ie = BB->end();
						while (ii != ie) {
							bool instchanged = false;
							Value *L, *R;
							if (ii->getNumOperands() == 2) {
								L = ii->getOperand(0);
								R = ii->getOperand(1);
							}

							unsigned op = ii->getOpcode();

							APInt zero, one;
							//32 bit or 64 bit integer?
							if (IntegerType *inttype = dyn_cast<IntegerType>(ii->getType())) {
								zero = APInt(inttype->getBitWidth(), 0);
								one = APInt(inttype->getBitWidth(), 1);	
							}


							if (op == Instruction::SExt) {
								Value *S = ii->getOperand(0);
								if (ConstantInt *SC = dyn_cast<ConstantInt>(S)) {
									//Constant -> Value
									Value *conv = ConstantInt::get(ii->getType(), SC->getSExtValue());//, false);
									replaceAndErase(conv, ii);
									//ops->constantFold++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}
							} else if (op == Instruction::Trunc) {
								Value *S = ii->getOperand(0);
								if (ConstantInt *SC = dyn_cast<ConstantInt>(S)) {
									//Value *conv = ConstantInt::get(ii->getType(), SC->getValue());
									Value *conv = ConstantInt::get(ii->getType(), SC->getSExtValue());
									replaceAndErase(conv, ii);
									//ops->constantFold++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}
							}

							if (op == Instruction::Add ||op == Instruction::Sub ||op == Instruction::Mul ||op == Instruction::SDiv ||op == Instruction::UDiv ||op == Instruction::Shl ||op == Instruction::AShr ||op == Instruction::LShr) {
								//no one use this instruction...then we delete it.....
								if (!ii->hasNUsesOrMore(1)) {
									//hope this works.....&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
									replaceAndErase(NULL, ii);
									ops->deleteUnused++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}
							}

							if (op == Instruction::Add) {
								if (ConstantInt *LC = dyn_cast<ConstantInt>(L)) {
									if (LC->getValue() == zero) {
										replaceAndErase(R, ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}
								} else if (ConstantInt *RC = dyn_cast<ConstantInt>(R)) {
									if (RC->getValue() == zero) {
										replaceAndErase(L, ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}
								}
							} else if (op == Instruction::Sub) {
								//dyn_cast<Instruction>(L);

								//if ((dyn_cast<Instruction>(L))->isIdenticalTo(dyn_cast<Instruction>(R))) {
								//}
								if (L == R) {
									replaceAndErase(ConstantInt::get(L->getContext(), zero), ii);
									ops->algbraicIdent++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								} else if (ConstantInt *RC = dyn_cast<ConstantInt>(R)) {
									if (RC->getValue() == zero) {
										replaceAndErase(L, ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}
									//change the following cast into dyn_cast???
								} 
							} else if (op == Instruction::Mul) {
								if (ConstantInt *LC = dyn_cast<ConstantInt>(L)) {
									if (LC->getValue() == zero) {
										replaceAndErase(ConstantInt::get(LC->getContext(), zero), ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									} else if (LC->getValue() == one) {
										replaceAndErase(R, ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}
								} else if (ConstantInt *RC = dyn_cast<ConstantInt>(R)) {
									if (RC->getValue() == zero) {
										replaceAndErase(ConstantInt::get(RC->getContext(), zero), ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									} else if (RC->getValue() == one) {
										replaceAndErase(L, ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}
								}
							} else if (op == Instruction::UDiv || op == Instruction::SDiv) {
								//.............we need to judge whether R is 0.....
								//if R is a variable, can we just add a assert R != 0??????????????????????
								//............................assert..............................

								//if (dyn_cast<Instruction>(L)->isIdenticalTo(dyn_cast<Instruction>(R))) {
								//}
								//...........

								if (ConstantInt *LC = dyn_cast<ConstantInt>(L)) {
									if (LC->getValue() == zero) {
										//........judge whether *RC is equal to zero?????????????????????????????????
										//
										if (ConstantInt *RC = dyn_cast<ConstantInt>(R)) {
											if (RC->getValue() == zero) {
												errs() << "Divided by Zero Error"<<"\n";
											}
										}

										replaceAndErase(ConstantInt::get(LC->getContext(), zero), ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}	
								} else if (ConstantInt *RC = dyn_cast<ConstantInt>(R)) {
									if (RC->getValue() == one) {
										replaceAndErase(L, ii);
										ops->algbraicIdent++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}
								} else if (L == R) {//...........and L != 0
									//if (dyn_cast<Instruction>(L)->isIdenticalTo(dyn_cast<Instruction>(R))) {
									//L is not a const........if (cast<ConstantInt>(L)->isIdenticalTo(cast<ConstantInt>(R))) {
									//}
									//}
									//

									//if L.type is Constant or Instruction??????

									if (ConstantInt *RC = dyn_cast<ConstantInt>(R)) {
										if (RC->getValue() == zero) {
											errs() << "Divided by Zero Error"<<"\n";
										}
									}

									replaceAndErase(ConstantInt::get(L->getContext(), one), ii);
									ops->algbraicIdent++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}
							} else if (op == Instruction::Store) {
								Value *varptr = dyn_cast<StoreInst>(ii)->getPointerOperand();
								Value *value = dyn_cast<StoreInst>(ii)->getValueOperand();
								if (isa<Constant>(*value)) {
									for (Value::use_iterator u = varptr->use_begin(), ue = varptr->use_end(); u != ue; ++u) {
										if (LoadInst *li = dyn_cast<LoadInst>(*u)) {
											li->replaceAllUsesWith(value);
											++ii;
											//we need to add counter to marker......
											//ops->algbraicIdent++;
											instchanged = true;	bbchanged = true; funcchanged = true;
											errs() << "flag***666" << "\n";
											continue;
										}
									}
								}
							} else {
								;
							}


							//...............Added some feature.............
							if (op == Instruction::Add) {
								// X + undef -> undef
								if (match(R, m_Undef())) {
									replaceAndErase(R, ii);
									ops->algbraicIdent++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}

								if (match(L, m_Undef())) {
									replaceAndErase(L, ii);
									ops->algbraicIdent++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}

								// X + 0 -> X, not necessarily
								//if (match(Op1, m_Zero())) {
								//	replaceAndErase(Op0, ii);
								//	ops->algbraicIdent++;
								//	instchanged = true; bbchanged = true; funcchanged = true;
								//	continue;
								//}

								// X + (Y - X) -> Y; (Y - X) + X -> Y
								Value *Y = 0;
								if (match(R, m_Sub(m_Value(Y), m_Specific(L))) || match(L, m_Sub(m_Value(Y), m_Specific(R)))) {
									replaceAndErase(Y, ii);
									ops->algbraicIdent++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}
							} else if (op == Instruction::Sub) {
								// X - undef -> undef
								// undef - X -> undef
								if (match(L, m_Undef()) || match(R, m_Undef())) {
									replaceAndErase(UndefValue::get(L->getType()), ii);
									ops->algbraicIdent++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}

								// (X*2) - X -> X
								//Value *X = 0;
								if (match(L, m_Mul(m_Specific(R), m_ConstantInt<2>())) || match(L, m_Shl(m_Specific(R), m_One()))) {
									replaceAndErase(R, ii);
									ops->algbraicIdent++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}

							}





							//Constant Folding
							if (op == Instruction::Add || op == Instruction::Sub || op == Instruction::Mul || op == Instruction::SDiv || op == Instruction::UDiv || op == Instruction::Shl || op == Instruction::AShr || op == Instruction::LShr ) {
								if (ii->getNumOperands() == 2 && isa<ConstantInt>(L) && isa<ConstantInt>(R)) {
									Value *result = calcOpRes(op, cast<ConstantInt>(L), cast<ConstantInt>(R));
									if (result) {
										replaceAndErase(result, ii);
										ops->constantFold++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									} else {

									}
								}
							}



							
							if (op == Instruction::Add ||op == Instruction::Mul) {
								//need to be careful enough.....likely that L cannot be an instruction......then dyn_cast<Instruction> should return NULL....
								//llvm::Instruction *LI = dyn_cast<Instruction>(L);
								errs() << "wo yao mei zi" << "\n";
								if (consecutiveJoin(op, L, R, ii)) { 
									//ops->consecutiveUnion++;
									ops->constantFold++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								} else if (consecutiveJoin(op, R, L, ii)) {
									//ops->consecutiveUnion++;
									ops->constantFold++;
									instchanged = true; bbchanged = true; funcchanged = true;
									continue;
								}
							}





							//Strength Reductions
							if (op == Instruction::Mul) {
								if (ConstantInt *LC = dyn_cast<ConstantInt>(L)) {
									APInt mulval = LC->getValue();

									Instruction *RI = dyn_cast<Instruction>(R);

									errs() << RI->getNumOperands() << "\n";


									if (mulval.isPowerOf2()) {
										unsigned lshift = mulval.logBase2();

										BinaryOperator *newInst = BinaryOperator::Create(Instruction::Shl, R, ConstantInt::get(L->getType(), lshift));// isSigned is set to false
										ii->getParent()->getInstList().insert(ii, newInst);

										replaceAndErase(newInst, ii);
										ops->strengthReduce++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									} 
								} else if (ConstantInt *RC = dyn_cast<ConstantInt>(R)) {
									APInt mulval = RC->getValue();
									if (mulval.isPowerOf2()) {
										unsigned lshift = mulval.logBase2();
										BinaryOperator *newInst = BinaryOperator::Create(Instruction::Shl, L, ConstantInt::get(R->getType(), lshift));// isSigned is set to false
										//ii->getParent()->getInstList().insertafter(ii, newInst);
										//insert before ii
										ii->getParent()->getInstList().insert(ii, newInst);

										replaceAndErase(newInst, ii);
										ops->strengthReduce++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}
								}
							} else if (op == Instruction::SDiv || op == Instruction::UDiv) {
								if (ConstantInt *RC = dyn_cast<ConstantInt>(R)) {
									APInt divval = RC->getValue();
									if (divval.isPowerOf2()) {
										unsigned rshift = divval.logBase2();
										BinaryOperator *newInst;
										if (op == Instruction::SDiv) {
											newInst = BinaryOperator::Create(Instruction::AShr, L, ConstantInt::get(R->getType(), rshift));// isSigned is set to false
										} else {
											newInst = BinaryOperator::Create(Instruction::LShr, L, ConstantInt::get(R->getType(), rshift));// isSigned is set to false
										}
										//ii->getParent()->getInstList().insertafter(ii, newInst);
										//insert before ii
										ii->getParent()->getInstList().insert(ii, newInst);

										replaceAndErase(newInst, ii);
										ops->strengthReduce++;
										instchanged = true; bbchanged = true; funcchanged = true;
										continue;
									}
								}
							}


							if (!instchanged) {
								++ii;
							} else {
								//bbchanged = true; funcchanged = true; 
							}

						}


					}
				}

				errs() << F.getName() << "\n";
				errs() << "Summary of Optimizations\n";
				errs() << "Algebraic Identities: " << ops->algbraicIdent << "\n";
				errs() << "Constant Folding: " << ops->constantFold << "\n";
				errs() << "Strength Reduction: " << ops->strengthReduce << "\n";
				errs() << "Delete Unused: " << ops->deleteUnused << "\n\n";
				return funcchanged;
				}

				bool consecutiveJoin(unsigned op, Value *L, Value *R, BasicBlock::iterator &ii) {
					Instruction::BinaryOps Opcode = (Instruction::BinaryOps)op;
					if (!isa<Constant>(L) ) {
						errs() << "wo yao mei zi2" << "\n";
						if (llvm::Instruction *LI = dyn_cast<Instruction>(L)) {

							errs() << "wo yao mei zi3" << "\n";
							if (ConstantInt *RV = dyn_cast<ConstantInt>(R)) {
								errs() << "wo yao mei zi4" << "\n";
								//unsigned op2 = LI->getOpcode();
								if  (LI->getNumOperands() == 2 && LI->getOpcode() == Opcode) {
									errs() << "wo yao mei zi5" << "\n";
									Value *LL, *LR; 
									LL = LI->getOperand(0);
									LR = LI->getOperand(1);
									if (ConstantInt *LRC = dyn_cast<ConstantInt>(LR)) {

										errs() << "wo yao mei zi6" << "\n";
										if (ConstantInt *Res = calcOpRes(op, dyn_cast<ConstantInt>(LR), dyn_cast<ConstantInt>(R))) {
											errs() << "wo yao mei zi7" << "\n";
											BinaryOperator *newInst = BinaryOperator::Create(Opcode, LL, Res);
											//insert before ii
											ii->getParent()->getInstList().insert(ii, newInst);

											replaceAndErase(newInst, ii);
											return true;
										}
									} else if (ConstantInt *LLC = dyn_cast<ConstantInt>(LL)) {
										if (ConstantInt *Res = calcOpRes(op, dyn_cast<ConstantInt>(LL), dyn_cast<ConstantInt>(R))) {
											errs() << "wo yao mei zi8" << "\n";
											BinaryOperator *newInst = BinaryOperator::Create(Opcode, LR, Res);
											//insert before ii
											ii->getParent()->getInstList().insert(ii, newInst);

											replaceAndErase(newInst, ii);
											return true;

										}
									}
								} else {
								}
							}
						}
					}
					return false;
				}




				ConstantInt *calcOpRes(unsigned op, ConstantInt *L, ConstantInt *R) {
					errs() << "coming inside......................";

					if (L == NULL || R == NULL) {
						return NULL;
					}

					if (op == Instruction::Add) {
						return ConstantInt::get(L->getContext(), L->getValue() + R->getValue());
						//return ConstantExpr::getAdd(cast<ConstantInt>(I->getOperand(0)), cast<ConstantInt>(I->getOperand(1)));
						//return ConstantInt::get(cast<IntegerType>(ii->getType()), L->getValue() + R->getValue());
						//return cast<ConstantInt>(ConstantInt::get(L->getType(), L->getValue() + R->getValue()));
					} else if (op == Instruction::Sub) {
						return ConstantInt::get(L->getContext(), L->getValue() - R->getValue());
					} else if (op == Instruction::Mul) {
						return ConstantInt::get(L->getContext(), L->getValue() * R->getValue());
					} else if (op == Instruction::UDiv) {
						if (!R->isZero()) {
							return ConstantInt::get(L->getContext(), L->getValue().udiv(R->getValue()));
						} else {
							return NULL;
						}
					} else if (op == Instruction::SDiv) {
						if (!R->isZero()) {
							return ConstantInt::get(L->getContext(), L->getValue().sdiv(R->getValue()));
						} else {
							return NULL;
						}
					} else if (op == Instruction::Shl) {
						return ConstantInt::get(L->getContext(), L->getValue().shl(R->getValue()));
					} else if (op == Instruction::AShr) {
						return ConstantInt::get(L->getContext(), L->getValue().ashr(R->getValue()));
					} else if (op == Instruction::LShr) {
						return ConstantInt::get(L->getContext(), L->getValue().lshr(R->getValue()));
					} else {
						errs() << "...........error....**********************";
						return NULL;
					}
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
