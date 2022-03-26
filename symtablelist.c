/*-------------------------------------------------------------------*/
/* symtablelist.h                                                    */
/* Author: Kai Obinata                                               */
/*-------------------------------------------------------------------*/

#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*-------------------------------------------------------------------*/


/* XX Each item is stored in a StackNode.  StackNodes are linked to
   form a list.  */

struct Node
{
    // Key is a string
    const char* pcKey;
    // An Item's value is an arbitrary type of data
    const void* pvValue;
    /* The address of the next Node. */
    struct Node* psNextNode;
};

/*-------------------------------------------------------------------*/

struct SymTable
{
    struct Node* psFirstNode;
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

  oSymTable->psFirstNode = NULL;
  oSymTable->uItemCount = 0;
  return oSymTable;
}

/*-------------------------------------------------------------------*/

/*  description */

void SymTable_free(SymTable_T oSymTable)
{
   struct Node* psCurrentNode;
   struct Node* psNextNode;

   assert(oSymTable != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psNextNode)
   {
      psNextNode = psCurrentNode->psNextNode;
      free(psCurrentNode);
   }

   free(oSymTable);
}

/*-------------------------------------------------------------------*/

/*  description */

size_t SymTable_getLength(SymTable_T oSymTable)
{
    assert(oSymTable != NULL);
    return oSymTable->uItemCount;
}

/*-------------------------------------------------------------------*/

/*  description */

int SymTable_put(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue)
{
   struct Node* psNewNode;

   assert(oSymTable != NULL);
   assert(pcKey != NULL);
   // assert(pvValue != NULL);

   if (SymTable_contains(oSymTable, pcKey)) return 0;
   
   psNewNode = (struct Node*)malloc(sizeof(struct Node));
   if (psNewNode == NULL)
      return 0;

   psNewNode->pcKey = pcKey;
   psNewNode->pvValue = pvValue;
   psNewNode->psNextNode = oSymTable->psFirstNode;
   oSymTable->psFirstNode = psNewNode;
   oSymTable->uItemCount++;
   return 1;
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue)
{
    struct Node* psCurrentNode;
    const void* pvOldValue;
    
   assert(oSymTable != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
   {
      if (strcmp(psCurrentNode->pcKey, pcKey) == 0)
      {
          pvOldValue = psCurrentNode->pvValue;
          psCurrentNode->pvValue = pvValue;
          // check if const is giving errors.
          return (void*)pvOldValue;
      }
   }

return NULL;
}

/*-------------------------------------------------------------------*/

/*  description */

int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
    struct Node* psCurrentNode;
    
   assert(oSymTable != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
   {
      if (strcmp(psCurrentNode->pcKey, pcKey) == 0) 
        return 1;
   }

return 0;
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
    struct Node* psCurrentNode;
    
   assert(oSymTable != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
   {
      if (strcmp(psCurrentNode->pcKey, pcKey) == 0) 
        return psCurrentNode->pvValue;
   }

return NULL;
}

/*-------------------------------------------------------------------*/

/*  description */

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    struct Node* psCurrentNode;
    struct Node* psPriorNode;
    const void* pvValue;
    
   assert(oSymTable != NULL);

   /* case 1: pcKey is in the FirstNode */
   psCurrentNode = oSymTable->psFirstNode;
   if (strcmp(psCurrentNode->pcKey, pcKey) == 0) 
   {
          pvValue = psCurrentNode->pvValue;
          oSymTable->psFirstNode = psCurrentNode->psNextNode;
          free(psCurrentNode);
          // check if const is giving errors.
          return (void*)pvValue;
   }

   /* case 2: pcKey is in any other Node */
   while (psCurrentNode != NULL)
   {
      if (strcmp(psCurrentNode->pcKey, pcKey) == 0)
      {
          pvValue = psCurrentNode->pvValue;
          psPriorNode->psNextNode = psCurrentNode->psNextNode;
          free(psCurrentNode);
          // check if const is giving errors.
          return (void*)pvValue;
      }
      
      psPriorNode = psCurrentNode;
      psCurrentNode = psCurrentNode->psNextNode
   }

return NULL;
}

/*-------------------------------------------------------------------*/

/*  description */

void SymTable_map(SymTable_T oSymTable,
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
    const void *pvExtra)
{
    struct Node* psCurrentNode;

   assert(oSymTable != NULL);
   assert(pfApply != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
    // check if casts are necessary.
      (*pfApply)((const char*)psCurrentNode->pcKey, 
      (void*)psCurrentNode->pvValue, (void*)pvExtra);
}
