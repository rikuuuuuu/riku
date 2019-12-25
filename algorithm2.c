//
//  main.c
//  algorithm2
//
//  Created by りく on 2019/06/10.
//  Copyright © 2019 りく. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int DP(int s[],int f[],int v[],int n)
{
    int i,j;
    int value[n];
    value[0]=v[0];
    int max;
    for(i=1;i<n;i++)
    {
        for(j=0;j<=i;j++)
        {
            if (f[j]<=s[i])
            {
                if (v[i]+value[j]>value[i-1])
                value[i]=v[i]+value[j];
                else value[i]=value[i-1];
            }
        }
        if (value[i]=='\0')
        {
            if(value[i-1]>v[i])
            value[i]=value[i-1];
            else value[i]=v[i];
        }
    }
    max = value[i-1];
    return max;
}
int main(int argc, const char * argv[]) {
    int s[] = {1,3,0,5,3,5,6,8,8,2,11};
    int f[] = {4,5,6,7,9,9,10,11,12,14,16};
    int v[] = {5,3,6,8,3,9,1,4,6,4,5};
    int value=0;
    int n=sizeof(s)/sizeof(s[0]);
    value=DP(s,f,v,n);
    printf("0から%dの区間最大の重みの和:%d\n",f[n-1],value);
    return 0;
}
