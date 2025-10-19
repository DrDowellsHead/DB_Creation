#ifndef DISPLAY_H
#define DISPLAY_H

#define WIDTH 80
#define HEIGHT 25
#define CONTENT_X 3
#define CONTENT_Y 2

void draw_border();
void set_cursor_position(int x, int y);
void print_centered(int y, const char *text);
void wait_for_enter();
void main_menu();
void modules_menu();
void levels_menu();
void events_menu();
void show_all_modules();
void clear_screen();
void print_at_position(int x, int y, const char *text);

#endif