#ifndef LEVELS.H
#define LEVELS.H

int levels_select_all(struct Levels *level);
int levels_insert(struct Levels *new_level);
int levels_update(struct Levels *update_level, int id);
int levels_delete(int id, int delete_type);
int levels_save_all(struct Levels *level, int count);

#endif