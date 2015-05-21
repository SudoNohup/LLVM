// CS380C S14 Assignment 4: dceAnalysis.h
// 
// Based on code from Todd C. Mowry
// Modified by Arthur Peters
// Modified by Jianyu Huang (UT EID: jh57266)
////////////////////////////////////////////////////////////////////////////////

#ifndef DCEANALYSIS_H
#define DCEANALYSIS_H

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

#include "IDFA.h"

#include <ostream>
#include <fstream>
#include <iostream>


using namespace llvm;

namespace {
	template <class FlowType>
	class DCEAnalysis: public IDFA<FlowType> {
		public:
		DCEAnalysis() : IDFA<FlowType>() {}
		//meet operator
		virtual void meetOp(BitVector *op1, BitVector *op2);
		//transfer functions
		virtual BitVector* transferFunc(BitVector *input, BitVector *gen, BitVector *kill);
		//generate the gen and kill set for the instructions inside a basic block
		virtual void initInstGenKill(Instruction *ii, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const Instruction *, idfaInfo *> &InstToInfo);
		//generate the gen and kill set for the PHINode instructions inside a basic block
		virtual void initPHIGenKill(BasicBlock *BB, Instruction *ii, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const Instruction *, idfaInfo *> &InstToInfo);
		//get the boundary condition
		virtual BitVector* getBoundaryCondition(int len, Function &F, ValueMap<FlowType, unsigned> &domainToIdx);
		//get the initial flow values
		virtual BitVector* initFlowValues(int len);
		//generate the gen and kill set for each block
		void initGenKill(BasicBlock *Bi, BasicBlock *Pi, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const BasicBlock *, idfaInfo *> &BBtoInfo) {};
	};

	/**
	 * meet operator
	 */
	template <class FlowType>
	void DCEAnalysis<FlowType>::meetOp(BitVector *op1, BitVector *op2) {
		(*op1) &= (*op2);
	}

	/**
	 * transfer functions
	 */
	template <class FlowType>
	BitVector* DCEAnalysis<FlowType>::transferFunc(BitVector *input, BitVector *gen, BitVector *kill) {

		BitVector* output = new BitVector(*kill);
		output->flip();
		(*output) &= *input;
		(*output) |= *gen;
		return output;
	}

	template <class FlowType>
	void DCEAnalysis<FlowType>::initInstGenKill(Instruction *ii, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const Instruction *, idfaInfo *> &InstToInfo) {
		idfaInfo *instInf = InstToInfo[ii];
		(instInf->gen)->reset(0, domainToIdx.size());
		(instInf->kill)->reset(0, domainToIdx.size());

		//temporarily we set the gen set as the empty set.
		ValueMap<Value*, unsigned>::const_iterator iter = domainToIdx.find(dyn_cast<Instruction>(ii));
		if (iter != domainToIdx.end()) {
			Value *val = ii;
			int valIdx = domainToIdx[val];
			if (!((*(instInf->out))[valIdx])) {
				User::op_iterator OI, OE;
				for (OI = ii->op_begin(), OE = ii->op_end(); OI != OE; ++OI) {
					Value *val2 = *OI;
					//check if val2 in domainToIdx??
					if (isa<Instruction>(val2) || isa<Argument>(val2)) {
						int valIdx2 = domainToIdx[val2];
						(instInf->kill)->set(valIdx2);
					}
				}
			}
		} else {
			User::op_iterator OI, OE;
			for (OI = ii->op_begin(), OE = ii->op_end(); OI != OE; ++OI) {
				Value *val2 = *OI;
				//check if val2 in domainToIdx??
				if (isa<Instruction>(val2) || isa<Argument>(val2)) {
					int valIdx2 = domainToIdx[val2];
					(instInf->kill)->set(valIdx2);
				}
			}

		}
	}

	template <class FlowType>
	void DCEAnalysis<FlowType>::initPHIGenKill(BasicBlock *BB, Instruction *ii, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const Instruction *, idfaInfo *> &InstToInfo) {
		idfaInfo *instInf = InstToInfo[ii];
		(instInf->gen)->reset(0, domainToIdx.size());
		(instInf->kill)->reset(0, domainToIdx.size());

		//temporarily we set the gen set as the empty set.
		ValueMap<Value*, unsigned>::const_iterator iter = domainToIdx.find(dyn_cast<Instruction>(ii));
		if (iter != domainToIdx.end()) {
							
			Value *val = ii;
			int valIdx = domainToIdx[val];
			if (!((*(instInf->out))[valIdx])) {
				PHINode *pN = dyn_cast<PHINode>(&*ii);
				unsigned idx = pN->getBasicBlockIndex(BB);
				if (idx >=0 && idx < pN->getNumIncomingValues()) {
					Value *brval = pN->getIncomingValue(idx);
					if (isa<Instruction>(brval) || isa<Argument>(brval)) {
						unsigned brvalIdx = domainToIdx[brval];
						(instInf->kill)->set(brvalIdx);
					}
				}
			}
		} else {
			//the phinode instrution is not in the domain!
			User::op_iterator OI, OE;
			for (OI = ii->op_begin(), OE = ii->op_end(); OI != OE; ++OI) {
				Value *val2 = *OI;
				//check if val2 in domainToIdx??
				if (isa<Instruction>(val2) || isa<Argument>(val2)) {
					int valIdx2 = domainToIdx[val2];
					(instInf->kill)->set(valIdx2);
				}
			}

		}
	}

	/**
	 * get the boundary condition
	 */
	template <class FlowType>
	BitVector* DCEAnalysis<FlowType>::getBoundaryCondition(int len, Function &F, ValueMap<FlowType, unsigned> &domainToIdx) {
		return new BitVector(len, true);
	}

	/**
	 * get the initial flow values
	 */
	template <class FlowType>
	BitVector* DCEAnalysis<FlowType>::initFlowValues(int len) {
		return new BitVector(len, true);
	}
}

#endif
