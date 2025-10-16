#include <stdio.h>
#include "auxiliary_menu_func.h"
#include "display.h"

void modules_menu() {
    int choice;

    do {
        clear_screen();
        draw_border();

        print_centered(2, "Управление Уровнями");

        print_at_position(CONTENT_X, CONTENT_Y + 2, "Доступные Операции:");
        print_at_position(CONTENT_X, CONTENT_Y + 4, "1. Показать все модули");
        print_at_position(CONTENT_X, CONTENT_Y + 5, "2. Найти модуль по ID");
        print_at_position(CONTENT_X, CONTENT_Y + 6, "3. Добавить модуль");
        print_at_position(CONTENT_X, CONTENT_Y + 7, "4. Обновить модуль");
        print_at_position(CONTENT_X, CONTENT_Y + 8, "5. Удалить модуль (мягкое удаление)");
        print_at_position(CONTENT_X, CONTENT_Y + 9, "6. Удалить модуль (физическое удаление)");
        print_at_position(CONTENT_X, CONTENT_Y + 10, "7. Модули на уровне");
        print_at_position(CONTENT_X, CONTENT_Y + 11, "0. Назад в главное меню.");

        print_at_position(CONTENT_X, CONTENT_Y + 13, "Выберите Операцию: ");
        set_cursor_position(CONTENT_X + 19, CONTENT_Y + 13);

        if(scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1; show_all_modules(); break; // Вызов modules_select_all()
            case 2: find_module_by_id(); break; // Поиск через modules_select_all() + фильтрация
            case 3: add_module(); break; // Вызов modules_insert()
            case 4: update_module(); break; // Вызов modules_update()
            case 5: delete_module_soft(); break; // Вызов modules_delete() с delete_type=0
            case 6: delete_module_hard(); break; // Вызов modules_delete() с delete_type=1
            case 7: show_modules_on_level(); break; // Фильтрация modules_select_all() по уровню
            case 0: main_menu();
            default:
                print_at_position(CONTENT_X, CONTENT_Y + 15, "Неверный Выбор!");
                wait_for_enter();
        }
    } while (choice != 0);
}

void levels_menu() {
    int choice;

    do {
        clear_screen();
        draw_border();

        print_centered(2, "Управление Событиями");

        print_at_position(CONTENT_X, CONTENT_Y + 2, "Доступные Операции:");
        print_at_position(CONTENT_X, CONTENT_Y + 4, "1. Показать все события");
        print_at_position(CONTENT_X, CONTENT_Y + 5, "2. Добавить событие");
        print_at_position(CONTENT_X, CONTENT_Y + 6, "3. Обновить событие");
        print_at_position(CONTENT_X, CONTENT_Y + 7, "4. Удалить событие");
        print_at_position(CONTENT_X, CONTENT_Y + 8, "5. События модуля");
        print_at_position(CONTENT_X, CONTENT_Y + 9, "0. Назад в главное меню.");

        print_at_position(CONTENT_X, CONTENT_Y + 11, "Выберите Операцию: ");
        set_cursor_position(CONTENT_X + 19, CONTENT_Y + 11);


        if(scanf("%d". &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
        case 1; show_all_events(); break; // Вызов status_events_select_all()
        case 2: add_event(); break; // Вызов status_events_insert()
        case 3: update_event(); break; // Вызов status_events_update()
        case 4: delete_event(); break; // Вызов status_events_delete()
        case 5: show_events_for_module(); // Фильтрация по module_id
        case 0: main_menu(); break;
        default:
            print_at_position(CONTENT_X, CONTENT_Y + 13, "Неверный Выбор!");
            wait_for_enter();
        }
    } while (choice != 0);
}

void events_menu() {
    int choice;

    do {
        clear_screen();
        draw_border();

        print_centered(2, "Управление Уровнями");

        print_at_position(CONTENT_X, CONTENT_Y + 2, "Доступные Операции:");
        print_at_position(CONTENT_X, CONTENT_Y + 4, "1. Показать все модули");
        print_at_position(CONTENT_X, CONTENT_Y + 5, "2. Найти модуль по ID");
        print_at_position(CONTENT_X, CONTENT_Y + 6, "3. Добавить модуль");
        print_at_position(CONTENT_X, CONTENT_Y + 7, "4. Обновить модуль");
        print_at_position(CONTENT_X, CONTENT_Y + 8, "5. Удалить модуль (мягкое удаление)");
        print_at_position(CONTENT_X, CONTENT_Y + 9, "6. Удалить модуль (физическое удаление)");
        print_at_position(CONTENT_X, CONTENT_Y + 10, "7. Модули на уровне");
        print_at_position(CONTENT_X, CONTENT_Y + 11, "0. Назад в главное меню.");

        print_at_position(CONTENT_X, CONTENT_Y + 13, "Выберите Операцию: ");
        set_cursor_position(CONTENT_X + 19, CONTENT_Y + 13);

        if(scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1; show_all_modules(); break; // Вызов modules_select_all()
            case 2: find_module_by_id(); break; // Поиск через modules_select_all() + фильтрация
            case 3: add_module(); break; // Вызов modules_insert()
            case 4: update_module(); break; // Вызов modules_update()
            case 5: delete_module_soft(); break; // Вызов modules_delete() с delete_type=0
            case 6: delete_module_hard(); break; // Вызов modules_delete() с delete_type=1
            case 7: show_modules_on_level(); break; // Фильтрация modules_select_all() по уровню
            case 0: break; // Просто выходим из цикла
            default:
                print_at_position(CONTENT_X, CONTENT_Y + 15, "Неверный Выбор!");
                wait_for_enter();
        }
    } while (choice != 0);
}

void show_all_modules();
    clear_screen();
    draw_border();

    print_centered(2, "Все Модули Базы Данных");

    struct Modules modules[1000];

    int count = modules_select_all(modules);

    if (count == 0) {
        print_at_position(CONTENT_X, CONTENT_Y, "Модули не найдены или файл пустой");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y, "┌─────┬──────────────────────────────┬───────┬───────┬──────────┐");
        print_at_position(CONTENT_X, CONTENT_Y, "│ ID  │ Название                     │ Уровень │ Ячейка │ Статус   │");
        print_at_position(CONTENT_X, CONTENT_Y, "├─────┼──────────────────────────────┼───────┼───────┼──────────┤");

        for (int i = 0; i < count && i < 15; i++) {
            char line[100];
            snprintf(line, sizeof(line), "│ %-3d │ %-28s │ %-5d │ %-5d │ %-8s │",
                modules[i].id, modules[i].name, modules[i].level,
                modules[i].cell, modules[i].del_flag ? "Удалён" : "Активен");
            print_at_position(CONTENT_X, CONTENT_Y + 3 + i, line);

            print_at_position(CONTENT_X, CONTENT_X + 3 + (count < 15 ? count : 15), "└─────┴──────────────────────────────┴───────┴───────┴──────────┘");

            char count_text[50];
            snprintf(count_text, sizeof(count_text), "Всего модулей: %d", count);
            print_at_position(CONTENT_X, CONTENT_Y + 5 + (count < 15 ? count : 15), count_text);
        }

        wait_for_enter();
    }

    void add_module() {
        clear_screen();
        draw_border();

        print_centered(2, "Добавление Нового Модуля");

        struct Modules new_module;

        print_at_position(CONTENT_X, CONTENT_Y, "Введите ID модуля: ");
        set_cursor_position(CONTENT_X + 20, CONTENT_Y);
        scanf("%d", &new_module.id);

        print_at_position(CONTENT_X, CONTENT_Y + 1, "Введите название модуля: ");
        set_cursor_position(CONTENT_X + 26, CONTENT_Y + 1);
        scanf("%d", &new_module.name);

        print_at_position(CONTENT_X, CONTENT_Y + 1, "Введите уровень: ");
        set_cursor_position(CONTENT_X + 18, CONTENT_Y + 2);
        scanf("%d", &new_module.level);

        print_at_position(CONTENT_X, CONTENT_Y + 1, "Введите ячейку: ");
        set_cursor_position(CONTENT_X + 17, CONTENT_Y + 3);
        scanf("%d", &new_module.cell);

        new_module.del_flag = 0; // Новый модуль всегда активен

        id (modules_insert(&new_module)) {
            print_at_position(CONTENT_X, CONTENT_Y + 5, "Моудль успешно добавлен!");
        } else {
            print_at_position(CONTENT_X, CONTENT_Y + 5, "Ошибка при добавлении модуля!");
        }

        wait_for_enter();
}