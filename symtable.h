
/*-------------------------------------------------------------------*/
/* symtable.h                                                        */
/* Author: Kai Obinata                                               */
/*-------------------------------------------------------------------*/

#ifndef SYMTABLE_INCLUDED
#define SYMTABLE_INCLUDED

/*  A SymTable_T object is... */

typedef struct SymTable* SymTable_T;

/*-------------------------------------------------------------------*/

/* XX Return a new Stack_T object, or NULL if insufficient memory is
   available. */

SymTable_T SymTable_new(void);

/*-------------------------------------------------------------------*/

/* XX Free oStack. */

void SymTable_free(SymTable_T oSymTable);

/*-------------------------------------------------------------------*/

/*  */

size_t SymTable_getLength(SymTable_T oSymTable);

/*-------------------------------------------------------------------*/

/*  */

int SymTable_put(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue);

/*-------------------------------------------------------------------*/

/*  */

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue);

/*-------------------------------------------------------------------*/

/*  */

int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/*-------------------------------------------------------------------*/

/*  */

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/*-------------------------------------------------------------------*/

/*  */

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*-------------------------------------------------------------------*/

/* XX Apply function *pfApply to each element of oStack, passing
   pvExtra as an extra argument.  That is, for each element pvItem
   of oStack, call (*pfApply)(pvItem, pvExtra). */

void SymTable_map(SymTable_T oSymTable,
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
    const void *pvExtra);

#endif
