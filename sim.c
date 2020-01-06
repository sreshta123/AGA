//compile with -lm for sims1.c (pwr function included)
//sim.c contains binary search type
//sims1.c actual simulated annealing method
#include "greedy.c"
int sims(struct pmus *,int,int ,struct graph *,int *,int **);
void sim(struct graph *g,int n,struct pmus *pmu,int p,int *degree1,int **adj)
{
	int l=0,u=p,test; // intitail lower and upper limits
	clock_t t; 
	t = clock(); 
	srand(time(NULL));
	struct pmus newpmus2[u]; //will store new set of pmu's needed after simulated annealing process
	for(int i=0;i<u;i++)
	{
		newpmus2[i].src=pmu[i].src;
		newpmus2[i].dest = pmu[i].dest;
	}
	while((u-l) != 1) // run till diff is '1'
	{
		if(l==0)
		{
			test = (0.85) * u; // 85% of upper limit
                        struct pmus newpmu[test]; //randomly select pmu's of size test from pmu's obtained from greedy
			for(int i=0;i<test;i++)
			{
				newpmu[i].src=newpmu[i].dest=-1; //initial allocation set to zero
			}
			//printf("tes value begin is %d \n",test);
			for(int i=0;i<test;i++)
			{

				int pp = rand()% p;
				printf("pp is %d \n",pp);
				newpmu[i].src = pmu[pp].src;
				newpmu[i].dest = pmu[pp].dest;
			}
			

			int yes =sims(newpmu,test,n,g,degree1,adj); //run simulated annealing process
			//printf("here s value is %d \n",yes);
			if(yes == 1)
			{
				u = test;   //change upper interval iff system observable
				for(int i=0;i<u;i++)
				{
					newpmus2[i].src=newpmu[i].src;
					newpmus2[i].dest = newpmu[i].dest;
				}
			}
			else
			{

				l = test;    //change lower interval if system not observable

			}
                          }

		
		else
		{
			test = (l+u)/2;      //take midpoint of lower and upper halfs
			struct pmus newpmu[test];
			for(int i=0;i<test;i++)
			{
				newpmu[i].src=newpmu[i].dest=-1;
			}
			for(int i=0;i<test;i++)
			{
				int pp = rand()% p;
				newpmu[i].src = pmu[pp].src;
				newpmu[i].dest = pmu[pp].dest;
			}
			int yes =sims(newpmu,test,n,g,degree1,adj); //simulated annealing
			//printf("here s is %d\n",yes);
			if(yes == 1)
			{
				u = test;             //change upper interval iff system observable
				for(int i=0;i<u;i++)
				{
					newpmus2[i].src=newpmu[i].src;
					newpmus2[i].dest = newpmu[i].dest;
				}

			}
			else
			{
				l = test;           //change lower interval if system not observable

			}

		}

	}
	printf("needed pmus are %d \n",u);
	for(int i=0;i<u;i++)
	{
		printf("%d -->%d \n",	newpmus2[i].src,newpmus2[i].dest);
	}
	t = clock() - t; 
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

	printf("fun() took %f seconds to execute \n", time_taken); 

}
