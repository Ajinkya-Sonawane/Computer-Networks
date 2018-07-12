/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.*;
import java.lang.Math;

public class SubnetMask {

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args)throws IOException
    {
        // TODO code application logic here
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		String inip;
		int nos,i,j,cl;
                double len;
                char nclass;
		System.out.println("Enter the IP address");
		inip=br.readLine();
		System.out.println("Enter the number of sub-networks");
		nos=Integer.parseInt(br.readLine());
		String[] IP=inip.split("\\.");
        String temp,zer;
	    String[] binip=new String[4];
        String[] binsubmask=new String[4];
        String[] binnetwadd=new String[4];
        String[] binbroadad=new String[4];
        int[] submask=new int[4];
        int[] netwadd=new int[4];
        int[] broadad=new int[4];
        for(i=0;i<4;i++)
        {
	        len=0;
            temp=Integer.toBinaryString(Integer.parseInt(IP[i]));
            zer="";
            if(temp.length()<8)
            {
	            len=8-temp.length();
                for(j=1;j<=len;j++)
                {
	                zer+="0"; 
                }
                temp=zer+temp;
	        }
	        binip[i]=temp;                   
       }
       cl=Integer.parseInt(IP[0]);
       SubnetMask sm=new SubnetMask();
       nclass=sm.findclass(cl);
       binsubmask=sm.calcsub(nclass, nos);
       for(i=0;i<4;i++)
	       submask[i]=Integer.parseInt(binsubmask[i],2);
       System.out.println("Subnet mask: "+submask[0]+"."+submask[1]+"."+submask[2]+"."+submask[3]);
       binnetwadd=sm.calcnet(binsubmask, binip);
       for(i=0;i<4;i++)
	       netwadd[i]=Integer.parseInt(binnetwadd[i],2);
       System.out.println("Network address: "+netwadd[0]+"."+netwadd[1]+"."+netwadd[2]+"."+netwadd[3]);
       binbroadad=sm.calcbroa(binsubmask, binnetwadd);
	   for(i=0;i<4;i++)
	       broadad[i]=Integer.parseInt(binbroadad[i],2);
       System.out.println("Broadcast address: "+broadad[0]+"."+broadad[1]+"."+broadad[2]+"."+broadad[3]);
    }
    public char findclass(int n)
    {
        if(n>=0 && n<=127)
            return 'A';
        else if(n>=128 && n<=191)
            return 'B';
        else if(n>=192 && n<=223)
            return 'C';
        return ' ';
    }
    public String[] calcsub(char c, int nos)
    {
        double len,i;
        String temp;
        String[] s=new String[4];
        switch(c)
        {
            case 'A':
                s[0]="11111111";
                len=0;
                temp="";
                len=Math.ceil(Math.log(nos)/Math.log(2.0));
                for(i=0;i<len;i++)
                    temp+="1";
                for(i=(int)len;i<8;i++)
                    temp+="0";
                s[1]=temp;
                s[2]="00000000";
                s[3]="00000000";
                        break;
            case 'B':
                s[0]="11111111";
                s[1]="11111111";
                len=0;
                temp="";
                len=Math.ceil(Math.log(nos)/Math.log(2.0));
                for(i=0;i<len;i++)
                    temp+="1";
                for(i=(int)len;i<8;i++)
                    temp+="0";
                s[2]=temp;
                s[3]="00000000";
                break;
            case 'C':
                s[0]="11111111";
                s[1]="11111111";
                s[2]="11111111";
                len=0;
                temp="";
                len=Math.ceil(Math.log(nos)/Math.log(2.0));
                for(i=0;i<len;i++)
                    temp+="1";
                for(i=(int)len;i<8;i++)
                    temp+="0";
                s[3]=temp;
                break;
        }
        return s;
    }
    public String[] calcnet(String sm[], String ip[])
    {
        int[] suma=new int[4];
        int[] ipad=new int[4];
        int[] neta=new int[4];
        String[] binneta=new String[4];
        String temp,zer;
        int len;
        int i,j;
        for(i=0;i<4;i++)
        {
            suma[i]=Integer.parseInt(sm[i],2);
            ipad[i]=Integer.parseInt(ip[i],2);
            neta[i]=suma[i]&ipad[i];
        }
        for(i=0;i<4;i++)
        {
            len=0;
            temp=Integer.toBinaryString(neta[i]);
            zer="";
            if(temp.length()<8)
            {
                len=8-temp.length();
                for(j=1;j<=len;j++)
                {
                    zer+="0"; 
                }
                temp=zer+temp;
            }
            binneta[i]=temp;                   
        }
        return binneta;
    }
    public String[] calcbroa(String sm[], String nw[])
    {
        int[] suma=new int[4];
        int[] ipad=new int[4];
        int[] broa=new int[4];
        String[] binbroa=new String[4];
        String temp,zer;
        int len,count=0;
        int i,j, index,sp;
        for(i=0;i<4;i++)
        {
            j=0;
            for(;j<8;j++)
            {
                if(sm[i].charAt(j)=='1')
                    count++;
            }
        }
        index=count/8;
        sp=count%8;
        binbroa=nw;
        for(i=sp;i<8;i++)
        {
            binbroa[index]=binbroa[index].substring(0,i)+'1'+binbroa[index].substring(i+1);
        }
        return binbroa;
    }
}
