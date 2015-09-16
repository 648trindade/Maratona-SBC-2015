#include <stdio.h>

int main() {
  long int b, esq = 1, dir, pto,ant;
  long int n,i,p;
  scanf("%ld %ld",&n,&b);
  dir = n/2;
  
  //metodo da bissecao. Encontra a volta da espiral em que parou em log2 (n/2) iterações
  while (1){
    p = (dir+esq)/2;
    pto = 4*(p*n - p*p);
    ant = pto - 4*(n - (p-1)*2 - 1);
    if (b>pto)
      esq = p;
    else if (b<pto && b<ant)
      dir = p;
    else if (b<=pto && b>ant){
      i = p*2 + 1;
      break;
    }
  }
  b -= pto;
  i -= (p>0)?2:0;
  long int pos[] = {p,p-1};
  
  b += (n - i - 1);
  pos[0] += n - i - 1;
  if (b>0){
    pos[0] -= b;
  }
  else{
    b += (n - i);
    pos[1] += n - i;
    if (b>0){
      pos[1] -= b;
    }
    else{
      b += (n - i);
      pos[0] -= n - i;
      if (b>0){
        pos[0] += b;
      }
      else{
        pos[1] += b;
      }
    }
  }
  printf("%ld %ld\n",pos[0]+1,pos[1]+1);
  return 0;
}
