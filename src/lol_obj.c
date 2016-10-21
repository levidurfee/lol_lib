#include "lol_obj.h"

lol_Obj lol_obj_new(void) {
    lol_Obj lol_obj;
    lol_obj.add_p = lol_add;
    lol_obj.sub_p = lol_sub;
    return lol_obj;
}

int lol_add(int a, int b) {
    return a + b;
}

int lol_sub(int a, int b) {
    return a - b;
}
