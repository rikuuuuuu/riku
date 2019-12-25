//
//  main.c
//  algorithm
//
//  Created by りく on 2019/05/24.
//  Copyright © 2019 りく. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

// Returns true if there is a subset of set[] with sun equal to given sum
bool isSubsetSum(int set[], int n, int sum) {
    // The value of subset[i][j] will be true if there is a subset of set[0..j-1]
    //  with sum equal to i
    bool subset[sum+1][n+1];
    
    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
        subset[0][i] = true;
    
    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
        subset[i][0] = false;
    
    // Fill the subset table in botton up manner
    for (int i = 1; i <= sum; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            //
            subset[i][j] = subset[i][j-1];
            if (i >= set[j-1])
                subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
        }
    }
    return subset[sum][n];
}

void Exhaustive(int set[],int n,int sum){
    int temp,m;
    for(int i=0;i<pow(2,n);i++)
    {
        temp=i; m=0;
        for(int j=0;j<n;j++)
        {
            if(temp%2)
                m+=set[j];
            temp=temp/2;
        }
        if(m==sum)
        {
            temp=i;
            for(int j=0;j<n;j++)
            {
                if(temp%2)
                {
                    printf("%4d",set[j]);
                }
                temp=temp/2;
            }
            printf("\n");
        }
    }
}

int main()
{
    clock_t start,end;
    double totaltime1[10],totaltime2[10];
    int n;
    int sum = 15;
    int j=0;
    for(n=5;n<15;n++){
    int set[n];
        for(int i=0;i<n;i++){
            set[i]=rand()%100;
        }

    start = clock();
        if (isSubsetSum(set, n, sum) == true)
            printf("Found a subset with given sum\n");
        else
            printf("No subset with given sum\n");
    end = clock();
    totaltime1[j]=(double)end-start;
   
    start = clock();
    Exhaustive(set,n,sum);
    end = clock();
    totaltime2[j]=(double)end-start;
        j++;
    }
    
    printf("\nDP Spend time was:\n");
    for(int i=0;i<j;i++){
        printf("%lf,",totaltime1[i]);
    }
    printf("\nExhaustive Attack method Spend time was:\n");
    for(int i=0;i<j;i++){
        printf("%lf,", totaltime2[i]);
    }
    
    return 0;
}
