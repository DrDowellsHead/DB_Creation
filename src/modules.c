#include "shared.h"

int modules_select_all(struct Modules *module) {
    return db_select_all("modules.db", module, sizeof(struct Modules));
}

int modules_insert(struct Modules *new_module) {
    return db_insert("modules.db", new_module, sizeof(struct Modules));
}

int modules_update(struct Modules *update_module, int id) {
    return db_update("modules.db", update_module, sizeof(struct Modules), id);
}

int modules_delete(int id, int delete_type) {
    return db_delete("modules.db", id, sizeof(struct Modules), delete_type);
}

int modules_save_all(struct Modules *module, int count) {
    return db_save_all("modules.db", module, sizeof(struct Modules), count);
}