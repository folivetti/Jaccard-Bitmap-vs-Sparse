typedef struct Node {
    struct Node * filhos[36];
    int frequencia;
    int idx;
} Node;

Node * cria_no ( );
void insere_no ( char * s, Node * raiz );
int busca_no ( char * s, Node * raiz );
void insere_letra (char * buf, unsigned char idx);
void remove_letra (char * buf);
void percorre_arvore ( Node * raiz, char * buf );
int conta_arvore ( Node * raiz, int elem );
