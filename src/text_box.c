#include "text_box.h"
#include <raylib.h>
#include <stdio.h>

void setup_text_box(TextBox *text_box) {
  printf("[DEBUG] Setting up text box\n");
  text_box->file_max_lines = 0;
  text_box->width = TEXT_BOX_WIDTH;
  text_box->height = TEXT_BOX_HEIGHT;
  text_box->line_spacing = LINE_SPACING;
  text_box->max_lines = (int) (TEXT_BOX_HEIGHT / text_box->line_spacing);
  text_box->max_char = 2048; 
  text_box->cursor_x = 0;
  text_box->cursor_y = 0;
  text_box->starting_line = 0;
  printf("[DEBUG] Text box variables initialized\n");
}

void draw_text_box(TextBox text_box) {
  DrawRectangle(0, 0, text_box.width, text_box.height, BLACK);
}

void draw_text_box_lines(TextBox text_box) {
  for (int i = 0; i < text_box.max_lines; i++) {
    DrawLine(0, i * text_box.line_spacing, text_box.width, i * text_box.line_spacing, RED);
  } 
}

void allocate_line(TextBox *text_box, char *text, int index) {
  strcpy(text_box->lines[index], text);
  text_box->file_max_lines++;
}

void draw_text(TextBox text_box) {
  int relative_line_number = 0;
  char buffer[10];
  for (int i = text_box.starting_line; i < text_box.file_max_lines; i++) {
    if (relative_line_number > text_box.max_lines) return;
    if (text_box.lines[i] != NULL) {
      sprintf(buffer, "%d", i);
      DrawText(buffer, 2, relative_line_number * FONT_SIZE, FONT_SIZE, BLUE);
      DrawText(text_box.lines[i], LEFT_PADDING, (i - text_box.starting_line) * text_box.line_spacing, FONT_SIZE, WHITE);
      relative_line_number++;
    }
  }
}

void draw_cursor(TextBox text_box) {
  DrawRectangle((text_box.cursor_x + 4) * FONT_SIZE / 2, (text_box.cursor_y - text_box.starting_line) * FONT_SIZE, FONT_SIZE / 2, FONT_SIZE, CURSOR_COLOR);
}

void insert_character(TextBox *text_box, char character, int line, int x) {
  printf("[DEBUG] Inserted: %c at %d %d\n", character, x, line);
  text_box->lines[line][x] = character;
}
