#include"Header.h"
int main()
{ 

    int iCounter,iCount,iDelData,iData,iPosition,iChoice;
	PNODE pFirst = NULL;
	PNODE pLast = NULL;
    PNODE pFirst1 = NULL;
	PNODE pLast1 = NULL;
	while(1)
	{
		printf(" \n 1.Insret_Element :-\n 2.Delete_Element :-\n 3.Search_Element :-\n 4.count_list :-\n 5.concat_list :-\n 6.Reveres_list :-\n 7.Display_list \n 8.Exit :-\n " );
		printf("\n! Enter Your choice !:-\t");
		scanf("%d",&iChoice);
        switch(iChoice)
        {
            case 1: 
            while(1)
            {
                printf("\n\n\t1.Add At beginning list :-\n\t2.Add At End :-\n\t3.Add After possition :\n\t4.back :-\n");
                printf("\n\t! Enter Your choice for Insreting !:-\t");
		        scanf("%d",&iChoice);
                if(iChoice ==3)
                {
                    printf("\n\tEnter the  possition of Node :-\t");
			        scanf("%d",&iPosition);    
                    if(iPosition<=0 ||iPosition>(count_node(pFirst,pLast)+1))	
       		        {
					    printf("\n\n\t Your Position is invalid :\n");
						continue;
					}  
                }
                if(iChoice<=3) 
                {  
                    printf("\n\n\tEnter the element to be insert First List \t:");
				    scanf("%d",&iData);            
                }        
                switch(iChoice)
			        {
			            case 1:
				              insert_first(&pFirst,&pLast,iData);
                              printf("\n\t!!Element to be inserted First position !!\n");
                              break;
	                    case 2:
	                            insert_last(&pFirst,&pLast,iData);
                                printf("\n\t!!Element to be inserted Last Position!:\n");                                     
                                break;
                        case 3:
					           insert_at_position(&pFirst,&pLast,iPosition,iData);
                               printf("\n\tElement to be inserted At-Position %d \t ",iPosition);
			        	       break;
                        case 4:
							break ;
			            default:
				              printf("\n\t! Your choice is Wrong !:-\n"); 
                                        
                    }
                        if(iChoice == 4)
                            break;
 
                                display(pFirst,pLast);
            }
            break;
            case 2:
            while(1)
            {
				if(pFirst == NULL)
                {                                        
                    printf("\n\n! Your List is Empty !");                               
                    break; 
                }    
                printf("\n\t1.Delete First Element :\n\t2.Delete last Element :\n\t3.Delete AtpossitionElement\n\t4.Back:-\n");
                printf("\n\t! Enter Your choice for Deleting !:-\t");
				scanf("%d",&iChoice);
                switch(iChoice)
			    {
                    case 1:
					    iDelData=delete_first(&pFirst,&pLast);
                        if(iDelData == -1)
                        	printf("Your Data is Wrong :\n");
                        else
					        printf("\n\tDeleted element value :-\t%d\n",iDelData);
					    break;
        			case 2:
						iDelData=delete_last(&pFirst,&pLast);
                        if(iDelData == -1)
                            printf("Your Data is Wrong :\n");
                        else
					        printf("\n\tDeleted element value :-\t%d\n",iDelData); 
					    break;
					case 3:
						printf("\n\tEnter the position to be deleted :-\t");
					    scanf("%d",&iPosition);
                        if(iPosition<=0 ||iPosition>(count_node(pFirst,pLast)))	
        			    {
					        printf("\n\n\t Your Position is invalid :\n");
							continue;
					    }  
					    iDelData=delete_at_position(&pFirst,&pLast,iPosition);
                        if(iDelData == -1)
                            printf("Your Position is Wrong :\n");
                        else
					      	printf("\n\tDeleted element given value :- \t%d\n",iDelData); 
					    break;
                    case 4:
                        break;

				    default:
        				printf("! Your choice is Wrong !:-\n"); 
                                        
                }
                if(iChoice == 4)
                    break;
                display(pFirst,pLast);
        	}
            break;
            case 3:
			while(1) 
            { 
                if(pFirst == NULL)
                {
                    printf("\n\t! Your List is Empty pleses Insert First Data Than search your Data...! :-\n\n");
                    break; 
                } 
                printf("\n\t 1.Search First occurrence list :-\n\t 2.Search Last occurrence list :-\n\t 3.Search All_list :-\n\t 4.Back :-\n");
                printf("\n\t! Enter Your choice For Searching !:-\t");
	            scanf("%d",&iChoice);
                switch(iChoice)
         		{
                    case 1:
						printf("\n\t\t Enter the element which want to search occurrence first \t:");
						scanf("%d",&iData);
						iCount=search_first_occurrence(pFirst,pLast,iData);
						if(iCount == -1)
							printf("\n\t\t Data %d  Not Present in List :\n",iData);
						else	
							printf("\n\t\t Data %d First found At position :%d\n",iData,iCount);
						break;
                            
					case 2:
						printf("\n\t\t Enter the element which want to search occurrence last \t:");
						scanf("%d",&iData);
						iCount=search_last_occurrence(pFirst,pLast,iData);
						if(iCount == -1)
							printf("\n\t\t Data %d Not Present in List :\n",iData);
						else	
							printf("\n\t\t Data %d Last found At position :%d\n",iData,iCount);
                        break;
					case 3:
                        printf("\n\t\t Enter the element to search All \t:");
                        scanf("%d",&iData);
                        iCount=search_all(pFirst,pLast,iData);
                        if(iCount == 0)
							printf("\n\t\t Data %d Not Present in List :%d\n",iData,iCount);
						else
                            printf("\n\t\tData %d Occurrence given number is  :%d \n",iData,iCount);
                        break;
                    case 4:
						break;
					default:
						printf("! Your choice is Wrong !:-\n"); 
                }
                    display(pFirst,pLast);
                    if(iChoice == 4)
                        break;
            }
            break;
            case 4:                 
				iCount=count_node(pFirst,pLast);
                printf("\t! Total Number of Elements Count is !:- %d\n",iCount);
			break;  
			case 5:                            
            while(1)
            {
                printf("\n\t1.concat list :-\n\t2.concatAtpossition list :- \n\t3.Back :-\n");
                printf("\n\t!Enter Your choice For concating !:-\t");
				scanf("%d",&iChoice);
				if(iChoice!=0 && iChoice<3)
				{
					if(iChoice==2)
					{
						printf("\n\t Enter The Position For Concating The Link List\t");	
						scanf("%d",&iPosition);
						if(iPosition<=0 ||iPosition>(count_node(pFirst,pLast)+1))
						{
							printf("\n\t Position is Invalid\n");
							continue;
						}
					}
				    printf("\n\t! Your 2nd list is Empty. You Want To Enter a Data Than Press Non Zero Number or No then enter 0 \t:");
					scanf("%d",&iCounter);
                    if(iCounter !=0)      
					{	
                        while(1)
                        {
                            printf("\n\n\t1.Add At beginning list :-\n\t2.Add At End :-\n\t3.Add After possition :\n\t4.over :-\n");
                            printf("\n\t! Enter Your choice for Insreting !:-\t");
							scanf("%d",&iCounter);
                            if(iCounter !=0 && iCounter<4)
                            {
                                if(iCounter ==3)
                                {
									printf("\n\tEnter the  possition of Node :-\t");
									scanf("%d",&iPosition);    
									if(iPosition<=0 ||iPosition>(count_node(pFirst1,pLast1)+1))	
									{
										printf("\n\n\t Your Position is invalid :\n");
										continue;
									}  
                                }
                                printf("\n\n\tEnter the element to be insert Secound List \t:");
								scanf("%d",&iData);            
                            }
							switch(iCounter)
							{
								case 1:
									insert_first(&pFirst1,&pLast1,iData);
                                    printf("\n\t!!Element to be inserted First position !!\n");
                                    break;
	                            case 2:
	                                insert_last(&pFirst1,&pLast1,iData);
                                    printf("\n\t!!Element to be inserted Last Position is \n"); 
                                    break;                                                                                                                                                                                                                                    break;
                                case 3:
									insert_at_position(&pFirst1,&pLast1,iPosition,iData);
                                    printf("\n\tElement to be inserted At-Position %d \t ",iPosition);
									break;
                                case 4:
                                    break ;
								default:
									printf("! Your choice is Wrong !:-\n"); 
                            }  
							if(iCounter == 4)
								break;
								printf("\n\n\t Second Link List ->"); 
								display(pFirst1,pLast1);
						} 
		            }      
					switch(iChoice)
                    {
                        case 1:
                            concat_list(&pFirst,&pLast,&pFirst1,&pLast1);
                            break;
						case 2:
                            concat_at_position(&pFirst,&pLast,&pFirst1,&pLast1,iPosition);
            				break; 
                        case 3:
                            break;
                        default:
						    printf("\n\t\t! Your choice is Wrong !:-\n"); 
                    }
                    if(iChoice == 3)
                        break;
                    printf("\n\n\t First Link List ->"); 
                    display(pFirst,pLast);

            }          
			break;
			case 6:
			while(1)
			{
                if(pFirst == NULL)
                {
                    printf("! Your List is Empty please Insert First Data we can't reverse...! :-\n\n");
                    break; 
                } 
                printf("\n\t1.Reverse_Display \n\t2.physically_Reverse_Display \n\t3.Back :-\n");
                printf("\n\t! Enter Your choice For Reversing !:-\t");
				scanf("%d",&iChoice);
                switch(iChoice)
                {		
                    case 1:
                        reverse_display(pFirst,pLast);	
		            	break;
					case 2:
                         reverse(&pFirst,&pLast);
                        break;
                    case 3 :
                        break;
                    default:
						printf("! Your choice is Wrong !:-\n"); 
                }
                if(iChoice == 3)
                    break;
                    display(pFirst,pLast);
            }  
            break; 
            case  7:  
                display(pFirst,pLast);
                break;
                        
            case 8:
				exit(1) ;
	        default:
			    printf("! Your choice is Wrong !:-\n");} 
        }
    }
        return 0;
}