#include <stdio.h>
#include "shared.h"

int main() {
    return 0;
}

int db_select_all(const char *filename, void* buffer, size_t struct_size) {
    filename = fopen("filename.txt", "r");

    if (filename == NULL) {
        printf("Лшибка при открытии файла!\n");
        return 1;
    }
}



int db_save_all(const char *filename, void *buffer, size_t struct_size, int count);
int db_insert(const char *filename, void *new_record, size_t struct_size);
int db_update(const char *filename, void *update_record, size_t struct_size, int id);
int db_delete(const char *filename, int id, size_t struct_size);