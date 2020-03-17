#include<stdio.h>
#include<stdlib.h>

#define SIZE 10001

typedef struct Set
{
	int parent[SIZE];
	int rank[SIZE];
	int type;     
} Set;

Set* init(int type)
{
	Set* ds = (Set*) malloc(sizeof(Set));
	for(int i = 0; i < SIZE; i++)
        ds->parent[i] = -1;
	ds->type = type;
	return ds;
}

Set* makeSet(Set *ds, int i)
{
	if(ds->parent[i] != -1) {
		if(ds->type == 0)
			printf("PRESENT\n");
	}
	else {
		if(ds->type == 0)
            printf("%d\n", i);	    
		ds->parent[i] = i;
		ds->rank[i] = 0;
	}
	return ds;
}
int find(Set *ds, int i, int* c)
{
	c[ds->type]++;	
	if(ds->parent[i] == -1)
        return -1;
	else if (ds->type == 0 || ds->type == 1) {	   	   
		if(i == ds->parent[i])
            return i;
		else
            return find(ds, ds->parent[i], c);
	}
	else if (ds->type == 2 || ds->type == 3)
	{
		if(i == (ds->parent[i]))
            return i;
		else
            return ds->parent[i] = find(ds, ds->parent[i], c);
    }
}
Set* uni(Set *ds, int x, int y, int* c)
{
	if ((ds->parent[x] == -1 || ds->parent[y] == -1)) {
		if(ds->type == 3)	    
			printf("ERROR ");		
		else
            printf("ERROR ");
	}
  	else {
		if(ds->type == 0 || ds->type == 2) {
			int px = find(ds, x, c);
			int py = find(ds, y, c);
			if(px == py) {
				printf("%d ", px);
				return ds;
			}
			else {
				ds->parent[py] = px;				
				printf("%d ", px);
			}
		}
		else {
			int px = find(ds, x, c);
			int py = find(ds, y, c);
			if(px == py) {
				printf("%d ", px);
				return ds;
			}
			else {			
				if(ds->rank[px] < ds->rank[py]) {
					ds->parent[px] = py;
					printf("%d ", py);
				}
				else if(ds->rank[px] > ds->rank[py]) {
					ds->parent[py] = px;
					printf("%d ", px);
				}
				else {
					printf("%d ", px);		 
					ds->parent[py] = px;
					ds->rank[px]++;
				}
			}
		}
	}   
	return ds;
}

int main()
{
	int i,n,x,y;	
	char choice;
    int c[4] = {0};
	Set *ds[4];
	
    for (i = 0; i < 4; i++)
        ds[i] = init(i);
	
    while(1)
	{
		scanf("%c", &choice);
		if(choice == 's')
            break;
        switch (choice)
		{
            case 'm':
                scanf("%d", &n);     
                for (i = 0; i < 4; i++)
                    ds[i] = makeSet(ds[i], n);
                break;
            case 'u':
                scanf("%d %d", &x, &y);			
                for (i = 0; i < 4; i++)	
                {
                    ds[i] = uni(ds[i], x, y, c);
                }
                printf("\n");
                break;
            case 'f':
                scanf("%d", &n);
                if (ds[0]->parent[n] == -1)
                    printf("NOT FOUND\n");
                else {
                    for (i = 0; i < 4; i++)       
                        printf("%d ", find(ds[i], n, c));			
                    printf("\n");
                }
                break;
		}
	}

	printf("%d ", c[0]);
	printf("%d ", c[1]);
	printf("%d ", c[2]);
	printf("%d ", c[3]);
	return 0;
}