#ifndef Generics_h
#define Generics_h

#define G_GET_NAME(itemName, NAME) __G_GET_NAME(itemName, NAME)
#define __G_GET_NAME(itemName, NAME) NAME##_##itemName

#define G_CON_NAME(itemName, NAME) __G_CON_NAME(itemName, NAME)
#define __G_CON_NAME(itemName, NAME) new_##NAME##_##itemName

#define G_INIT_NAME(itemName, NAME) __G_INIT_NAME(itemName, NAME)
#define __G_INIT_NAME(itemName, NAME) init_##NAME##_##itemName

#endif