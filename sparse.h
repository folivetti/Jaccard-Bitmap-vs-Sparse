typedef struct elem {
    int idx;
    struct elem * next;
} Elem;

Elem * cria_elem( );
Elem * insere_sparse ( int idx, Elem * raiz );
double sparse_jaccard ( Elem * d1, Elem * d2 );
