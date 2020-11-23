import java.io.*;
import java.util.*;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileInputStream;
class Main
{
	public static void main(String arg[])
	{
		Scanner Sobj=new Scanner(System.in);
		System.out.println("-----------------------------------");
		System.out.println("\n Project_Name : Packer-Unpacker(CMD) ");
		while(true)
		{	
			System.out.println("\n-----------------------------------");
			System.out.println("\t1.Packing");
			System.out.println("\t2.Unpacking");
			System.out.println("\t3.Exit");
			System.out.println("\n-----------------------------------");
			System.out.print("ENter Your Choice :");

			int iChoice=Sobj.nextInt();
			switch(iChoice)
			{
				case 1:
					System.out.print("Enter Directory name :");
					String Dir=Sobj.next();

					System.out.print("Enter FileName name :");
					String FileName=Sobj.next();
					Packer pobj=new Packer(Dir,FileName);
					break;
				
				case 2:
					System.out.println("Enter Packed file Name");
					String PackFName=Sobj.next();
					Unpacker uobj=new Unpacker(PackFName);
					break;
				
				case 3:
					System.out.println("\n--------------------------------------");
					System.out.println("\n Thank-You for Using My Application By CMD Style : ");
					System.out.println("\n---------------------------------------");
					System.exit(0);	
				
				default:
					System.out.println("Your Choice is Wrong");		
			}
		}	
	}
}
class Packer
{
	public FileOutputStream outstream=null;

	public Packer(String FolderName,String FileName)
	{
		try
		{
			
			File outfile=new File(FileName);
			outstream=new FileOutputStream(FileName);
			TravelDirectory(FolderName);
		}
		catch(Exception obj)
		{
			System.out.println(obj);
		}
	}
	public void TravelDirectory(String path)
	{
		File directoryPath =new File(path);
		File arr[]=directoryPath.listFiles();
		int iCounter=0;
		System.out.println("-------------------------------\n");
		for(File filename:arr) 
		{
           if(filename.getName().endsWith(".txt"))
            {	
            	iCounter ++;
            	System.out.println("Packed File :"+filename.getName());
            	PackFile(filename.getAbsolutePath());
        	}
        }	

		System.out.println("-------------------------------");
		System.out.println("Succesfully packed files : "+iCounter);
		System.out.println("-------------------------------\n");
	}
	public void PackFile(String FilePath)
	{
		
		byte Header[]=new byte[100];
		byte Buffer[]=new byte[1024];
		int iLength=0;

		FileInputStream istream=null;

		File fobj=new File(FilePath);
		
		String Temp= FilePath+" "+fobj.length();
		
		for(int iCnt =Temp.length(); iCnt < 100 ; iCnt ++)
		{
			Temp=Temp +" ";
		}
		Header =Temp.getBytes();
		try
		{
			istream =new FileInputStream(FilePath);

			outstream.write(Header,0,Header.length);
			while((iLength=istream.read(Buffer))>0)
			{	
				outstream.write(Buffer,0,iLength);
			}
			istream.close();
		}
		catch(Exception obj)
		{}	
				
	}
}
class Unpacker
{
	FileOutputStream outstream =null;
	public Unpacker(String src)
	{
		unpackFile(src);
	}
	public void unpackFile(String FilePath)
	{
		try
		{
			FileInputStream instream =new FileInputStream(FilePath);
			byte Header[]=new byte[100];
			int iLength=0;
			int iCounter=0;

			while((iLength=instream.read(Header,0,100))>0)
			{
				String str=new String(Header);

				String ext=str.substring(str.lastIndexOf("\\"));
				ext=ext.substring(1);

				String words[]=ext.split("\\s");
				String sName=words[0];
				int iSize=Integer.parseInt(words[1]);

				byte bArr[]=new byte[iSize];
				instream.read(bArr,0,iSize);

				System.out.println("\n New File gets created as :"+sName);
				FileOutputStream fout=new FileOutputStream(sName);
				fout.write(bArr,0,iSize);

				iCounter ++;
			}
			
			System.out.println("\n Sucessfully Unpacked Files :"+iCounter);
		}
		catch(Exception obj)
		{

		}	
	}
}	
