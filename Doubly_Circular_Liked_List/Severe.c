#include"Header.h"
void insert_first(PPNODE ppHead,PPNODE ppTail,int iNo)
{
	PNODE pNewnode = NULL;
	pNewnode = (PNODE)malloc (sizeof (NODE));
	if(NULL == pNewnode)
	{
		printf  ("Memory Allocation is failed :- ");
		return ;
	}
    pNewnode->iData=iNo;
	if(NULL == *ppHead)
	{
		*ppHead =*ppTail=pNewnode ;
		 (*ppHead)->pPrev=*ppTail;
		(*ppTail)-> pNext = *ppHead;
               
		return ;
	}
	pNewnode->pNext=*ppHead;
    pNewnode->pNext->pPrev=pNewnode;
    *ppHead=pNewnode;
    (*ppHead)->pPrev=*ppTail;
	(*ppTail)->pNext = *ppHead;
	
}  

void insert_last(PPNODE ppHead,PPNODE ppTail,int iNo)
{
    PNODE pNewnode = NULL;
	pNewnode = (PNODE)malloc (sizeof (NODE));
	if(NULL == pNewnode)
	{
		printf  ("Memory Allocation is failed :- ");
		return ;
	}
    pNewnode->iData=iNo;
	if(NULL == *ppHead)
    {
        *ppHead =*ppTail=pNewnode ;
		(*ppHead)->pPrev=*ppTail;
		(*ppTail)-> pNext = *ppHead;
        return ;
	}
    (*ppTail)-> pNext =pNewnode;
    pNewnode->pPrev=*ppTail;
    *ppTail =pNewnode;
    (*ppHead)->pPrev=*ppTail;
    (*ppTail)-> pNext = *ppHead;
                
}

int count_node(PNODE pHead,PNODE pTail)
{
    int iCount = 0;
    if(NULL == pHead)
    {
         printf("\n ! Your List is Empty...!:- ");
        return 0;
    }
    do
    {
        iCount ++;
        pHead = pHead -> pNext;
   	}while(pHead != pTail -> pNext );
    return iCount;
}

void insert_at_position(PPNODE ppHead,PPNODE ppTail,int iPos,int iNo)
{
    PNODE pNewnode = NULL;
    PNODE pTemp=NULL;
    int iCounter=count_node(*ppHead,*ppTail);
        

        if(1 == iPos)
        {
                insert_first(ppHead,ppTail,iNo);
                return ;
        }
        if(iPos == iCounter +1)
        {
                insert_last(ppHead,ppTail,iNo);
                return ;
        }
        pNewnode=(PNODE)malloc (sizeof(NODE));
        if(NULL == pNewnode)
        {
                printf("Memory Allocatin is Faild :-");
                return ;
        }
        pNewnode->iData=iNo;
        pTemp=*ppHead;
        iCounter = 1;
        while(iCounter < iPos - 1)
        {
                iCounter ++;
                pTemp = pTemp -> pNext;
        }
        pNewnode -> pNext = pTemp -> pNext;
        pNewnode ->pNext -> pPrev=pNewnode;
        pTemp ->pNext = pNewnode ;
       pNewnode ->pPrev =pTemp;
        pTemp ->pNext ->pPrev =pTemp;
}

int delete_first(PPNODE ppHead,PPNODE ppTail)
{
	PNODE pTemp=NULL;
	int iDelData;	

	if(NULL == *ppHead)
	{
        printf("\n ! Your List is Empty...! :-");
		return -1;
	}
	iDelData=(*ppHead)->iData;
	if(*ppHead == *ppTail)
	{
		(*ppHead)->pNext=NULL;
		(*ppHead)->pPrev=NULL;
		free(*ppHead);
		*ppHead=*ppTail=NULL;
		return iDelData;
	}
	pTemp=*ppHead;
	*ppHead=pTemp->pNext;
	pTemp->pNext=NULL;
	pTemp->pPrev=NULL;
	(*ppHead)->pPrev=*ppTail;
	(*ppTail)->pNext=*ppHead;
	
	free(pTemp);
	pTemp=NULL;
	return iDelData;	
}

int delete_last(PPNODE ppHead,PPNODE ppTail)
{
    PNODE pTemp=NULL;
    int iDelData;
    if(NULL == *ppHead)
    {
        printf("\n ! Your List is Empty...! :-");
         return -1;
    }
    if(*ppHead == *ppTail)
    {
        (*ppHead)->pNext = NULL;
        (*ppHead)->pPrev=NULL;
        iDelData=(*ppHead)->iData;
        free(*ppHead);
        *ppHead=*ppTail=NULL;
        return iDelData;
        }
        pTemp=*ppHead;
        while(pTemp->pNext != *ppTail)
              pTemp=pTemp->pNext;

        (*ppTail)=pTemp;
        pTemp=(*ppTail)->pNext;
        pTemp->pNext=NULL;
        pTemp->pPrev=NULL;
        iDelData=pTemp->iData;
        (*ppTail)->pNext=*ppHead;
       (*ppHead)->pPrev=*ppTail;
        free(pTemp);
        pTemp=NULL;
        return iDelData;
}

int delete_at_position(PPNODE ppHead ,PPNODE ppTail , int iPos)
{
	PNODE pTemp = NULL; 
	int iDelData=count_node(*ppHead,*ppTail);
	
	if(iPos == 1)
	{
		return delete_first(ppHead,ppTail);
	}
	if(iPos == iDelData)
	{
		return delete_last(ppHead,ppTail);
	}
	pTemp = *ppHead;
	iDelData = 1;
	while(iDelData < iPos)
	{	
		iDelData ++;
		pTemp = pTemp -> pNext;
	}
	pTemp -> pPrev -> pNext = pTemp -> pNext;
	pTemp -> pNext -> pPrev = pTemp -> pPrev;
	iDelData = pTemp -> iData;
	pTemp -> pNext = NULL;
	pTemp -> pPrev = NULL;
	free (pTemp);
	pTemp = NULL;
 
	return iDelData;
	
}
int search_all(PNODE pHead,PNODE pTail,int iKey)    
{
    int iCount =0;
    if(NULL == pHead)
    {
        printf("list is empty");
        return 0;
    }
    do 
    {
        if(iKey == pHead -> iData)
            iCount ++;
        pHead = pHead ->pNext ;
    }while(pHead != pTail -> pNext);
    
    return iCount;
             
}

int search_first_occurrence(PNODE pHead,PNODE pTail,int iKey)    
{
    int iPosition =-1,iCount=0;
    do
    {
        iCount ++;
        if(iKey == pHead ->iData )
		{	
		  iPosition=iCount;
      	  break;
		}	
		pHead = pHead -> pNext;
    }while(pHead != pTail -> pNext);
    return iPosition;
}
int search_last_occurrence(PNODE pHead,PNODE pTail,int iKey)
{
 	int iPosition = 0;
    iPosition=count_node(pHead,pTail);
    do
    {
       if(iKey == pTail ->iData )
        break;
        iPosition --;
       pTail = pTail -> pPrev;
    }while(pTail != pHead -> pPrev);
    if(iKey == pTail -> iData)
        return iPosition;
    else
       return -1; 
}

void concat_list(PPNODE ppHead1,PPNODE ppTail1 ,PPNODE ppHead2,PPNODE ppTail2)
{
        if(NULL == *ppHead2)
        {
                printf("! Your List is Empty...! :- ");
                return ;
        }
        if(NULL == *ppHead1)
        {
                printf("! Your List is Empty...! :- ");
                *ppHead1 = *ppHead2;
                *ppTail1 = *ppTail2;
                *ppTail2 = *ppHead2 = NULL;
                     
                return ;
        }
         (*ppTail1) -> pNext = *ppHead2;
        (*ppHead2) -> pPrev=*ppTail1;
          *ppTail1 = *ppTail2;   
        (*ppTail1) -> pNext = *ppHead1;
        (*ppHead1) -> pPrev = *ppTail1;
         *ppTail2 = *ppHead2 = NULL;
        printf("\n\t! Concatating of The Linked List is Successfully Done ! :-\n");
}
 
void concat_at_position(PPNODE ppHead1,PPNODE ppTail1 ,PPNODE ppHead2,PPNODE ppTail2,int iPos)
{	
	PNODE pTemp = NULL;
	
	int iCounter;
	 iCounter=count_node(*ppHead1,*ppTail1);
	if(iPos <= 0 ||iPos > iCounter +1)
	{
		printf(" ! Position invalid ! :-");
		return ;
	}
	if(NULL == *ppHead2)
	{
		return ;
	}
	if(1 == iPos)
	{
		concat_list( ppHead2,ppTail2,ppHead1,ppTail1);
		*ppHead1 = *ppHead2;
                *ppTail1 = *ppTail2;
		 *ppTail2 = *ppHead2 =NULL;
		return ;
	}
	if(iPos == iCounter + 1)
	{
		concat_list(ppHead1,ppTail1,ppHead2,ppTail2);
		return ;
						
	}
	pTemp = *ppHead1;
	iCounter = 1;
	while(iCounter < iPos -1)
        {
            iCounter ++;
            pTemp = pTemp -> pNext;	
        }
       (*ppTail2) -> pNext = pTemp -> pNext;
        (*ppTail2) -> pNext -> pPrev = (*ppTail2);		
         pTemp -> pNext -> pPrev = *ppTail2;
        pTemp ->pNext = *ppHead2;
		(*ppHead2) -> pPrev = pTemp;
        *ppTail2 = *ppHead2 =NULL; 
        printf("\n\t! Concat The List is successfully Done....! :-\n");

} 

void reverse(PPNODE ppHead ,PPNODE ppTail)
{
	
    PNODE pCurrent = *ppHead;
    PNODE Next = NULL;
	if(NULL == *ppHead)
	{
		printf("\n! Your List is Empty...! :- ");
		return;
	}
	do
	{
		Next = pCurrent -> pNext;
		pCurrent -> pNext = pCurrent -> pPrev;
		pCurrent -> pPrev = Next;
		pCurrent = Next;
	}while(pCurrent != *ppHead);
        *ppTail = pCurrent;
	*ppHead = (*ppTail) -> pNext;
         printf("\n\tYour List is Reverse order Display...:-\t ");
}
void reverse_display(PNODE pHead,PNODE pTail)
{
	if(NULL==pHead)
	{
		printf("\t Linked list is empty \n");
		return;
	}
	do
	{

		printf("<-| %d |->",pTail->iData);
		pTail=pTail->pPrev;
	}while(pTail!=pHead->pPrev);
}
void display (PNODE pHead,PNODE pTail)
{
	if(NULL == pHead)
	{
		printf("\n\n\t! Your List is Empty...! :-");
		return ;
	}
    printf(" \n\n\t! Your List is...! :-\t");      
	do
	{
		printf("<-|%d|->",pHead -> iData);
		pHead = pHead -> pNext;
	}while (pHead != pTail -> pNext);
}
