
import java.util.*;
import java.io.*;
import java.net.*;




public class sub {
	Scanner sc = new Scanner(System.in); 
    String ip;	
    
    static String appendZeroes(String s)
    {
    String temp= new  String("00000000");
    return temp.substring(s.length())+ s;
    }
     
    void Find_class()throws IOException
	{
		DataInputStream dis = new DataInputStream(System.in);
        System.out.println("Enter IP Address");
        String ipAddr1 = dis.readLine();
        String[] ipAddrParts=ipAddr1.split("\\.");
        String mask="";
        int firstoctet = Integer.parseInt(ipAddrParts[0]);
        if(firstoctet<=127)
        {
                        mask = "255.0.0.0";
                        System.out.println("Class A IP Address");
                        System.out.println("The Subnet mask is: "+mask);
        }
        else if(firstoctet>=128 && firstoctet<=191)
        {
                        mask = "255.255.0.0";
                        System.out.println("Class B IP Address");
                        System.out.println("The Subnet mask is: "+mask);
        }
        else if(firstoctet>=192 && firstoctet<=223)
        {
                        mask = "255.255.255.0";
                        System.out.println("Class C IP Address");
                        System.out.println("The Subnet mask is: "+mask);
        }
        else if(firstoctet>=224 && firstoctet<=239)
        {
                        mask = "255.0.0.0";
                        System.out.println("Class D IP Address; Used for multicasting");
        }
        else if(firstoctet>=240 && firstoctet<=254)
        {
                        mask = "255.0.0.0";
                        System.out.println("Class D IP Address; Experimental Use");
        }
		
		String split_ip[]=ipAddr1.split("\\.");
		
		String split_bip[]= new String[4];
		String bip = "";

		for(int i=0;i<4;i++)
		{
		split_bip[i]=appendZeroes(Integer.toBinaryString(Integer.parseInt(split_ip[i])));
		bip+=split_bip[i];
		}
		System.out.println("\nThe binary IpAddress is:"+bip);

		

		System.out.println("\nEnter no of address for each subnet:");
		int n=sc.nextInt();
        System.out.println("-----------------------");
		int bits=(int)Math.ceil(Math.log(n)/Math.log(2));
		
		int c=0;
		int mask1=32-bits;
		for(int i=bits;i<=7;i++)
		{
			
			c=c+(int)Math.pow(2,i);
		}
		System.out.println(c);
	
			
		int total_address=(int)Math.pow(2,bits);
		if(mask1>=0 && mask1<=8)
		{
			System.out.println("Subnet mask is= "+c+"0.0.0");
		}
		else if(mask1>8 && mask1<=16)
		{System.out.println("Subnet mask is= 255."+c+".0.0");
			
		}
		else if(mask1>16 && mask1<=24)
		{
			System.out.println("Subnet mask is= 255.255"+c+".0");
		}
		else if(mask1>24 && mask1<=32)
		{
			System.out.println("Subnet mask is= 255.255.255."+c);
		}
		
		int fbip[]=new int[32];

		for(int i=0;i<32;i++)
		{


		fbip[i]=(int)bip.charAt(i)-48;

		}

		for(int i=31;i>31-bits;i--)
		{
		

		fbip[i] &=0;
		}

		String fip[]={"","","",""};
		for(int i=0;i<32;i++)
		{
		fip[i/8]=new String(fip[i/8]+fbip[i]);
		} 
		int first_offset=0;
		int ipAddr[]=new int[4];  	
		System.out.println("------------------------------");
		
		for(int i=0;i<4;i++)
		{
		System.out.print(ipAddr[i]=first_offset=Integer.parseInt(fip[i],2));
		if(i!=3)
		System.out.print(".");
		}
		System.out.println();


	
		int lbip[]=new int [32];

		for(int i=0;i<32;i++)
		{
		
		lbip[i]=(int)bip.charAt(i)-48;
		}

		for(int i=31;i>31-bits;i--)
		{

		
		lbip[i]|= 1;
		}
		 String lip[]={"","","",""};
		for(int i=0;i<32;i++)
		{
		lip[i/8]=new String(lip[i/8]+lbip[i]);
		}
		int ipLast[]=new int[4]; 
		
		for(int i=0;i<4;i++)
		{
		System.out.print(ipLast[i]=Integer.parseInt(lip[i],2));
		if(i!=3)
		System.out.print(".");
		}
		System.out.println("\n------------------------------------");
		System.out.println();
		int scount=(int)Math.pow(2,bits);
		int no1=256/scount;
		
		
		
		for(int j=1;j<no1;j++)
		{
		//System.out.println(" GROUP "+ (j+1)+" FIRST ADDRESS:");
		for(int i=0;i<4;i++)
		{
		if(i<3)
		{
		System.out.print(ipAddr[i]+".");
		}
		else
		System.out.println(ipAddr[i]=ipAddr[i]+total_address);
		}
		//System.out.println(" GROUP "+ (j+1)+" LAST ADDRESS:");
		for(int i=0;i<4;i++)
		{
		if(i<3)
		{
		System.out.print(ipLast[i]+".");
		}
		else
		System.out.println(ipLast[i]=ipLast[i]+total_address);

		}
		System.out.println();
		}
	}
	
	
	public static void main(String args[])throws IOException
	{	Scanner sc = new Scanner(System.in); 
	sub s=new sub();
	
		int ch;
		do{
			System.out.println("1.Find the class and Default Subnet mask of the ip address");
			System.out.println("2.Ping with another pc");
			System.out.println("3.Exit");
			System.out.println(" choice:");
			ch=sc.nextInt();
			switch(ch)
			{
			case 1:s.Find_class();
			       break;
			case 2: String adr;
                  				try
                  				{
                  					System.out.println("Enter the IP address to ping:");
                  					adr=sc.nextLine();
                  					adr=sc.nextLine();
                  					Process p1=java.lang.Runtime.getRuntime().exec("ping -c 5 "+adr);
                  					BufferedReader reader=new BufferedReader(new InputStreamReader(p1.getInputStream()));
                  					String line="";
                  					while((line=reader.readLine())!=null)
                  					{
                  						System.out.println(line);
                  					}
                  					int returnVal=p1.waitFor();
                  					if(returnVal==0)
                  						System.out.println("\n\nHost Reachable!");
                  					else if(returnVal==2)
                  						System.out.println("Host Unreachable!");
                  					
                  				}
                  				catch(Exception e)
                  				{
                  					System.out.println(e);
                  				}
                     break;
			}
			
						
		}while(ch!=3);
	}

}
