#include <stdio.h>
#include <string.h>

int main(){
	int n,k,i,h,aux2;
	scanf("%d %d",&n,&k);
	int j[n][k];
	int par[2][k],impar[k];
	memset(par[0],0,k*sizeof(int));
	memset(par[1],0,k*sizeof(int));
	for(i=0;i<n;i++){
		aux2=0;
		memset(impar,0,k*sizeof(int));
		for(h=0;h<k;h++){
			scanf("%d",&j[i][h]);
			if(j[i][h]%2){
				if (!par[0][h]){
					par[0][h] = 1;
					impar[h] = 1;
				}
				aux2++;
			}
			else
				par[1][h] = 1;
		}
		if (aux2==k){
			//printf("coco gold %d\n",i);
			for(h=0;h<k;h++)
				if(impar[h])
					par[0][h] = 0;
		}
	}
	if(n>k){
		for(i=0;i<k;i++){
			if(par[0][i]+par[1][i]<2){
				printf ("S\n");
				return 0;
			}
		}
		printf ("N\n");
		return 0;
	}
	printf("S\n");
	return 0;
}