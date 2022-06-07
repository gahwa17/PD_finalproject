#ifndef inventoryOperation
#define inventoryOperation
#include "basic.h"
#include "myDS.h"

 void initInv(void);//initialization
 bool addInv(char name[], double prrice, int quantity, enum bookType type);//add produce
 struct category *traversaInv();//printf each item
 bool sortInv(int order, int order_by);//order(1:升序 0:降序) order_by(1:price 0:id)
 void deleteInv(int id);//delete produce
 void searchInvByID(int id);//search id and print the specific item
 void searchInvByName(char name[]);//search name and print the specific item
 void replenish(int replenish_id,int replenish_num);//replenish the inventory

 int cmpDesById(const void *a, const void *b);
 int cmpAscById(const void *a, const void *b);
 int cmpDesByPrice(const void *a, const void *b);
 int cmpAscByPrice(const void *a, const void *b);
#endif
