#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {

  regex_t exp_reg;

  char regex_kword[] = "int|printf|printint|return";
  char regex_ident[] = "^(_|[a-zA-Z])([_a-zA-Z0-9])*";
  char regex_lit_num[] = "^[0-9]+$";
  char regex_lit_string[] = "^\"([^\"\\]|\\[nrt])*\"$";
  char regex_oper[] = "(\\+|-|\\*|/|<|&&)";
  char regex_coment[] = "^//.*$";

  char text[] = "\"Este e um programa escrito em linguagem C\"";

  printf("String: %s\n", text);
  printf("Expressao Regular: %s\n", regex_lit_string);

  int reter = regcomp(&exp_reg, regex_lit_string, REG_EXTENDED);
  if(reter == 1){
    printf("Erro ao compilar regex\n");
  } else {
    printf("Compilado com sucesso\n");
  }

  int n_matches = 1;
  regmatch_t M[n_matches];

  int reter2 = regexec(&exp_reg, text, n_matches, M, 0);

  if (!reter2) {
      // encontrado
      // M[i].rm_so -> start (negativo significa falha)
      // M[i].rm_eo -> end
      if (M[0].rm_so >= 0) {
        printf("- match: %d:%d\n", M[0].rm_so, M[0].rm_eo);

      }
    printf("Encontrado\n");
  } else if (reter2 == REG_NOMATCH) {
    printf("Nao Encontrado\n");
  } else {
    char message[128];
    regerror(reter2, &exp_reg, message, sizeof(message));
    printf("Erro: %s (%d)\n", message, reter);
  }

  regfree(&exp_reg);

  return 0;

}