//
//  main.c
//  study2
//
//  Created by りく on 2019/05/14.
//  Copyright © 2019 りく. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define  MAX  100

typedef  struct {
    int   Queue[MAX];  /*キューの保存配列*/
    int   front, rear;  /*キューの先頭と末尾へのポイント*/
}SeqQueue,*PointQueue;

PointQueue  Init_SeqQueue( )
{   /*キューを初期化する。　戻り値：新たなキューポインタ、null->失敗*/
    PointQueue  Q;
    Q=(PointQueue)malloc(sizeof(SeqQueue));
    if (Q) {
        Q->front=0;
        Q->rear=0;
    }
    return Q;
}

int  Empty_SeqQueue(PointQueue Q)
{   /*キューが空いてるか否か判断する。戻り值：1->empty、0->not empty*/
    if (Q && Q->front==Q->rear)
    return (1);
else
    return (0);
}

int   Enqueue (PointQueue Q , int x)
{   /*キューに状態を入れる。戻り値：1->成功、-1->オーバーフロー*/
    if ((Q->rear+1)%MAX==Q->front)
    {    printf("FULL");
        return -1;
    }
    else
    {     Q->rear=(Q->rear+1) % MAX;
        Q->Queue[Q->rear]=x;
        return 1;
    }
}
int  Dequeue (PointQueue Q,int *x)
{   /*配列の一番先頭の状態を取り出す。戻り值：1->成功，－1->キューが空いてる,取り出された状態を*xに保存する  */
    if (Empty_SeqQueue(Q)) {
        printf("EMPTY");
        return -1;
    }
    else
    {  Q->front=(Q->front+1) % MAX;
        *x=Q->Queue[Q->front];
        return 1;
    }
}

int isSafe(int s)
{   /*状態が安全か否か判断する。安全な場合：岸A、Bのウサギの数がオオカミの数より多い。　ウサギとオオカミの数が等しい。　ある岸にウサギがいない。　制約条件：ウサギとオオカミの数は0〜3*/
    int x,y;
    x=(s/1)%10;
    y=(s/10)%10;
    if( ((y<=x) && ((3-y)<=(3-x)) && y>=0 && y<=3 && x>=0 && x<=3) || ((x==0)||(3-x==0)) )
    {
        return 1;
    }
    else return 0;
}

int enCoding(int x)
{  /*32個の3桁の状態を0-31の10進数にエンコードする*/
    int y=0;
    y=(x/1)%10*1+(x/10)%10*4+(x/100)%10*16;
    return y;
}

int deCoding(int x)
{   /*0-31の10進数をディコードする*/
    int p=1,y=0,remainder;
    while(1)
    {
        remainder=x%4;
        x/=4;
        y+=remainder*p;
        p*=10;
        if(x<4)
        {
            y+=x*p;
            break;
        }
    }
    return y;
}

void Crossing()
{
    PointQueue Q;
    int visited[32]; /*岸Aの32個の可能な状態*/
    int i,j,nextStatus,nextStatusX; /*岸Aの次の状態とその状態をエンコードした結果*/
    int status,statusX; /*岸Aの現時点の状態とその状態をエンコードした結果*/
    int cross[]={101,102,110,111,120}; /*状態の変化量　毎回、ウサギとオオカミの変化量は1〜2*/
    int m=0,x,y;
    int reverseRoute[50];
    int Route[50];
    
    Q = Init_SeqQueue( );
    for(i = 0;i < 32;i++)
        visited[i] = -1; /*岸Aの32個の状態の値を−1とする。−1->この状態を通過してない*/
    
    status = 133;
    /* 岸Aの最初の状態。百の位：1->船は岸Aにある 0->船は岸Bにある  十の位：岸Aのオオカミの数　一の位：岸Aのウサギの数 */
    Enqueue (Q , status);
    visited[31] = 0;
    while(!Empty_SeqQueue(Q) && (visited[0]== -1))/* 幅優先探索 */
    {
        Dequeue (Q,&status);
        printf("\n");
        printf("今の状態%d  ",status);
        for(j = 0; j <= 4; j++)
        {
            if((status/100)%10==1)/*現時点の状態、船が岸Aにある（百の位=1）　現時点の状態-変化量=次の状態*/
            {
                nextStatus = status-cross[j];
                nextStatusX = enCoding(nextStatus);
                statusX = enCoding(status);
               

                if(isSafe(nextStatus) && (visited[nextStatusX]== -1))
                {
                    Enqueue (Q , nextStatus);
                    visited[nextStatusX] = statusX;
                    printf("次の状態%d ",nextStatus);
                }
            }
            
            else if((status/100)%10==0)/*現時点の状態、船が岸Bにある（百の位=0）　現時点の状態+変化量=次の状態*/
                {
                    nextStatus = status+cross[j];
                    nextStatusX = enCoding(nextStatus);
                    statusX = enCoding(status);
                    
                    if(isSafe(nextStatus) && (visited[nextStatusX]== -1))
                    {
                        Enqueue (Q , nextStatus);
                        visited[nextStatusX] = statusX;
                        printf("次の状態%d ",nextStatus);
                    }
                }
        }
    }
    nextStatusX = 0;
    for(m=0;visited[nextStatusX]!= -1 && visited[nextStatusX]!= 0;m++)
    {   /*最終状態から初期状態に遡り、川を渡る状態の変化を得る*/
        reverseRoute[m]=visited[nextStatusX];
        nextStatusX = visited[nextStatusX];
        if(nextStatusX == 0) exit(0);
    }
    
    printf("\n岸Aの変化過程:");
    for(x=0,y=m-1;x<m&&y>=0;++x,--y)
    {   /*reverseRoute配列を逆にする*/
        Route[x]=deCoding(reverseRoute[y]);
        printf("%d ",Route[x]);
    }
    nextStatusX = 0;
    printf("%d \n",deCoding(nextStatusX));
    printf("最短回数:%d \n",m);
}

int main(void)
{
    Crossing();
    return 0;
}
