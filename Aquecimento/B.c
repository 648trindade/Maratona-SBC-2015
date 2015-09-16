#include <stdio.h>
#include <math.h>

#define checa(a,b,c) do {abs(a-b)<c && d < a+b}while (0);

int main(){
    int i,a,b,c,d,cont=0;
    scanf ("%d %d %d %d",&a,&b,&c,&d);
    if (abs(a-b)<c && c < a+b) printf ("S\n");
    else if (abs(a-b)<d && d < a+b) printf ("S\n");
    else if (abs(a-c)<b && b < a+c) printf ("S\n");
    else if (abs(a-c)<d && d < a+c) printf ("S\n");
    else if (abs(a-d)<b && d < a+c) printf ("S\n");
    else if (abs(a-d)<c && c < a+d) printf ("S\n");
    else if (abs(b-c)<d && d < c+b) printf ("S\n");
    else if (abs(b-c)<a && a < c+b) printf ("S\n");
    else if (abs(d-b)<a && a < d+b) printf ("S\n");
    else if (abs(d-b)<c && c < d+b) printf ("S\n");
    else if (abs(c-d)<a && a < c+d) printf ("S\n");
    else if (abs(c-d)<b && b < c+d) printf ("S\n");
    else printf("N\n");
    return 0;
}
