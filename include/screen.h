#ifndef SCREEN_H
#define SCREEN_H

void write(int *pos, char *str);
void write_to(int pos, char *str);
void clear_screen();
void left(int *pos, int amount);
void right(int *pos, int amount);

#endif