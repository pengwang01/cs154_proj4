//Group: Carina Rammelkamp, Andro Stotts, Peng Wang
//CS154, Project 4
#ifndef BRANCHSIM_H
#define BRANCHSIM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _predictor{
	int state;
}Predictor;
typedef struct _table{
	Predictor **predictor;
	int numEntries;
	int numAccess;
	int numMispredict;
}Table;

//Allocate a table with numEntries entries, each initialized to the not-taken state
void *createAndInitialize(int numEntries);

//Given the PC of a branch, report whether this branch is taken or not taken.
int accessBranchPredictor(void *bp, int PC);

//Given the PC of the branch and the actual result (1 = taken, 0 = not taken), update the branch predictor for that entry in the table.
void updateBranchPredictor(void *bp, int PC, int result);

//Report the total number of accesses
int numAccesses(void *bp);

//Report the total number of branches that were incorrectly predicted 
int numMispredictions(void *bp);

#endif

