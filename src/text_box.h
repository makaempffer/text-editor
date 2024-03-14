#ifndef TEXT_BOX_H
#define TEXT_BOX_H
#define CURSOR_COLOR RED
#include "constants.h"
#include <stdio.h>
#include "raylib.h"
#include <string.h>

typedef struct {
  int width;
  int height;
  int max_lines;
  int line_spacing;
  int max_char;
  char lines[2048][TEXT_BOX_WIDTH / FONT_SIZE];
  int file_max_lines;
  int cursor_x;
  int cursor_y;
  int starting_line;
} TextBox;

void setup_text_box(TextBox *text_box);
void draw_text_box(TextBox text_box);
void draw_text_box_lines(TextBox text_box);
void allocate_line(TextBox *text_box, char *text, int index);
void draw_text(TextBox text_box);
void draw_cursor(TextBox text_box);
void insert_character(TextBox *text_box, char character, int line, int x);

#endif // !TEXT_BOX
