#include "display.h"
#include "levels.h"
#include "modules.h"
#include "status_events.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 25

void clear_screen() { printf("\033[2J\033[1;1H"); }

void draw_border() {

    printf("╔");
    for (int x = 0; x < WIDHT - 2; x++)
        printf("═");
    printf("╗\n");

    for (int y = 0; y < HEIGHT - 2; y++) {
        printf("║");
        for (int x = 0; x < WIDHT - 2; x++)
            printf(" ");
        printf("║\n");
    }

    printf("╚");
    for (int x = 0; x < WIDHT - 2; x++)
        printf("═");
    printf("╝\n");
}

void set_cursor_position(int x, int y) { printf("\033[%d;%dH", y, x); }

void print_at_position(int x, int y, const char *text) {
    set_cursor_position(x, y);
    printf("%s", text);
}

void print_centered(int y, const char *text) {
    int x = (WIDHT - strlen(text)) / 2;
    print_at_position(x, y, text);
}

void wait_for_enter() {
    print_at_position(CONTENT_X, CONTENT_Y + 18,
                      "Нажмите Enter для продолжения...");
    getchar();
    getchar(); // Два getchar() потому что первый забирает \n от scanf
}

void main_menu() {
    int choice;

    do {

        clear_screen();
        draw_border();

        print_centered(2, "Система Управления Базой Данных");

        print_at_position(CONTENT_X, CONTENT_Y + 2, "Главное Меню:");
        print_at_position(CONTENT_X, CONTENT_Y + 4, "1. Управление Модулями");
        print_at_position(CONTENT_X, CONTENT_Y + 5, "2. Управление Уровнями");
        print_at_position(CONTENT_X, CONTENT_Y + 6, "3. Управлеие Событиями");
        print_at_position(CONTENT_X, CONTENT_Y + 7, "4. Обезвреживание ИИ");
        print_at_position(CONTENT_X, CONTENT_Y + 8, "0. Выход");

        print_at_position(CONTENT_X, CONTENT_Y + 10, "Выберите Опцию: ");
        set_cursor_position(CONTENT_X + 16, CONTENT_Y + 10);

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n')
                ;
            choice = -1;
        }

        switch (choice) {
        case 1:
            modules_menu();
            break;
        case 2:
            levels_menu();
            break;
        case 3:
            events_menu();
            break;
        case 4:
            ai_disabler();
            break;
        case 0:
            clear_screen();
            printf("Программа Завершена...\n");
            break;
        default:
            print_at_position(CONTENT_X, CONTENT_Y + 12,
                              "Введите, пожалуйста, верное значение.");
            wait_for_enter();
        }
    }
}
