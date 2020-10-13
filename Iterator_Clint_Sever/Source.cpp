#include"Header.h"
template<typename T>
void display_iterator(List<T>  &refList)
{   

    cout<<"\n\n\t\tIterator Display Start:"<<endl<<endl;
    for (List<T>::Iterator Iter = refList.begin();Iter != refList.end(); ++Iter )
    {

        cout<<"<-|"<<*Iter<<"|->";
    }
    cout<<endl;
}
template <typename T>
int MyMain(T)
{
	
	List <T> obj;
	int iCount =0,iChoice=0,iPosition=0;
	T iData=0,iDelData=0;
	while(1)
    {
    	
        cout<<"\n [1] INSERT_ELEMENT \t:\n [2] DELETE_ELEMENT \t:\n [3] SEARCH_ELEMENT \t:\n [4] COUNT_ELEMENT \t:\n [5] BACK \t:\n"<<endl;
        cout<<"\n\t Enter your choice \t:";
        cin>>iChoice; 
		 if(iChoice == 5)
		 {
		 	break;
		 }
            switch(iChoice)
            {
                case 1:
                
                    while(1)
                    {
                        cout<<"\n\n\t [1] ADD ELEMENT AT BEGINNING \t:\n\t [2] ADD ELEMNET AT END \t:\n\t [3] ADD ELEMENT AT POSITION \t:\n\t [4] BACK "<<endl;
                        cout<<"\n\n\t\tEnter your choice inserting element \t:";
                        cin>>iChoice;
						if(iChoice == 3)
                        {
                            cout<<"\n\t\t Enter The Position of Node \t:";
                            cin>>iPosition;
                            if(iPosition<=0 || iPosition>(obj.count_node()+1))
                            {
                                cout<<"\n\n\t Your Position is invalid :\n";
                                continue;
                            }
                        }
                        if(iChoice<=3)
                        {
                            cout<<"\n\n\t\t Enter the Element to list \t:";
                            cin>>iData;
                        }
                    	 switch(iChoice)
                    	{
                        	case 1:
                        
                            	obj.insert_first(iData);
                            	cout<<"\n\t\t Element to be inserted first position\t:";
                       		     break;
                        
                        	case 2:
                        
                            	obj.insert_last(iData);
                            	cout<<"\n\t\t Element to be inserted last position \t:";
                            	break;
                            
                        	case 3:
                        
                            	obj.insert_at_position(iPosition,iData);
                            	cout<<"\n\t\t Element to be inserted at-posotion \t:";
                            	break;
                            
                        	case 4:
                                break ;


                        	default:
                           			 cout<<"\n \t Your choice is worng \t:"<<endl;
                    	}   
											display_iterator(obj);
											if(iChoice == 4)
												break;
											
			
				}
				break ;
				case 2:
					 while(1)
                    {
                     iCount=obj.count_node();
                     if(iCount == 0)
                       	break;
                     else	 
                        cout<<"\n\t [1] DELETE THE FIRST ELEMENT :\n\t [2] DELETE THE LAST ELEMENT :\n\t [3] DELETE THE AT-POSITION : \n\t [4] BACK \n ";
                        cout<<"\n\t Enter your choice \t:";
                        cin>>iChoice;
                        switch(iChoice)
                        {
                            case 1:
                            
                                 iDelData=obj.delete_first();
                                 if(iDelData== -1)
                                    cout<<"Data is wrong :\t";
                                 else
                                    cout<<"\n\t\t Deleted element value is \t:"<<iDelData;
                                 break;    
                              
                            case 2 :
                            
                                 iDelData=obj.delete_last(); 
                                 if(iDelData== -1)
                                    cout<<"Data is wrong :\t";
                                 else
                                    cout<<"\n\t\t Deleted element value is \t:"<<iDelData;
                                 break;
                                  
                            case 3:
                            
                                cout<<"\n\t\tEnter the position to de deleted :\t";
                                cin>>iPosition;
                                    if(iPosition<=0 || iPosition>(obj.count_node())) 
                                    {
                                        cout<<"\n\t Your position is invalid \n";
                                        continue;
                                    }
                                    iDelData=obj.delete_at_position(iPosition );
                                        if(iDelData == -1)
                                            cout<<"\t Position is wrong \t :";
                                        else 
                                            cout<<"\n\t\t Deleted element value is \t:"<<iDelData; 
                                  break;
                                  
                            case 4:
                                    break;
                                    
                            default :
                                  cout<<"\n\t choice is worng :\t";
                                          
                        }   
                         display_iterator(obj);
                         if(iChoice == 4)
                            break;
                            
                                
                }
				break;
				case 3:
					 while(1)
                    {
                     	iCount=obj.count_node();
                     	if(iCount == 0)
                       		break;
                     	else
                        cout<<"\n\n\t [1] SEARCH FIRST OCCURRENCE LIST :\n\t [2] SEARCH LAST OCCURRENCE LIST :\n\t [3] SEARCH ALL OCCURRENCE LIST :\n\t [4] BACK : \n";
                        cout<<"\n\t Enter your choice \t:";
                        cin>>iChoice;
                        switch(iChoice)
                        {
                            case 1:
                            	cout<<"\n\t\t Enter the element which want to search first occurrence \t:";
                                cin>>iData;
                                iCount=obj.search_first_occurrence(iData);
								if(iCount == -1)
										cout<<"\n\t\t Data Not Present in List :\n";
								else	
										cout<<"\n\t\t Data First found At position :"<<iCount ;
                            break;
                            
							case 2:
                            	cout<<"\n\t\t Enter the element which want to search last occurrence\t:";
                                cin>>iData;
                                iCount=obj.search_last_occurrence(iData);
                            	if(iCount == -1)
										cout<<"\n\t\t Data Not Present in List :\n";
								else	
									cout<<"\n\t\t Data Last found At position :"<<iCount ; 
                                break;
							 
                            case 3:
                                
                                cout<<"\n\t\t Enter the Element to search All \t:";
                                cin>>iData;
                                iCount=obj.search_all(iData);
                                if(iCount == -1)
									cout<<"\n\t\t Data Not Present in List :\n";
								else
									cout<<"\n\t\tData Occurrence given number is  :"<<iCount;
                             break;
                            
                            case 4:
                                break;
                            
                             default :
                                  cout<<"\n\t choice is worng :\t";
                                          
                        }   
                         display_iterator(obj);
                         if(iChoice == 4)
                            break; 
                        
                        
                    }
                break; 
				case 4:
					iCount=obj.count_node();
					cout<<"\n\t Total Number of Count is : "<<iCount<<endl;
					break;

				case 5:
					    break;
				default :
					cout<<"\n \t Your Choice is worng"<<endl;
                
            }

    }
               					
  return 0;         
}
int main()
{

    int iChoice=0 ;
       cout<<"\n \t * GENERIC DOUBLY CIRCULAR LINKED LIST USING C++ TEMPLATE *"<<endl;
       cout<<"\n \t \t \t \t VERSION -6 "<<endl;
       
    while(1)
    {
    		cout<<" \n\t\t *** Which List You Want Create ***"<<endl;
            cout<<"\n[1]Integer :\n[2]Character :\n[3]Single Precision Floating Point :\n[4]Double precision Floating Point :\n[5]Exit :"<<endl;
            cout<<"\n \t Enter Your Choice :";
            cin>>iChoice;
            if(iChoice == 5)
            	break;
            switch(iChoice)
            {
                case 1:
                		cout<<"\n\t\t -- -- -- INTEGER -- -- --"<<endl;
                    	MyMain(10);
                        break;
                case 2:
                		cout<<"\n\t\t -- -- -- CHARACTER -- -- --"<<endl;
                        MyMain('A');
                        break ;
                case 3:
                		cout<<"\n\t\t -- -- -- FLOAT -- -- --"<<endl;
                        MyMain(10.1f);
                        break;
                case 4:
                		cout<<"\n\t\t -- -- -- DOUBLE -- -- --"<<endl;
                        MyMain(10.000);
                        break ;
                
                case 5:
                        exit(1);
                
                default :
                        cout<<"\n\t Your iChoice is wrong "<<endl; 
                           
            }
        }
    return 0;
}
