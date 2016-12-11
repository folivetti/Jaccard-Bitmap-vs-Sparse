#include <stdio.h>
#include <string.h>
#include "hashtrie.h"
#include "sparse.h"

#define MAXLEN 1024
#define MB 8388608.0

int main( int argc, char **argv )
{
    char buffer[MAXLEN];
    char * token;
    FILE * fp;
    Node * raiz = cria_no();
    int features, docs = 0, n_elems;
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

    Elem * corpus[docs];
    
    /* representa cada documento como um vetor esparso */
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Falha ao abrir %s\n", argv[1]);
        return -1;
    }

    i = 0;
    while ( (fgets(buffer, MAXLEN, fp)) != NULL ) {
        corpus[i] = NULL;
        buffer[ strlen(buffer)-1 ] = '\0';
        token = strtok(buffer, " ");
        while(token != NULL) {
            j = busca_no(token, raiz);
            corpus[i] = insere_sparse(j, corpus[i]);
            token = strtok(NULL, " ");            
        }
        ++i;
    }

    fclose(fp);

    /* calcula jaccard medio para cada documento */
    for (it=0; it<10; ++it){
    for (i=0; i<docs-1; i++) {
        jacc = 0.0;
        for (j=i+1; j<docs; j++) {
            jacc += sparse_jaccard( corpus[i], corpus[j] );                        
        }
        printf("%d = %lf\n", i, jacc/(double)docs);
    }
    }

    return 0;
}
