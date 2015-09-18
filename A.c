#include <stdio.h>
#include <stdlib.h>

/* --------------- Estruturas e Funções responsáveis pela Fila ---------------- */
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
/* ---------------------------------------------------------------------------- */

// Estrutura responsável pelos vértices
typedef struct{
    int *viz;       // Vetor com o indice dos vértices vizinhos
	int *peso;		// Vetor com o peso das arestas
	int step;		// Distancia em vértices da raiz
    int n;          // Quantia de vértices vizinhos
    int out;        // Se já visitado ou não
    int dist;       // Distancia da raiz
}vert;

void le(int *b){ //CAPIROTAGEM!!!
    *b = 0;
    char c = getchar_unlocked(); 
    while(c<'0' || c> '9')
        c = getchar_unlocked();
    while(c>='0' && c <='9')
        *b = (*b<<3)+(*b<<1)+c-'0', c =getchar_unlocked();
}

void djikstra(vert v[],int dst){
    fila *f = cria();	// Crio uma fila
    no *n;				// Crio um ponteiro para item da fila
    vert u;				// Crio um vertice para armazenar o vertice lido
    int i,j;
    insert(f,0);		// Insiro o indice 0 (primeiro vertice) na fila
    while(!vazia(f)){	// Enquanto a fila não estiver vazia
        n = pop(f);		// Retiro o primeiro indice de vertice da fila
        u = v[n->val];	// Pego o vertice no vetor usando o indice
		if(!u.out){		// Se ainda não foi visitado
			for(i=0;i<u.n;i++){		// Percorre os vizinhos
				j = u.viz[i];		// Pega o vertice vizinho no vetor usando o indice j
				if (!(v[j].out))	// Se o vértice vizinho ainda não foi visitado
					if (u.dist + u.peso[i] < v[j].dist && (j<dst || u.step%2)){
						//	Se a distancia ate esse vertice for menor E
						//	o vertice não for o destino OU se for, chegar em uma passada par
						v[j].dist = u.dist+u.peso[i];
						v[j].step = u.step+1;
						insert(f,j);	// Insiro o vertice vizinho na fila para posterior checagem
					}
			}				// Fim for
		}					// Fim if
        v[n->val].out = 1;	// Marco como visitado
        free(n);			// Libero memória do elemento que removi da fila 
    }			// Fim while
    free(f);	// Libero a fila
}

int main(){
    int n,m,a,b,c,i,cont=0;
    // Leio quantia de vertices e de arestas
	le(&n);
	le(&m);
	// Inicializo os vértices
    vert v[n];
    for (i=0;i<n;i++){
        v[i].out = 0;
        v[i].viz = NULL;
		v[i].peso = NULL;
        v[i].n = 0;
		v[i].step = -1;
        v[i].dist = 60000;
    }
    v[0].dist = 0;
	v[0].step = 0;
	// Leio e processo as descrições das arestas
    for (i=0;i<m;i++){
        le(&a);
        le(&b);
        le(&c);
        a--;
        b--;
        v[a].n++;
        v[b].n++;
        v[a].viz = realloc(v[a].viz,v[a].n*sizeof(int));
		v[a].peso = realloc(v[a].peso,v[a].n*sizeof(int));
        v[b].viz = realloc(v[b].viz,v[b].n*sizeof(int));
		v[b].peso = realloc(v[b].peso,v[b].n*sizeof(int));
        v[a].viz[v[a].n-1] = b;
        v[b].viz[v[b].n-1] = a;
		v[a].peso[v[a].n-1] = c;
		v[b].peso[v[b].n-1] = c;
    }
	// Aplico djikstra
    djikstra(v,n-1);
	// Imprimo resultado
	printf("%d\n",(v[n-1].step>0)?v[n-1].dist:-1);
    // Libero memória alocada
	for(i=0;i<n/2;i++)
        free(v[i].viz), free(v[i].peso);
    return 0;
}

