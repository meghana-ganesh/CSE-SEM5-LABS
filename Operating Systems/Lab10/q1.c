#include <stdio.h>
void Bankers(int n,int m,int alloc[n][m],int max[n][m],int avail[m])
{
    int need[n][m];
	for (int i = 0; i < n; i++) 
    {
		for (int j = 0; j < m; j++)
        {
			need[i][j] = max[i][j] - alloc[i][j];
        }
	}
    int finish[n];
    for (int i = 0;i < n;i++) 
    {
		finish[i] = 0;
	}
    int sequence[n];
    int ind = 0;
    for(int i=0;i<5;i++)
    {
        for(int proc=0;proc<n;proc++)
        {
            if(finish[proc] == 0)
            {
                int flag = 0;
                for(int j=0;j<m;j++)
                {
                    if(need[proc][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    sequence[ind++] = proc;
                    for(int j=0;j<m;j++)
                    {
                        avail[j] += alloc[proc][j];
                    }
                    finish[proc] = 1;
                }
            }
        }
    }

    int resultflag = 1;
    for(int i=0;i<n;i++)
    {
        if(finish[i] == 0)
        {
            resultflag = 0;
            printf("The system is not safe.");
            break;
        }        
    }
    if(resultflag == 1)
    {
        printf("The safe sequence is:");
        for(int i=0;i<n;i++)
        {
            printf("P%d ",sequence[i]);
        }
    }
}
int main()
{
	// P0, P1, P2, P3, P4 are the Process names here

	int n, m, i, j, k;
	n = 5; // Number of processes
	m = 3; // Number of resources
	int alloc[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix
						{ 2, 0, 0 }, // P1
						{ 3, 0, 2 }, // P2
						{ 2, 1, 1 }, // P3
						{ 0, 0, 2 } }; // P4

	int max[5][3] = { { 7, 5, 3 }, // P0 // MAX Matrix
					{ 3, 2, 2 }, // P1
					{ 9, 0, 2 }, // P2
					{ 2, 2, 2 }, // P3
					{ 4, 3, 3 } }; // P4

	int avail[3] = { 3, 3, 2 }; // Available Resources
    Bankers(n,m,alloc,max,avail);
}