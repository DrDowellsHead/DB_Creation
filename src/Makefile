CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
CPPCHECK = ccpchek --enable=all --suppress=missingIncludeSystem
CLANG_FORMAT = clang-format -i

SRC = main.c display.c auxiliary_menu_func.c modules.c levels.c status_events.c shared.c
OBJ = $(SRC:.c=.o)
TARGET = modules_db

all: build_db

build_db: $(OBJ)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
		@echo "Программа успешно собрана!"

main.o: main.c display.h
		$(CC) $(CFLAGS) -c main.c

display.o: display.c display.h modules.h levels.h status_events.h
		$(CC) $(CFLAGS) -c display.c

auxiliary_menu_func.o: auxiliary_menu_func.c auxiliary_menu_func.h display.h modules.h levels.h status_events.h
		$(CC) $(CFLAGS) -c auxiliary_menu_func.c

modules.o: modules.c modules.h shared.h
		$(CC) $(CFLAGS) -c modules.c

levels.o: levels.c levels.h shared.h
		$(CC) $(CFLAGS) -c levels.c

status_events.o: status_events.c status_events.h shared.h
		$(CC) $(CFLAGS) -c status_events.c

shared.o: shared.c shared.h
		$(CC) $(CFLAGS) -c shared.c

format:
		$(CLANG_FORMAT) *.c *.h
		@echo "Код отформатирован!"

check:
		$(CPPCHECK) *.c
		@echo "Статический анализ завершён!"

clean:
		rm -f $(OBJ) $(TARGET)
		@echo "Очистка завершена!"

rebuild: clean build_db

test: build_db
		@echo "Запуск тестов..."
		./$(TARGET)

.PHONY: all build_db format check clean rebuild test