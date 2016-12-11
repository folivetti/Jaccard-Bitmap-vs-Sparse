#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtrie.h"

#define MAXLEN 1024

Node * cria_no ( )
{
    int i;
    Node * no = (Node *) malloc(sizeof(Node));

    if (no != NULL) {
        for (i=0;i<36;i++) no->filhos[i] = NULL;
        no->frequencia = 0;
        no->idx = -1;
    }

    return no;
}

void insere_no ( char * s, Node * raiz )
{
    Node * no_atual = raiz;
    char idx;
    static int lbl = 0;

    while (*s) {

        if (*s >= '0' && *s <= '9') idx = (*s)-'0';
        else if (*s >= 'A' && *s <= 'Z') idx = (*s)-'A'+10;
        else if (*s >= 'a' && *s <= 'z') idx = (*s)-'a'+10;
        else return;
        
        if (no_atual->filhos[idx] == NULL) {
            no_atual->filhos[idx] = cria_no();
        }
        no_atual = no_atual->filhos[idx];
        s++;
    }
    no_atual->frequencia += 1;
    if (no_atual->idx == -1)
        no_atual->idx = lbl++;
}

int busca_no ( char * s, Node * raiz )
{
    Node * no_atual = raiz;
    char idx;

    while (*s) {
    
        if (*s >= '0' && *s <= '9') idx = (*s)-'0';
        else if (*s >= 'A' && *s <= 'Z') idx = (*s)-'A'+10;
        else if (*s >= 'a' && *s <= 'z') idx = (*s)-'a'+10;
        else return -1;
    
        if (no_atual->filhos[idx] == NULL) return -1;
        no_atual = no_atual->filhos[idx];
        s++;
    }
    return no_atual->idx;
}

void insere_letra (char * buf, unsigned char idx)
{
    int len = strlen(buf);
    char letra;
    
    if (idx < 10) letra = '0' + idx;
    else if (idx < 36) letra = 'a' + idx - 10;
    buf[len] = letra;
    buf[len+1] = '\0';
}

void remove_letra (char * buf)
{
    buf[strlen(buf)-1] = '\0';
}

void percorre_arvore ( Node * raiz, char * buf )
{
    unsigned char i;
    Node * no_atual = raiz;

    if (raiz->frequencia > 0) {
        printf("%d: %s -> %d\n", raiz->idx, buf, raiz->frequencia);
    }

    for (i=0;i<36;i++) {
        if (no_atual->filhos[i] != NULL) {
            insere_letra(buf, i);
            percorre_arvore( no_atual->filhos[i], buf );
            remove_letra(buf);
        }
    }
}

int conta_arvore ( Node * raiz, int elem )
{
    unsigned char i;
    int maxidx = 0;    
    Node * no_atual = raiz;

    if (raiz->idx >= 0) {
        elem = (elem > raiz->idx)?elem:raiz->idx;
    }

    for (i=0;i<36;i++) {
        if (no_atual->filhos[i] != NULL) {
            maxidx = conta_arvore( no_atual->filhos[i], elem );
            elem = (elem > maxidx)?elem:maxidx;
        }
    }
    
    return elem;
}
/*

int main ( int argc, char **argv )
{
    char buffer[MAXLEN];
    char * token;
    FILE * fp;
    Node * raiz = cria_no();

    if (argc == 1) {
        printf("Uso: %s <nome_arquivo>\n", argv[0]);
        return -1;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Falha ao abrir %s\n", argv[1]);
        return -1;
    }

    while ( (fgets(buffer, MAXLEN, fp)) != NULL ) {
        buffer[ strlen(buffer)-1 ] = '\0';
        token = strtok(buffer, " ");
        while(token != NULL) {
            insere_no( token, raiz );
            token = strtok(NULL, " ");
        }
    }

    fclose(fp);

    buffer[0] = '\0';
    percorre_arvore(raiz, buffer);
    printf("%d\n", conta_arvore(raiz, 0));

    return 0;
}*/
