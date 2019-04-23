import java.net.*; 
import java.util.*; 

public class IPget 
{ 
	public static void main(String[] args){ 
		String host; 
		System.out.println("\t********** Domain Name System ************");
		Scanner input = new Scanner(System.in); 
		System.out.print("\n Enter  valid host name: "); 
		host = input.nextLine(); 
		try { 
			InetAddress address = InetAddress.getByName(host);
			
			System.out.println("IP address: " + address.getHostAddress());
			System.out.println("Host name : " + address.getHostName());  

			System.out.println("Host name and IP address: " + address.toString()); 


		} 
		catch (UnknownHostException ex) {
		     System.out.println("Could not find " + host); 
		}
		String ip;
		System.out.print("\n Enter valid IP: "); 
		ip = input.nextLine(); 
		try { 
			

	        InetAddress address1 = InetAddress.getByName(ip);
			System.out.println("IP address: " + address1.getHostAddress());
			System.out.println("Host name : " + address1.getHostName());  
			System.out.println("Host name and IP address: " + address1.toString()); 
		} 
		catch (UnknownHostException ex) {
		     System.out.println("Could not find " + ip); 
		}


	} 
}
