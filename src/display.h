#ifndef DISPLAY.H
#define DISPLAY.H

void draw_border();
void set_cursor_position(int x, int y);
void print_centered(int y, const char *text);
void wait_for_enter();
void main_menu();
void modules_menu();
void levels_menu();
void events_menu();
void show_all_modules();
void ai_disabler();

#endif