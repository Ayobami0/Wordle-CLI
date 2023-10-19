#include "colors.h"
#include "main.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_table(word **word_list) {
  int i;
  printf("%s", CLRSCR);
  printf("==============WORDLE================\n");
  printf("==============ENJOY================\n");
  for (i = 0; i < TRIES; i++) {
    printf("%s\n", word_list[i]->word);
  }
}

int set_default(word **word_list) {
  int i;
  word *default_word;
  char *placeHolder;
  for (i = 0; i < TRIES; i++) {
    default_word = malloc(sizeof(word));
    if (default_word == NULL)
      return 0;
    default_word->word = malloc(LEN_WORDS + 1);
    if (default_word->word == NULL)
      return 0;
    strcpy(default_word->word, "******");
    default_word->len = LEN_WORDS;
    word_list[i] = default_word;
  }
  return 1;
}

int check_word(word *input, char *word_to_check) {
  int i, j, buf_count = 0, correct_count = 0;
  char RESULT_WORD[BUFSIZE];

  for (i = 0; i < input->len; i++) {
    switch (contains(word_to_check, toupper(input->word[i]))) {
    case 1:
      if (word_to_check[i] == toupper(input->word[i])) {
        add_color_to_buffer(RESULT_WORD, input->word[i], BGRN, &buf_count);
        correct_count++;
      } else
        add_color_to_buffer(RESULT_WORD, input->word[i], BCYN, &buf_count);
      break;
    case 0:
      add_color_to_buffer(RESULT_WORD, input->word[i], BRED, &buf_count);
      break;
    }
  }
  RESULT_WORD[buf_count] = '\0';
  free(input->word);
  input->word = malloc(strlen(RESULT_WORD) + 1);
  if (input->word == NULL)
    return -1;
  strcpy(input->word, RESULT_WORD);
  printf("%i\n", correct_count);
  if (correct_count == LEN_WORDS)
    return 1;
  return 0;
}
void add_color_to_buffer(char *buf, char c, char *color_string,
                         int *buf_count) {
  int j;
  for (j = 0; color_string[j] != '\0'; j++) {
    buf[*buf_count] = color_string[j];
    (*buf_count)++;
  }
  buf[*buf_count] = c;
  (*buf_count)++;
  for (j = 0; RESET[j] != '\0'; j++) {
    buf[*buf_count] = RESET[j];
    (*buf_count)++;
  }
}

int contains(char *s, char c) {
  int i;

  for (i = 0; s[i] != '\0'; i++)
    if (s[i] == c)
      return 1;
  return 0;
}
