#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define MAXFILES 1000
#define MAXINODES 1000
#define FILESIZE 1024

#define READ  1
#define WRITE 2

#define REGULAR 1

#define START  0
#define CURRENT 1
#define END 2

struct SuperBlock
{
	int TotalInodes;
	int FreeInode;

};
struct inode
{
	char FileName[50];
	int Inode_Number;
	int File_Size;
	int File_Type;
	int Actual_File_Size;
	int Link_Count;
	int Reference_Count;
	int Permission;
	char *Data;
	struct inode *pNext;
	
};

typedef struct inode INODE;
typedef struct  inode *PINODE;
typedef struct inode ** PPINODE;

struct FileTable
{
	int ReadOffSet;
	int WriteOffset;
	int Count;
	PINODE ptriNode;
	int Mode;
};
typedef FileTable FILETABLE;
typedef FileTable *PFILETABLE;

struct UFDT
{
	PFILETABLE ptrfiletable;
};
typedef struct UFDT UFDTOBJ;


void CreateUFDT();
void CreatSuperBlock();
void CreateDILB();
void SetEnvoirnment();
void DisplayHelp();
void ManPage(char *);
bool CheckFile(char *);
int CreateFile(char *,int );
void ls_file();
int WriteFile(int ,char *,int );
void DeleteFile(char *);
int GetFDFromName(char *Name);
PINODE Get_Inode(char * Name);
int OpenFile(char *Name,int Mode);
int CloseFileByName(char *Name);
void CloseAllFiles();
int ReadFile(int Fd,char *Arr,int iSize);
int StatFile(char *Name);
int FstatFile(int Fd);
int TruncateFile(char *Name);
int lseekFile( int Fd,int Size, int From);
