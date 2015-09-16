#include <stdio.h>

int main(){
    int j,r,i,k,sa,sb,sc;
    scanf("%d %d",&j,&r);
    int v[j];
    for(i=0;i<j;i++)
        v[i] = 0;
    for(i=0;i<r;i++)
        for(k=0;k<j;k++){
            scanf("%d",&sa);
            v[k] += sa;
        }
    sb=0, sc=0;
    for(i=0;i<j;i++)
        if(v[i]>=sb){
            sb = v[i];
            sc = i+1;
        }
    printf("%d\n",sc);
    return 0;
}
