// Analisador léxico para MiniC

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <regex.h>
#include "arq.h"
#include "lexer.h"

static Buffer *buffer;
static Token *tok = NULL;

static long pos = 0;

// onde as expressoes regulares serao armazenadas
static regex_t re_kword;
static regex_t re_ident;
static regex_t re_lit_num;
static regex_t re_lit_string;
static regex_t re_oper;
static regex_t re_coment;

// definicao das expressoes regulares
static char regex_kword[]       = "int|printf|printint|return";
static char regex_ident[]       = "^(_|[a-zA-Z])([_a-zA-Z0-9])*";
static char regex_lit_num[]     = "^[0-9]+$";
static char regex_lit_string[]  = "\"([^\"\\]|[\\n\\r\\t])*\"\0";
static char regex_oper[]        = "(\\+|-|\\*|/|<|&&)";
static char regex_coment[]      = "^//.*$";

void InicializaLexer(char *arqFonte) {
    buffer = CriaBuffer(arqFonte);

    pos = 0;

    tok = (Token*) malloc(sizeof(Token));

    if (tok == NULL) {
        fprintf(stderr, "Erro alocando memoria para o token\n");
        exit(2);
    }

    tok->tipo = TOKEN_EOF;
    tok->valor = 0;

    int reter = 0;
    reter += regcomp(&re_kword, regex_kword, REG_EXTENDED);
    reter += regcomp(&re_ident, regex_ident, REG_EXTENDED);
    reter += regcomp(&re_lit_num, regex_lit_num, REG_EXTENDED);
    reter += regcomp(&re_lit_string, regex_lit_string, REG_EXTENDED);
    reter += regcomp(&re_oper, regex_oper, REG_EXTENDED);
    reter += regcomp(&re_coment, regex_coment, REG_EXTENDED);

    if (reter > 0) {
        fprintf(stderr, "Erro criacao expressao regular\n");
        exit(1);
    }

}

bool eof() {
    return !(pos < buffer->tam - 1);
}

char* TextoToken(long ini, long fim) {
    char *str = (char*) malloc(fim - ini + 1);

    if (str == NULL) {
        fprintf(stderr, "Erro alocando memoria\n");
        exit(1);
    }
    for (int i = 0; i + ini < fim; ++i) {
        str[i] = buffer->cont[i + ini];
    }

    str[fim - ini] = '\0';
    return str;
}


bool simbolo(char c) {
    return (c == '(' || c == ')' || c == '{' || c == '}' || c == '=' || c == ',' || c == ';');
}

// função: ProximoToken
//
// Dado o arquivo-fonte, obtem e retorna o próximo token
Token* ProximoToken() {
    // obtem o proximo token da entrada e preenche tok

    // pula espaços em branco
    while (!eof() && isspace(buffer->cont[pos]))
        pos++;

    if (isalpha(buffer->cont[pos])) {
        long initPos = pos;
        while (!eof() && !isspace(buffer->cont[pos]) && !simbolo(buffer->cont[pos]))
            pos++;
        // texto do token: entre initPos e pos-1 no buffer
        char *texto = TextoToken(initPos, pos);
        if (!regexec(&re_kword, texto, 0, NULL, 0)) {
            tok->tipo = TOKEN_KWORD;
            tok->valor = 0;
        } else if (!regexec(&re_ident, texto, 0, NULL, 0)) {
            tok->tipo = TOKEN_IDENT;
            tok->valor = 0;
        }
        free(texto);

    } else if (buffer->cont[pos] == '"') {
        long initPos = pos;
        pos++;
       
        while(buffer->cont[pos] != '"'){
            pos++;
        }
        pos++;

        char *texto = TextoToken(initPos, pos); 
        if (!regexec(&re_lit_string, texto, 0, NULL, 0)) {
            tok->tipo = TOKEN_LIT_STRING;
            strcpy(tok->string, texto); 
        }
        free(texto);

    }else if (isdigit(buffer->cont[pos])) {
        long initPos = pos;

        while (!eof() && isdigit(buffer->cont[pos]))
            pos++;
        char *texto = TextoToken(initPos, pos);
        if(!regexec(&re_lit_num, texto, 0, NULL, 0)) {
          tok->tipo = TOKEN_LIT_NUM;
          tok->valor = atoi(texto);
        }
        free(texto);
    } else if ((buffer->cont[pos] == '/') && (buffer->cont[pos+1] ==  '/')){
        long initPos = pos;
        while(!eof() && buffer->cont[pos] != '\n')
            pos++;

        char *texto = TextoToken(initPos, pos);
        if(!regexec(&re_coment, texto, 0, NULL, 0)){
          tok->tipo = TOKEN_COMENT;
          tok->valor = 0;
        }

    } else if (!regexec(&re_oper, TextoToken(pos, pos+1), 0, NULL, 0)) {
        tok->tipo = TOKEN_OPER;
        tok->valor = 0;
        pos++;
    } else if (simbolo(buffer->cont[pos])) {
         switch (buffer->cont[pos]) {
            case '(':
                tok->tipo = TOKEN_ABREPAR;
                break;
            case ')':
                tok->tipo = TOKEN_FECHAPAR;
                break;
            case '{':
                tok->tipo = TOKEN_ABRECHA;
                break;
            case '}':
                tok->tipo = TOKEN_FECHACHA;
                break;
            case '=':
                tok->tipo = TOKEN_IGUAL;
                break;
            case ',':
                tok->tipo = TOKEN_VIRG;
                break;
            case ';':
                tok->tipo = TOKEN_PONTOVIRG;
                break;
            default:
                fprintf(stderr, "Simbolo não esperado: %c\n", buffer->cont[pos]);
          }
        tok->valor = 0;
        pos++;
    } else if (eof()) {
        tok->tipo = TOKEN_EOF;
        tok->valor = 0;
    } else {
        tok->tipo = TOKEN_ERRO;
        tok->valor = 0;
    }

    return tok;
}

void FinalizaLexer() {
    DestroiBuffer(buffer);
    free(tok);
}
