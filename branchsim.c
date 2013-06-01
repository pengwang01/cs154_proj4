//Group: Carina Rammelkamp, Andro Stotts, Peng Wang
//CS154, Project 4
#include "branchsim.h"
#define DEBUG 0

//Allocate a table with numEntries entries, each initialized to the not-taken state
void *createAndInitialize(int numEntries){
  if(DEBUG)
    printf("numEntries: %d\n", numEntries);
   Table *table = malloc(sizeof(Table));
    table->numAccess=0;
    table->numMispredict=0;
    table->numEntries = numEntries;
    int i;
    table->predictor = calloc(numEntries,sizeof(Predictor*));
    for(i=0;i<numEntries;i++){
	table->predictor[i] = malloc(sizeof(Predictor));
     	table->predictor[i]->state=0;
    }
    return (void*)table;
}

//Given the PC of a branch, report whether this branch is taken or not taken.
int accessBranchPredictor(void *bp, int PC){
  ((Table*)bp)->numAccess++;

//  if((((Table*)bp)->predictor[(PC >> 2)]->state) > 1)
  if((((Table*)bp)->predictor[(PC >> 2) & (((Table*)bp)->numEntries - 1)]->state) > 1)
    return 1;
  else
    return 0;

//SHOULD NEVER REACH HERE
return -1;
}

//Given the PC of the branch and the actual result (1 = taken, 0 = not taken), update the branch predictor for that entry in the table.
void updateBranchPredictor(void *bp, int PC, int result){
  //((Table*)bp)->numAccess++;
  int state = ((Table*)bp)->predictor[(PC >> 2) & (((Table*)bp)->numEntries - 1)]->state; 
  //int state = ((Table*)bp)->predictor[(PC >> 2)]->state; 

switch(state){
 case 0:
   state = result ? 1 : 0;
   if(state)		
     ((Table*)bp)->numMispredict++;
   break;
 case 1:
   state = result ? 3 : 0;
   if(state)		
     ((Table*)bp)->numMispredict++;
   break;
 case 2:
   state = result ? 3 : 0;
   if(!state)		
     ((Table*)bp)->numMispredict++;
   break;
 case 3:
   state = result ? 3 : 2;
   if(state==2)
     ((Table*)bp)->numMispredict++;
   break;
 default:
   printf("ERROR: incorrect result given");
   break;
 }
((Table*)bp)->predictor[(PC >> 2)  & (((Table*)bp)->numEntries - 1)]->state=state;
// ((Table*)bp)->predictor[(PC >> 2)]->state=state;
}

//Report the total number of accesses
int numAccesses(void *bp){
  return ((Table*)bp)->numAccess;
}

//Report the total number of branches that were incorrectly predicted 
int numMispredictions(void *bp){

  return ((Table*)bp)->numMispredict;
}
