#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura responsável pelos vértices
typedef struct{
    int val;        // Valor do vértice
    int *viz;       // Vetor com o indice dos vértices vizinhos
    int n;          // Quantia de vértices vizinhos
    int out;        // Se já visitado ou não
    int ant;        // Indice do vertice anterior no caminho mais curto
    int dist;       // Distancia da raiz
    int *path;
}vert;

typedef struct nodo{
    int val;
    struct nodo *prox;
}no;

typedef struct{
    no *inicio;
    no *fim;
    int size;
}fila;

fila* cria(){
    fila *f = malloc(sizeof(fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->size = 0;
    return f;
}

void insert(fila *f, int val){
    no* n;
    for (n=f->inicio;n!=NULL;n=n->prox)
        if(n->val==val)
            return;
    n = malloc(sizeof(no));
    n->val = val;
    n->prox = NULL;
    if (f->size)
        f->fim->prox = n;
    else{
        f->inicio = n;
        f->fim = n;
    }
    f->size++;
}

no* pop(fila *f){
    no *n;
    n = f->inicio;
    if (f->size){
        f->inicio = f->inicio->prox;
        f->size--;
    }
    return n;
}

int vazia(fila *f){
    return !(f->size);
}

void le(int *b){ //CAPIROTAGEM!!!
    *b = 0;
    char c = getchar_unlocked(); 
    while(c<'0' || c> '9')
        c = getchar_unlocked();
    while(c>='0' && c <='9')
        *b = (*b<<3)+(*b<<1)+c-'0', c =getchar_unlocked();
}

int distancia(vert V[], int x, int y){
    int i;
    vert u = V[x], v = V[y];
    for(i=0; i<u.dist && i<v.dist && u.path[i]==v.path[i]; i++);
        //printf("i %d u %d v %d igual %d\n",i,u.path[i],v.path[i],u.path[i]==v.path[i]);
    if((v.dist >= u.dist && V[v.path[i]].val!=u.val) || (v.dist < u.dist && V[u.path[i]].val!=v.val))
        i--;
    //printf("%d + %d - %d\n",u.dist,v.dist, 2*i);
    return u.dist + v.dist - 2*i;
}

void djikstra(vert v[]){
    fila *f = cria();
    no *n;
    vert u;
    int i,j;
    insert(f,0);
    while(!vazia(f)){
        //printf("Djikstra: Novo Laço\n");
        n = pop(f);
        u = v[n->val];
        //printf("Djikstra: Analisando v[%d], carta %d vizinhos %d\n",n->val,u.val+1,u.n);
        for(i=0;i<u.n;i++){
            j = u.viz[i];
            if (!(v[j].out)){
                //printf("Djikstra: Analisando vizinho %d\n",i);
                //printf("Djikstra: Distancia atual: %d nova: %d\n",u.dist+1, v[j].dist);
                if (u.dist + 1 < v[j].dist){
                    v[j].dist = u.dist+1;
                    v[j].ant = n->val;
                    if(v[j].path!=NULL) free(v[j].path);
                    v[j].path = malloc(sizeof(int)*v[j].dist);
                    if(u.path!=NULL) memcpy(v[j].path, u.path, sizeof(int)*u.dist);
                    v[j].path[u.dist] = n->val;
                    insert(f,j);
                }
            }
        }
        v[n->val].out = 1;
        free(n);
    }
    free(f);
}

int main(){
    int n,a,b,i,cont=0;
    le(&n);
    vert v[n];
    int mat[n/2][2];
    for (i=0;i<n/2;i++){
        mat[i][0] = -1;
        mat[i][1] = -1;
    }
    for (i=0;i<n;i++){
        le(&v[i].val);
        v[i].val--;
        v[i].out = 0;
        v[i].viz = NULL;
        v[i].n = 0;
        v[i].ant = -1;
        v[i].dist = 60000;
        v[i].path = NULL;
        //v[i].viz = malloc(n*sizeof(int));
        if (mat[v[i].val][0]==-1)
            mat[v[i].val][0] = i;
        else
            mat[v[i].val][1] = i;
    }
    v[0].dist = 0;
    /*for (i=0;i<n/2;i++){
        printf("%d %d\n",mat[i][0]+1,mat[i][1]+1);
    }*/
    for (i=0;i<n-1;i++){
        //scanf("%d %d",&a,&b);
        le(&a);
        le(&b);
        a--;
        b--;
        v[a].n++;
        v[b].n++;
        v[a].viz = realloc(v[a].viz,v[a].n*sizeof(int));
        v[b].viz = realloc(v[b].viz,v[b].n*sizeof(int));
        v[a].viz[v[a].n-1] = b;
        v[b].viz[v[b].n-1] = a;
    }
    djikstra(v);
    int j;
    //for(i=0;i<n;i++){
    //    printf("%d carta %d ant %d dist %d\n",i+1,v[i].val+1,v[i].ant+1,v[i].dist);
        //for(j=0;j<v[i].dist;j++)
        //    printf("%d ",v[i].path[j]+1);
        //printf("\n");
    //}
    //printf("\n");
    a = v[mat[v[0].val][1]].dist;
    //printf("%d\n",a);
    for(i=(v[0].val)?0:1; i<n/2;i += 2-(i+1!=v[0].val)){
        a += distancia(v,mat[i][0],mat[i][1]);
        //printf("%d\n",a);
    }
    printf("%d\n",a);
    for(i=0;i<n/2;i++){
        free(v[i].viz);
        if(i)   free(v[i].path);
    }
    return 0;
}

