#include <stdio.h>
#include <stdlib.h>

int binomnikoef(int n, int k){
    if (k<0 || k>n){
        return 0;
    }
    int rez=1;
    if (k==0||k==n){
        return 1;
    }
    if (k>n-k){
        k=n-k;
    }
    for (int i=0; i<k; i++){
        rez*=(n-i);
        rez/=(i+1);
    }
    return rez;
}
int ternarna_pretraga(int K[], int key, int n){
    int cnt=0;
    int low=0;
    int high=(n-1)/2;
    while(low<=high){
        cnt+=1;
        int mid1=low+(high-low)/3;
        int mid2=high-(high-low)/3;
        printf("low1: %d\n", low);
        printf("high1: %d\n", high);
        printf("mid1: %d\n", mid1);
        printf("mid2: %d\n", mid2);
        printf("Trenutni niz:\n");
        for (int m=low; m<=high; m++){
            printf("%d ", K[m]);
        }
        printf("\n");
        if(key==K[mid1] || key==K[mid2]){
            printf("Nadjen!\n");
            return cnt;
        }
        if(key<K[mid1]){
            high=mid1-1;
            continue;
        }
        else if(key>K[mid2]){
            low=mid2+1;
            continue;
        }
        else{
            low=mid1+1;
            high=mid2-1;
            continue;
        }
    }
    printf("Nije nadjen!\n");
    return cnt;
}

int interpolaciono_pretrazivanje(int K[],int key, int n){
    int low=0;
    int high=(n-1)/2;
    int cnt=0;
    while (low<=high){
        cnt+=1;
        int poz=low+(high-low)*(key-K[low])/(K[high]-K[low]);
        printf("low2: %d\n", low);
        printf("high2: %d\n", high);
        printf("poz: %d\n", poz);
        printf("Trenutni niz:\n");
        for (int m=low; m<=high; m++){
            printf("%d ", K[m]);
        }
        printf("\n");
        if(poz<low || poz>high){
            break;
        }
        if (K[poz]==key) {
            printf("Nadjen!\n");
            return cnt;
        }
        if (K[poz]>key) {
            high=poz-1;
        }
        else {
            low=poz+1;
        }
    }
    printf("Nije nadjen!\n");
    return cnt;
}

int main() {
    int opcija;
    int n,br;
    int mat[100][100];
    int red, keys[100], cnt1, cnt2;
    double avg1,avg2;
    while (1) {
        int sum1, sum2;
        printf("Meni:\n 1.Kreiraj Lozanicev trougao\n 2.Pretrazi trougao\n 3.Uporedi performanse\n 4.Napusti program\n");
        scanf("%d", &opcija);
        switch(opcija) {
            case 1:
                printf("Unesite red trougla:");
                scanf("%d", &n);
                for (int i = 0; i < n + 1; i++) {
                    for (int j = 0; j < n + 1; j++) {
                        if (i >= j) {
                            int p = i % 2;
                            int q = j % 2;
                            mat[i][j] = 0.5 * (binomnikoef(i, j) + (binomnikoef(p, q)) * (binomnikoef(i / 2, j / 2)));
                        } else {
                            mat[i][j] = 0;
                        }
                    }
                }
                for (int i = 0; i < n + 1; i++) {
                    for (int j = 0; j < n + 1; j++) {
                        if (mat[i][j] != 0) {
                            printf("%d ", mat[i][j]);
                        }
                    }
                    printf("\n");
                }
                break;

            case 2:
                sum1 = 0;
                sum2 = 0;
                printf("Unesite redni broj reda u kom zelite da izvrsite pretragu (brojanje krece od 0):\n");
                scanf("%d", &red);
                printf("Unesite broj kljuceva za koje zelite da izvrsite pretragu:\n");
                scanf("%d", &br);
                printf("Unesite sekvencu kljuceva za koju zelite da izvrsite pretragu:\n");
                for (int k = 0; k < br; k++) {
                    printf("%d. kljuc:\n", k + 1);
                    scanf("%d", &keys[k]);
                }
                for (int k = 0; k < br; k++) {
                    printf("\nTernarna pretraga za kljuc %d:\n", keys[k]);
                    cnt1 = ternarna_pretraga(mat[red], keys[k], red + 1);
                    printf("Broj koraka: %d\n", cnt1);
                    printf("\nInterpolaciono pretrazivanje za kljuc %d:\n", keys[k]);
                    cnt2 = interpolaciono_pretrazivanje(mat[red], keys[k], red + 1);
                    printf("Broj koraka: %d\n", cnt2);
                    sum1 += cnt1;
                    sum2 += cnt2;
                }
                break;

            case 3:
                avg1 = (double) sum1 / br;
                avg2 = (double) sum2 / br;
                printf("Performanse ternarne pretrage: %.2f\n", avg1);
                printf("Performanse interpolacionog pretrazivanja: %.2f\n", avg2);
                break;

            case 4:
                exit(0);
        }
    }
    return 0;
}