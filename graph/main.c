#include <stdio.h>
#include <stdlib.h>

typedef struct graph{
    int nv;
    struct vertex *handle;
}graph_t;
typedef struct vertex{
    int key;
    struct vertex *next;
    struct edge *head;
}vertex_t;
typedef struct edge{
    int weight;
    struct edge *next;
    struct vertex *dst;
}edge_t;
graph_t *initGraph(int nv);
vertex_t *createVertex(int i);
vertex_t *insertVertex(vertex_t *head,vertex_t *newNode);
vertex_t *findVertex(graph_t *g,int key);
edge_t *createEdge(int w, vertex_t *dst);
void insertEdge(vertex_t *src,edge_t *tmpEdge);
int main(int argc,char *argv[])
{
    graph_t *g;
    FILE *fp;
    int nv,dir,src,dst,w;
    vertex_t *dstVertex, *srcVertex;
    edge_t *tmpEdge;
    fp=fopen(argv[1],"r");
    if(fscanf(fp,"%d %d",&nv,&dir)!=2){
        fscanf(fp,"%d",&nv);
        dir=0;
    }
    g=initGraph(nv);
    while(fscanf(fp,"%d %d %d",&src,&dst,&w)!=EOF){
        dstVertex=findVertex(g,dst);
        srcVertex=findVertex(g,src);
        tmpEdge=createEdge(w,dstVertex);
        insertEdge(srcVertex,tmpEdge);
    }
    return 0;
}
graph_t *initGraph(int nv){
    graph_t *g;
    vertex_t *tmp;
    int i;
    g=(graph_t)malloc(1*sizeof(graph_t));
    if(g==NULL){
        printf("error!");
        exit(0);
    }
    g->nv=nv;
    g->handle=NULL;
    for(i=0;i<nv;i++){
        tmp=createVertex(i);
        g->handle=insertVertex(g->handle,tmp);
    }
    return g;
}
vertex_t *createVertex(int i){
    vertex_t *tmp;
    tmp=(vertex_t *)malloc(1*sizeof(vertex_t));
    if(tmp==NULL){
        printf("error!");
        exit(0);
    }
    tmp->head=NULL;
    tmp->next=NULL;
    tmp->key=i;
    return tmp;
}
vertex_t *insertVertex(vertex_t *head,vertex_t *newNode){
    vertex_t *tmp;
    tmp=head;
    if(tmp==NULL){
        head=newNode;
        return head;
    }
    while(tmp->next!=NULL){
        tmp=tmp->next;
        tmp->next=newNode;
        return head;
    }
    return head;
}
vertex_t *findVertex(graph_t *g,int key){
    vertex_t *tmp=g->handle;
    while(tmp!=NULL){
        if(tmp->key==key){
            return tmp;
        }
        tmp=tmp->next;
    }
    return NULL;
}
edge_t *createEdge(int w, vertex_t *dst){
    edge_t *tmp;
    tmp=(edge_t *)malloc(1*malloc(edge_t));
    if(tmp==NULL){
        printf("error!");
        exit(0);
    }
    tmp->weight=w;
    tmp->dst=dst;
    tmp->next=NULL;
    return tmp;
}
void insertEdge(vertex_t *src,edge_t *tmpEdge){
    tmpEdge->next=src->head;
    src->head=tmpEdge;
    return;
}
