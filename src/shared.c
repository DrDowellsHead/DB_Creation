#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int db_select_all(const char *filename, void *buffer, size_t struct_size) {

    if (filename == NULL || buffer == NULL || struct_size == 0) {
        printf("Ошибка: неверные параметры\n");
        return 1;
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

int db_save_all(const char *filename, void *buffer, size_t struct_size,
                int count) {

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

    size_t elements_written = fwrite(buffer, struct_size, count, file);

    if (elements_written != (size_t)count) {
        printf("Ошибка: записано %zu из %d записей\n", elements_written, count);
        fclose(file);
        return (int)elements_written;
    }

    printf("Файл успешно перезаписан\n");

    fclose(file);
    return (int)elements_written;
}

int db_insert(const char *filename, void *new_record, size_t struct_size) {

    if (filename == NULL || new_record == NULL || struct_size == 0) {
        printf("Ошибка: неверные параметры\n");
        return 1;
    }

    void *buffer = NULL;
    int count = 0;

    FILE *file = fopen(filename, "rb");

    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        count = file_size / struct_size;

        if (file_size > 0) {
            buffer = malloc(file_size);
            if (buffer != NULL) {
                fread(buffer, struct_size, count, file);
            }
        }
        fclose(file);
    }

    void *new_buffer = realloc(buffer, (count + 1) * struct_size);
    if (new_buffer == NULL) {
        free(buffer);
        return 0;
    }

    memcpy((char *)new_buffer + count * struct_size, new_record, struct_size);
    count++;

    int result = db_save_all(filename, new_buffer, struct_size, count);
    free(new_buffer);
    return result;
}

int db_update(const char *filename, void *update_record, size_t struct_size,
              int id) {

    if (filename == NULL || update_record == NULL || struct_size == 0) {
        printf("Ошибка: неверные параметры\n");
        return 1;
    }

    void *buffer = NULL;
    int count = 0;

    FILE *file = fopen(filename, "rb");

    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        count = file_size / struct_size;

        if (file_size > 0) {
            buffer = malloc(file_size);
            if (buffer != NULL) {
                fread(buffer, struct_size, count, file);
            }
        }
        fclose(file);
    }

    if (buffer == NULL || count == 0) {
        printf("Файл пустой или не найден\n");
        return 1;
    }

    int found_index = -1;
    for (int i = 0; i < count; i++) {
        void *current_record = (char *)buffer + i * struct_size;

        int *current_id = (int *)current_record;

        if (*current_id == id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Ошибка: запись с ID %d не найдена\n", id);
        free(buffer);
        return 1;
    }
    void *record_to_update = (char *)buffer + found_index * struct_size;
    memcpy(record_to_update, update_record, struct_size);

    int result = db_save_all(filename, buffer, struct_size, count);

    if (result) {
        printf("Запись с ID %d успешно обновлена\n", id);
    } else {
        printf("Ошибка при создании обновлённой записи\n");
    }

    free(buffer);

    return result;
}

int db_delete(const char *filename, int id, size_t struct_size,
              int delete_type) {
    // delete_type: 0 - мягкое удаление, 1 - физическое удаление

    if (filename == NULL || struct_size == 0) {
        printf("Ошибка: неверные параметры\n");
        return 1;
    }

    void *buffer = NULL;
    int count = 0;

    FILE *file = fopen(filename, "rb");

    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        count = file_size / struct_size;

        if (file_size > 0) {
            buffer = malloc(file_size);
            if (buffer != NULL) {
                fread(buffer, struct_size, count, file);
            }
        }
        fclose(file);
    }

    if (buffer == NULL || count == 0) {
        printf("Файл пустой или не найден\n");
        free(buffer);
        return 1;
    }

    int found_index = -1;

    for (int i = 0; i < count; i++) {
        int *current_id = (int *)((char *)buffer + i * struct_size);
        if (*current_id == id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Запись по ID %d не найдена\n", id);
        free(buffer);
        return 1;
    }

    int result = 0;

    if (delete_type == 0) {
        int *del_flag =
            (int *)((char *)buffer + found_index * struct_size + 16);
        *del_flag = 1;
        result = db_save_all(filename, buffer, struct_size, count);

        if (result)
            printf("Запись с ID %d помечена, как удалённая\n", id);
    } else {
        for (int i = found_index; i < count - 1; i++) {
            memcpy((char *)buffer + i * struct_size,
                   (char *)buffer + (i + 1) * struct_size, struct_size);
        }
        count--;
        result = db_save_all(filename, buffer, struct_size, count);
        if (result)
            printf("Запись с ID %d физически удалена\n", id);
    }

    free(buffer);
    return result;
}