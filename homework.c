//
//  main.c
//  study3
//
//  Created by りく on 2019/05/27.
//  Copyright © 2019 りく. All rights reserved.
//

#include <stdio.h>

#define M 10  //グラフのノード数
int step = 1;   //移動のステップ数
int num = 1;    //到達可能なノードの数
int before = 0; //毎回移動の前の到達可能なノード数
int after = 1 ;  //毎回移動の後の到達可能なノード数

int Fixedpoint()    //移動してから、新しい到達可能なノードが出ない、不動点と見なす
{
    if (after == before)    //不動点である
        return 1;
    else                    //不動点ではない
        return 0;
}

int Overlap(int V[M], int node)    //1ステップ移動した後の到達可能なノードの重複性を判定
{
    int i;
    for(i = 0; i < num; i++ )
    {
        if(V[i] == node)       //重複なノードである
        {
            return 1;
        }
    }
    return 0;  //重複ではない、新しい到達可能なノード
}


//iステップで、重複ではなくて、到達可能なすべてのノードを配列Vに入れる
int Search(int X[M][M], int V[M])
{
    int node;
    before = num;   //移動の前の到達可能なノード数
    for(node = 0; node < M; node++)
    {
        if(X[step][node] == 1 && ( Overlap(V, node) == 0) )  //到達可能、かつ重複ではないノード
        {
            V[num] = node;      //到達可能なノードの集合に入れる
            num++;
        }
    }
    after = num;    //移動の後の到達可能なノード数
    return 0;
}


//行列かけ算　X0・A=X1 , X1・A=X2 ,...
int Multiplacation(int X[M][M], int A[M][M])
{
    int j, k;
        for (j = 0; j < M; j++)
        {
            int sum = 0;
            for (k = 0; k < M; k++)
            {
                sum = sum || (X[step-1][k] * A[k][j]);  //ブール代数の演算
            }
                X[step][j] = sum;
            }
    return 0;
}


//到達可能性の判定
int Judge(int X[M][M], int A[M][M], int V[M], int m, int n)
{
    int k;
    int reach = 0;
    while(Fixedpoint() == 0)    //不動点ではない、ループに入る
    {
        Multiplacation(X, A);   //行列かけ算し、1ステップ移動
        Search(X, V);           //重複ではなくて、到達可能なすべてのノードを配列Vに入れる
        step++;
    }
    
    printf("不動点の到達可能なノード集合: V = { ");
    for(k = 0; k < num; k++)
    {
        printf("%d ",V[k]);
    }
    printf("}\n");
    
    for(k = 0; k < num; k++)
    {
        if(V[k] == n)       //終点nに到達可能
        {
            reach = 1;
            printf("ノード%dが到達可能である\n", n);
        }
    }

    if(reach == 0)          //終点nに到達不能
        printf("ノード%dが到達不能である\n", n);
    
    return 0;
}

int main()
{
    int X[M][M] = {0};    //X0,X1,...,Xmからなる配列
    int A[M][M];        //隣接行列
    int V[M] = {0};       //到達可能なノードの集合
    int m;      //起点のノードIDを入力
    int n;      //終点のノードIDを入力
    int i = 0;
    int j = 0;
    printf("開始のノードm:");
    scanf("%d",&m);
    printf("終点のノードn:");
    scanf("%d",&n);
    
    //起点ノードmにより、X0ベクトルを初期化
    for (j = 0; j < M; j++)
    {
        if(j == m)
            X[0][j] = 1;
        else
            X[0][j] = 0;
    }
    V[0] = m;   //0ステップ、起点mは到達可能なノード
    
    printf("隣接行列Aを入力してください：\n");
    for (i = 0; i < M; i++)
    {
        printf("隣接行列Aの%d行目:\n", i);
        for (j = 0; j < M; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    
    Judge(X, A, V, m, n);   //到達可能性の判定器
    
    return 0;
}
