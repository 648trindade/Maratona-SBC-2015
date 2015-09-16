#include <stdio.h>

int n;

void quick(int v[][2], int low, int high, int m){
    int i=low, j=high, swap;
    int k,x = v[(high+low)>>1][m];
    while(i<j){
        while(v[i][m]<x && i<high)
            i++;
        while(v[j][m]>x && j>low)
            j--;
        if (i<=j){
            swap = v[i][m];
            v[i][m] = v[j][m];
            v[j][m] = swap;
            swap = v[i][1-m];
            v[i][1-m] = v[j][1-m];
            v[j][1-m] = swap;
            i++;
            j--;
        }
    }
    if (j > low)
        quick(v, low, j, m);
    if (i < high)
        quick(v, i, high, m);
}

void ordena(int v[][2]){
	quick(v,0,n-1,0);
	int i;
	/*for(i=0;i<n;i++){
    	printf("(%d,%d)\n",v[i][0],v[i][1]);	
    }*/
    //printf("\n");
	
	int k = v[0][0];
	int pos = 0;
	for(i=1;i<n;i++){
		if (v[i][0]!=k){
			if (i-pos>1){
				//printf("vou ordenar\n");
				quick(v,pos,i-1,1);
			}
			pos = i;
			k = v[i][0];
		}
	}
}

void le(int *b){ //CAPIROTAGEM!!!
    *b = 0;
    int d =1;
    char c = getchar_unlocked(); 
    while((c<'0' || c> '9') && c!='-')
        c = getchar_unlocked();
    if (c=='-')
    	d = -1, c=getchar_unlocked();
    while(c>='0' && c <='9')
        *b = (*b<<3)+(*b<<1)+c-'0', c =getchar_unlocked();
    *b *= d;
}

int poste_dentro(int v[][2], int i, int j){
	int k, vi=v[i][1], vj=v[j][1], vk;
	for(k=i+1;k<j;k++){
		vk = v[k][1];
		if (v[k][0]>v[i][0] && vk>(vi<vj?vi:vj) && vk<(vi>vj?vi:vj)){
			return 1;
		}
	}
	return 0;
}


int main(){
	int i,j;
    //scanf("%d",&n);
    le(&n);
    int v[n][2], cont=0;
    for (i=0;i<n;i++){
    	//scanf("%d %d",&v[i][0],&v[i][1]);
    	le(&v[i][0]);
    	le(&v[i][1]);
    }
    ordena(v);
    /*for(i=0;i<n;i++){
    	printf("(%d,%d)\n",v[i][0],v[i][1]);
    	
    }*/
   	for(i=0;i<n-1;i++){
   		for(j=i+1;j<n;j++)
   			if (v[i][0]!=v[j][0] && v[i][1]!=v[j][1])
   				if (j==i+1)
   					cont++;
   				else if (!poste_dentro(v,i,j))
   					cont++;
   	}
   	printf("%d\n",cont);
    return 0;
}
