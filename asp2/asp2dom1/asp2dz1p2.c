#include <stdio.h>
#include <stdlib.h>

typedef struct cvor{
    int info;
    int balans;
    struct cvor* left;
    struct cvor* right;
}cvor;

void desnarotacija(cvor* x) {
    cvor *y, *pom;
    y=x->left;
    pom=y->right;
    y->right=x;
    x->left=pom;
}
void levarotacija(cvor* x) {
    cvor *y, *pom;
    y = x->right;
    pom = y->left;
    y->left = x;
    x->right = pom;
}

typedef struct Stack {
    int front;
    cvor* arr;
} Stack;

Stack* init_stack() {
    Stack* stk = malloc(sizeof(Stack));
    stk->front = 0;
    stk->arr = malloc(100 * sizeof(cvor));
    return stk;
}

void push(Stack* stk, cvor* e) {
    if (stk->front<100) {
        stk->arr[stk->front] = *e;
        stk->front++;
    }
}

cvor* pop(Stack* stk) {
    if (stk->front > 0) {
        stk->front--;
        return &(stk->arr[stk->front]);
    }
    else {
        return NULL;
    }
}

typedef struct CvorOK{
    cvor* data;
    struct CvorOK* next;
} CvorOK;

typedef struct Red {
    CvorOK* front;
    CvorOK* rear;
} red;

red* napravired() {
    red* q=malloc(sizeof(red));
    if(!q){
        return NULL;
    }
    q->front=q->rear=NULL;
    return q;
}

int dalijeprazan(red* q) {
    return (q==NULL || q->front==NULL);
}

void dodajured(red* red, cvor* data) {
    CvorOK * noviOK=malloc(sizeof(CvorOK));
    if (!noviOK) {
        return;
    }
    noviOK->data = data;
    noviOK->next = NULL;

    if (dalijeprazan(red)) {
        red->front=red->rear=noviOK;
    }
    else {
        red->rear->next=noviOK;
        red->rear =noviOK;
    }
}

cvor* izbaciizreda(red* red) {
    if (dalijeprazan(red)) {
        return NULL;
    }
    CvorOK * temp=red->front;
    cvor* data=temp->data;
    red->front=red->front->next;

    if (red->front==NULL) {
        red->rear=NULL;
    }
    free(temp);
    return data;
}

int max(int a, int b){
    if (a>b) return a;
    else return b;
}

void AVLinsert(cvor **root, int k) {
    cvor *p,*q,*fp,*fx,*x,*y;
    int imbal;
    fp=fx=NULL;
    p=*root;
    x=p;
    while(p!=NULL){
        if (k==p->info) {
            return;
        }
        if (k<p->info) {
            q=p->left;
        }
        else {
            q=p->right;
        }
        if (q!=NULL) {
            if (q->balans!=0) {
                fx=p;
                x=q;
            }
        }
        fp=p;
        p=q;
    }
    q=malloc(sizeof(cvor));
    q->info=k;
    q->left=NULL;
    q->right=NULL;
    q->balans=0;
    if (*root==NULL) {
        *root=q;
        return;
    }
    if (k<fp->info) {
        fp->left=q;
    }
    else {
        fp->right=q;
    }
    if (k<x->info) {
        p=x->left;
    }
    else {
        p=x->right;
    }
    y=p;
    while (p!=q) {
        if (k<p->info) {
            p->balans=1;
            p=p->left;
        }
        else {
            p->balans=-1;
            p=p->right;
        }
    }
    if (k<x->info) {
        imbal=1;
    }
    else {
        imbal=-1;
    }
    if (x->balans==0) {
        x->balans=imbal;
        return;
    }
    if (x->balans!=imbal) {
        x->balans=0;
        return;
    }
    if (y->balans==imbal) {
        p=y;
        if (imbal==1) {
            desnarotacija(x);
        }
        else {
            levarotacija(x);
        }
        x->balans=0;
        y->balans=0;
    } else {
        if (imbal==1) {
            p=y->right;
            levarotacija(y);
            x->left=p;
            desnarotacija(x);
        }
        else {
            p=y->left;
            x->right=p;
            desnarotacija(y);
            levarotacija(x);
        }
        if (p->balans==0) {
            x->balans=0;
            y->balans=0;
        }
        else {
            if (p->balans==imbal) {
                x->balans=-imbal;
                y->balans=0;
            }
            else {
                x->balans=0;
                y->balans=imbal;
            }
            p->balans=0;
        }
    }
    if (fx==NULL) {
        *root=p;
    }
    else {
        if (x==fx->right) {
            fx->right=p;
        }
        else {
            fx->left=p;
        }
    }
}

int BSTsearch(cvor* root, int key){
    cvor* p;
    int indikator=0;
    p=root;
    while(p!=NULL && key!=p->info){
        if(key<p->info){
            p=p->left;
        }
        else{
            p=p->right;
        }
    }
    if(p!=NULL && p->info==key){
        indikator=1;
    }
    return indikator;
}

int subtreeHeight(cvor *node) {
    if(!node) return -1;
    return 1+max(subtreeHeight(node->left),subtreeHeight(node->right));
}

int treeHeight(cvor *root) {
    if(!root) return -1;
    return subtreeHeight(root);
}

void print(cvor *root){
    if(!root) return;
    else{
        red *q=napravired();
        int i,lineLen=62;
        int firstSkip=lineLen,inBetweenSkip;
        int treeH;
        treeH=treeHeight(root);
        if (!dalijeprazan(q)) return;
        dodajured(q,root);
        for(i=0;i<=treeH;i++){
            int j=1<<i,k,l;
            inBetweenSkip=firstSkip;
            firstSkip=(firstSkip-2)/2;
            for(k=0;k<firstSkip;k++){
                putchar(' ');
            }
            for(k=0;k<j;k++){
                cvor* pom= izbaciizreda(q);
                if(pom){
                    dodajured(q,pom->left);
                    dodajured(q,pom->right);
                }
                else{
                    dodajured(q,0);
                    dodajured(q,0);
                }
                if(pom) printf("%2d",pom->info);
                else printf("  ");
                for (l=0;l<inBetweenSkip;l++) putchar(' ');
            }
            putchar('\n');
            putchar('\n');
        }
    }
}

void delete(cvor *root) {
    cvor *pom = root,*del=NULL;
    Stack *stack = init_stack();
    while (1) {
        while (pom != NULL) {
            push(stack, pom);
            pom = pom->left;
        }
        if (stack->front != 0) {
            pom = pop(stack);
            del = pom;
            pom = pom->right;
            //free(del);
        } else {
            return;
        }
    }
}

cvor* presek(cvor* rootA, cvor *rootB,int a, int b) {
    cvor* vCvor,*mCvor,*presek=NULL;
    if(a>=b){
        vCvor=rootA;
        mCvor=rootB;
    }
    else{
        vCvor=rootB;
        mCvor=rootA;
    }
    cvor* pom=mCvor;
    Stack *stack=init_stack();
    while(1){
        while (pom){
            push(stack,pom);
            pom=pom->left;
        }
        if(stack->front!=NULL){
            pom=pop(stack);
            int indikator=BSTsearch(vCvor,pom->info);
            if (indikator==1) {
                AVLinsert(&presek,pom->info);
            }
            pom=pom->right;
        }
        else{
            return presek;
        }
    }
}

int main(){
    cvor *koren;
    int opcija;
    int kljuc;
    int broj;
    int vrednost;
    while(1){
        printf("Meni\n1.Formiranje praznog skupa\n2.Umetanje novog elementa u skup\n3.Provera pripadnosti elementa skupu\n"
               "4.Ispis skupa\n5.Brisanje skupa iz memorije\n6.Presek dva skupa\n7.Napusti program\n");
        scanf("%d", &opcija);
        if(opcija>7){
            printf("Izabrali ste nepostojecu opciju!");
        }
        if(opcija==7){
            exit(0);
        }
        if(opcija==1){
            koren=NULL;
        }
        if(opcija==2){
            printf("Unesite broj cvorova koje zelite da umetnete:\n");
            scanf("%d", &broj);
            printf("Unesite vrednosti cvorova koje zelite da umetnete:\n");
            for(int i=0; i<broj; i++){
                printf("Cvor %d:", i+1);
                scanf("%d", &vrednost);
                AVLinsert(&koren, vrednost);
            }
        }
        if(opcija==3){
            printf("Unesite cvor za koji zelite da proverite pripadnost:\n");
            scanf("%d", &kljuc);
            int indikator=BSTsearch(koren,kljuc);
            if(indikator==1){
                printf("Nadjen!\n");
            }
            else{
                printf("Nije nadjen!\n");
            }
        }
        if(opcija==4){
            putchar('\n');
            print(koren);
            putchar('\n');
        }
        if(opcija==5){
            delete(koren);
            printf("Obrisano!\n");
        }
        if(opcija==6){
            cvor *a=NULL,*b=NULL,*rez;
            int aa,bb;
            printf("Unesite broj cvorova skupa A:\n");
            scanf("%d", &aa);
            printf("Unesite vrednosti cvorova koje zelite da umetnete:\n");
            for(int i=0; i<aa; i++){
                printf("Cvor %d:", i+1);
                scanf("%d", &vrednost);
                AVLinsert(&a, vrednost);
            }
            printf("Unesite broj cvorova skupa B:\n");
            scanf("%d", &bb);
            printf("Unesite vrednosti cvorova koje zelite da umetnete:\n");
            for(int i=0; i<bb; i++){
                printf("Cvor %d:", i+1);
                scanf("%d", &vrednost);
                AVLinsert(&b, vrednost);
            }
            rez=presek(a,b,aa,bb);
            printf("Presek skupova A i B je skup:");
            putchar('\n');
            print(rez);
            putchar('\n');
        }
    }
}
