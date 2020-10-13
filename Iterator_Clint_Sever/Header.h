#include<iostream>
using namespace std;
#ifndef HEADER_H
#define HEADER_H

template<typename T>
class Node
{
	private:
		Node *pNext;
		T iData;
		Node *pPrev;
	public:
		Node()
		{
			iData=0;
			pNext=NULL;
			pPrev=NULL;
		}
		~Node()
		{
		     iData =0;
			if(pNext != NULL)
			{
				pNext=NULL;
				pPrev=NULL;
			}
		}
		template<typename T>
		friend class List;
};

template<typename T>
class List
{
	private:
		Node<T> *pDummyNode;
	public:
		List()
		{
			pDummyNode  = new Node<T>;
			pDummyNode->pNext = pDummyNode;
			pDummyNode->pPrev = pDummyNode;

		}
		~List()
		{
			if(pDummyNode != pDummyNode ->pNext)
				delete_all();
			pDummyNode->pNext=NULL;
			pDummyNode->pPrev=NULL;
			delete pDummyNode;
		}
	void insert_first(T);
	void insert_last(T);
	void insert_at_position(int,T);
	int count_node();
	T delete_first();
	T delete_last();
	T delete_at_position(int);
	int search_all(T);
	int search_first_occurrence(T);
	int search_last_occurrence(T);
	void delete_all();


	class Iterator
	{
		private:
			Node<T>  *pCurrentNode;
		public:
			Iterator()
			{
				pCurrentNode=NULL;
			}	
			~Iterator()
			{
				pCurrentNode=NULL;
			}

		T operator *()
		{
			return pCurrentNode->iData;
		}	
		Iterator& operator  ++()
		{
			pCurrentNode=pCurrentNode ->pNext;
			return *this;
		}
		Iterator& operator --()
		{
			pCurrentNode=pCurrentNode ->pPrev;
			return *this;
		}
		Iterator operator ++(int)
		{
			Iterator iTemp=*this;
			pCurrentNode=pCurrentNode->pNext;
			return iTemp;
		}
		Iterator operator --(int)
		{
			Iterator iTemp=*this;
			pCurrentNode=pCurrentNode->pPrev;
			return iTemp;
		}
		bool operator !=(Iterator Iter)
		{
			return pCurrentNode != Iter.pCurrentNode;
		}
		bool operator ==(Iterator Iter)
		{
			return pCurrentNode->iData ==Iter.pCurrentNode->iData;
		}
		bool operator < (Iterator Iter)
		{
			return pCurrentNode->iData < Iter.pCurrentNode->iData;
		}
		bool operator >(Iterator Iter)
		{
			return pCurrentNode->iData > Iter.pCurrentNode->iData;
		}
		bool operator <=(Iterator Iter)
		{
			return pCurrentNode->iData <=Iter.pCurrentNode->iData;
		}
		bool operator >=(Iterator Iter)
		{
			return pCurrentNode->iData >=Iter.pCurrentNode->iData;
		}

		void set_current(Node<T> *pNew)
        {
            pCurrentNode = pNew; 
        }
        

	};	
	Iterator IterStart,IterEnd;
		
		Iterator& begin ()
		{
         	IterStart.set_current(pDummyNode->pNext);
			return IterStart; 
		}
	 	Iterator& end()
		{
        	IterEnd.set_current(pDummyNode);
			return IterEnd;
		}


};
#endif

template<typename T>
void List <T>:: insert_first(T iNo)
{
	Node<T> *pNewNode =new Node<T>;
	pNewNode ->iData=iNo;
	pNewNode ->pNext =pDummyNode->pNext;
	pDummyNode->pNext =pNewNode;
	pNewNode ->pPrev=pDummyNode;
	pNewNode->pNext->pPrev=pNewNode;
}
template<typename T>
void List <T> :: insert_last(T iNo)
{
	Node <T> *pNewNode =new Node <T>;
	pNewNode ->iData=iNo;
	
	pNewNode ->pPrev =pDummyNode-> pPrev;
	pNewNode->pNext=pDummyNode;
	pDummyNode->pPrev->pNext=pNewNode;	
	pDummyNode->pPrev=pNewNode;
}
template<typename T>
int List <T> :: count_node()
{
	int iCount=0;
	Node <T> *pTemp=pDummyNode->pNext;
	if(pDummyNode->pNext == pDummyNode)
		return 0;

	while(pTemp != pDummyNode)
	{
		iCount ++;
		pTemp = pTemp->pNext;
		 
	}
	return iCount; 

} 
template<typename T>
void List <T> :: insert_at_position(int iPos,T iNo)
{
	int iCounter=0;
	Node <T>*pTemp=pDummyNode->pNext;;
	Node <T>*pNewNode =new Node <T>;
	iCounter=count_node();
	if(iPos == 1)
	{
		insert_first(iNo);
		return ;
	}
	if(iPos == iCounter + 1)
	{
		insert_last(iNo);
		return;
	}

	pNewNode ->iData=iNo;
	iCounter =1;
	while(iCounter < iPos -1)
	{
		iCounter ++;
		pTemp=pTemp->pNext;
	}
	pNewNode->pNext = pTemp->pNext;
	pNewNode->pNext->pPrev=pNewNode;
	pTemp->pNext=pNewNode;
	pNewNode->pPrev=pTemp;
	pTemp->pNext->pPrev=pTemp;
}	
template<typename T>
T List <T> :: delete_first()
{
	T iDelData=0;
	iDelData=pDummyNode->pNext->iData;
	pDummyNode->pNext = pDummyNode->pNext->pNext;
	pDummyNode->pNext->pPrev->pNext=NULL;
	pDummyNode->pNext->pPrev->pPrev=NULL;
	delete pDummyNode->pNext->pPrev;
	pDummyNode->pNext->pPrev=pDummyNode;
	return iDelData; 
}
template<typename T>
T List <T>:: delete_last()
{
	T iDelData =0;
	iDelData=pDummyNode->pPrev->iData;
	pDummyNode->pPrev = pDummyNode->pPrev->pPrev;
	pDummyNode->pPrev->pNext-> pNext=NULL;
	pDummyNode->pPrev->pNext-> pPrev=NULL;
	delete pDummyNode->pPrev->pNext;
	pDummyNode->pPrev->pNext=pDummyNode;
	return iDelData;
}
template<typename T>
T List <T> :: delete_at_position(int iPos)
{
	T iDelData =0;
	int iCount =0;
	Node<T> *pTemp=pDummyNode->pNext;
	iCount=count_node();
	if(iPos == 1)
	{
		return delete_first();
	}
	if(iPos == iCount)
	{
		return delete_last();
	}
	iCount =1;
	while(iCount < iPos)
	{
		iCount ++;
		pTemp=pTemp->pNext;
	}
	pTemp ->pPrev ->pNext=pTemp->pNext;
	pTemp->pNext->pPrev=pTemp->pPrev;
	iDelData=pTemp->iData;
	pTemp->pNext=NULL;
	pTemp->pPrev=NULL;
	delete pTemp;
	pTemp=NULL;
	return iDelData;
}
template<typename T>
int List <T> :: search_all(T iKey)
{
	int iCount=0;
	Node <T>*pTemp=pDummyNode->pNext;
	while(pTemp != pDummyNode)
	{
		if(iKey == pTemp ->iData)
			iCount++;

		pTemp=pTemp ->pNext;
	}
	if(iCount == 0 && pTemp == pDummyNode)
		iCount =-1;

	return iCount;
}
template<typename T>
int List <T>:: search_first_occurrence(T iKey)
{
	int iPos=0;
	Node <T>*pTemp=pDummyNode->pNext;
	while(pTemp != pDummyNode)	
	{
		iPos++;
		if(iKey ==pTemp ->iData)
			break;
		
		pTemp=pTemp->pNext;
	}

	if(iPos != 0 && pTemp == pDummyNode)
		iPos =-1;

	return iPos;
}
template<typename T>
int List <T> ::search_last_occurrence(T iKey)
{
	int iPos=0;
	iPos=count_node();
	Node<T> *pTemp=pDummyNode->pPrev;
	while(pTemp !=pDummyNode)
	{
		iPos--;
		if(iKey ==pTemp ->iData)
			break;
		
		pTemp=pTemp->pPrev;
	 }
		++iPos;
	if(iPos != 0 && pTemp == pDummyNode)
		iPos =-1;

	return iPos;

}
template<typename T>
void List <T> :: delete_all()
{
	while (pDummyNode->pNext != pDummyNode)
	{
		pDummyNode->pNext->pPrev=NULL;
		pDummyNode->pNext=pDummyNode->pNext->pNext;
		pDummyNode->pNext->pPrev->pNext=NULL;
		delete pDummyNode->pNext->pPrev;
		pDummyNode->pNext->pPrev=pDummyNode;
	}
	cout<<"\n \t Deleted All Sucessfully"<<endl;
}
