//
// Analisador lexico
//

#ifndef MINIC_LEXER_H
#define MINIC_LEXER_H

#define TAM_MAX  100


typedef enum tagTipoToken {
    TOKEN_KWORD,
    TOKEN_IDENT,
    TOKEN_LIT_NUM,
    TOKEN_LIT_STRING,
    TOKEN_OPER,
    TOKEN_COMENT,

    TOKEN_ABREPAR,
    TOKEN_FECHAPAR,
    TOKEN_ABRECHA,
    TOKEN_FECHACHA,
    TOKEN_IGUAL,
    TOKEN_VIRG,
    TOKEN_PONTOVIRG,
    TOKEN_EOF,
    TOKEN_ERRO
} TipoToken;

typedef struct tagToken {
    TipoToken tipo;
    int       valor;
    char      string[TAM_MAX];
} Token;


void InicializaLexer(char *arqFonte);
Token* ProximoToken();
void FinalizaLexer();


#endif //MINIC_LEXER_H
