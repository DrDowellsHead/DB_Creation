#ifndef AUXILIARY_MENU_FUNC_H
#define AUXILIARY_MENU_FUNC_H

// Menu

void modules_menu();
void levels_menu();
void events_menu();

// Modules

void show_all_modules();
void find_module_by_id();
void add_module();
void update_module();
void delete_module_soft();
void delete_module_hard();
void show_modules_on_level();

// Levels

void show_all_levels();
void add_level();
void update_level();
void delete_level();

// Events

void show_all_events();
void add_event();
void update_event();
void delete_event();
void show_events_for_module();

#endif