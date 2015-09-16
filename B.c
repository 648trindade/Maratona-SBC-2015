#include <stdio.h>

int main(int argc, char const *argv[]) {
  int i,j,n,c;
  scanf("%d %d",&n,&c);
  int p[n];
  for (i=0;i<n;i++)
    scanf("%d",&p[i]);
  int luc = 0, com = 1001+c, pven = 0;
  for (i=0;i<n;i++) {
    if (p[i]-com>0 && p[i]>pven){
      // escolhe uma venda melhor
      pven = p[i];
    }
    else if (p[i]+c <= com || pven-p[i]>c) {
      // escolhe uma compra melhor ou finaliza uma venda se perceber que da pra lucrar comprando o valor atual
      if (pven>0){
        luc += pven-com;
        pven = 0;
      }
      com = p[i]+c;
    }
  }
  if (pven>0)
    luc += pven-com;
  printf("%d\n",luc);
  return 0;
}
