#include "finale1.c"
#include<stdio.h>
#include<stdlib.h>
struct pmus
{
	int src;
	int dest;
};
void checkforone(int *,int *,struct graph *,int *,int );
void sim(struct graph *,int,struct pmus * ,int ,int *,int **);
int max(int a[],int n)
{

	int max2=0,max1=a[0]; //max2 for storing vertex which has higher degree
	for(int i=1;i<n;i++)
	{
		if(a[i] > max1 )
		{
			max1=a[i];
			max2=i;
		}
	}
	return max2; //returns  vertex which has higher degree
}
int min(struct graph *g,int s,int degree[],int *visit)
{
	struct node *temp= g->array[s].head;
	while(visit[temp->data]==1)
	{
		temp=temp->next;
	}

	int d= degree[(temp->data)];
	int d1= temp->data;
	while(temp!=NULL)
	{
		if( d > degree[(temp->data)] )
		{
			if(visit[(temp->data)]!=1) //chances of choosing same vertex again
			{
				d= degree[(temp->data)];
				d1= temp->data;
				
			}
		}
		temp=temp->next;
	}
	return d1;
} 
void update(struct graph *g,int *degree,int *count,int n,int *visit)
{
	if((*count)!= (n+1)){
		for(int i=0;i<n;i++)
		{
			struct node *t=g->array[i].head;
			int cnt=0;
			while(t!=NULL)
			{
				if(visit[t->data]!=1)
				{
					cnt++;
				}
				t=t->next;
			}
			degree[i]=cnt;
		}

		checkforone(degree,count,g,visit,n);  
	}
}

void checkforone(int *degree,int *count,struct graph *g,int *visit,int n)
{
	if((*count)!=n)
	{

		for(int i=0;i<n;i++)
		{
			int cp=0,cpp,count1; // cpp for storing vertex which is one and only unvisited 
			struct node *temp = g->array[i].head;
			if(visit[i]==1)
			{     
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
					(*count)+=1;
					update(g,degree,count,n,visit);


				}
			}
		}
	}

}


void greedy(struct graph *g,int n, int *degree,int *visit,int m,int **adj,int *degree1)
{
	struct pmus pmu[m];
	for(int i=0;i<m;i++)
	{
		pmu[i].src=pmu[i].dest=-1;
	}

	int count=0,p=0; 
	while(count != n)
	{
		int s=max(degree,n); // source vertex
		int d=min(g,s,degree,visit); // destination by taking minimum degree in N(s)
		if(visit[s]==0 && visit[d]==0)
		{
			count+=2;                    //there may be a chance of taking same vertex again
		}
		else if(visit[s]==0 || visit[d]==0)
		{
			count+=1;
		}
		visit[s]=visit[d]=1;
		pmu[p].src=s;
		pmu[p].dest=d;
		update(g,degree,&count,n,visit); //update degree when of each vertex iff it's neighbours are visited
		p++; //increment number of PMU's

	}

	printf("----------------------------------------------\n");
	printf("total no.of PMU's needed are %d \n",p);
	printf("PMU's placed edges are\n");
	for(int i=0;i<m;i++)
	{
		if(pmu[i].src !=-1)
		{
			printf("%d ---> %d\n",pmu[i].src,pmu[i].dest); 
		}

	}
     sim(g,n,pmu,p,degree1,adj);
}
