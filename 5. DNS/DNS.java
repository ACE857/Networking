import javax.naming.directory.Attributes;
import javax.naming.directory.InitialDirContext;
import javax.naming.NamingEnumeration;
import javax.naming.NamingException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Scanner;
public class DNS
{
    public static void main(String args[])
    {
        
        String url;
        System.out.print("\nEnter URL of Website : ");
        Scanner sc = new Scanner(System.in);
        url = sc.next();
        try
        {
            InetAddress inetAddress;
            if (Character.isDigit(url.charAt(0)))
            {   
                byte[] b = new byte[4];
                String[] bytes = url.split("[.]");
                for (int i = 0; i < bytes.length; i++)
                {
                    b[i] = new Integer(bytes[i]).byteValue();
                }
                
                inetAddress = InetAddress.getByAddress(b);
            }
            else
            {   
                inetAddress = InetAddress.getByName(url);
            }

            System.out.println(inetAddress.getHostName() + " - " + inetAddress.getHostAddress());
            
        }
        catch (UnknownHostException exception)
        {
            System.err.println(" ");
        }
    }
}
