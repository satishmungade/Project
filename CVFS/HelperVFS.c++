#include"Header.h"
struct SuperBlock Obj_Super;
UFDTOBJ ufdt[MAXFILES];
PINODE Head=NULL;

void CreateUFDT()
{
	int iCnt=0;
	for(iCnt =0 ; iCnt <MAXFILES ; iCnt ++ )
	{
		ufdt[iCnt].ptrfiletable=NULL;
	}	
	
}
void CreatSuperBlock()
{
	Obj_Super.TotalInodes=MAXFILES;
	Obj_Super.FreeInode=MAXFILES;
	
}
void CreateDILB()
{
	int iNo=1;
	PINODE NewNode=NULL;
	PINODE Temp=NULL;
	while(iNo <= MAXFILES)
	{
		NewNode=(PINODE)malloc(sizeof(INODE));
		NewNode->Inode_Number=iNo;
		NewNode->File_Size=FILESIZE;
		NewNode->File_Type=0;
		NewNode->Actual_File_Size=0;
		NewNode->Link_Count=0;
		NewNode->Reference_Count=0;
		NewNode->Data=NULL;
		NewNode->pNext=NULL;
		if(Head == NULL)
		{
			Head=NewNode;
			Temp=Head;
		}
		else
		{
			Temp->pNext=NewNode;
			Temp=Temp->pNext;
		}
		iNo ++;
	}
	
}

void SetEnvoirnment()
{
	CreateDILB();
	CreatSuperBlock();
	CreateUFDT();
	
}

void DisplayHelp()
{
	printf("\n -------------! Its Display All System Call Short information !-------\n");
	printf("\n\t OPEN 	 : Its used to open the Exting file : ");
	printf("\n\t CLOSE 	 : Its used to Close the Opened file : ");
	printf("\n\t READ  	 : Its used to Read the Contain of file : ");
	printf("\n\t WRITE 	 : Its used to write the  data into file : ");
	printf("\n\t LS   	 : Its used to List out all Files :");
	printf("\n\t CLEAR 	 : Its uesd to clear the console :");
	printf("\n\t CLOSEALL: Close the All Files :");
	printf("\n\t EXIT  	 : Its uesd to Terminates the process :");
	printf("\n\t LSEEK 	 : Its used to change the offset of file :");
	printf("\n\t STAT 	 : Its used to display the information of file : ");
	printf("\n\t FSTAT 	 : Its used to display the information of opened file :");
	printf("\n\t TRUNCATE: Its uesd to Remove the File Data :");
	printf("\n\t RM 	 : Its used to Remove the File Directories :\n");
	printf("\n\t EXIT    : Its uesd to close the running process");
	printf("\n --------------------------------------------------------------------\n");
}
void ManPage(char *Command)
{
	if(Command == NULL)
		return ;
	if(strcmp(Command,"read")==0)
	{
		printf("\n\t Description : Its used to read Data from regular file : ");
		printf("\n\t Usage       : read file_Name No_of_Bytes_To_Read :");
	}
	else if(strcmp(Command,"creat")==0)
	{
		printf("\n\t Description : used to create new regular file :");
		printf("\n\t Usage       :create file_name Permission");
	}
	else if(strcmp(Command,"write")==0)
	{
		printf("\n\t Description : It is used to write data into file");
		printf("\n\t Usage       : write File_Desriptor");
		printf("After the command please enter the data\n");
	}
	else if(strcmp(Command,"ls")==0)
	{
		printf("\n\t Description : Its used to List out all Name of the files : ");
		printf("\n\t Usage       : open file_Name and Mode :");
	}
	else if(strcmp(Command,"stat")==0)
	{
		printf("\n\t Description : uesd To Display information of Files ");
		printf("\n\t Usage       : Stat FileName");
	}
	else if(strcmp(Command,"fstat")==0)
	{
		printf("\n\t Description : Used To Display information of file :");
		printf("\n\t Usage       : stat File_Desriptor ");
	}
	else if(strcmp(Command,"truncate")==0)
	{
		printf("\n\t Description : Uesd to Remove data From file ");
		printf("\n\t Usage       : truncate File_Name");
	}
	if(strcmp(Command,"open")==0)
	{
		printf("\n\t Description : Its used to open an Existing file : ");
		printf("\n\t Usage       : open file_Name and Mode :");
	}
	else if(strcmp(Command,"close")==0)
	{
		printf("\n\t Description : Its used to close the opened file : ");
		printf("\n\t Usage       : close file_Name :");
	}
	else if(strcmp(Command,"clossall")==0)
	{
		printf("\n\t Description :Used to close All opened file");
		printf("\n\t Usage       :clossall ");
	}
	else if(strcmp(Command,"lseek")==0)
	{
		printf("\n\t Description : Used to change file offset");
		printf("\n\t Usage       : lseek File_name changeInOffset StatPoint ");
	}
	else if(strcmp(Command,"rm")==0)
	{
		printf("\n\t Description : It is used to delete regular file");
		printf("\n\t Usage       :rm File_name ");
	}
	else if(strcmp(Command,"")!=0)
		printf("\n\t       ERROR : No Any Manual Entry Avaiable");

}

bool CheckFile(char *Name)
{
	PINODE Temp=Head;
	while(Temp != NULL)
	{
		if(Temp->File_Type != 0)
		{
			if(strcmp(Temp->FileName,Name)==0)
			{
				break;
			}
		}
		Temp=Temp->pNext;
	}
	if(Temp ==NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void ls_file()
{
    PINODE Temp = Head;
	if(Obj_Super.FreeInode == MAXINODES)
	{
		printf("\n\t ERROR : There are No files :\n");
	}
	printf("\n File_name\tInode_Number\t File_Size\tLinkCount\n");
	while(Temp != NULL)
    {
        if(Temp -> File_Type != 0)
        {
            printf("%s\t\t%d\t\t%d\t\t%d\n",Temp->FileName,Temp->Inode_Number,Temp->Actual_File_Size,Temp->Link_Count);
        }
        Temp = Temp->pNext;
    }
    printf("-------------------------------------------------\n");
}

void DeleteFile(char *Name)
{
    bool bret = false;
    
    if(Name == NULL)
    {
        return;
    }
    
    bret = CheckFile(Name);
    if(bret == false)
    {
        printf("\n\t There is no such file\n");
        return;
    }
    int i = 0;
    for(i = 0; i < MAXFILES; i++)
    {
        if(strcmp(ufdt[i].ptrfiletable->ptriNode->FileName, Name) == 0)
        {
            break;
        }
    }
    
    strcpy(ufdt[i].ptrfiletable->ptriNode->FileName,"");
    ufdt[i].ptrfiletable->ptriNode->File_Type = 0;
    ufdt[i].ptrfiletable->ptriNode->Actual_File_Size = 0;
    ufdt[i].ptrfiletable->ptriNode->Link_Count = 0;
    ufdt[i].ptrfiletable->ptriNode->Reference_Count = 0;
    
    free( ufdt[i].ptrfiletable->ptriNode->Data);
    
    free(ufdt[i].ptrfiletable);
    
    ufdt[i].ptrfiletable = NULL;
    
    Obj_Super.FreeInode++;
}
int WriteFile(int fd,char *arr,int size)
{
	if(ufdt[fd].ptrfiletable ==NULL)
	{
		printf("Invalide file Description :");
		return -1;
	}
	if(ufdt[fd].ptrfiletable ->Mode==READ)
	{
		printf("\nThere is No Write permition");
		return -1;
	}
	
	strncpy(((ufdt[fd].ptrfiletable->ptriNode->Data)+(ufdt[fd].ptrfiletable ->WriteOffset)),arr,size);
    
    ufdt[fd].ptrfiletable ->WriteOffset = ufdt[fd].ptrfiletable ->WriteOffset + size;

	return size;

}
int CreateFile(char *Name,int Permission)
{
	bool bRet=false;
	if(( Name==NULL )||(Permission > READ + WRITE ) || (Permission < WRITE))
	{
		return -1;
	}
	bRet=CheckFile(Name);
	if(bRet == true)
	{
		return -2;
	}
	if(Obj_Super.FreeInode==0)
	{
		return -3;
	}
	int iCnt=0;
	for(iCnt=0; iCnt < MAXFILES ; iCnt ++)
	{
		if(ufdt[iCnt].ptrfiletable ==NULL)
		{
			break;
		}
	}
	if(iCnt == MAXFILES)
	{
		return -4;
	}
	ufdt[iCnt].ptrfiletable=(PFILETABLE)malloc(sizeof(FILETABLE));

	ufdt[iCnt].ptrfiletable->ReadOffSet=0;
	ufdt[iCnt].ptrfiletable->WriteOffset=0;
	ufdt[iCnt].ptrfiletable->Mode=Permission;
	ufdt[iCnt].ptrfiletable->Count=1;
	PINODE Temp=Head;
	while(Temp != NULL)
	{
		if(Temp -> File_Type == 0)
		{
			break;
		}
		Temp=Temp->pNext;
	}
	ufdt[iCnt].ptrfiletable->ptriNode=Temp;
	strcpy(ufdt[iCnt].ptrfiletable->ptriNode->FileName,Name);
	ufdt[iCnt].ptrfiletable->ptriNode->File_Type=REGULAR;
	ufdt[iCnt].ptrfiletable->ptriNode->Actual_File_Size=0;
	ufdt[iCnt].ptrfiletable->ptriNode->Link_Count=1;
	ufdt[iCnt].ptrfiletable->ptriNode->Reference_Count=1;
	ufdt[iCnt].ptrfiletable->ptriNode->Permission =Permission;
	ufdt[iCnt].ptrfiletable->ptriNode->Data=(char *)malloc(sizeof(FILESIZE));

	Obj_Super.FreeInode --;
	
	return iCnt;
}
int GetFDFromName(char *Name)
{
	int iCnt=0;
	while(iCnt < MAXFILES)
	{
		if(ufdt[iCnt].ptrfiletable->ptriNode !=NULL)
		{	
			if(strcmp((ufdt[iCnt].ptrfiletable->ptriNode->FileName),Name)==0)
			{
				break;
			}	
		}	
	}	
	iCnt ++;
	if(iCnt == MAXFILES)
	{	
		return -1;
	}
	else
	{	
		return iCnt;			
	}
		
}
PINODE Get_Inode(char * Name)
{
	PINODE Temp=Head;
	if(Name == NULL)
	{
		return NULL;
	}
	while(Temp != NULL)
	{
		if(strcmp(Name,Temp->FileName)==0)
			break;
		Temp=Temp->pNext;
	}	
	return Temp;
}
int OpenFile(char *Name,int Mode)
{
	int iCnt=0;
	PINODE Temp=NULL;

	if(Name == NULL || Mode <= 0)
	{
		return -1;
	}
	Temp=Get_Inode(Name);
	if(Temp == NULL)
		return -2;
	if(Temp->Permission < Mode)
		return -3;
	while(iCnt < MAXFILES)
	{
		if( ufdt[iCnt].ptrfiletable == NULL)
			break;
		iCnt ++;
	}
	ufdt[iCnt].ptrfiletable=(PFILETABLE)malloc(sizeof(FILETABLE));
	if(ufdt[iCnt].ptrfiletable == NULL)
		return -1;
	ufdt[iCnt].ptrfiletable-> Count=1;
	ufdt[iCnt].ptrfiletable->Mode=Mode;
	if(Mode == READ + WRITE)
	{
		ufdt[iCnt].ptrfiletable->ReadOffSet=0;
		ufdt[iCnt].ptrfiletable->WriteOffset=0;
	}		
	else if(Mode == READ)
	{
		ufdt[iCnt].ptrfiletable->ReadOffSet=0;
	}
	else if (Mode ==WRITE)
	{
		ufdt[iCnt].ptrfiletable->WriteOffset=0;
	}
	ufdt[iCnt].ptrfiletable->ptriNode=Temp;
	(ufdt[iCnt].ptrfiletable->ptriNode-> Reference_Count) ++;

	return iCnt;
}
int CloseFileByName(char *Name)
{
	int iNo=0;
	iNo=GetFDFromName(Name);
	if(iNo == -1)
		return -1;
	ufdt[iNo].ptrfiletable->ReadOffSet=0;
	ufdt[iNo].ptrfiletable->WriteOffset=0;
	(ufdt[iNo].ptrfiletable->ptriNode->Reference_Count)--;
	return 0;
}
void CloseAllFiles()
{
	int iNo=0;
	while(iNo < MAXFILES)
	{
		if(ufdt[iNo].ptrfiletable != NULL)
		{
			ufdt[iNo].ptrfiletable->ReadOffSet=0;
			ufdt[iNo].ptrfiletable->WriteOffset=0;
			(ufdt[iNo].ptrfiletable->ptriNode->Reference_Count)--;
		}
		iNo --;
	}
}
int ReadFile(int Fd,char *Arr,int iSize)
{
	int Read_Size=0;
	if(ufdt[Fd].ptrfiletable == NULL)
		return -1;
	if(ufdt[Fd].ptrfiletable ->Mode != READ && ufdt[Fd].ptrfiletable->Mode != READ + WRITE)
		return -2;
	if(ufdt[Fd].ptrfiletable->ptriNode->Permission != READ && ufdt[Fd].ptrfiletable->ptriNode->Permission != READ + WRITE)
		return -2;
	if(ufdt[Fd].ptrfiletable->ReadOffSet == ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)
		return -3;
	if(ufdt[Fd].ptrfiletable->ptriNode->File_Type != REGULAR)
		return -4;
	Read_Size=(ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)-(ufdt[Fd].ptrfiletable->ReadOffSet);
	if(Read_Size < iSize)
	{
		strncpy(Arr,(ufdt[Fd].ptrfiletable->ptriNode->Data)+(ufdt[Fd].ptrfiletable->ReadOffSet),Read_Size);
		ufdt[Fd].ptrfiletable->ReadOffSet=ufdt[Fd].ptrfiletable->ReadOffSet +Read_Size;
	}
	else
	{
		strncpy(Arr,(ufdt[Fd].ptrfiletable->ptriNode->Data)+(ufdt[Fd].ptrfiletable->ReadOffSet),iSize);
		(ufdt[Fd].ptrfiletable->ReadOffSet)=(ufdt[Fd].ptrfiletable->ReadOffSet )+iSize;
	
	}
	return iSize;

}
int StatFile(char *Name)
{
	PINODE Temp=Head;
	if(Name == NULL)
		return -1;
	while(Temp != NULL)
	{
		if(strcmp(Name,Temp->FileName)==0)
			break;
		Temp=Temp->pNext;
	}
	if(Temp == NULL)
		return -2;

	printf("\n\t---- Statistical information about file ----\n");
	printf("FileName 	:%s\n",Temp->FileName);
	printf("InodeNumber 	:%d\n",Temp->Inode_Number);
	printf("FileSize 	:%d\n",Temp->File_Size);
	printf("ActualFileSize 	:%d\n",Temp->Actual_File_Size);
	printf("LinkCount 	:%d\n",Temp->Link_Count);
	printf("ReferenceCount  :%d\n",Temp->Reference_Count);
	if(Temp ->Permission == 1)
		printf("File Permission : Read-Only\n");	
	if(Temp ->Permission == 2)
		printf("File Permission : Write-Only\n");	
	if(Temp ->Permission == 3)
		printf("File Permission : Read & Write\n");
	printf("\n------------------------------------------------\n");		
	return 0;
}
int FstatFile(int Fd)
{
	PINODE Temp=Head;
	int i=0;
	if(Fd < 0)
	{
		return -1;
	}
	if(ufdt[Fd].ptrfiletable == NULL)
		return -2;
	Temp =ufdt[Fd].ptrfiletable->ptriNode;
	printf("\n\t---- Statistical information about file ----\n");
	printf("FileName 	:%s\n",Temp->FileName);
	printf("InodeNumber 	:%d\n",Temp->Inode_Number);
	printf("FileSize 	:%d\n",Temp->File_Size);
	printf("ActualFileSize 	:%d\n",Temp->Actual_File_Size);
	printf("LinkCount 	:%d\n",Temp->Link_Count);
	printf("ReferenceCount  :%d\n",Temp->Reference_Count);
	if(Temp ->Permission == 1)
		printf("File Permission : ReadOnly\n");	
	if(Temp ->Permission == 2)
		printf("File Permission : WriteOnly\n");	
	if(Temp ->Permission == 3)
		printf("File Permission : Read & Write\n");
	printf("\n------------------------------------------------\n");		
	return 0;

}
int TruncateFile(char *Name)
{
	int Fd=GetFDFromName(Name);
	if(Fd ==-1)
		return -1;
	memset(ufdt[Fd].ptrfiletable->ptriNode->Data,0,1024);
	ufdt[Fd].ptrfiletable->ReadOffSet=0;
	ufdt[Fd].ptrfiletable->WriteOffset=0;
	ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size=0;
	return 0;
}
int lseekFile( int Fd,int Size, int From)
{
	if((Fd < 0) || (From > 2))
		return -1;
	if(ufdt[Fd].ptrfiletable == NULL)
		return -1;
	if((ufdt[Fd].ptrfiletable->Mode == READ)||(ufdt[Fd].ptrfiletable->Mode == READ + WRITE))
	{
		if(From == CURRENT)
		{
			if(((ufdt[Fd].ptrfiletable->ReadOffSet) +Size)> ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)
				return -1;
			if(((ufdt[Fd].ptrfiletable->ReadOffSet)+Size)< 0)
				return -1;
			(ufdt[Fd].ptrfiletable->ReadOffSet)=(ufdt[Fd].ptrfiletable->ReadOffSet)+Size;
		}
		else if(From == START)
		{
			if(Size >(ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size))
				return-1;
			if(Size < 0)
				return -1;
			(ufdt[Fd].ptrfiletable->ReadOffSet)=Size;
		}
		else if(From == END)
		{
			if((ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)+ Size >FILESIZE)
				return -1;
			if(((ufdt[Fd].ptrfiletable->ReadOffSet)+Size) < 0)
				return -1;
			(ufdt[Fd].ptrfiletable->ReadOffSet)==(ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)+Size;
		}
	}
	else if(ufdt[Fd].ptrfiletable->Mode == WRITE)
	{
		if(From == CURRENT)
		{
			if(((ufdt[Fd].ptrfiletable->WriteOffset)+Size)>FILESIZE)
				return -1;
			if(((ufdt[Fd].ptrfiletable->WriteOffset)+Size)< 0)
				return -1;
			if(((ufdt[Fd].ptrfiletable->WriteOffset)+Size) >(ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size))
				(ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)=(ufdt[Fd].ptrfiletable->WriteOffset)+Size;		
			(ufdt[Fd].ptrfiletable->WriteOffset)=(ufdt[Fd].ptrfiletable->WriteOffset)+Size;
		}
		else if(From == START)
		{
			if(Size > FILESIZE)
				return -1;
			if(Size < 0)
				return -1;
			if(Size >(ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size))
				(ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)=Size ;	
			(ufdt[Fd].ptrfiletable->WriteOffset)=Size;
		}
		else if(From == END)
		{
			if((ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)+Size>FILESIZE)
				return -1;
			if(((ufdt[Fd].ptrfiletable->WriteOffset)+Size)< 0)
				return -1;
			(ufdt[Fd].ptrfiletable->WriteOffset)=(ufdt[Fd].ptrfiletable->ptriNode->Actual_File_Size)+Size;
		}
	}
	return 0;
}