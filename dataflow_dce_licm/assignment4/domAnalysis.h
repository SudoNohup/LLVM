// CS380C S14 Assignment 3: domAnalysis.h
// 
// Based on code from Todd C. Mowry
// Modified by Arthur Peters
// Modified by Jianyu Huang (UT EID: jh57266)
////////////////////////////////////////////////////////////////////////////////

#ifndef DOMANALYSIS_H
#define DOMANALYSIS_H

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
		class DomAnalysis : public IDFA<FlowType> {
			public:
				DomAnalysis() : IDFA<FlowType>() {}


				//meet operator
				void meetOp(BitVector *op1, BitVector *op2);
				//transfer functions
				BitVector* transferFunc(BitVector *input, BitVector *gen, BitVector *kill);
				//generate the gen and kill set for the instructions inside a basic block
				void initInstGenKill(Instruction *ii, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const Instruction *, idfaInfo *> &InstToInfo) {};
				//generate the gen and kill set for the PHINode instructions inside a basic block
				void initPHIGenKill(BasicBlock *BB, Instruction *ii, ValueMap<FlowType, unsigned> &domainToIdx, IinfoMap &InstToInfo) {};
				//generate the gen and kill set for each block
				void initGenKill(BasicBlock *Bi, BasicBlock *Pi, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const BasicBlock *, idfaInfo *> &BBtoInfo);
				//get the boundary condition
				BitVector* getBoundaryCondition(int len, Function &F, ValueMap<FlowType, unsigned> &domainToIdx);
				//get the initial flow values
				BitVector* initFlowValues(int len);
		};

	/**
	 * meet operator
	 */
	template <class FlowType>
	void DomAnalysis<FlowType>::meetOp(BitVector *op1, BitVector *op2) {
		(*op1) &= (*op2);
	}

	/**
	 * transfer functions
	 */
	template <class FlowType>
	BitVector* DomAnalysis<FlowType>::transferFunc(BitVector *input, BitVector *gen, BitVector *kill) {
		BitVector* output = new BitVector(*kill);
		output->flip();
		(*output) &= *input;
		(*output) |= *gen;
		return output;
	}

	/**
	 * generate the gen and kill set for the instructions inside a basic block
	 */
	/*
	template <class FlowType>
	void DomAnalysis<FlowType>::initInstGenKill(Instruction *ii, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const Instruction *, idfaInfo *> &InstToInfo) {
		//nonsense here
	}
	*/

	/*
	 * generate the gen and kill set for each block
	 */
	template <class FlowType>
	void DomAnalysis<FlowType>::initGenKill(BasicBlock *Bi, BasicBlock *Pi, ValueMap<FlowType, unsigned> &domainToIdx, ValueMap<const BasicBlock *, idfaInfo *> &BBtoInfo) {
		idfaInfo *BBinf = BBtoInfo[&*Bi];
		(BBinf->gen)->reset(0, domainToIdx.size());
		int valIdx = domainToIdx[Bi];
		(BBinf->gen)->set(valIdx);
		(BBinf->kill)->reset(0, domainToIdx.size());	
	}

	/**
	 * get the boundary condition
	 */
	template <class FlowType>
	BitVector* DomAnalysis<FlowType>::getBoundaryCondition(int len, Function &F, ValueMap<FlowType, unsigned> &domainToIdx) {
		return new BitVector(len, false);
	}

	/**
	 * get the initial flow values
	 */
	template <class FlowType>
	BitVector* DomAnalysis<FlowType>::initFlowValues(int len) {
		return new BitVector(len, true);
	}

}

#endif
