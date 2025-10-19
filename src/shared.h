#ifndef SHARED_H
#define SHARED_H

#include <stddef.h>

struct Modules {
    int id;
    char name[30];
    int level;
    int cell;
    int del_flag;
};

struct Levels {
    int levels_num;
    int count_levels;
    int flag_levels;
};

struct Status_Events {
    int event_id;
    int module_id;
    int module_status;
    char date[11]; // "dd.mm.yyyy\0"
    char time[9];  // "hh:mm:ss\0"
};

int db_select_all(const char *filename, void *buffer, size_t struct_size);
int db_save_all(const char *filename, void *buffer, size_t struct_size,
                int count);
int db_insert(const char *filename, void *new_record, size_t struct_size);
int db_update(const char *filename, void *update_record, size_t struct_size,
              int id);
int db_delete(const char *filename, int id, size_t struct_size,
              int delete_type);

#endif