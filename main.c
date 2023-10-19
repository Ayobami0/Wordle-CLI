#include "main.h"
#include "colors.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  main_loop();

  printf("\n==============THANK YOU FOR PLAYING===============\n");
  return EXIT_SUCCESS;
}

void main_loop(void) {
  int i, c, tries = 0, j, result = 0;
  char input[LEN_WORDS + 1], *TEST = "WORKER";
  word **word_list;

  word_list = malloc(sizeof(word *) * TRIES);
  if (word_list == NULL)
    return;
  if (set_default(word_list) == 0) {
    free(word_list);
    return;
  }
  while (1) {
    print_table(word_list);
    if (tries == TRIES) {
      printf("THE CORRECT WORD IS %s%s%s\n", UGRN, TEST, RESET);
      printf("TRY AGAIN TOMORROW\n");
      break;
    }
    if (result == -1) {
      break;
    } else if (result == 1) {
      printf("Right Word Found!!!");
      break;
    }
    printf("%sEnter a word (exit to Exit program)\n", BYEL);
    printf("ATTEMPTS LEFT %i =>> %s", TRIES - tries, RESET);
    i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
      if (c < 65 || c > 122)
        break;
      input[i++] = c;
    }
    input[i] = '\0';
    if (strcmp(input, "exit") == 0)
      break;
    if (i != LEN_WORDS)
      printf("%sYou are required to enter a %i letters word%s\n", RED,
             LEN_WORDS, RESET);
    else {
      strcpy(word_list[tries]->word, input);
      result = check_word(word_list[tries], TEST);
      tries++;
    }
  }
  for (j = 0; j < TRIES; j++) {
    free(word_list[j]->word);
    free(word_list[j]);
  }
  free(word_list);
}
