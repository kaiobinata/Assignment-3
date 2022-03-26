/*-------------------------------------------------------------------*/
/* symtablehash.c                                                    */
/* Author: Kai Obinata                                               */
/*-------------------------------------------------------------------*/

#include "symtable.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

/*-------------------------------------------------------------------*/

enum { INIT_BUCKET_COUNT = 509 };
/* enum { 509, 1021, 2039, 4093, 8191, 16381, 32749, 65521 } */

/* In lieu of a boolean data type. */
enum {FALSE, TRUE};

/*-------------------------------------------------------------------*/

struct Binding
{
    /* Key is a string */
    char* pcKey;
    /* An Item's value is an arbitrary type of data */
    const void* pvValue;
    /* The address of the next Binding. */
    struct Binding* psNextBind;
};

struct SymTable
{
    struct Binding** ppsBindings;
    size_t uBucketCount;
    size_t uItemCount;
};

/*-------------------------------------------------------------------*/

/*  description */

SymTable_T SymTable_new(void)
{
  SymTable_T oSymTable;
  
  oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
   if (oSymTable == NULL)
      return NULL;

  /* Does Initializing an array of Bindings make them all NULL? */
  oSymTable->ppsBindings = (struct Binding**)
  malloc(INIT_BUCKET_COUNT * sizeof(struct Binding*));

  oSymTable->uBucketCount = INIT_BUCKET_COUNT;
  oSymTable->uItemCount = 0;

  return oSymTable;
}

/*-------------------------------------------------------------------*/

 /* Return a hash code for pcKey that is between 0 and uBucketCount-1,
       inclusive. */

static size_t SymTable_hash(const char *pcKey, size_t uBucketCount)
{
    const size_t HASH_MULTIPLIER = 65599;
    size_t u;
    size_t uHash = 0;
    
    assert(pcKey != NULL);
    
    for (u = 0; pcKey[u] != '\0'; u++)
    uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];
    
    return uHash % uBucketCount;
}

/*-------------------------------------------------------------------*/

/*  description */

void SymTable_free(SymTable_T oSymTable)
{
   struct Binding* psCurrentBind;
   struct Binding* psNextBind;
   size_t i;

   assert(oSymTable != NULL);

   /* Does Initializing an array of Bindings make them all NULL? */
   for (i = 0; i < oSymTable->uBucketCount; i++)
   {
      for (psCurrentBind = oSymTable->ppsBindings[i];
      psCurrentBind != NULL;
      psCurrentBind = psNextBind)
      {        
             psNextBind = psCurrentBind->psNextBind;        
             free(psCurrentBind);        
      }

   }

   free(oSymTable);
}

/*-------------------------------------------------------------------*/

/*  description */

size_t SymTable_getLength(SymTable_T oSymTable)
{
    assert(oSymTable != NULL);
    return oSymTable->uBucketCount;
}

/*-------------------------------------------------------------------*/

/*  description */

int SymTable_put(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue)
{
   struct Binding* psNewBind;
   char* pcNewKey;
   size_t uHash;

   assert(oSymTable != NULL);
   assert(pcKey != NULL);
   /* assert(pvValue != NULL); */

   if (SymTable_contains(oSymTable, pcKey)) return FALSE;
   
   psNewBind = (struct Binding*)malloc(sizeof(struct Binding));
   if (psNewBind == NULL)
      return FALSE;

   /* +1 is necessary via strlen specifications. */
   pcNewKey = (char*)malloc(strlen(pcKey) * sizeof(char) + 1);
   if (pcNewKey == NULL)
      return FALSE;
   strcpy(pcNewKey, pcKey);

   oSymTable->uItemCount++;
   /* Expansion if uItemCount > uBucketCount: Code here */

   uHash = SymTable_hash(pcKey, oSymTable->uBucketCount);
   psNewBind->pcKey = pcNewKey;
   psNewBind->pvValue = pvValue;
   psNewBind->psNextBind = oSymTable->ppsBindings[uHash];
   oSymTable->ppsBindings[uHash] = psNewBind;
   return TRUE;
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue)
{
   struct Binder* psCurrentBind;
   const void* pvOldValue;
   size_t uHash;

   assert(oSymTable != NULL);
   
   uHash = SymTable_hash(pcKey, oSymTable->uBucketCount);

   for (psCurrentBind = (*oSymTable->ppsBindings)[uHash]; 
   psCurrentBind != NULL; psCurrentBind = psCurrentBind->psNextBind)
   {
       if (strcmp(psCurrentBind->pcKey, pcKey) == 0)
       {
       pvOldValue = psCurrentBind->pvValue;
       psCurrentBind->pvValue = pvValue;
       return (void*)pvOldValue;
       }
   }

return NULL;
}

/*-------------------------------------------------------------------*/

/*  description */

int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
   struct Binder* psCurrentBind;
   size_t uHash;

   assert(oSymTable != NULL);

   uHash = SymTable_hash(pcKey, oSymTable->uBucketCount);
   for (psCurrentBind = oSymTable->ppsBindings[uHash];
       psCurrentBind != NULL;
       psCurrentBind = psCurrentBind->psNextBind)
   {
       if (strcmp(psCurrentBind->pcKey, pcKey) == 0) 
       return TRUE;
   }

return FALSE;
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
   struct Binder* psCurrentBind;
   size_t uHash;

   assert(oSymTable != NULL);
   
   uHash = SymTable_hash(pcKey, oSymTable->uBucketCount);
   for (psCurrentBind = oSymTable->ppsBindings[uHash];
       psCurrentBind != NULL;
       psCurrentBind = psCurrentBind->psNextBind)
   {
       if (strcmp(psCurrentBind->pcKey, pcKey) == 0) 
       return (void*)psCurrentBind->pvValue;
   }

return NULL;
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{    
   struct Binder* psCurrentBind;
   struct Bind* psPriorBind;
   const void* pvValue;
   size_t uHash;

   assert(oSymTable != NULL);
   
   uHash = SymTable_hash(pcKey, oSymTable->uBucketCount);
   psCurrentBind = oSymTable->ppsBindings[uHash];
   while (psCurrentBind != NULL)
   {
       if (strcmp(psCurrentBind->pcKey, pcKey) == 0)
       {
          pvValue = psCurrentBind->pvValue;

          /* case 1: pcKey is in the First Binding */
          if (psCurrentBind == oSymTable->ppsBindings[uHash])
            oSymTable->ppsBindings[uHash] = psCurrentBind->psNextBind;
          /* case 2: pcKey is in any other Bind */
          else psPriorBind->psNextBind = psCurrentBind->psNextBind;
          
          free(psCurrentBind->pcKey);
          free(psCurrentBind);
          oSymTable->uItemCount--;
          /* revisit const mismatch practice problems */
          return (void*)pvValue;
       }
      
       psPriorBind = psCurrentBind;
       psCurrentBind = psCurrentBind->psNextBind;
   }

return NULL;
}

/*-------------------------------------------------------------------*/

/*  description */

void SymTable_map(SymTable_T oSymTable,
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
    const void *pvExtra)
{
   struct Binding* psCurrentBind;
   struct Binding* psNextBind;
   size_t i;

   assert(oSymTable != NULL);
   assert(pfApply != NULL);

   /* Does Initializing an array of Bindings make them all NULL? */
   for (i = 0; i < oSymTable->uBucketCount; i++)
   {
       for (psCurrentBind = oSymTable->ppsBindings[i];
       psCurrentBind != NULL;
       psCurrentBind = psCurrentBind->psNextBind)
       /* check if casts are necessary. */
       (*pfApply)((const char*)psCurrentBind->pcKey, 
       (void*)psCurrentBind->pvValue, (void*)pvExtra);
   }

}