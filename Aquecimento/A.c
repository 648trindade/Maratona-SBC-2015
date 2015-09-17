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
    n = malloc(sizeof(no));
    n->val = val;
    n->prox = NULL;
    if (f->size)
        f->fim->prox = n;
    else
        f->inicio = n;
    f->fim = n;
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
    int i=0, k, j;
    k = x; j = y;
    if (V[x].dist > V[y].dist)
        for (i=0;i < V[x].dist-V[y].dist; i++)
            k = V[k].ant;
    else if (V[y].dist > V[x].dist)
        for (i=0;i < V[y].dist-V[x].dist; i++)
            j = V[j].ant;
    if (k==y || j==x)
        return i;
    while(k!=-1){
        if (k==j)
            return i;
        k = V[k].ant;
        j = V[j].ant;
        i += 2;
    }
}

void djikstra(vert v[]){
    fila *f = cria();
    no *n;
    vert u;
    int i,j;
    insert(f,0);
    while(!vazia(f)){
        n = pop(f);
        u = v[n->val];
        for(i=0;i<u.n;i++){
            j = u.viz[i];
            if (!(v[j].out))
                if (u.dist + 1 < v[j].dist){
                    v[j].dist = u.dist+1;
                    v[j].ant = n->val;
                    insert(f,j);
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
        if (mat[v[i].val][0]==-1)
            mat[v[i].val][0] = i;
        else
            mat[v[i].val][1] = i;
    }
    v[0].dist = 0;
    for (i=0;i<n-1;i++){
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
    a = v[mat[v[0].val][1]].dist;
    for(i=(v[0].val)?0:1; i<n/2;i += 2-(i+1!=v[0].val))
        a += distancia(v,mat[i][0],mat[i][1]);
    printf("%d\n",a);
    for(i=0;i<n/2;i++)
        free(v[i].viz);
    return 0;
}

