#include <stdio.h>
#include <stdlib.h>

#include "arq.h"
#include "lexer.h"

void ImpBuffer(Buffer *b) {
    for (long c = 0; c < b->tam; ++c)
        putchar(b->cont[c]);
}

void ImprimeTipoToken(TipoToken tipo) {
    switch(tipo) {
        case TOKEN_KWORD:
            printf("TOKEN_KWORD");
            break;
        case TOKEN_IDENT:
            printf("TOKEN_IDENT");
            break;
        case TOKEN_LIT_NUM:
            printf("TOKEN_LIT_NUM");
            break;
        case TOKEN_LIT_STRING:
            printf("TOKEN_LIT_STRING");
            break;
        case TOKEN_OPER:
            printf("TOKEN_OPER");
            break;
        case TOKEN_COMENT:
            printf("TOKEN_COMENT");
            break;
        
        case TOKEN_ABREPAR:
            printf("TOKEN_ABREPAR");
            break;
        case TOKEN_FECHAPAR:
            printf("TOKEN_FECHAPAR");
            break;
        case TOKEN_ABRECHA:
            printf("TOKEN_ABRECHA");
            break;
        case TOKEN_FECHACHA:
            printf("TOKEN_FECHACHA");
            break;
        case TOKEN_IGUAL:
            printf("TOKEN_IGUAL");
            break;
        case TOKEN_VIRG:
            printf("TOKEN_VIRG");
            break;
        case TOKEN_PONTOVIRG:
            printf("TOKEN_PONTOVIRG");
            break;

        default:
            printf("Tipo desconhecido");
    }
}

int main() {
    InicializaLexer("../test/exp5.mc");

    Token *t = ProximoToken();
    while (t->tipo != TOKEN_EOF && t->tipo != TOKEN_ERRO) {
        printf("Tipo do token: ");
        ImprimeTipoToken(t->tipo);
        if (t->tipo == TOKEN_LIT_NUM) {
            printf(" - Valor do token: %d\n", t->valor);
        } else if (t->tipo == TOKEN_LIT_STRING) {
            printf(" - String: %s\n", t->string);
        } else
            printf("\n");

        t = ProximoToken();
    }

    if (t->tipo == TOKEN_ERRO) {
        fprintf(stderr, "Erro lexico\n");
    }

    FinalizaLexer();
    return 0;
}
