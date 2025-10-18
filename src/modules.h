#ifndef MODULES.H
#define MODULES .H

int modules_select_all(struct Modules *module);
int modules_insert(struct Modules *new_module);
int modules_update(struct Modules *update_module, int id);
int modules_delete(int id, int delete_type);
int modules_save_all(struct Modules *module, int count);

#endif