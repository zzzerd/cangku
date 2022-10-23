#include<stdio.h>
#include<string.h>
#define maxNum 256
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define MAX(x, y) (x)>(y) ? (x):(y)
#define MAXCH 256
void PreBmBc(char *pattern,int m,int bmBc[])
{
    int i;
    for(i=0;i<256;i++){//一个字符占八位，共256个字符，把所有字符都覆盖到，这里的初始化是将所有字符失配时的移动距离都赋值为m
        bmBc[i]=m;
    }
    for(i=0;i<m-1;i++){//针对模式串pattern中存在的每一个字符，计算出它们最靠右的（非最后一个字符）地方距离串末尾的距离，即它们失配时该移动的距离,这一操作更新了初始化中一些字符的移动距离
        bmBc[pattern[i]]=m-1-i;
    }
}
void suffix(char *pattern,int m,int suff[])
{
    int i,j;
    suff[m-1]=m;
    for(i=m-2;i>=0;i--){
        j = i;
        while(j>=0&&pattern[j]==pattern[m-1-i+j]) j--; 
        suff[i]=i-j;
    }
}
void PreBmGs(char *pattern,int m,int bmGs[])
{
    int i, j;
    int suff[maxNum];  
    // 计算后缀数组
    suffix(pattern,m,suff);
    // 先全部赋值为m，包含Case3
    for(i=0;i<m;i++){
        bmGs[i]=m;
    }
    // Case2
    j=0;
    for(i=m-1;i>=0;i--){
        if(suff[i]==i+1){
            for(;j<m-1-i;j++){
                if(bmGs[j]==m)
                    bmGs[j]=m-1-i;
            }
        }
    }
    // Case1
    for(i=0;i<=m-2;i++){
        bmGs[m-1-suff[i]]=m-1-i;
    }
}
char* BoyerMoore(char *text,int n,char *pattern,int m,int bmBc[],int bmGs[])
{
    int i,pos;
    
    pos=0;
    while(pos<=n-m){
        for(i=m-1;i>=0&&pattern[i]==text[i+pos];i--);
        if(i < 0){
            printf("match:%d\n",pos);
            pos+=m;
            if(pos>n-m)
            break;
            printf("yidongdao:%d\n",pos);
        }
        else{
            pos+=MAX(bmBc[text[i+pos]]-m+1+i,bmGs[i]);
             printf("yidongdao:%d\n",pos);
        }
    }
    return NULL;
}
int main(){
 char* pattern="abcda";
 char* TXT="aabcabcdaabbdddabcda";
 printf("pattern is %s\n", pattern);
 printf("TXT is %s\n", TXT);
int lenp,len_txt;
lenp=strlen(pattern);
len_txt=strlen(TXT);
int bmBc[MAXCH];//BM坏字符数组
int bmGs[lenp];//BM好后缀数组
PreBmBc(pattern,lenp,bmBc);
PreBmGs(pattern,lenp,bmGs);
BoyerMoore(TXT,len_txt,pattern,lenp,bmBc,bmGs);
return 0;
}
