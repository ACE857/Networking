import java.util.*;

public class client{
	static String appZero(String x){
		int a=x.length(),b=8;
		while(b-a>0){
			x='0'+x;
			a++;
		}
		return x;
	}

	static void getIP(String ips,int[] ipi){
		int i=0;
		for(i=0;i<32;i++){
			ipi[i] = ips.charAt(i)-'0';
		}
	}
	
	static void printIP(int a[]){
		int i,j,k;
		String s;
		System.out.println();
		for(i=0;i<4;i++){
			s="";
			for(j=0;j<8;j++){
				s=s+a[i*8+j];
			}
			System.out.print(Integer.parseInt(s,2)+".");
		}
	}
	
	static void printInt(int[] b){
		int i=0,j=0;
		for(i=0;i<4;i++){
			for(j=0;j<8;j++){
				System.out.print(b[i*8+j]);
			}
			System.out.print(".");
		}
	}
	
	static void printBits(String b){
		int i=0,j=0;
		for(i=0;i<4;i++){
			for(j=0;j<8;j++){
				System.out.print(b.charAt(i*8+j));
			}
			System.out.print(".");
		}
	}
	
	static void setUnset(int[] a,int b,int c,int d,int[] e){
		int i,j;
		for(i=0;i<32;i++){ e[i] = a[i]; }
		for(i=b;i<=c;i++){
			e[i] = d;
		}
	}

	public static void main(String args[]){
		Scanner sc = new Scanner(System.in);
		String ip = sc.next();
		int nm = sc.nextInt();
		int i,j,k,l,m,n;
		String ips[] = ip.split("[.]");
		String sip="";
		for(i=0;i<4;i++){
			sip = sip + appZero(Integer.toBinaryString(Integer.parseInt(ips[i])));
			//System.out.print("\nIP in binary : "+sip+sip.length());
		}
		int iip[] = new int[32];
		System.out.print("\nIP in binary : "); printBits(sip);
		int intIP[] = new int[32];
		getIP(sip,intIP);
		getIP(sip,iip);
		System.out.print("\nIP in int Binary : ");	printInt(iip);
		System.out.print("\nENter No of Subnets : ");	int no = sc.nextInt();
		int sm = (int)Math.ceil(Math.log(no)/Math.log(2))+nm;
		System.out.print("\nNew Subnet Mask "+sm);
		setUnset(iip,nm,31,0,intIP);
		System.out.print("\nNID in int Binary : ");	printInt(intIP);
		setUnset(iip,sm,31,0,intIP);
		System.out.print("\nSID in int Binary : ");	printInt(intIP);
		
		setUnset(iip,nm,31,0,intIP);
		int tmp[] = new int[32];
		for(i=0;i<no;i++){
			String x = Integer.toBinaryString(i);
			for(j=sm-1,k=x.length()-1;j>=nm && k>=0;j--,k--){
				intIP[j] = x.charAt(k)-'0';
			}
			if(i==no-1){
				System.out.print("\n\n");
				setUnset(intIP,sm,31,0,tmp);
				printIP(tmp);
				setUnset(intIP,nm,31,1,tmp);
				printIP(tmp);
			}
			else {
				System.out.print("\n\n");
				setUnset(intIP,sm,31,0,tmp);
				printIP(tmp);
				setUnset(intIP,sm,31,1,tmp);
				printIP(tmp);
			}
		}
		
		
		
		
	}
}


















