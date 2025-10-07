#include <stdio.h>
#include "shared.h"

int main() {
    return 0;
}

int db_select_all(const char *filename, void* buffer, size_t struct_size) {

    if (filename == NULL || buffer == NULL || struct_size == NULL) {
        printf("Ошибка: неверные параметры\n");
        return 0;
    }
    FILE *file;
    long file_size;
    int count = 0;

    file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    if (file_size == 0) {
        fclose(file);
        return 0;
    }

    count = file_size / struct_size;

    size_t elements_read = fread(buffer, struct_size, count, file);

    fclose(file);
    return (int)elements_read;
}


int db_save_all(const char *filename, void *buffer, size_t struct_size, int count) {

    if (filename == NULL || buffer == NULL || struct_size == 0) {
        printf("Ошибка сохранения файла: неверные параметры\n");
        return 1;
    }

    FILE *file;
    file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return 1;
    }

    size_t elemants_written = fwrite(buffer, struct_size, count, file);

    if (elemants_written != count) {
        printf("Ошибка: записано %zu из %d записей\n", elemants_written, count);
        fclose(file);
        return (int)elemants_written;
    }

    printf("Файл успешно перезаписан\n");

    fclose(file);
    return (int)elemants_written;

}


int db_insert(const char *filename, void *new_record, size_t struct_size);
int db_update(const char *filename, void *update_record, size_t struct_size, int id);
int db_delete(const char *filename, int id, size_t struct_size);