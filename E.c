#include <stdio.h>

int main() {
  long int b;
  long int n,i,p;
  scanf("%ld %ld",&n,&b);

  p = b/(n*2);
  i = p*2+1;
  //printf("b %ld - %ld\n",b,4*(p*n + (n/2 + n%2)*(n/2 + n%2) - (n-p)*(n-p)));
  b -= 4*(p*n + (n/2 + n%2)*(n/2 + n%2) - (n-p)*(n-p));
  //for(i=1,p=0;b>0;i+=2,p++)
  //  b -= (n-i)<<2;
  i -= (p>0)?2:0;
  long int pos[] = {p,p-1};
  printf("%ld %d b %ld tam %ld p %ld i %ld\n",pos[0],pos[1],b,n-i,p,i);

  b += (n - i - 1);
  pos[0] += n - i - 1;
  printf("%ld %d b %ld tam %ld p %ld i %ld\n",pos[0],pos[1],b,n-i,p,i);
  if (b>0){
    pos[0] -= b;
  }
  else{
    b += (n - i);
    pos[1] += n - i;
    printf("%ld %d b %ld tam %ld p %ld i %ld\n",pos[0],pos[1],b,n-i,p,i);
    if (b>0){
      pos[1] -= b;
    }
    else{
      b += (n - i);
      pos[0] -= n - i;
      printf("%ld %d b %ld tam %ld p %ld i %ld\n",pos[0],pos[1],b,n-i,p,i);
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
