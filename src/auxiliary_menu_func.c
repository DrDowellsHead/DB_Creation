#include "auxiliary_menu_func.h"
#include "display.h"
#include "levels.h"
#include "modules.h"
#include "status_events.h"
#include <stdio.h>
#include <string.h>

// ==================== МОДУЛИ ====================

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
        print_at_position(CONTENT_X, CONTENT_Y + 8,
                          "5. Удалить модуль (мягкое удаление)");
        print_at_position(CONTENT_X, CONTENT_Y + 9,
                          "6. Удалить модуль (физическое удаление)");
        print_at_position(CONTENT_X, CONTENT_Y + 10, "7. Модули на уровне");
        print_at_position(CONTENT_X, CONTENT_Y + 11,
                          "0. Назад в главное меню.");

        print_at_position(CONTENT_X, CONTENT_Y + 13, "Выберите Операцию: ");
        set_cursor_position(CONTENT_X + 19, CONTENT_Y + 13);

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n')
                ;
            choice = -1;
        }

        switch (choice) {
        case 1:
            show_all_modules();
            break; // Вызов modules_select_all()
        case 2:
            find_module_by_id();
            break; // Поиск через modules_select_all() + фильтрация
        case 3:
            add_module();
            break; // Вызов modules_insert()
        case 4:
            update_module();
            break; // Вызов modules_update()
        case 5:
            delete_module_soft();
            break; // Вызов modules_delete() с delete_type=0
        case 6:
            delete_module_hard();
            break; // Вызов modules_delete() с delete_type=1
        case 7:
            show_modules_on_level();
            break; // Фильтрация modules_select_all() по уровню
        case 0:
            main_menu();
        default:
            print_at_position(CONTENT_X, CONTENT_Y + 15, "Неверный Выбор!");
            wait_for_enter();
        }
    } while (choice != 0);
}

void show_all_modules() {
    clear_screen();
    draw_border();

    print_centered(2, "Все Модули Базы Данных");

    struct Modules modules[1000];

    int count = modules_select_all(modules);

    if (count == 0) {
        print_at_position(CONTENT_X, CONTENT_Y,
                          "Модули не найдены или файл пустой");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y,
                          "┌─────┬──────────────────────────────┬───────┬──────"
                          "─┬──────────┐");
        print_at_position(CONTENT_X, CONTENT_Y + 1,
                          "│ ID  │ Название                     │ Уровень │ "
                          "Ячейка │ Статус   │");
        print_at_position(CONTENT_X, CONTENT_Y + 2,
                          "├─────┼──────────────────────────────┼───────┼──────"
                          "─┼──────────┤");

        for (int i = 0; i < count && i < 15; i++) {
            char line[100];
            snprintf(line, sizeof(line),
                     "│ %-3d │ %-28s │ %-5d │ %-5d │ %-8s │", modules[i].id,
                     modules[i].name, modules[i].level, modules[i].cell,
                     modules[i].del_flag ? "Удалён" : "Активен");
            print_at_position(CONTENT_X, CONTENT_Y + 3 + i, line);
        }

        print_at_position(CONTENT_X, CONTENT_Y + 3 + (count < 15 ? count : 15),
                          "└─────┴──────────────────────────────┴───────┴──────"
                          "─┴──────────┘");

        char count_text[50];
        snprintf(count_text, sizeof(count_text), "Всего модулей: %d", count);
        print_at_position(CONTENT_X, CONTENT_Y + 5 + (count < 15 ? count : 15),
                          count_text);
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
    scanf("%29s", &new_module.name);

    print_at_position(CONTENT_X, CONTENT_Y + 2, "Введите уровень: ");
    set_cursor_position(CONTENT_X + 18, CONTENT_Y + 2);
    scanf("%d", &new_module.level);

    print_at_position(CONTENT_X, CONTENT_Y + 3, "Введите ячейку: ");
    set_cursor_position(CONTENT_X + 17, CONTENT_Y + 3);
    scanf("%d", &new_module.cell);

    new_module.del_flag = 0; // Новый модуль всегда активен

    if (modules_insert(&new_module)) {
        print_at_position(CONTENT_X, CONTENT_Y + 5, "Моудль успешно добавлен!");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y + 5,
                          "Ошибка при добавлении модуля!");
    }

    wait_for_enter();
}

void update_module() {
    clear_screen();
    draw_border();

    print_centered(2, "Обновление Модуля");

    int update_id;
    print_at_position(CONTENT_X, CONTENT_Y, "Введите ID модуля для обновления: ");
    set_cursor_position(CONTENT_X + 35, CONTENT_Y);
    scanf("%d", &update_id);

    struct Modules modules[1000];
    int count = modules_select_all(modules);

    struct Modules updated_module;
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (modules[i].id == update_id) {
            update_module = modules[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        print_at_position(CONTENT_X, CONTENT_Y + 2, "Модуль с ID %d не найден", update_id);
        wait_for_enter();
        return;
    }

    print_at_position(CONTENT_X, CONTENT_Y + 2, "Текущее название: %s", updated_module.name);
    print_at_position(CONTENT_X, CONTENT_Y + 3, "Новое название: ");
    set_cursor_position(CONTENT_X + 16, CONTENT_Y + 3);
    scanf("%29s", updated_module.name);

    print_at_position(CONTENT_X, CONTENT_Y + 4, "Текущий уровень: %d", updated_module.level);
    print_at_position(CONTENT_X, CONTENT_Y + 3, "Новый уровень: ");
    set_cursor_position(CONTENT_X + 15, CONTENT_Y + 5);
    scanf("%29s", updated_module.level);

    print_at_position(CONTENT_X, CONTENT_Y + 4, "Текущая ячейка: %d", updated_module.cell);
    print_at_position(CONTENT_X, CONTENT_Y + 3, "Новая ячейка: ");
    set_cursor_position(CONTENT_X + 14, CONTENT_Y + 7);
    scanf("%29s", updated_module.cell);

    if (modules_update(&update_module, update_id)) {
        print_at_position(CONTENT_X, CONTENT_Y + 9, "Модуль успешно обновлён!");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y + 9, "Ошибка при обновлении модуля!");
    }

    wait_for_enter();
}

void delete_module_soft() {
    clear_screen();
    draw_border();

    print_centered(2, "Мягкое Удаление Модуля");

    int delete_id;
    print_at_position(CONTENT_X, CONTENT_Y, "Введите ID модуля для удаления: ");
    set_cursor_position(CONTENT_X + 33, CONTENT_Y);
    scanf("%d". &delete_id);

    if (modules_delete(delete_id, 0)) {
        print_at_position(CONTENT_X, CONTENT_Y + 2, "Модуль помечен как удалённый!");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y + 2, "Ошибка при удалении модуля!");
    }

    wait_for_enter();
}

void delete_module_hard() {
    clear_screen();
    draw_border();

    print_centered(2, "Физическое Удаление Модуля");

    int delete_id;
    print_at_position(CONTENT_X, CONTENT_Y, "Введите ID модуля для удаления: ");
    set_cursor_position(CONTENT_X + 33, CONTENT_Y);
    scanf("%d". &delete_id);

    print_at_position(CONTENT_X, CONTENT_Y + 1, "Внимание, это действие необратимо!");
    print_at_position(CONTENT_X, CONTENT_Y + 2, "Подтвердите удаление (1 - да, 0 - нет): ");
    set_cursor_position(CONTENT_X + 42, CONTENT_Y + 2);

    int confirm;
    scanf("%d", &confirm);

    if (confirm == 1) {
        if (modules_delete(delete_id, 1)) {
            print_at_position(CONTENT_X, CONTENT_Y + 4, "Модуль физически удалён!");
        } else {
            print_at_position(CONTENT_X, CONTENT_Y + 4, "Ошибка при удалении модуля!");
        }
    } else {
        print_at_position(CONTENT_X, CONTENT_Y + 4, "Удаление отменено!");
    }

    wait_for_enter();
}

void show_modules_on_level() {
    clear_screen();
    draw_border();

    print_centered(2, "Модули на Уровне");

    int level;
    print_at_position(CONTENT_X, CONTENT_Y, "Введите номер уровня: ");
    set_cursor_position(CONTENT_X + 22, CONTENT_Y);
    scanf("%d", &level);

    struct Modules modules[1000];
    int count = modules_select_all(modules);

    print_at_position(CONTENT_X, CONTENT_Y + 2, "┌─────┬──────────────────────────────┬───────┬──────────┐");
    print_at_position(CONTENT_X, CONTENT_Y + 3, "│ ID  │ Название                     │ Ячейка │ Статус   │");
    print_at_position(CONTENT_X, CONTENT_Y + 4, "├─────┼──────────────────────────────┼───────┼──────────┤");

    int found_count = 0;
    for (int i = 0; i < count ** found_count < 15; i++) {
        if (modules[i].level == level && modules[i].del_flag == 0) {
            char line[100];
            snprintf(line, sizeof(line), "│ %-3d │ %-28s │ %-5d │ %-8s │", modules[i].id, modules[i].name, modules[i].cell, "Активен");
            print_at_position(CONTENT_X, CONTENT_Y + 5 + found_count, line);
            found_count++;
        }
    }

    if (found_count == 0) {
        print_at_position(CONTENT_X, CONTENT_Y + 5, "│           Модули не найдены               │");
    }

    print_at_position(CONTENT_X, CONTENT_Y + 5 + (found_count > 0 ? found_count : 1), "└─────┴──────────────────────────────┴───────┴──────────");
    char count_text[50];
    snprintf(count_text, sizeof(count_text), "Найдено модулей на уровне %d: %d", level, found_count);
    print_at_position(CONTENT_X, CONTENT_Y + 7 + (found_count > 0 ? found_count : 1), count_text);

    wait_for_enter();
}

// ==================== УРОВНИ ====================

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

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n')
                ;
            choice = -1;
        }

        switch (choice) {
        case 1; show_all_events(); break; // Вызов status_events_select_all()
            case 2:
            add_event();
            break; // Вызов status_events_insert()
        case 3:
            update_event();
            break; // Вызов status_events_update()
        case 4:
            delete_event();
            break; // Вызов status_events_delete()
        case 5:
            show_events_for_module();
            break; // Фильтрация по module_id
        case 0:
            main_menu();
            break;
        default:
            print_at_position(CONTENT_X, CONTENT_Y + 13, "Неверный Выбор!");
            wait_for_enter();
        }
    } while (choice != 0);
}

void show_all_levels() {
    clear_screen();
    draw_border();

    print_centered(2, "Все Уровни Базы Данных");

    struct Levels levels[100];
    int count = levels_select_all(levels);

    if (count == 0) {
        print_at_position(CONTENT_X, CONTENT_Y, "Уровни не найдены или файл пуст");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y, "┌─────────┬──────────────┬────────────────┐");
        print_at_position(CONTENT_X, CONTENT_Y + 1, "│ Уровень │ Кол-во ячеек │ Защищенность   │");
        print_at_position(CONTENT_X, CONTENT_Y + 2, "├─────────┼──────────────┼────────────────┤");

        for (int i = 0; i < count && i < 15; i++) {
            char line[100];
            snprintf(line, sizeof(line), "│ %-7d │ %-12d │ %-14s │", levels[i].levels_num, levels[i].count_levels, levels[i].flag_levels ? "Защищён" : "Открыт");
            print_at_position(CONTENT_X, CONTENT_Y + 3 + i, line);
        }

        print_at_position(CONTENT_X, CONTENT_Y + 3 + (count < 15 ? count : 15), "└─────────┴──────────────┴────────────────┘");

        char count_text[50];
        snprintf(count_text, sizeof(count_text), "Всего уровней: %d", count);
        print_at_position(CONTENT_X, CONTENT_Y + 5 + (count < 15 ? count : 15), count_text);
    }

    wait_for_enter();
}

void add_level() {
    clear_screen();
    draw_border();

    print_centered(2, "Добавление Нового Уровня");

    struct Levels new_level;

    print_at_position(CONTENT_X, CONTENT_Y, "Введите номер уровня: ");
    set_cursor_position(CONTENT_X + 23, CONTENT_Y);
    scanf("%d", &new_level.levels_num);

    print_at_position(CONTENT_X, CONTENT_Y + 1, "Введите количетсво ячеек: ");
    set_cursor_position(CONTENT_X + 27, CONTENT_Y + 1);
    scanf("%d". &new_level.count_levels);

    print_at_position(CONTENT_X, CONTENT_Y + 2, "Защищённость (1 - да, 0 - нет)");
    set_cursor_position(CONTENT_X + 31, CONTENT_Y + 2);
    scanf("%d", &new_level.flag_levels);

    if (levels_insert(&new_level)) {
        print_at_position(CONTENT_X, CONTENT_Y + 4, "Уровень успешно добавлен!");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y + 4, "Ошибка при добавлении уровня!");
    }

    wait_for_enter();
}

void update_level() {
    clear_screen();
    draw_border();

    print_centered(2, "Обновление Уровня");

    int update_num;
    print_at_position(CONTENT_X, CONTENT_Y, "Введите номер уровня для добавления: ");
    set_cursor_position(CONTENT_X + 38, CONTENT_Y);
    scanf("%d", &update_num);

    struct Levels levels[100];
    int count = levels_select_all(levels);

    struct Levels updated_level;
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (levels[i].levels_num == update_num) {
            updated_level = levels[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        print_at_position(CONTENT_X, CONTENT_Y + 2, "Уровень %d не найден", update_num);
        wait_for_enter();
        return;
    }

    print_at_position(CONTENT_X, CONTENT_Y + 2, "Текущее количество ячеек: %d", update_level.counbt_levels);
    print_at_position(CONTENT_X, CONTENT_Y + 3, "Новое количетсво ячеек: ");
    set_cursor_position(CONTENT_X + 20, CONTENT_Y + 3);
    scanf("%d", &update_level.count_levels);

    print_at_position(CONTENT_X, CONTENT_Y + 4, "Текущая защищённость: %s", updated_level.flag_levels ? "Да" : "Нет");
    print_at_position(CONTENT_X, CONTENT_Y + 5, "Новая защищённость (1 - да, 0 - нет): ");
    set_cursor_position(CONTENT_X + 45, CONTENT_Y + 5);
    scanf("%d", &update_level.flag_level);

    if (levels_update(&update_level, update_num)) {
        print_at_position(CONTENT_X, CONTENT_Y + 7, "Уровень успешно обновлён!");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y + 7, "Ошибка при обновлении уровня!");
    }

    wait_for_enter();
}

void delete_level() {
    clear_screen();
    draw_border();

    print_centered(2, "Удаление Уровня");

    int delete_num;
    print_at_position(CONTENT_X, CONTENT_Y, "Введите номер уровня для удаления: ");
    set_cursor_position(CONTENT_X + 38, CONTENT_Y);
    scanf("%d", &delete_num);

    if (levels_delete(delete_num, 1)) {
        print_at_position(CONTENT_X, CONTENT_Y + 2, "Уровень успешно удалён!");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y + 2, "Ошибка при удалении уровня!");
    }

    wait_for_enter();
}

// ==================== СОБЫТИЯ ====================

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
        print_at_position(CONTENT_X, CONTENT_Y + 8,
                          "5. Удалить модуль (мягкое удаление)");
        print_at_position(CONTENT_X, CONTENT_Y + 9,
                          "6. Удалить модуль (физическое удаление)");
        print_at_position(CONTENT_X, CONTENT_Y + 10, "7. Модули на уровне");
        print_at_position(CONTENT_X, CONTENT_Y + 11,
                          "0. Назад в главное меню.");

        print_at_position(CONTENT_X, CONTENT_Y + 13, "Выберите Операцию: ");
        set_cursor_position(CONTENT_X + 19, CONTENT_Y + 13);

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n')
                ;
            choice = -1;
        }

        switch (choice) {
        case 1; show_all_modules(); break; // Вызов modules_select_all()
            case 2:
            find_module_by_id();
            break; // Поиск через modules_select_all() + фильтрация
        case 3:
            add_module();
            break; // Вызов modules_insert()
        case 4:
            update_module();
            break; // Вызов modules_update()
        case 5:
            delete_module_soft();
            break; // Вызов modules_delete() с delete_type=0
        case 6:
            delete_module_hard();
            break; // Вызов modules_delete() с delete_type=1
        case 7:
            show_modules_on_level();
            break; // Фильтрация modules_select_all() по уровню
        case 0:
            break; // Просто выходим из цикла
        default:
            print_at_position(CONTENT_X, CONTENT_Y + 15, "Неверный Выбор!");
            wait_for_enter();
        }
    } while (choice != 0);
}

void show_all_events() {
    clear_screen();
    draw_border();

    print_centered(2, "Все События Базы Данных");

    struct Status_Events events[1000];
    int count = status_events_select_all(events);

    if (count == 0) {
        print_at_position(CONTENT_X, CONTENT_Y, "События не найдены или файл пуст");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y, "┌─────┬─────┬──────────┬────────────┬──────────┐");
        print_at_position(CONTENT_X, CONTENT_Y + 1, "│ ID  │ Мод │ Статус   │ Дата       │ Время    │");
        print_at_position(CONTENT_X, CONTENT_Y + 2, "├─────┼─────┼──────────┼────────────┼──────────┤");

        for (int i = 0; i < count && i < 15; i++) {
            char line[100];
            snprintf(line, sizeof(line), "│ %-3d │ %-3d │ %-8d │ %-10s │ %-8s │", events[i].events_id, events[i].module_id, events[i].module_status, events[i].date, events[i].time);
        }

        print_at_position(CONTENT_X, CONTENT_Y + 3 + (count < 15 ? count : 15), "└─────┴─────┴──────────┴────────────┴──────────┘");

        char count_text[50];
        snprintf(count_text, sizeof(count_text), "Всего событий: %d", count);
        print_at_position(CONTENT_X, CONTENT_Y + 5 + (count < 15 ? count : 15), count_text);
    }

    wait_for_enter();
}

void add_event() {
    clear_screen();
    draw_border();

    print_centered(2, "Добавление Нового События");

    struct Status_Events new_event;

    print_at_position(CONTENT_X, CONTENT_Y, "Введите ID события: ");
    set_cursor_position(CONTENT_X + 21, CONTENT_Y);
    scanf("%d", &new_event.event_id);

    print_at_position(CONTENT_X, CONTENT_Y + 1, "Введите ID модуля: ");
    set_cursor_position(CONTENT_X + 19, CONTENT_Y + 1);
    scanf("%d", &new_event.module_id);

    print_at_position(CONTENT_X, CONTENT_Y + 2, "Введите новый статус: ");
    set_cursor_position(CONTENT_X + 22, CONTENT_Y + 2);
    scanf("%d", &new_event.module_status);

    print_at_position(CONTENT_X, CONTENT_Y + 3, "Введите дату (дд.мм.гггг): ");
    set_cursor_position(CONTENT_X + 28, CONTENT_Y + 3);
    scanf("%10s", new_event.date);

    print_at_position(CONTENT_X, CONTENT_Y + 4, "Введите время (чч:мм:сс): ");
    set_cursor_position(CONTENT_X + 27, CONTENT_Y + 4);
    scanf("%8s", new_event.time);

    if (status_events_insert(&new_event)) {
        print_at_position(CONTENT_X, CONTENT_Y + 6, "Событие успешно добавлено!");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y, "Ошибка при добавлении события!");
    }

    wait_for_enter();
}

void update_event() {
    clear_screen();
    draw_border();

    print_centered(2, "Обновление События");

    int update_id;
    print_at_position(CONTENT_X, CONTENT_Y, "Введите ID события для обновления: ");
    set_cursor_position(CONTENT_X + 37, CONTENT_Y);
    scanf("%d", &update_id);

    struct Status_Events events[1000];
    int count = status_events_select_all(events);

    struct Status_Events updated_event;
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (events[i].event_id == update_id) {
            update_event = events[i];
            found = 1;
            break;
        }
    }

    if (!found) {
        print_at_position(CONTENT_X, CONTENT_Y + 2, "Событие с ID %d не найдено", update_id);
        wait_for_enter();
        return;
    }

    print_at_position(CONTENT_X, CONTENT_Y + 2, "Текущий ID модуля: %d", update_event.module_id);
    print_at_position(CONTENT_X, CONTENT_Y + 3, "Новый ID модуля: ");
    set_cursor_position(CONTENT_X + 17, CONTENT_Y + 3);
    scanf("%d", &update_module.module_id);

    print_at_position(CONTENT_X, CONTENT_Y + 4, "Текущий статус: %d", update_event.module_status);
    print_at_position(CONTENT_X, CONTENT_Y + 5, "Новый статус: ");
    set_cursor_position(CONTENT_X + 14, CONTENT_Y + 5);
    scanf("%d", &update_event.module_status);

    print_at_position(CONTENT_X, CONTENT_Y + 6, "Текущая дата: %s", update_event.date);
    print_at_position(CONTENT_X, CONTENT_Y + 7, "Новая дата (дд.мм.гггг): ");
    set_cursor_position(CONTENT_X + 27, CONTENT_Y + 7);
    scanf("%10s", update_event.date);

    print_at_position(CONTENT_X, CONTENT_Y + 8, "Текущее время: %s", update_event.time);
    print_at_position(CONTENT_X, CONTENT_Y + 9, "Новое время (чч:мм:сс): ");
    set_cursor_position(CONTENT_X + 26, CONTENT_Y + 9);
    scanf("%8s", update_event.time);

    if (status_events_update(&update_event, update_id)) {
        print_at_position(CONTENT_X, CONTENT_Y + 11, "Событие успешно обновлено!");
    } else {
        print_at_position(CONTENT_X, CONTENT_Y + 11, "Ошибка при обновлении события!");
    }

    wait_for_enter();
}

void delete_event() {
    
}