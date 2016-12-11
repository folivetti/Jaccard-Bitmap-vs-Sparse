#include <stdio.h>
#include <stdlib.h>
#include "sparse.h"

Elem * cria_elem( )
{
    Elem * no = (Elem *)malloc(sizeof(Elem));

    if (no != NULL) {
        no->idx = 0;
        no->next = NULL;
    }

    return no;
}

Elem * insere_sparse ( int idx, Elem * raiz )
{
    Elem * atual = raiz;

    if (raiz == NULL) {
        
        atual = cria_elem();
        atual->idx = idx;
        return atual;

    } else {

        while (atual->next != NULL && atual->next->idx < idx) {
            atual = atual->next;
        }

        Elem * no = cria_elem();
        no->idx = idx;
        no->next = atual->next;
        atual->next = no;
    }

    return raiz;

}

double sparse_jaccard ( Elem * d1, Elem * d2 )
{
    int set_inter = 0, set_union = 0;
    
    while (d1 != NULL && d2 != NULL) {
        if (d1->idx < d2->idx) {set_union++; d1 = d1->next;}
        else if (d1->idx > d2->idx) {set_union++; d2 = d2->next;}
        else {set_inter++; set_union++; d1 = d1->next; d2 = d2->next;}
    }
    while (d1 != NULL) {set_union++; d1 = d1->next;}
    while (d2 != NULL) {set_union++; d2 = d2->next;}

    if (!set_union) return 0.0;
    
    return (double)set_inter/(double)set_union;
}
