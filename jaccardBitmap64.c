#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hashtrie.h"
#include <smmintrin.h>

#define MAXLEN 1024
#define MB 8388608.0

inline double jaccard( uint64_t * d1, uint64_t * d2, int n )
{
    double j = 0.0;
    int set_union=0, set_inter=0;
    int i;
    
    for (i=0; i<n; i++) {
        set_union += _mm_popcnt_u64(d1[i] | d2[i]);
        set_inter += _mm_popcnt_u64(d1[i] & d2[i]);
    }
    
    if (set_union==0) return 0.0;
    return (double)set_inter/(double)set_union;
}

int main( int argc, char **argv )
{
    char buffer[MAXLEN];
    char * token;
    FILE * fp;
    Node * raiz = cria_no();
    unsigned int features, docs = 0, n_elems;
    int i, j, it;
    double jacc = 0.0;

    if (argc == 1) {
        printf("Uso: %s <nome_arquivo>\n", argv[0]);
        return -1;
    }

    /* abre arquivo e gera ids unicos para cada atributo */
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Falha ao abrir %s\n", argv[1]);
        return -1;
    }

    while ( (fgets(buffer, MAXLEN, fp)) != NULL ) {
        ++docs;
        buffer[ strlen(buffer)-1 ] = '\0';
        token = strtok(buffer, " ");
        while(token != NULL) {
            insere_no( token, raiz );
            token = strtok(NULL, " ");
        }
    }

    fclose(fp);

    /* conta numero de atributos unicos e aloca memoria */
    features = conta_arvore(raiz, 0);
      
    printf("%.2lf MB de memoria, %d unique features\n", (double)( (features - (features%64) + 64)*docs) / MB, features );
    
    n_elems = (features >> 6) + 1;

    uint64_t corpus[docs][ n_elems ];

    /* gera atributos bitmap para cada documento */
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Falha ao abrir %s\n", argv[1]);
        return -1;
    }

    i = 0;
    while ( (fgets(buffer, MAXLEN, fp)) != NULL ) {
        buffer[ strlen(buffer)-1 ] = '\0';
        token = strtok(buffer, " ");
        while(token != NULL) {
            j = busca_no(token, raiz);
            if (j>-1) {
                corpus[i][j>>6] |= j & 63;
            }
            token = strtok(NULL, " ");
        }
        ++i;
    }

    fclose(fp);

    /* calcula jaccard medio para cada documento */
    for (it=0;it<10;++it) {
        for (i=0; i<docs-1; ++i) {
            jacc = 0.0;
            for (j=i+1; j<docs; ++j) {
                jacc += jaccard( corpus[i], corpus[j], n_elems );            
            }
            printf("%d = %lf\n", i, jacc/(double)docs);
        }
    }

    return 0;
}
