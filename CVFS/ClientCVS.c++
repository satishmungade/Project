#include"Header.h"
int main()
{
	char Chstr[80];
	char Command[4][80];
	char *chPtr=NULL;
	int iCount=0,iRet=0;
	
	printf("\n\t !! Project-Name :- Customised Virtual File System !!  \n");
	SetEnvoirnment();
	while(1)
	{
		printf("\n\nSatish Mungade VFS :>");
		fgets(Chstr,80,stdin);
		fflush(stdin);
		iCount=sscanf(Chstr,"%s %s %s %s",Command[0],Command[1],Command[2],Command[3]);
		if(iCount==1)
		{
			if(strcmp(Command[0],"help")==0)
			{
				DisplayHelp();
				continue;
			}
			else if(strcmp(Command[0],"exit")==0)
			{
				printf("\n\n !** Thank-you for using My Virual File System **!\n");
				break;
			}
			if(strcmp(Command[0],"ls")==0)
			{	
				ls_file();
			}
			else if(strcmp(Command[0],"closeall")==0)
			{
				CloseAllFiles();

			}
			else if(strcmp(Command[0],"clear")==0)
			{
				system("cls");
				continue;
			
			}
			else
			{
				printf("\n\n Command Not Found !! ");
			}
			
		}
		else if(iCount == 2)
		{
			if(strcmp(Command[0],"man")==0)
			{
				ManPage(Command[1]);
			}
			else if(strcmp(Command[0],"stat")==0)
			{
				iRet=StatFile(Command[1]);
				if(iRet == -1)
					printf("\n ERROR : Incorrect Parameter :");
				if(iRet == -2)
					printf("\n ERROR :There is no Such File");
			}
			else if(strcmp(Command[0],"fstat")==0)
			{
				iRet=FstatFile(atoi(Command[1]));
				if(iRet == -1)
					printf("\n ERROR : Incorrect Parameter :");
				if(iRet == -2)
					printf("\n ERROR :There is no Such File");
			}
			else if(strcmp(Command[0],"rm")==0)
			{
				DeleteFile(Command[1]);
				continue;
			}
			else if(strcmp(Command[0],"write")==0)
			{
				char arr[1024];
				printf("\n Plase Enter a Data to Write :");
				fgets(arr,1024,stdin);
				fflush(stdin);
				int iRet=WriteFile(atoi(Command[1]),arr,strlen(arr)-1);
				if(iRet != -1)
				{
					printf("\n%d bytes gets written succesfully in the file\n",iRet);
				}

			}
			else if(strcmp(Command[0],"close")==0)
			{
				iRet=CloseFileByName(Command[1]);
				if(iRet == -1)
					printf("\n\t ERROR : There is No Such File :");
				else
					printf("\n\t File Succufully closed");
				continue;
			}	
			else if(strcmp(Command[0],"truncate")==0)
			{
				iRet=TruncateFile(Command[1]);
				if(iRet == -1)
					printf("\n\t ERROR : Incorrect Parameter");
			}	
			else
			{
				printf("\n Command Not Found !!");
			}
		}
		else if(iCount==3)
		{
			if(strcmp(Command[0],"creat")==0)
			{
				int Fd=0;
				Fd=CreateFile(Command[1],atoi(Command[2]));
				if(Fd ==-1)
					printf("\n There is No Permission create a file : ");
				else if(Fd == -2)
					printf("\n File Already is Present  :");
				else if(Fd == -3)
					printf("There is no inode to create the file :");
				else if(Fd == -4)
					printf("\n Unable to get entry in UFDT :");
				else
					printf("\nFile Succufully Created with Fd %d :",Fd);
				continue;

			}
			else if(strcmp(Command[0],"open")==0)
			{
				iRet=OpenFile(Command[1],atoi(Command[2]));
				if(iRet >=0)
					printf("\n\tFile is Succufully opened with file Descriptor :%d",iRet );
				if(iRet== -1)
					printf("\n\tERROR : Incorrect Parameter ");
				if(iRet == -2)
					printf("\n\t ERROR : File Not Pasent :");
				if(iRet== -3)
					printf("\n\t ERROR :Permission defied ");
				continue;			
			}
			else if(strcmp(Command[0],"read")==0)
			{
				int Fd=GetFDFromName(Command[1]);
				if(Fd == -1)
				{
					printf("\n\tERROR :Incorrect Parameter");
					continue;
				}
				chPtr=(char *)malloc(sizeof(atoi(Command[2]))+1);
				if(chPtr ==NULL)
				{
					printf("ERROR : Memory Allocation is failure");
					continue;
				}
				iRet=ReadFile(Fd,chPtr,atoi(Command[2]));
				if(iRet ==-1)
					printf("\n\t ERROR : File Not Existing");	
				if(iRet == -2)
					printf("\n\t ERROR : Permission defied");
				if(iRet == -3)
					printf("\n\t ERROR : Reached at end of file");
				if(iRet == -4)
					printf("\n\t ERROR :Its Not regular file");
				if(iRet == 0)
					printf("\n\t ERROR : File is Empty ");
				if(iRet > 0)
					write(2,chPtr,iRet);							
				continue;

			}
			else
			{
				printf("\n\t ERROR : Command Not Found");
			}

		}
		else if(iCount==4)
		{
			if(strcmp(Command[0],"lseek")==0)
			{
				int Fd=GetFDFromName(Command[1]);
				if(Fd== -1)
				{
					printf("\n\t ERROR :Incorrect Parameter");
					continue;
				}
				int iRet=lseekFile(Fd,atoi(Command[2]),atoi(Command[3]));
				if(iRet == -1)
				{
					printf("\n\t Unable to Perform Lseek");
				}

			}
			else
			{
					printf("\n\tERROR : Command Not Found");
					continue;
			}
		}
		else
		{
			printf("\n\t ERROR :Bad Command File :");
			continue;
		}

	}


	return 0;
}
