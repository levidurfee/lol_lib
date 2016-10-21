#ifndef LOL_OBJ_H
#define LOL_OBJ_H
typedef struct lol_Objs {
    int (*add_p)(int, int);
    int (*sub_p)(int, int);
} lol_Obj;

lol_Obj lol_obj_new(void);
int lol_add(int a, int b);
int lol_sub(int a, int b);
#endif
