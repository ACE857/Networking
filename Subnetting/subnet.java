
package suraj;
import java.util.*;
public class subnet{
	public static void main(String args[]){
		Scanner sc= new Scanner(System.in);
		System.out.print("Enter IP address  :  ");
		String ip=sc.nextLine();

		int in=0,i,netsub,submask,nosub,j,k,l;
		int nsub[] = new int[32];
		int subm[] = new int[32];
		String split_ip[] = ip.split("\\.");
		


		String split_bip[]= new String[4];

		String bip = "";

		for(i=0;i<4;i++)
		{
			split_bip[i]=appendZeroes(Integer.toBinaryString(Integer.parseInt(split_ip[i])));
			bip+=split_bip[i]+" ";
		}
		System.out.println("Binary IP : "+bip);
	
	int ips[] = new int[32];
	
	for(i=0;i<bip.length();i++)
	{
		if(bip.charAt(i)!=' '){
			ips[in++] = (int)bip.charAt(i)-48;
		}
		
		
	}
	
	System.out.print("\n\nEnter Network Subnet Mask ");	
	netsub = sc.nextInt();  //  no of bits in network ID 
	
	
                        setUnsetBits(nsub, 0, netsub-1, 1);
                        System.out.print("\n\nNetwork Subnet Mask   ");
                        printIPBits(nsub);
        
        
                        System.out.print("\n\nEnter No of Subnets Required ");
                        nosub = sc.nextInt();       //  total no os subnets required
                        
                        int bits=(int)Math.ceil(Math.log(nosub)/Math.log(2));
                        submask=bits+netsub;      //    final no of bits in subnet mask
	
                        
                        setUnsetBits(subm, 0, submask-1, 1);
                        System.out.print("\n\nSubnetMask After Subnetting  ");
                        printIPBits(subm);
        
                        int intsub[] = new int[4];
                        getIP(subm, intsub);
                        
                        System.out.print("    ");
                        printIPNum(intsub);
	
                        //  get the subnet divisions here
                        
                        int networkID[]=new int[32];
                        for(i=0;i<32;i++){
                            networkID[i]=ips[i]&nsub[i];
                        }
                        System.out.print("\n\nNetworkID  ");
                        printIPBits(networkID);
                        
                        for(i=0;i<nosub;i++){
                            String s = Integer.toBinaryString(i);
                            for(j=submask-1,k=s.length()-1;j>=netsub-1 && k>=0;j--,k--){
                                networkID[j]=s.charAt(k)-'0';
                            }
                      /*      System.out.print("\n"+s+"\n");
                            printIPBits(networkID);
                           */ 
                      if(i+1==nosub){
                           System.out.print("\n\nThe Group "+(i+1)+" IP address ranges are \n");
                            setUnsetBits(networkID, submask, 31, 0);
                            printIPBits(networkID);
                            getIP(networkID, intsub);
                            System.out.print("    ");
                            printIPNum(intsub);
                            System.out.print("\nTo\n");
                            setUnsetBits(networkID, netsub, 31, 1);
                            printIPBits(networkID);
                            getIP(networkID, intsub);
                            System.out.print("    ");
                            printIPNum(intsub);
                      }
                      
                     else {
                            System.out.print("\n\nThe Group "+(i+1)+" IP address ranges are \n");
                            setUnsetBits(networkID, submask, 31, 0);
                            printIPBits(networkID);
                            getIP(networkID, intsub);
                            System.out.print("    ");
                            printIPNum(intsub);
                            System.out.print("\nTo\n");
                            setUnsetBits(networkID, submask, 31, 1);
                            printIPBits(networkID);
                            getIP(networkID, intsub);
                            System.out.print("    ");
                            printIPNum(intsub);
                      }
                        }
                        
                        
                        //  get the subnet divisions here
        
	System.out.print("\n\n\nEntire Network Address Range is \n");
                        setUnsetBits(networkID, netsub, 31, 0);
                        printIPBits(networkID);
                        getIP(networkID, intsub);
                        System.out.print("    ");
                        printIPNum(intsub);
                        System.out.print("\nTo\n");
                        setUnsetBits(networkID, netsub, 31, 1);
                        printIPBits(networkID);
                        getIP(networkID, intsub);
                        System.out.print("    ");
                        printIPNum(intsub);
                
	
	
	}
	
	
	
	static String appendZeroes(String s)
		{
			String temp= new  String("00000000");
			return temp.substring(s.length())+ s;
		}
        
                        static void getIP(int a[],int ans[]){
                            
                            int i,j,k,l;
                            String ip;
                            for(i=0;i<4;i++){
                                ip="";
                                for(j=0;j<8;j++){
                                    ip=ip+a[8*i+j];
                                }
                                ans[i]=Integer.parseInt(ip,2);
                            }
                            
                        }
                        
                        static void setUnsetBits(int []a,int x,int b,int c){
                            int i,j,k,l;
                            for(i=x;i<=b;i++) a[i]=c;
                        }
                        
                        static void printIPBits(int a[]){
                            for(int i=0;i<32;i++) {System.out.print(a[i]); if((i+1)%8==0) System.out.print("."); }
                        }
                        static void printIPNum(int a[]){
                           for(int i=0;i<4;i++) System.out.print(a[i]+".");
                        }
                        
                        


}

