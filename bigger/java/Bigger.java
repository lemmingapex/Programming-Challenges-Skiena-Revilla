/*******************************************************************************/
//  Bigger.java
//  NAME: Scott Wiedemann
//  DATE: 10/27/10
//  PROBLEM: Is bigger smarter?
/*******************************************************************************/

import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.*;

public class Bigger
{	
	public static void main(String arg[])
	{
		System.out.println("test\n");
		new Bigger();
		System.out.println("test\n");
		return;
	}
	
	public Bigger()
	{
		read();
		solve();
		print();
	}
	
	ArrayList<Elephant> elephants=new ArrayList<Elephant>();
	
	public class Elephant
	{
		int id;
		int iq;
		int size;
		
		public Elephant()
		{
			iq=0;
			size=0;
		}

		public Elephant(int IQ, int SIZE, int ID)
		{
			iq=IQ;
			size=SIZE;
			id=ID;
		}

		/*
		public int count()
		{
			int count=0; 
			for(int i=0; i<friends.size(); i++)
			{
				if(this.friends.get(i).side==this.side)
				{
					count++;
				}
				else
				{
					count--;
				}
			}
			return count;
		}
*/
	
	}


	class SizeComparator implements Comparator<Object>
	{
		public int compare(Object e1, Object e2)
		{
			int e1Size = ((Elephant)e1).size;
			int e2Size = ((Elephant)e2).size;
			if(e1Size > e2Size)
				return 1;
			else if(e1Size < e2Size)
				return -1;
			else
				return 0;
		}
	}

	class IQ implements Comparator<Object>
	{
		public int compare(Object e1, Object e2)
		{
			int e1Size = ((Elephant)e1).iq;
			int e2Size = ((Elephant)e2).iq;
			if(e1Size > e2Size)
				return 1;
			else if(e1Size < e2Size)
				return -1;
			else
				return 0;
		}
	}
	
	public void solve()
	{
		Collections.sort(elephants, new SizeComparator());
		/*
		int last;
		for(int i=0; i<powerLevel; ++i)
		{
			last=0;
			splitNodes();
			totalCrossEdges = getScore(Graph);
			int minValueFound = totalCrossEdges;
			do
			{
				System.out.println("Cross Edges: " + minValueFound);
				last = totalCrossEdges;
				minValueFound = getBest(minValueFound,1);
			}
			while(minValueFound != last);
			updateBestGraph();
			System.out.println("\n");
		}
		*/
	}
	
	public void read()
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Scanner scan = new Scanner(br);

		int IQ;
		int SIZE;
		int ID=0;

		while(scan.hasNext())
		{
			ID++;
			IQ = scan.nextInt();
			SIZE = scan.nextInt();
			elephants.add(new Elephant(IQ,SIZE,ID));
		}
	}
	
	public void print()
	{

		for(int i=0; i<elephants.size(); i++)
		{
			//System.out.println(elephants.get(i).iq);
			System.out.println(elephants.get(i).size);
		}
	}
}
