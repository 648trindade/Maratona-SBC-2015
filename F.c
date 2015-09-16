#include<stdio.h>

int main(){
    int v[] = {1,2,6,24,120,720,5040,40320};
    int n, cont=0;
    scanf("%d",&n);
    int i = 7;
    while (n>0){
        if (v[i]>n){
            i--;
            continue;
        }
        cont++;
        n-=v[i];
    }
    printf("%d\n",cont);
    return 0;
}
