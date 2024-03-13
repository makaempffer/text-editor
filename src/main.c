#include "raylib.h"
#include "constants.h"
#include "text_box.h"
#include <stdio.h>

int main(void)
{
  InitWindow(WIDTH, HEIGHT, "TXT");
  SetTargetFPS(FPS);

  TextBox text_box;
  setup_text_box(&text_box);

  FILE *file = fopen("example.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  char line[256];
  int index = 0;
  while (fgets(line, sizeof(line), file) != NULL) {
    printf("%d %s", index, line);
    allocate_line(&text_box, line, index);
    index++;
  }

  fclose(file);

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_DOWN)) {
      text_box.cursor_y++;
      if (text_box.cursor_y - text_box.starting_line >= text_box.max_lines) {
        text_box.starting_line++;
      } 
      printf("cursor_y: %d / starting_line: %d / Line: [%d]\n", text_box.cursor_y, text_box.starting_line, text_box.cursor_y + text_box.starting_line);
      insert_character(&text_box, 'c', text_box.cursor_y, text_box.cursor_x, text_box.cursor_y);
    } else if (IsKeyPressed(KEY_UP)) {
      text_box.cursor_y--;
      if (text_box.cursor_y < text_box.starting_line) {
        text_box.starting_line--;
      }
      printf("cursor_y: %d / starting_line: %d / Line: [%d]\n", text_box.cursor_y, text_box.starting_line, text_box.cursor_y + text_box.starting_line);
      insert_character(&text_box, 'c', text_box.cursor_y, text_box.cursor_x, text_box.cursor_y);
    }
    if (IsKeyPressed(KEY_RIGHT) && text_box.cursor_x < text_box.max_char) {
      text_box.cursor_x++;
      insert_character(&text_box, 'c', text_box.cursor_y, text_box.cursor_x, text_box.cursor_y);
    } else if (IsKeyPressed(KEY_LEFT) && text_box.cursor_x > 0) {
      insert_character(&text_box, 'c', text_box.cursor_y, text_box.cursor_x, text_box.cursor_y);
      text_box.cursor_x--;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    // Drawing 
    draw_text_box(text_box);
    // draw_text_box_lines(text_box);
    draw_cursor(text_box);
    draw_text(text_box);
    //

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
