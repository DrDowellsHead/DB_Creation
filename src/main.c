#include "display.h"
#include <stdio.h>

int main() {
    printf("Загрузка системы управления базой данных...\n");
    printf("Активация протокола обезвреживания ИИ...\n");

    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        for (int j = 0; j < 100000000; j++)
            ;
    }
    printf("\n\n");

    main_menu();

    return 0;
}