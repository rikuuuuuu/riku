//
//  main.c
//  study
//
//  Created by りく on 2019/4/17.
//  Copyright © 2019 りく. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
struct Student{
    char name[10];
    float english;
    float japanese;
    float math;
}Student;       //学生の情報がまとめとしたStudentという構造体を定義
struct Student Stu[50];     //５０個要素を持つStudent型の配列を宣言
float sum[50];              //成績の合計の配列を宣言
int n=0;                    //学生数
char i[50];                 //入力する文字列を保存する配列
char *input[50];            //分割された文字列を保存する配列
char filename[10];          //ファイル出力及び入力のファイル名

//対話的に成績を入力する関数
void add(){
    printf("%d人目の成績を入力してください.\n名前：",n+1);
    scanf("%s",Stu[n].name);
    printf("英語：");
    scanf("%f",&Stu[n].english);
    printf("国語：");
    scanf("%f",&Stu[n].japanese);
    printf("数学：");
    scanf("%f",&Stu[n].math);
    n+=1;
    fflush(stdin);      //入力バッファをクリア
    getchar();          //読み込んだ改行文字を除去
}

//成績の省力入力の関数
void add2(){
    strcpy(Stu[n].name,input[1]);       //文字列の代入
    Stu[n].english=atoi(input[2]);      //入力のchar型をint型に変換し、代入
    Stu[n].japanese=atoi(input[3]);
    Stu[n].math=atoi(input[4]);
    n+=1;
    fflush(stdin);      //入力バッファをクリア
}

//各科目と合計の平均、最高点、最低点と偏差を計算し、表示する関数
void search(){
    //各科目の平均点と平均点の合計を計算
    float avgE,sumE=0,avgJ,sumJ=0,avgM,sumM=0;
    for(int i=0;i<n;i++){
        sumE+=Stu[i].english;
        sumJ+=Stu[i].japanese;
        sumM+=Stu[i].math;
    }
    avgE=sumE/n;
    avgJ=sumJ/n;
    avgM=sumM/n;
    float sumA=avgE+avgJ+avgM;
    
    //各科目と合計の最高点を計算
    float maxE=0,maxJ=0,maxM=0,sumMax=0;
    for(int i=0;i<n;i++){
        if (Stu[i].english>=maxE)
            maxE=Stu[i].english;
        if (Stu[i].japanese>=maxJ)
            maxJ=Stu[i].japanese;
        if (Stu[i].math>=maxM)
            maxM=Stu[i].math;
        int sum=Stu[i].english+Stu[i].japanese+Stu[i].math;
        if (sum>=sumMax)
            sumMax=sum;
    }
    
    //各科目と合計の最低点を計算
    float minE=100,minJ=100,minM=100,sumMin=300;
    for(int i=0;i<n;i++){
        if (Stu[i].english<=minE)
            minE=Stu[i].english;
        if (Stu[i].japanese<=minJ)
            minJ=Stu[i].japanese;
        if (Stu[i].math<=minM)
            minM=Stu[i].math;
        int sum=Stu[i].english+Stu[i].japanese+Stu[i].math;
        if (sum<=sumMin)
            sumMin=sum;
    }
    
    //各科目と合計の標準偏差を計算
    float a=0,b=0,c=0,d=0;
    for(int i=0;i<n;i++){
        a+=pow(Stu[i].english-avgE,2);
        b+=pow(Stu[i].japanese-avgJ,2);
        c+=pow(Stu[i].math-avgM,2);
        d+=pow(Stu[i].english+Stu[i].japanese+Stu[i].math-sumA,2);
    }
    double devE=sqrt((double)(a/n));
    double devJ=sqrt((double)(b/n));
    double devM=sqrt((double)(c/n));
    double sumDev=sqrt((double)(d/n));
    printf("---成績一覧---.\n登録者数：%d人.\n\t英語\t\t国語\t\t数学\t\t合計.\n平均:%3.1f\t%3.1f\t%3.1f\t%3.1f.\n最高点:%.1lf\t%.1lf\t%.1lf\t%.1lf.\n最低点:%.1f\t%.1f\t%.1f\t%.1f.\n標準偏差:%.2lf\t%.2lf\t%.2lf\t%.2lf.\n"
           ,n,avgE,avgJ,avgM,sumA,maxE,maxJ,maxM,sumMax,minE,minJ,minM,sumMin,devE,devJ,devM,sumDev);
}

//全ての成績データをファイルに出力する関数
void outport(){
    FILE *fp = NULL;            //ファイル構造体へのポインタを宣言
    fp=fopen(input[2],"w+");    //入力配列の三番目の文字列をファイル名として、書き込むモードでファイルを開く
    for(int j=0; j<n; j++){
        sum[j]=Stu[j].english+Stu[j].japanese+Stu[j].math;
        fprintf(fp, "%s,%.1f,%.1f,%.1f,%.1f\n",Stu[j].name,Stu[j].english,Stu[j].japanese,Stu[j].math,sum[j]);
    }                           //ファイルにデータを書き込む
    printf("%sファイルに出力しました!\n",input[2]);
    fclose(fp);         //ファイルを閉じる
}

//ファイルの成績データを読み込む関数
void import(){
    FILE * fp;          //ファイル構造体へのポインタを宣言
    char *line=NULL;    //ファイルの内容の文字列へのポインタを宣言
    char *p;            //分割される文字列へのポインタを宣言
    char buffer[1024];  //文字配列を宣言
    int  j=n;       //ファイル読み込む前の学生数
    if((fp = fopen(input[2], "r")) == NULL){
        printf("File open error!\n");
    }       //入力配列の三番目の文字列をファイル名として、読み込むモードでファイルを開く
    while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL) //lineにに文字列一行ずつを代入し、最後までループを実行
    {
        p = strtok(line, ",");      //「,」で文字列を分割
        while (p != NULL)           //１行ずつ読み込む
        {
            strcpy(Stu[n].name,p);  //文字列の代入
            p = strtok(NULL, ",");  //「,」で文字列を分割
            Stu[n].english=atoi(p); //char型をint型に変換し、代入
            p = strtok(NULL, ",");
            Stu[n].japanese=atoi(p);
            p = strtok(NULL, ",");
            Stu[n].math=atoi(p);
            p = strtok(NULL, ",");
            sum[n]=atoi(p);
            p = strtok(NULL, ",");
        }
        n++;
    }
    printf("%d人の成績を登録しました!\n",n-j);     //増加の学生数を表示
    if( fclose(fp) ){
        printf( "Can not close the file!\n" );
    }                   //ファイルを閉じる
}

//登録されている学生の名前の一覧表示する関数
void namesearch(){
    printf("登録学生一覧\n");
    for(int j=0;j<n;j++)
    {
        printf("%s\n",Stu[j].name);
    }
}

//引数で与えた学生の成績のみを表示する関数
void studentsearch(){
    printf("名前\t\t英語\t\t国語\t\t数学\t\t合計\n");
    for (int j=0; j<n; j++) {
        if (strcmp(Stu[j].name,input[2])==0) {
            printf("%s\t%.1f\t%.1f\t%.1f\t%.1f\n",Stu[j].name,Stu[j].english,Stu[j].japanese,Stu[j].math,sum[j]);
        }   //入力の名前と合う学生の成績を表示
    }
}

//英語の点数の高い方から順に、学生を並べる
void englishsearch(){
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n ; j++){
            if(Stu[i].english < Stu[j].english){
                struct Student temp = Stu[i];
                Stu[i] = Stu[j];
                Stu[j] = temp;
            }
        }
    }
}

//英語の点数が高い方から順に、学生名とその点数を表示
void englishprint(){
    printf("---英語の成績---\n登録者数：%d人\n名前\t点数\n",n);
    for(int i = 0;i < n; i++){
        printf("%s %.1f\n",Stu[i].name,Stu[i].english);
    }
}

//国語の点数の高い方から順に、学生を並べる
void japanesesearch(){
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n ; j++){
            if(Stu[i].japanese < Stu[j].japanese){
                struct Student temp = Stu[i];
                Stu[i] = Stu[j];
                Stu[j] = temp;
            }
        }
    }
}

//国語の点数が高い方から順に、学生名とその点数を表示
void japaneseprint(){
    printf("---国語の成績---\n登録者数：%d人\n名前\t点数\n",n);
    for(int i = 0;i < n; i++){
        printf("%s %.1f\n",Stu[i].name,Stu[i].japanese);
    }
}

//数学の点数の高い方から順に、学生を並べる
void mathsearch(){
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n ; j++){
            if(Stu[i].math < Stu[j].math){
                struct Student temp = Stu[i];
                Stu[i] = Stu[j];
                Stu[j] = temp;
            }
        }
    }
}

//数学の点数が高い方から順に、学生名とその点数を表示
void mathprint(){
    printf("---数学の成績---\n登録者数：%d人\n名前\t点数\n",n);
    for(int i = 0;i < n; i++){
        printf("%s %.1f\n",Stu[i].name,Stu[i].math);
    }
}

//入力の文字列の中からファイル名を判明し、変数filenameに代入
void fileselect(){
    if (strcmp(input[1],"-f")==0){
        strcpy(filename,input[2]);
    }
    if (strcmp(input[2],"-f")==0){
        strcpy(filename,input[3]);
    }
    if (strcmp(input[3],"-f")==0){
        strcpy(filename,input[4]);
    }
}

//登録されている学生の名前をファイル出力
void nameoutport(){
    fileselect();                  //入力の文字列の中からファイル名を判明する関数を呼び出す
    FILE *fp = NULL;               //ファイル構造体へのポインタを宣言
    fp=fopen(filename,"w+");       //書き込むモードでファイルをファイルを開く
    fprintf(fp,"登録学生一覧\n");
    for(int j=0;j<n;j++)
    {
        fprintf(fp,"%s\n",Stu[j].name);
    }                               //全ての学生の名前を出力
    printf("%sファイルに出力しました!\n",filename);
    fclose(fp);
}

//引数で与えた学生の成績のみをファイル出力
void studentoutport(){
    fileselect();       //入力の文字列の中からファイル名を判明する関数を呼び出す
    FILE *fp = NULL;
    fp=fopen(filename,"w+");
    fprintf(fp,"名前\t英語\t国語\t数学\t合計\n");
    //入力の文字列に学生名前という引数の位置により、当該学生の成績をファイルに書き込む
    for (int j=0; j<n; j++) {
        if (strcmp(Stu[j].name,input[4])==0) {
            fprintf(fp,"%s\t%.1f\t%.1f\t%.1f\t%.1f\n",Stu[j].name,Stu[j].english,Stu[j].japanese,Stu[j].math,sum[j]);
        }
        else if (strcmp(Stu[j].name,input[2])==0) {
            fprintf(fp,"%s\t%.1f\t%.1f\t%.1f\t%.1f\n",Stu[j].name,Stu[j].english,Stu[j].japanese,Stu[j].math,sum[j]);
        }
    }
    printf("%sファイルに出力しました!\n",filename);
    fclose(fp);
}

//英語の点数が高い方から順に、学生名とその点数をファイル出力
void englishoutport(){
    englishsearch();        //英語の点数の高い方から順に、学生を並べる関数を呼び出す
    fileselect();           //入力の文字列の中からファイル名を判明する関数を呼び出す
    FILE *fp = NULL;
    fp=fopen(filename,"w+");
    fprintf(fp,"---英語の成績---\n登録者数：%d人\n名前\t点数\n",n);
    //学生名と英語の点数をファイルに書き込む
    for(int j=0; j<n; j++){
        fprintf(fp, "%s\t%.1f\n",Stu[j].name,Stu[j].english);
    }
    printf("%sファイルに出力しました!\n",filename);
    fclose(fp);
}

//国語の点数が高い方から順に、学生名とその点数をファイル出力
void japaneseputport(){
    japanesesearch();       //国語の点数の高い方から順に、学生を並べる関数を呼び出す
    fileselect();           //入力の文字列の中からファイル名を判明する関数を呼び出す
    FILE *fp = NULL;
    fp=fopen(filename,"w+");
    fprintf(fp,"---国語の成績---\n登録者数：%d人\n名前\t点数\n",n);
    //学生名と国語の点数をファイルに書き込む
    for(int j=0; j<n; j++){
        fprintf(fp, "%s\t%.1f\n",Stu[j].name,Stu[j].japanese);
    }
    printf("%sファイルに出力しました!\n",filename);
    fclose(fp);
}

//数学の点数が高い方から順に、学生名とその点数をファイル出力
void mathoutport(){
    mathsearch();           //数学の点数の高い方から順に、学生を並べる関数を呼び出す
    fileselect();           //入力の文字列の中からファイル名を判明する関数を呼び出す
    FILE *fp = NULL;
    fp=fopen(filename,"w+");
    fprintf(fp,"---数学の成績---\n登録者数：%d人\n名前\t点数\n",n);
    //学生名と数学の点数をファイルに書き込む
    for(int j=0; j<n; j++){
        fprintf(fp, "%s\t%.1f\n",Stu[j].name,Stu[j].math);
    }
    printf("%sファイルに出力しました!\n",filename);
    fclose(fp);
}

int main(int argc, const char * argv[]) {
    printf( "q:終了\nh:ヘルプ\n");
    //コマンドを入力するループ
    while(1){
        printf( "Enter a value :");
        gets(i);        //キーボードから文字列を配列iに読み込む
        int m=0;        //input配列の文字の位置
        char *p;        //分割される文字列へのポインタを宣言
        p = strtok(i," ");  //空白で文字列を分割
        //キーボードから入力の文字列を分割し、順番にinput配列に代入
        while(p != NULL){
            input[m]=p;
            p = strtok(NULL," ");
            m++;
        }
        //入力の一番目の文字により、コマンドを判断
        switch(*input[0]){
            case 'i':
            {
                //コマンドはiだけの場合
                if (input[1]=='\0')  {
                    add();      //対話的に入力する関数を呼び出す
                    break;
                }
                //i -f fileの場合
                else if((strcmp(input[1],"-f")==0)&&(input[2]!='\0')&&(input[3]=='\0')){
                    import();   //ファイルの成績データを読み込む関数を呼び出す
                    break;
                }
                //i name english language mathの場合
                else if((input[1]!='\0')&&(input[2]!='\0')&&(input[3]!='\0')&&(input[4]!='\0')){
                    add2();     //省力入力する関数を呼び出す
                    break;
                }
                //他の場合
                else{
                    printf("ERROR\n");
                    break;
                }
            }
                
            case 'o':
            {
                //コマンドはoだけの場合
                if(input[1]=='\0'){
                    search();       //各科目と合計の平均、最高点、最低点と偏差を計算し、表示する関数を呼び出す
                    break;
                }
                //o -f fileの場合
                else if ((strcmp(input[1],"-f")==0)&&(input[2]!='\0')&&(input[3]=='\0')){
                    outport();      //全ての成績データをファイルに出力する関数を呼び出す
                    break;
                }
                //o -uの場合
                else if (strcmp(input[1],"-u")==0&&input[2]=='\0'){
                    namesearch();      //登録されている学生の名前の一覧表示する関数を呼び出す
                    break;
                }
                //o -n nameの場合
                else if (strcmp(input[1],"-n")==0&&input[2]!='\0'&&input[3]=='\0'){
                    studentsearch();       //引数で与えた学生の成績のみを表示する関数を呼び出す
                    break;
                }
                //o -eの場合
                else if (strcmp(input[1],"-e")==0&&input[2]=='\0'){
                    englishsearch();        //英語の点数の高い方から順に、学生を並べる関数を呼び出す
                    englishprint();         //学生名と英語の点数を表示する関数を呼び出す
                    break;
                }
                //o -lの場合
                else if (strcmp(input[1],"-l")==0&&input[2]=='\0'){
                    japanesesearch();       //国語の点数の高い方から順に、学生を並べる関数を呼び出す
                    japaneseprint();        //学生名と国語の点数を表示する関数を呼び出す
                    break;
                }
                //o -mの場合
                else if (strcmp(input[1],"-m")==0&&input[2]=='\0'){
                    mathsearch();           //数学の点数の高い方から順に、学生を並べる関数を呼び出す
                    mathprint();            //学生名と数学の点数を表示する関数を呼び出す
                    break;
                }
                //o -f file -u 及び o -u -f fileの場合
                else if ((strcmp(input[1],"-f")==0&&strcmp(input[3],"-u")==0)||(strcmp(input[2],"-f")==0&&strcmp(input[1],"-u")==0)){
                    nameoutport();          //登録されている学生の名前をファイル出力する関数を呼び出す
                    break;
                }
                //o -f file -n name 及び o -n name -f fileの場合
                else if ((strcmp(input[1],"-f")==0&strcmp(input[3],"-n")==0)||(strcmp(input[3],"-f")==0&strcmp(input[1],"-n")==0)){
                    studentoutport();       //引数で与えた学生の成績のみをファイル出力する関数を呼び出す
                    break;
                }
                //o -f file -e 及び o -e -f fileの場合
                else if ((strcmp(input[1],"-f")==0&strcmp(input[3],"-e")==0)||(strcmp(input[2],"-f")==0&strcmp(input[1],"-e")==0)){
                    englishoutport();   //英語の点数が高い方から順に、学生名とその点数をファイル出力する関数を呼び出す
                    break;
                }
                //o -f file -l 及び o -l -f fileの場合
                else if ((strcmp(input[1],"-f")==0&strcmp(input[3],"-l")==0)||(strcmp(input[2],"-f")==0&strcmp(input[1],"-l")==0)){
                    japaneseputport();  //国語の点数が高い方から順に、学生名とその点数をファイル出力する関数を呼び出す
                    break;
                }
                //o -f file -m 及び　o -m -f fileの場合
                else if ((strcmp(input[1],"-f")==0&strcmp(input[3],"-m")==0)||(strcmp(input[2],"-f")==0&strcmp(input[1],"-m")==0)){
                    mathoutport();      //数学の点数が高い方から順に、学生名とその点数をファイル出力する関数を呼び出す
                    break;
                }
                //他の場合
                else {
                    printf("ERROR\n");
                    break;
                }
            }
            //ヘルプ
            case 'h':
            {
                printf("i:対話的に入力\ni name English Japanese Math:省力入力\no:集計結果\no -f file:ファイル出力\ni -f file:ファイル入力\no -u:学生の名前の一覧\no -u name:引数で与えた学生の成績\no -e:英語の点数が高い方から順に学生名とその点数を表示\no -l:国語の点数が高い方から順に、学生名とその点数を表示\no -m:数学の点数が高い方から順に、学生名とその点数を表示\no -f file -u/o -u -f file:登録されている学生の名前の出力\no -f file -n name/o -n name -f file:指定した学生の成績のみをファイル出力\no -f file -e/o -e -f file:英語の成績リストのみをファイル出力\no -f file -l/o -l -f file:国語の成績リストのみをファイル出力\no -f file -m/o -m -f file:数学の成績リストのみをファイル出力\n");
                break;
            }
            //終了
            case 'q':
            {
                return 0;
            }
            //エラーの場合
            default:{
                printf("ERROR\n");
            }
        }
        memset(input, 0, sizeof input);  //毎回のコマンドを実行した後、入力の文字列を保存するinput配列をクリア
    }
    return 0;
}


