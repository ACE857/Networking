import java.util.*;
import java.lang.*;
import java.io.*;
class lsr
{
    static int V;
    public lsr(int n)
    {
        V=n;
    }
    int minD(int dist[], Boolean vis[])
    {
        int min = Integer.MAX_VALUE, min_index=-1;
        for (int v = 0; v < V; v++)
            if (vis[v] == false && dist[v] <= min)
            {
                min = dist[v];
                min_index = v;
            }
        return min_index;
    }

    void getTable(int dist[], int n,int par[])
    {
        for (int i = 0; i < V; i++)
        {
            int ans = par[i];
            while(par[ans]!=ans)
            {
                ans=par[ans];
            }
            System.out.println("Dest "+i+" Cost "+dist[i]+"  NextHop "+ans);
        }
    }
 
    void shortPath(int graph[][], int src)
    {
        int dist[] = new int[V]; 
    
        Boolean vis[] = new Boolean[V];
        int par[] = new int[V];
   
        for (int i = 0; i < V; i++)
        {
            dist[i] = Integer.MAX_VALUE;
            vis[i] = false;
        }
        dist[src] = 0;
        par[src]=src;
        for (int count = 0; count < V-1; count++)
        {
           
            int u = minD(dist, vis);
            vis[u] = true;
 
            for (int v = 0; v < V; v++)
 
                if (!vis[v] && graph[u][v]!=-1 && graph[u][v]!=0 &&
                        dist[u] != Integer.MAX_VALUE &&
                        dist[u]+graph[u][v] < dist[v])
                {dist[v] = dist[u] + graph[u][v]; if(u!=src) par[v]=u; else par[v]=v; }
        }
 
        getTable(dist, V,par);
    }
 
 
    public static void main (String[] args)
    {
       int i,j,k,m,n;
       Scanner sc=new Scanner(System.in);
       System.out.print("\nEnter Total no of Routers ");    n=sc.nextInt();
       int routers[][] = new int[n][n];
       
     System.out.print("\nEnter Total Links "); m = sc.nextInt();
     for(i=0;i<m;i++)
     {
         System.out.print("\nEnter Src Dest And Cost  ");
         j=sc.nextInt(); k = sc.nextInt();    routers[j][k] = sc.nextInt(); routers[k][j] = routers[j][k];
     }
     for(i=0;i<n;i++)
     {
         for(j=0;j<n;j++) if(routers[i][j]==0) routers[i][j]=-1;
     }  
     for(i=0;i<n;i++) routers[i][i]=0;
     
   System.out.println();
      for(i=0;i<n;i++)
     {
        for(j=0;j<n;j++)
      {
        System.out.print(routers[i][j]+" ");
      }
       System.out.println();
     }
        lsr l = new lsr(n);
       for(i=0;i<n;i++)
       {
           System.out.println("Routing table for  "+i);
          l.shortPath(routers, i);
         System.out.println();
       }
    }
}


