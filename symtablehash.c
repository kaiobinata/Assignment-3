/*-------------------------------------------------------------------*/
/* symtablehash.c                                                    */
/* Author: Kai Obinata                                               */
/*-------------------------------------------------------------------*/

#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*-------------------------------------------------------------------*/

enum { BUCKET_COUNT = 64 };

struct Binding
{
    // Key is a string
    const char* pcKey;
    // An Item's value is an arbitrary type of data
    const void* pvValue;
    /* The address of the next Binding. */
    struct Binding* next;
};

struct Library
{
       struct Binding* buckets[BUCKET_COUNT];
};

struct SymTable
{
    struct Library* polibrary;
    size_t uBucketCount;
    size_t uItemCount;
};

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
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/

/*  description */

SymTable_T SymTable_new(void)
{
  SymTable_T oSymTable;
  
  oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
   if (oSymTable == NULL)
      return NULL;

  oSymTable->pnFirstNode = NULL;
  return oSymTable;
}

/*-------------------------------------------------------------------*/

/*  description */

void SymTable_free(SymTable_T oSymTable)
{
   /*
   struct StackNode *psCurrentNode;
   struct StackNode *psNextNode;

   assert(oStack != NULL);

   for (psCurrentNode = oStack->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psNextNode)
   {
      psNextNode = psCurrentNode->psNextNode;
      free(psCurrentNode);
   }

   free(oStack);
   */
}

/*-------------------------------------------------------------------*/

/*  description */

size_t SymTable_getLength(SymTable_T oSymTable)
{
    // code
}

/*-------------------------------------------------------------------*/

/*  description */

int SymTable_put(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue)
{
   /* 
   struct StackNode *psNewNode;

   assert(oStack != NULL);

   psNewNode = (struct StackNode*)malloc(sizeof(struct StackNode));
   if (psNewNode == NULL)
      return 0;

   psNewNode->pvItem = pvItem;
   psNewNode->psNextNode = oStack->psFirstNode;
   oStack->psFirstNode = psNewNode;
   return 1;
   */
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue)
{
   /*
   // void *Stack_pop(Stack_T oStack)
   const void *pvItem;
   struct StackNode *psNextNode;

   assert(oStack != NULL);
   assert(oStack->psFirstNode != NULL);

   pvItem = oStack->psFirstNode->pvItem;
   psNextNode = oStack->psFirstNode->psNextNode;
   free(oStack->psFirstNode);
   oStack->psFirstNode = psNextNode;
   return (void*)pvItem;
   */
}

/*-------------------------------------------------------------------*/

/*  description */

int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
   /*
   // void *Stack_pop(Stack_T oStack)
   const void *pvItem;
   struct StackNode *psNextNode;

   assert(oStack != NULL);
   assert(oStack->psFirstNode != NULL);

   pvItem = oStack->psFirstNode->pvItem;
   psNextNode = oStack->psFirstNode->psNextNode;
   free(oStack->psFirstNode);
   oStack->psFirstNode = psNextNode;
   return (void*)pvItem;
   */
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
   /*
   // void *Stack_pop(Stack_T oStack)
   const void *pvItem;
   struct StackNode *psNextNode;

   assert(oStack != NULL);
   assert(oStack->psFirstNode != NULL);

   pvItem = oStack->psFirstNode->pvItem;
   psNextNode = oStack->psFirstNode->psNextNode;
   free(oStack->psFirstNode);
   oStack->psFirstNode = psNextNode;
   return (void*)pvItem;
   */
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
   /*
   // void *Stack_pop(Stack_T oStack)
   const void *pvItem;
   struct StackNode *psNextNode;

   assert(oStack != NULL);
   assert(oStack->psFirstNode != NULL);

   pvItem = oStack->psFirstNode->pvItem;
   psNextNode = oStack->psFirstNode->psNextNode;
   free(oStack->psFirstNode);
   oStack->psFirstNode = psNextNode;
   return (void*)pvItem;
   */
}

/*-------------------------------------------------------------------*/

/*  description */

void SymTable_map(SymTable_T oSymTable,
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
    const void *pvExtra)
{
    /*
    struct StackNode *psCurrentNode;

   assert(oStack != NULL);
   assert(pfApply != NULL);

   for (psCurrentNode = oStack->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
      (*pfApply)((void*)psCurrentNode->pvItem, (void*)pvExtra);
      */
}