#include "DecisionTree.h"
#include "../CLib/Stack.h"
#include "../CLib/HashSet.h"

static char *line = NULL;
static const int min_samples_split = 2;
static const double min_impurity = 1e-7;
static const int max_depth = 0xffff;

static char* readline(FILE *input, int max_line_len)
{
    int len;
    
    if(fgets(line,max_line_len,input) == NULL)
            return NULL;

    while(strrchr(line,'\n') == NULL)
    {
            max_line_len *= 2;
            line = (char *) realloc(line,max_line_len);
            len = (int) strlen(line);
            if(fgets(line+len,max_line_len-len,input) == NULL)
                    break;
    }
    return line;
}


void readTheProblem(char *filePath, ClassificationStruct *cs)
{
    int i,j;
    FILE *fp = fopen(filePath,"r");
    if(fp == NULL)
    {
        fprintf(stderr,"can't open input file %s\n",filePath);
        exit(1);
    }
    const int max_line_len = 1024;
    line = (char*)malloc(sizeof(char)*max_line_len);
    // first get the feature number and the sample number
    int feature_num=0,sample_num=0;
    while(readline(fp,max_line_len)!=NULL)
    {
        feature_num = 1;
        char *p = strtok(line," ");
        while(1)
        {
            p = strtok(NULL," ");
            if(p==NULL || *p=='\n')
            {
                break;
            }
            feature_num++;
        }
        sample_num++;
    }
    // feature num should exclude the label count
    feature_num--;
    //printf("sample_num=%d and feature_num=%d\n",sample_num,feature_num);
    cs->sample_num = sample_num;
    cs->feature_num = feature_num;
    cs->features = (double**)malloc(sizeof(double*)*sample_num);
    cs->labels = (double*)malloc(sizeof(double)*sample_num);
    // copy the data to ClassificationStruct
    rewind(fp);
    for(i=0;i<sample_num;++i)
    {
        cs->features[i] = (double*)malloc(sizeof(double)*feature_num);
        if(readline(fp,max_line_len)==NULL)
        {
            fprintf(stderr,"Read Line Error\n");
            exit(1);
        }
        char *p = strtok(line," ");
        double p_float = atof(p);
        cs->features[i][0]=p_float;
        for(j=1;j<feature_num;j++)
        {
            p = strtok(NULL," ");
            cs->features[i][j] = atof(p);
        }
        p = strtok(NULL," ");
        cs->labels[i] = atof(p);
    }
    
    fclose(fp);
}


double* createUniqueValues(double feature_values[], int feature_sz, int *op_hash_sz)
{
    HashSet *set = createHashSet(HashCodeInt, EqualDouble);
    int i=0;
    for(i=0;i<feature_sz;i++)
    {
        double *tmpval = (double*)malloc(sizeof(double));
        *tmpval = feature_values[i];
        HashSetAddData(set, tmpval);
    }
    int hash_sz = set->size;
    double *UniqueValuesArr = (double*)calloc(hash_sz,sizeof(double));
    HashSetIterator *it = createHashSetIterator(set);
    int count = 0;
    while(HashSetIteratorHasNext(it))  
    {  
        double *tmp= HashSetIteratorNext(it);
        UniqueValuesArr[count] = *tmp;
        count++;
        free(tmp);
    }
    freeHashSetIterator(it);
    freeHashSet(set);
    *op_hash_sz = hash_sz;
    return UniqueValuesArr;
}


void divide_on_feature(double **featuresXY, int n_samples, 
                       int n_features, ClassificationStruct *cs1,
                       ClassificationStruct *cs2, int feature_i, double threshold)
{
    int i,j;
    int cs1_samples=0, cs2_samples=0;
    // count divide samples number
    
    
}


DecisionNode *build_DecisionTree(ClassificationStruct *cs, int current_depth)
{
    int i,j;
    double largest_impurity = 0.0;
    // Add y as last column of X
    double **featuresXY = NULL;
    featuresXY = (double**)malloc(sizeof(double*)*cs->sample_num);
    for(i=0;i<cs->sample_num;i++)
    {
        featuresXY[i] = (double*)malloc(sizeof(double)*(cs->feature_num+1));
        for(j=0;j<cs->feature_num;++j)
        {
            featuresXY[i][j] = cs->features[i][j];
        }
        featuresXY[i][cs->feature_num] = cs->labels[i];
    }
    
    int n_samples = cs->sample_num;
    int n_features = cs->feature_num;
    int feature_i = 0; int k=0; double threshold;
    
    if(n_samples>min_samples_split && current_depth <= max_depth)
    {
        for(feature_i=0;feature_i<n_features;feature_i++)
        {
            double feature_values[n_samples];
            //feature_values = unique(X[:, feature_i])
            for(k=0;k<n_samples;k++)
            {
                feature_values[k] = featuresXY[k][feature_i];
            }
            int unique_sz = 0;
            double *unique_features = createUniqueValues(feature_values,n_samples, &unique_sz);
            // Iterate through all unique values of feature column i and
            // calculate the impurity
            for(j=0;j<unique_sz;++j)
            {
                threshold = unique_features[j];
                // init the split ClassificationStruct Xy1, Xy2
                ClassificationStruct *cs_Xy1, *cs_Xy2;
                cs_Xy1 = (ClassificationStruct*)malloc(sizeof(ClassificationStruct));
                cs_Xy2 = (ClassificationStruct*)malloc(sizeof(ClassificationStruct));
                
            }
        }
    }
    
    
    free(featuresXY);
    return NULL;
}


