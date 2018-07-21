#ifndef _DECISIONTREE_H
#define _DECISIONTREE_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ClassificationStruct
{
    double **features;
    double *labels;
    int feature_num;
    int sample_num;
}ClassificationStruct;

    
typedef struct DecisionNode
{
    int feature_i;
    double threshold;
    double value;
    /*left tree*/
    struct DecisionNode *true_branch;
    /*right tree*/
    struct DecisionNode *false_branch;
}DecisionNode;


void readTheProblem(char *filePath, ClassificationStruct *cs);

DecisionNode *build_DecisionTree(ClassificationStruct *cs, int current_depth);
    

#ifdef __cplusplus
}
#endif
#endif  /* _DECISIONTREE_H */
