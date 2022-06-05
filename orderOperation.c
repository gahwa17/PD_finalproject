#include "orderOperation.h"

//initial order queue
struct orderQueue order_queue = {NULL,NULL};  
static int num_order = 0;
void showOrder(struct order *ptr)
{
    //print: orderId CustomerName inventoryIds[5] inventoryQuantity[5] totalPrice orderDate
    struct tm *order_time;
    order_time = gmtime(&ptr->orderDate);
    printf("%d\t%s\t%d %d\t%d %d\t%d %d\t%d %d\t%d %d\t%d\t%d/%d/%d\n",
        ptr->orderId, ptr->CustomerName, ptr->inventoryIds[0], ptr->inventoryQuantity[0],
        ptr->inventoryIds[1], ptr->inventoryQuantity[1], ptr->inventoryIds[2], ptr->inventoryQuantity[2],
        ptr->inventoryIds[3], ptr->inventoryQuantity[3], ptr->inventoryIds[4], ptr->inventoryQuantity[4],
        ptr->totalPrice,(1900+order_time->tm_year), (1+order_time->tm_mon),order_time->tm_mday);   
}

BOOL isEmpty(void)
{  
    return !(order_queue.head) ? true : false;
}

BOOL addOrder(char CustomerName[], int inventoryIds[], int inventoryQuantity[], int totalPrice)
{
    static int orderID = 0;
    num_order++;

    //declare order_new
    struct order *order_new = malloc(sizeof(struct order));
    if (!order_new)
    {
        return false;
    }

    //initalize order_new
    strcpy(order_new->CustomerName , CustomerName);
    order_new->orderId = orderID++;
    for(int i = 0 ; i < 20 ; i++)
    {
        order_new->inventoryIds[i] = inventoryIds[i];
        order_new->inventoryQuantity[i] = inventoryQuantity[i];
    }
    order_new->totalPrice = totalPrice;
    time(&order_new->orderDate);
    //order_new->orderDate = orderDate;
    order_new->prev = NULL;
    order_new->next = NULL;
    
    //queue is empty. enqueue order_new.
    if (isEmpty()) 
    {
        order_queue.head = order_new;
        order_queue.tail = order_new;
        return true;
    }
    
    //queue is not empty. enqueue order_new. 
    order_queue.tail->next = order_new;
    order_new->prev = order_queue.tail;
    order_queue.tail = order_new;
    
    return true;
}

void insertion_sort(int total_price[],struct order *order[], int n) {
  for (int i = 0; i < n; i++) {
    int j = i;
    while (j > 0 && total_price[j - 1] > total_price[j]) 
    {
        int temp = total_price[j];
        total_price[j] = total_price[j - 1];
        total_price[j - 1] = temp;

        struct order *temp_order = order[j];
        order[j] = order[j - 1];
        order[j - 1] = temp_order;

        j--;
    }
  }
}

//order(0:increasing, 1:decreasing) order_by(0:id, 1:total price )
void sortOrder(int order, int order_by)
{
    if(isEmpty())
    {
        printf("There is no order.\n");
        return;
    }

    struct order *ptr;
    if(order_by == 0)
    {
        if(order == 0)
        {
            for(ptr = order_queue.tail ; ptr != NULL ; ptr = ptr->prev)
            {
                showOrder(ptr);
            }
        }
        else if(order == 1)
        {
            for(ptr = order_queue.head ; ptr != NULL ; ptr = ptr->next)
            {
                showOrder(ptr);
            }
        }
    }
    else if(order_by == 1)
    {
        struct order **price_order = malloc( num_order * sizeof(struct order *));
        int *total_price = malloc(num_order * sizeof( int ));
        int i = 0;
        for(ptr = order_queue.tail ; ptr != NULL ; ptr = ptr->prev)
        {
            total_price[i] = ptr->totalPrice;
            price_order[i++] = ptr;
        }

        insertion_sort(total_price,price_order,num_order);
         
        if(order == 0)
        {   
            for(i = 0;i<num_order;i++)
            {
                showOrder(price_order[i]);                
            }
        }
        else if(order == 1)
        {
            for(i = num_order-1 ; i >= 0 ; i++)
            {
                showOrder(price_order[i]);                 
            }
        }
    }
}

void searchOrder(int orderId){
    if(isEmpty()){
        printf("There is no order.\n");
        return;
    }
    else{
        struct order *cur = order_queue.head;
        while (cur->next != NULL){
            if(cur->orderId == orderId){
                printf("Find order:%d!\n", cur->orderId);
                return;
            }
            else{
                cur = cur->next;
            }
        }
        printf("Order not exist\n");
    }
}

BOOL completeOrder(){
    if(isEmpty()){
        printf("There is no order.\n");
        return false;
    }
    else{
        num_order--;
        struct order *toComplete = order_queue.head;
        order_queue.head = order_queue.head->next;
        printf("Order:%d complete!\n", toComplete->orderId); //for debug
        free(toComplete);
        return true;
    }
}

BOOL cancelOrder(int orderId){
    if(isEmpty()){
        printf("There is no order.\n");
        return false;
    }
    else{
        struct order *cur = order_queue.head;
        while (cur->next != NULL){
            if(cur->orderId == orderId){
                struct order *toCancel = cur;
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                printf("Order:%d canceled!\n", toCancel->orderId); //for debug
                free(toCancel);
                return true;
            }
            else{
                cur = cur->next;
            }
        }
        printf("Order not exist\n");
        return false;
    }
}
