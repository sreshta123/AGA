#include "sim.c"
#include "math.h"
int check(int first,struct pmus *pmu,int p)
{
	int flag=0;
	for(int i=0;i<p;i++)
	{
		if(pmu[i].src == first)
		{
			flag=1; /////////////break
		}
		else if(pmu[i].dest==first)
		{
			flag=1;
		}
	}
	return flag;
}
int* randoms(struct pmus *pmu,int p,int n,int *degree,int **adj)
{

	int* ra=(int *)malloc(2 * sizeof(int));
	ra[0]=-1;
	ra[1]=-1;
	int first=rand()%n,end,pos,flag=0;
	int ff=check(first,pmu,p);

	while(degree[first]==1 && ff==1)
	{
		first=rand()%n;
		ff=check(first,pmu,p);
	}
	for(int i=0;i<p;i++)
	{
		if(pmu[i].src == first)
		{
			flag=1;
			pos=pmu[i].dest;   //storing matched src/dest value
		}
		else if(pmu[i].dest==first)
		{
			flag=1;
			pos= pmu[i].src;
		}
	}
	if(flag==1)
	{
		end=rand()%n;
		while(first == end || adj[first][end] !=1 || pos== end)
		{
			end=rand()%n;
		}
	}
	else
	{
		end=rand()%n;
		while(first==end  || adj[first][end]!=1)
		{
			end=rand()%n;
		}
	}
	ra[0]=first;
	ra[1]=end;

	return ra;
}
int cover(struct pmus *pmu,int p,int n,struct graph *g)
{
	int visit[n],yes,count=0,pos; 


	for(int  i=0;i<n;i++)
	{
		visit[i]=0;
	}
	for(int i=0;i<p;i++)
	{
		if(visit[pmu[i].src]==0 && visit[pmu[i].dest]==0)
		{
			count+=2; 
		}
		else if(visit[pmu[i].src]==0 || visit[pmu[i].dest]==0)
		{
			count+=1;
		}
		visit[pmu[i].src]=1;
		visit[pmu[i].dest]=1; 
	}


	int i=0;
	while(i<n )
	{
		int cp=0,cpp,count1; // cpp for storing vertex which is one and only unvisited 
		if(visit[i]==1)
		{	
			struct node *temp = g->array[i].head;
			while(temp!=NULL)
			{
				if(visit[(temp->data)]==0)
				{
					cp++;
					cpp=temp->data;
				}
				temp=temp->next;
			}
			if(cp==1)
			{
				visit[cpp]=1;
				count+=1;
				i=0; 

			}
			else
			{
				i++;}}

		else
		{ i++;}

	}
	int count1 = n-count;
	return count1;
}
int fact(int n)
{
	int i,f=1;
	for(int i=1;i<=n;i++)
	{
		f=f*i;
	}
	return f;
}

int sims(struct pmus *newpmu,int test,int n, struct graph *g,int * degree1,int **adj)
{
	int e = cover(newpmu,test,n,g); //checking satisfiability
	//printf("c is %d \n",c); 
	//srand(time(NULL));

	float t=15;  //initial temperature
	for(int i=0;i<50;i++)  //globally running
	{
		if(t > 0)
		{
			for(int j=0;j<10;j++)  //internally for each temperature 
			{
				int cp = rand()%test;       //randomly displacing a PMU
				int first = newpmu[cp].src;
				int second=newpmu[cp].dest;  
				int *fa= randoms(newpmu,test,n,degree1,adj); //random selection of PMU's
				newpmu[cp].src = fa[0];
				newpmu[cp].dest = fa[1];
				int e1 = cover(newpmu,test,n,g);  //checking satisfiablity function
				if(e1 == 0)
				{
					return 1;
					break;
				}
				int e2 = e1 - e; // if diff is negative will accept else
				if( e2 > 0)
				{
					float t1 = e2/t;
					float exp = pow(2.71,t1);   //probability function where 2.71 is bolatzmnn constant
					if(exp > 0 && exp < 1)
					{
						continue;
					}
					else
					{
						newpmu[cp].src= first;
						newpmu[cp].dest = second;  //if not accepted go back to previous edges location

					}
				}
			}
			t = 0.879*(t); // decrease temperature
		}
	}
	return 0;

}


































