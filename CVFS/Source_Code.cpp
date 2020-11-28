#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h> 
#include<iostream> 
#include<io.h> 

#define MAXINODE 1000 

#define READ 1 
#define WRITE 2 

#define MAXFILEiSize 2048 

#define REGULAR 1 
#define SPECIAL 2 

#define START 0 
#define CURRENT 1 
#define END 2 

struct superblock 
{ 
	int TotalInodes; 
	int FreeInode; 
};
typedef struct superblock SUPERBLOCK;
typedef struct superblock * PSUPERBLOCK; 

struct inode 
{ 
	char FileName[50]; 
	int InodeNumber; 
	int FileiSize; 
	int FileActualiSize; 
	int FileType; 
	char *Buffer; 
	int LinkiCount; 
	int ReferenceiCount; 
	int permission; 
	struct inode *next; 
};
typedef struct inode INODE;
typedef struct inode * PINODE;
typedef struct inode **PPINODE; 

struct filetable 
{ 
	int readoffset; 
	int writeoffset; 
	int iCount; 
	int mode;  
	PINODE ptrinode; 
};
typedef struct filetable FILETABLE;
typedef struct filetable *PFILETABLE; 
 

 struct ufdt 
{ 
	PFILETABLE ptrfiletable; 
};

typedef struct ufdt UFdT; 

UFdT UFdTArr[50];
SUPERBLOCK SUPERBLOCKobj; 
PINODE head = NULL; 

void InitialiseSuperBlock();
int CreateFile(char *Name,int permission); 
void CreateDILB();
int GetFdFromName(char *Name);
PINODE Get_Inode(char * Name); 
void man(char *Name);
void DisplayHelp(); 
int rm_File(char * Name); 
int ReadFile(int Fd, char *Arr, int iSize); 
int WriteFile(int Fd, char *Arr, int iSize); 
int OpenFile(char *Name, int mode); 
void CloseFileByName(int Fd); 
int CloseFileByName(char *Name); 
void CloseAllFile(); 
int LseekFile(int Fd, int iSize, int from); 
void ls_file(); 
int fstat_file(int Fd); 
int stat_file(char *Name); 
int truncate_File(char *Name);

int main() 
{ 
	char *ptr = NULL; 
	int iRet = 0, Fd = 0, iCount = 0; 
	char command[4][80], str[80], Arr[1024]; 
	
	printf("\n\t !! Project-Name :- Customised Virtual File System !!  \n");
	InitialiseSuperBlock(); 
	CreateDILB();
 
	while(1) 
	{ 
		printf("\n\nSatish Mungade CVFS :>");
		fgets(str,80,stdin);
		fflush(stdin); 
		iCount = sscanf(str,"%s %s %s %s",command[0],command[1],command[2],command[3]); 

		if(iCount == 1) 
		{ 
			if(strcmp(command[0],"ls") == 0) 
			{ 
				ls_file(); 
			} 
			else if(strcmp(command[0],"closeall") == 0) 
			{ 
				CloseAllFile(); 
				printf("\n\t All files closed successfully\n"); 
				continue; 
			} 
			else if(strcmp(command[0],"clear") == 0) 
			{ 
				system("cls"); 
				continue; 
			} 	
			else  if(strcmp(command[0],"help") == 0) 
			{ 
				DisplayHelp(); 
				continue; 
			} 
			else if(strcmp(command[0],"exit") == 0) 
			{ 
				printf("\n\n !** Thank-you for using My Virual File System **!\n");
				break; 
			} 
			else 
			{
				printf("\nERROR : Command not found !!!\n"); 
				continue; 
			}	 
		} 
		else if(iCount == 2) 
		{ 
			if(strcmp(command[0],"stat") == 0) 
			{ 
				iRet = stat_file(command[1]); 
				if(iRet == -1) 
				printf("\n\t ERROR : Incorrect parameters"); 
				if(iRet == -2) 
				printf("\n\t ERROR : There is no such file"); 
				continue; 
			} 
			else if(strcmp(command[0],"fstat") == 0) 
			{ 
				iRet = fstat_file(atoi(command[1])); 
				if(iRet == -1) 
				printf("\n\t ERROR : Incorrect parameters"); 
				if(iRet == -2) 
				printf("\n\t ERROR : There is no such file"); 
				continue; 
			} 
			else if(strcmp(command[0],"close") == 0) 
			{ 
				iRet = CloseFileByName(command[1]); 
				if(iRet == -1) 
				printf("\n\t ERROR : There is no such file :"); 
				continue; 
			}
			else if(strcmp(command[0],"rm") == 0) 
			{ 
				iRet = rm_File(command[1]); 
				if(iRet == -1) 
				printf("\n\t ERROR : There is no such file :"); 
				continue; 
			}	 	
			else if(strcmp(command[0],"man") == 0) 
			{ 
				man(command[1]); 
			} 	
			else if(strcmp(command[0],"write") == 0) 
			{ 
			
				Fd = GetFdFromName(command[1]); 
				if(Fd == -1) 
				{ 
					printf("\n\tError : Incorrect parameter :"); 
					continue; 
				} 
				printf("\n\t Enter the data to write file :"); 
				gets(Arr); 
 				iRet = strlen(Arr); 
				if(iRet == 0) 
				{ 
					printf("\n\t Error : Incorrect parameter :"); 
					continue; 
				}
				iRet = WriteFile(Fd,Arr,iRet); 
				if(iRet == -1) 
				{	
					printf("\n\t ERROR : Permission denied :"); 
					continue;
				}
				if(iRet == -2) 
				{	
					printf("\n\t ERROR : There is no sufficient memory to write :"); 
					continue;
				}
				if(iRet == -3)
				{	 
					printf("\n\tERROR : It is not regular file\n");  
					continue;
				}
				else
				{
					printf("\n\t %d bytes gets written succesfully in the file\n",iRet);
				}
			} 
			else if(strcmp(command[0],"truncate") == 0) 
			{ 
				iRet = truncate_File(command[1]); 
				if(iRet == -1) 
				printf("\n\t Error : Incorrect parameter"); 
			} 
			else 		
			{ 
				printf("\n\t ERROR : Command not found !!!"); 
				continue; 
			} 
		} 
		else if(iCount == 3) 
		{ 
			if(strcmp(command[0],"creat") == 0) 
			{ 
				iRet = CreateFile(command[1],atoi(command[2])); 
				if(iRet >= 0) 
				printf("\n\t File is successfully created with file descriptor : %d\n",iRet); 
				if(iRet == -1) 
				printf("\n\t ERROR : Incorrect parameters :"); 
				if(iRet == -2) 
				printf("\n\t ERROR : There is no inodes :"); 
				if(iRet == -3) 
				printf("\n\t ERROR : File already exists :"); 
				if(iRet == -4) 
				printf("\n\t ERROR : Memory allocation failure :"); 
				continue; 
			} 
			else if(strcmp(command[0],"open") == 0) 
			{ 
				iRet = OpenFile(command[1],atoi(command[2])); 
				if(iRet >= 0) 
				printf("\n\t File is successfully opened with file descriptor : %d",iRet); 
				if(iRet == -1) 
				printf("\n\t  ERROR : Incorrect parameters :"); 
				if(iRet == -2) 
				printf("\n\t ERROR : File not present :"); 
				if(iRet == -3) 
				printf("\n\t ERROR : Permission denied :"); 
				continue; 
			} 
			else if(strcmp(command[0],"read") == 0) 
			{ 
				Fd = GetFdFromName(command[1]); 
				if(Fd == -1) 
				{ 
					printf("\n\t Error : Incorrect parameter :"); 
					continue; 
				} 
				ptr = (char *)malloc(sizeof(atoi(command[2]))+1);
				if(ptr == NULL) 
				{ 
					printf("\n\t Error : Memory allocation failure :"); 
					continue; 
				} 
				iRet = ReadFile(Fd,ptr,atoi(command[2])); 
				if(iRet == -1) 
				printf("\n\t ERROR : File not existing :"); 
				if(iRet == -2) 
				printf("\n\t ERROR : Permission denied :"); 
				if(iRet == -3) 
				printf("\n\t ERROR : Reached at end of file :"); 
				if(iRet == -4) 
				printf("\n\t ERROR : It is not regular file :"); 
				if(iRet == 0) 
				printf("\n\t ERROR : File is empty :"); 
				if(iRet > 0) 
				{ 
					write(2,ptr,iRet); 
				} 
				continue; 
			} 
			else 
			{ 
				printf("\n ERROR : Command not found !!!\n"); 
				continue; 
			} 
		} 
		else if(iCount == 4) 
		{ 
			if(strcmp(command[0],"lseek") == 0) 
			{ 
				Fd = GetFdFromName(command[1]); 
				if(Fd == -1) 
				{ 
					printf("\n\t Error : Incorrect parameter :"); 
					continue; 
				} 
				iRet = LseekFile(Fd,atoi(command[2]),atoi(command[3])); 
				if(iRet == -1) 
				{ 
					printf("\n\t ERROR : Unable to perform lseek :"); 
				} 
			} 
			else 
			{ 
				printf("\n\t ERROR : Command not found !!! :"); 
				continue; 
			} 
		} 
		else 
		{ 
			printf("\n ERROR : Command not found !!!\n"); 
			continue; 
		} 
	} 
	return 0; 
}


int GetFdFromName(char *Name) 
{ 
	int iCounter = 0; 
	
	while(iCounter <50) 
	{ 
		if(UFdTArr[iCounter].ptrfiletable != NULL) 
		if(strcmp((UFdTArr[iCounter].ptrfiletable->ptrinode->FileName),Name)==0) 
		break; 
		iCounter ++; 
	} 

	if(iCounter  == 50)
		 return -1; 
	else 
		return iCounter ; 
} 

PINODE Get_Inode(char * Name) 
{ 
	PINODE temp = head;

	if(Name == NULL) 
	return NULL; 

	while(temp!= NULL) 
	{ 
		if(strcmp(Name,temp->FileName) == 0) 
		break; 
		temp = temp->next; 
	}
	return temp; 
} 

void CreateDILB() 
{ 
	int iCounter  = 1; 
	PINODE newn = NULL; 
	PINODE temp = head; 

	while(iCounter <= MAXINODE) 
	{ 
		newn = (PINODE)malloc(sizeof(INODE)); 

		newn->LinkiCount =0; 
		newn->ReferenceiCount = 0; 
		newn->FileType = 0; 
		newn->FileiSize = 0; 
 
		newn->Buffer = NULL; 
		newn->next = NULL; 
 
		newn->InodeNumber = iCounter ; 
 
	if(temp == NULL) 
	{ 
		head = newn; 
		temp = head; 
	} 
	else 
	{ 
		temp->next = newn; 
		temp = temp->next; 
	} 
	iCounter ++; 
	} 
} 

void InitialiseSuperBlock() 
{ 
	int iCounter  = 0; 
	while(iCounter  < MAXINODE) 
	{ 
		UFdTArr[iCounter].ptrfiletable = NULL; 
		iCounter ++; 
	} 

	SUPERBLOCKobj.TotalInodes = MAXINODE; 
	SUPERBLOCKobj.FreeInode = MAXINODE; 
}

void man(char *Command) 
{ 
	if(Command == NULL)
		return ;
	else if(strcmp(Command,"read")==0)
	{
		printf("\n\t Description : Its used to read Data from regular file : ");
		printf("\n\t Usage       : read file_Name No_of_Bytes_To_Read :");
	}
	else if(strcmp(Command,"creat")==0)
	{
		printf("\n\t Description : used to create new regular file :");
		printf("\n\t Usage       :create file_Name Permission");
	}
	else if(strcmp(Command,"write")==0)
	{
		printf("\n\t Description : It is used to write data into file");
		printf("\n\t Usage       : write File_Desriptor");
		printf("After the command please enter the data\n");
	}
	else if(strcmp(Command,"ls")==0)
	{
		printf("\n\t Description : Its used to List out all files Name : ");
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
	else if(strcmp(Command,"open")==0)
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
		printf("\n\t Usage       : lseek File_Name changeInOffset StatPoint ");
	}
	else if(strcmp(Command,"rm")==0)
	{
		printf("\n\t Description : It is used to delete regular file");
		printf("\n\t Usage       :rm File_Name ");
	}
	else 
	{
		printf("\n\t ERROR : No Any Manual Entry Avaiable");
	}
 
} 

void DisplayHelp() 
{ 

	printf("\n -------------! Its Display All System Call Short information !-------\n");
	printf("\n\t OPEN 	 : Its used to open the Exting file : ");
	printf("\n\t Creat 	 : Its used to Create a New file : ");
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
	printf("\n\t RM 	 : Its used to Remove the File Directories :");
	printf("\n\t EXIT    : Its uesd to close the running process");
	printf("\n --------------------------------------------------------------------\n");
} 

int CreateFile(char *Name,int permission) 
{ 
	int iCounter  = 0; 
	PINODE temp = head; 

	if((Name == NULL) || (permission == 0) || (permission > 3)) 
	return -1; 

	if(SUPERBLOCKobj.FreeInode == 0)
	return -2; 

	(SUPERBLOCKobj.FreeInode)--; 
 
	if(Get_Inode(Name) != NULL) 
	return -3; 

	while(temp!= NULL) 
	{ 
		if(temp->FileType == 0) 
		break; 
		temp=temp->next; 
	} 
 
	while(iCounter <50) 
	{ 
		if(UFdTArr[iCounter ].ptrfiletable == NULL) 
		break; 
		iCounter ++; 
	} 
 
	UFdTArr[iCounter ].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE)); 

	UFdTArr[iCounter ].ptrfiletable->iCount = 1; 
	UFdTArr[iCounter ].ptrfiletable->mode = permission; 
	UFdTArr[iCounter ].ptrfiletable->readoffset = 0; 
	UFdTArr[iCounter ].ptrfiletable->writeoffset = 0; 
	
	UFdTArr[iCounter ].ptrfiletable->ptrinode = temp; 
 
	strcpy(UFdTArr[iCounter ].ptrfiletable->ptrinode->FileName,Name); 
	UFdTArr[iCounter ].ptrfiletable->ptrinode->FileType = REGULAR; 
	UFdTArr[iCounter ].ptrfiletable->ptrinode->ReferenceiCount = 1; 
	UFdTArr[iCounter ].ptrfiletable->ptrinode->LinkiCount = 1; 	
	UFdTArr[iCounter ].ptrfiletable->ptrinode->FileiSize = MAXFILEiSize; 
	UFdTArr[iCounter ].ptrfiletable->ptrinode->FileActualiSize = 0; 
	UFdTArr[iCounter ].ptrfiletable->ptrinode->permission = permission; 
	UFdTArr[iCounter ].ptrfiletable->ptrinode->Buffer = (char *)malloc(MAXFILEiSize); 
 
	return iCounter ; 
} 
int rm_File(char * Name) 
{ 
	int Fd = 0; 

	Fd = GetFdFromName(Name); 
	if(Fd == -1) 
	return -1; 

	(UFdTArr[Fd].ptrfiletable->ptrinode->LinkiCount)--; 

	if(UFdTArr[Fd].ptrfiletable->ptrinode->LinkiCount == 0) 
	{ 
		UFdTArr[Fd].ptrfiletable->ptrinode->FileType = 0; 
		free(UFdTArr[Fd].ptrfiletable); 
		printf("\n\t File Successfully Delete :");
	}

	UFdTArr[Fd].ptrfiletable = NULL; 
	(SUPERBLOCKobj.FreeInode)++; 
	return Fd;
} 

int ReadFile(int Fd, char *Arr, int iSize) 
{ 
	int read_iSize = 0; 

	if(UFdTArr[Fd].ptrfiletable == NULL) return -1; 
	
	if(UFdTArr[Fd].ptrfiletable->mode !=READ && UFdTArr[Fd].ptrfiletable->mode != READ+WRITE)
	return -2; 

	if(UFdTArr[Fd].ptrfiletable->ptrinode->permission != READ && UFdTArr[Fd].ptrfiletable->ptrinode->permission != READ+WRITE) return -2; 

	if(UFdTArr[Fd].ptrfiletable->readoffset == UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) return -3; 

	if(UFdTArr[Fd].ptrfiletable->ptrinode->FileType != REGULAR) return -4; 

	read_iSize = (UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) - (UFdTArr[Fd].ptrfiletable->readoffset); 
	if(read_iSize < iSize) 
	{ 
		strncpy(Arr,(UFdTArr[Fd].ptrfiletable->ptrinode->Buffer) + (UFdTArr[Fd].ptrfiletable->readoffset),read_iSize); 
 
		UFdTArr[Fd].ptrfiletable->readoffset = UFdTArr[Fd].ptrfiletable->readoffset + read_iSize; 
	} 
	else 
	{ 
		strncpy(Arr,(UFdTArr[Fd].ptrfiletable->ptrinode->Buffer) + (UFdTArr[Fd].ptrfiletable->readoffset),iSize); 
 
		(UFdTArr[Fd].ptrfiletable->readoffset) = (UFdTArr[Fd].ptrfiletable->readoffset) + iSize; 
	} 

	return iSize; 
} 

int WriteFile(int Fd, char *Arr, int iSize) 
{ 
	if(((UFdTArr[Fd].ptrfiletable->mode) !=WRITE) && ((UFdTArr[Fd].ptrfiletable->mode) !=READ+WRITE)) return -1; 
 
	if(((UFdTArr[Fd].ptrfiletable->ptrinode->permission) != WRITE) && ((UFdTArr[Fd].ptrfiletable->ptrinode->permission) != READ+WRITE)) return -4; 
 	
 	if((UFdTArr[Fd].ptrfiletable->writeoffset) == MAXFILEiSize) return -2; 
 
	if((UFdTArr[Fd].ptrfiletable->ptrinode->FileType) != REGULAR) return -3; 

	strncpy((UFdTArr[Fd].ptrfiletable->ptrinode->Buffer) + (UFdTArr[Fd].ptrfiletable->writeoffset),Arr,iSize); 

	(UFdTArr[Fd].ptrfiletable->writeoffset) = (UFdTArr[Fd].ptrfiletable->writeoffset )+ iSize; 

	(UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) = (UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) + iSize;	
	return iSize; 
} 

int OpenFile(char *Name, int mode) 
{ 
	int iCounter  = 0; 
	PINODE temp = NULL; 

	if(Name == NULL || mode <= 0) 
	return -1; 
 
	temp = Get_Inode(Name); 
	if(temp == NULL) 
	return -2; 

	if(temp->permission < mode) 
	return -3; 
	
	while(iCounter <50) 
	{ 
		if(UFdTArr[iCounter ].ptrfiletable == NULL) 
		break; 
		iCounter ++; 
	} 

	UFdTArr[iCounter ].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE)); 
	if(UFdTArr[iCounter ].ptrfiletable == NULL) return -1; 
	UFdTArr[iCounter ].ptrfiletable->iCount = 1; 
	UFdTArr[iCounter ].ptrfiletable->mode = mode; 
	if(mode == READ + WRITE) 
	{ 
		UFdTArr[iCounter ].ptrfiletable->readoffset = 0; 
		UFdTArr[iCounter ].ptrfiletable->writeoffset = 0; 
	} 
	else if(mode == READ) 
	{ 
		UFdTArr[iCounter ].ptrfiletable->readoffset = 0; 
	} 
	else if(mode == WRITE) 
	{ 
		UFdTArr[iCounter ].ptrfiletable->writeoffset = 0; 
	} 
	UFdTArr[iCounter ].ptrfiletable->ptrinode = temp; 
	(UFdTArr[iCounter ].ptrfiletable->ptrinode->ReferenceiCount)++; 

	return iCounter ; 
} 

void CloseFileByName(int Fd) 
{ 
	UFdTArr[Fd].ptrfiletable->readoffset = 0; 
	UFdTArr[Fd].ptrfiletable->writeoffset = 0; 
	(UFdTArr[Fd].ptrfiletable->ptrinode->ReferenceiCount)--; 
} 

int CloseFileByName(char *Name) 
{ 
	int iCounter  = 0; 
	iCounter  = GetFdFromName(Name);
	if(iCounter  == -1) 
 return -1; 
 
 UFdTArr[iCounter ].ptrfiletable->readoffset = 0; 
 UFdTArr[iCounter ].ptrfiletable->writeoffset = 0; 
 (UFdTArr[iCounter ].ptrfiletable->ptrinode->ReferenceiCount)--; 

 return 0; 
} 
void CloseAllFile() 
{ 
	int iCounter  = 0; 
	while(iCounter <50) 
	{ 
		if(UFdTArr[iCounter ].ptrfiletable != NULL) 
		{ 
			UFdTArr[iCounter ].ptrfiletable->readoffset = 0; 
			UFdTArr[iCounter ].ptrfiletable->writeoffset = 0; 
			(UFdTArr[iCounter ].ptrfiletable->ptrinode->ReferenceiCount)--; 
			break; 
		} 
		iCounter ++; 
	} 
} 

int LseekFile(int Fd, int iSize, int from) 
{ 
	if((Fd<0) || (from > 2)) return -1; 
	if(UFdTArr[Fd].ptrfiletable == NULL) return -1; 

	if((UFdTArr[Fd].ptrfiletable->mode == READ) || (UFdTArr[Fd].ptrfiletable->mode == READ+WRITE)) 
	{ 
		if(from == CURRENT) 
		{ 
			if(((UFdTArr[Fd].ptrfiletable->readoffset) + iSize) > UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) return -1; 
			if(((UFdTArr[Fd].ptrfiletable->readoffset) + iSize) < 0) return -1; 
			(UFdTArr[Fd].ptrfiletable->readoffset) = (UFdTArr[Fd].ptrfiletable->readoffset) + iSize; 
		} 
		else if(from == START) 
		{ 
			if(iSize > (UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize)) return -1; 
			if(iSize < 0) return -1; 
			(UFdTArr[Fd].ptrfiletable->readoffset) = iSize; 
		} 
		else if(from == END) 
		{ 
			if((UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) + iSize > MAXFILEiSize)  return -1; 
			if(((UFdTArr[Fd].ptrfiletable->readoffset) + iSize) < 0) return -1; 
			(UFdTArr[Fd].ptrfiletable->readoffset) = (UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) - iSize; 
		} 
	} 
	else if(UFdTArr[Fd].ptrfiletable->mode == WRITE) 
	{ 
		if(from == CURRENT)
		{ 
			if(((UFdTArr[Fd].ptrfiletable->writeoffset) + iSize) > MAXFILEiSize) return -1; 
			if(((UFdTArr[Fd].ptrfiletable->writeoffset) + iSize) < 0) return -1; 
			if(((UFdTArr[Fd].ptrfiletable->writeoffset) + iSize) > (UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize)) 
			(UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) = (UFdTArr[Fd].ptrfiletable->writeoffset) + iSize; 
			(UFdTArr[Fd].ptrfiletable->writeoffset) = (UFdTArr[Fd].ptrfiletable->writeoffset) + iSize; 
		} 
		else if(from == START) 
		{ 
			if(iSize > MAXFILEiSize) return -1; 
			if(iSize < 0) return -1; 
			if(iSize > (UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize)) 
			(UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) = iSize; 
			(UFdTArr[Fd].ptrfiletable->writeoffset) = iSize; 
		} 
		else if(from == END) 
		{ 
			if((UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) + iSize > MAXFILEiSize)  return -1; 
			if(((UFdTArr[Fd].ptrfiletable->writeoffset) + iSize) < 0) return -1; 
			(UFdTArr[Fd].ptrfiletable->writeoffset) = (UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize) - iSize; 
		} 
	}
		return Fd;
} 

void ls_file() 
{ 
	
	PINODE temp = head; 

	if(SUPERBLOCKobj.FreeInode == MAXINODE) 
	{ 
		printf("Error : There are no files\n"); 
		return; 
	} 
 
	printf("\nFile Name\tInode number\tFile iSize\tLink iCount\n"); 
	printf("---------------------------------------------------------------\n"); 
	while(temp != NULL) 
	{ 
		if(temp->FileType != 0) 
		{ 
			printf("%s\t\t%d\t\t%d\t\t%d\n",temp->FileName,temp->InodeNumber,temp->FileActualiSize,temp->LinkiCount); 
		} 
		temp = temp->next; 
	} 
	printf("\n---------------------------------------------------------------\n"); 
} 

int fstat_file(int Fd) 
{ 
	PINODE temp = head; 
	
	if(Fd < 0) return -1;
	if(UFdTArr[Fd].ptrfiletable == NULL) 
		return -2; 

	temp = UFdTArr[Fd].ptrfiletable->ptrinode; 

	printf("\n---------Statistical Information about file----------\n"); 
	printf("\n\t File Name : %s",temp->FileName); 
	printf("\n\t Inode Number %d",temp->InodeNumber); 
	printf("\n\t File iSize : %d",temp->FileiSize); 
	printf("\n\t Actual File iSize : %d",temp->FileActualiSize); 
	printf("\n\t Link iCount : %d",temp->LinkiCount); 
	printf("\n\t Reference iCount : %d",temp->ReferenceiCount); 
 
	if(temp->permission == 1) 
	printf("\n\t File Permission : Read only"); 
	else if(temp->permission == 2) 
	printf("\n\t File Permission : Write"); 
	else if(temp->permission == 3) 
	printf("\n\t File Permission : Read & Write"); 
	printf("\n------------------------------------------------------\n"); 

	return 0; 
} 

int stat_file(char *Name) 
{ 
	PINODE temp = head; 

	if(Name == NULL) return -1; 
 
	while(temp!= NULL) 
	{ 
		if(strcmp(Name,temp->FileName) == 0) 
		break; 
		temp = temp->next; 
	} 

	if(temp == NULL) return -2; 

	printf("\n---------Statistical Information about file----------\n"); 
	printf("\n\t File Name : %s",temp->FileName); 
	printf("\n\t Inode Number %d",temp->InodeNumber); 
	printf("\n\t File iSize : %d",temp->FileiSize); 
	printf("\n\t Actual File iSize : %d",temp->FileActualiSize); 
	printf("\n\t Link iCount : %d",temp->LinkiCount); 
	printf("\n\t Reference iCount : %d",temp->ReferenceiCount); 
 
	if(temp->permission == 1) 
	printf("\n\t File Permission : Read only"); 
	else if(temp->permission == 2) 
	printf("\n\t File Permission : Write"); 
	else if(temp->permission == 3) 
	printf("\n\t File Permission : Read & Write"); 
	printf("\n------------------------------------------------------\n"); 

	return 0; 
} 

int truncate_File(char *Name)
{ 
	int Fd = GetFdFromName(Name); 
	if(Fd == -1) 
	return -1; 

	memset(UFdTArr[Fd].ptrfiletable->ptrinode->Buffer,0,1024); 
	UFdTArr[Fd].ptrfiletable->readoffset = 0; 
	UFdTArr[Fd].ptrfiletable->writeoffset = 0; 
	UFdTArr[Fd].ptrfiletable->ptrinode->FileActualiSize = 0; 
	return Fd;
} 
