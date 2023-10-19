#ifndef MAIN_H
#define MAIN_H

#define LEN_WORDS 6
#define TRIES 5
#define BUFSIZE 1024

typedef struct word_s {
  char *word;
  int len;
} word;

void print_table(word **);
void main_loop(void);
int contains(char *s, char c);
int set_default(word **word_list);
int check_word(word *, char *);
void add_color_to_buffer(char *buf, char c, char *color_string, int *buf_count);

#endif /*MAIN_H*/
