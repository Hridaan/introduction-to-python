#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SIZE1 2*SIZE
#define NOTHREADS 2
int array1[SIZE];
int array2[SIZE];
int array3[SIZE];
int array4[SIZE];
int array5[SIZE1];
int array6[SIZE1];
int array7[SIZE1];
int temp1[SIZE1];
int temp2[SIZE1];

void fillArray(int size) 
{
    int i;
    srand(time(NULL));
    for (i=0; i<size; i++)
        array1[i] = rand() % 100;
        
}
void fillArray1(int size) 
{
    int i;
    srand(time(NULL));
    for (i=0; i<size; i++)
        array2[i] = rand() % 150;
}
void printArray(int *list, int size) 
{
    int i;
    for (i=0; i<size-1; i++)
        printf("%d, ", list[i]);
        printf("%d\n", list[i]);
}
void copyArray(int size)
{
	int i;
	for (i=0; i<size; i++)
	{
        array3[i]=array1[i];
	    array4[i]=array2[i];
	}
}

void copyArray5(int size)
{
	int i,j=0;
    for (i=0; i<size; i++)
        array5[i]=array1[i];
	for (i=size; i<2*size;i++)
    {
	    array5[i]=array2[j];
        if (j<size)
           j++;
    }

}
typedef struct node 
{
    int i;
    int j;
} NODE;


void merge(int i, int j)
{   
    int mid = (i+j)/2;
    int ai = i;
    int bi = mid+1;
    int newa[j-i+1], newai = 0;
    while(ai <= mid && bi <= j) 
	{
        if (array1[ai] > array1[bi])
		{
           newa[newai++] = array1[bi++];
	    }
        else              
	    {    
	       newa[newai++] = array1[ai++];
		}
    }
    while(ai <= mid) 
	{
        newa[newai++] = array1[ai++];
	}
    while(bi <= j) 
	{
        newa[newai++] = array1[bi++];
	}
    for (ai = 0; ai < (j-i+1) ; ai++)
	{
        array1[i+ai] = newa[ai];
	}
        
}
void merge1(int i, int j)
{
    int mid = (i+j)/2;
    int ai = i;
    int bi = mid+1;
    int newa[j-i+1], newai = 0;
    while(ai <= mid && bi <= j) 
	{
        if (array2[ai] > array2[bi])
	    {
            newa[newai++] = array2[bi++];
	    }
        else              
	    {    
		    newa[newai++] = array2[ai++];
		}
    }
    while(ai <= mid) 
    {
        newa[newai++] = array2[ai++];
	}
    while(bi <= j) 
    {
        newa[newai++] = array2[bi++];
	}
    for (ai = 0; ai < (j-i+1) ; ai++)
    {
        array2[i+ai] = newa[ai];
	}
}
void combine(int max)
{
	int i=0,a=0,k;
    for(k = 0; k <2*SIZE ; k++)
	{
     	if(a < SIZE && i < SIZE )
        {
           if(array1[i]<=array2[a])
		    {			   
		      array6[k]=array1[i];
		      i++;
            } 
            else
            {
                array6[k]=array2[a];
	            a++;
            }
        }
        else if (a>SIZE)
        {
           array6[k]=array1[i];
	       i++;
        }
        else
        {          
            array6[k]=array2[a];
	        a++;
        }
	}
}
void * mergesort(void *a)
{
    NODE *p = (NODE *)a;
    NODE n1, n2;
    int mid = (p->i+p->j)/2;
    pthread_t tid1, tid2;
    int ret;
    n1.i = p->i;
    n1.j = mid;
    n2.i = mid+1;
    n2.j = p->j;
    if (p->i >= p->j) return(0);
        ret = pthread_create(&tid1, NULL, mergesort, &n1);
        if (ret) 
		{
            printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret); 
            exit(1);
        }
        ret = pthread_create(&tid2, NULL, mergesort, &n2);
        if (ret) 
		{
            printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret); 
            exit(1);
        }
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
        merge(p->i, p->j);
        merge1(p->i, p->j);
        pthread_exit(NULL);
}
void merging(int low, int mid, int high) 
{
    int l1, l2, i;
    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) 
    {
        if(temp1[l1] <= temp1[l2])
           temp2[i] = temp1[l1++];
        else
           temp2[i] = temp1[l2++];
    }
   
    while(l1 <= mid)    
        temp2[i++] = temp1[l1++];
    while(l2 <= high)   
        temp2[i++] = temp1[l2++];
    for(i = low; i <= high; i++)
        temp1[i] = temp2[i];
}
void sort1(int low, int high) 
{
    int mid;   
    if(low < high) 
    {
        mid = (low + high) / 2;
        sort1(low, mid);
        sort1(mid+1, high);
        merging(low, mid, high);
    } 
	else 
    { 
        return;
    }   
}
void combine1(int max)
{
	int i=0,a=0,k;
    for(k = 0; k <2*SIZE ; k++)
	{
       	if(a < SIZE && i < SIZE )
        {
            if(array3[i]<=array4[a])
		    {			   
		       array7[k]=array3[i];
		       i++;
            } 
            else
            {
                array7[k]=array4[a];
	            a++;
            }
        }
        else if (a > SIZE)
        {
           array7[k]=array3[i];
	       i++;
        }
        else
        {          
            array7[k]=array4[a];
	        a++;
        }
	}
}
int main()
{
fillArray(SIZE);
fillArray1(SIZE);
copyArray(SIZE);
copyArray5(SIZE);
printArray(array3, SIZE);
printArray(array4, SIZE);
clock_t t,t1,t2;
int i;
int max=SIZE;
t= clock(); 
NODE m;
m.i = 0;
m.j = SIZE-1;
pthread_t tid;
int ret;
ret=pthread_create(&tid, NULL, mergesort, &m);
        if (ret) 
		{
            printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret); \
			exit(1);
        }
        pthread_join(tid, NULL);
        for (i = 0; i < SIZE; i++)
        {
        printf ("%d ", array1[i]);
        }
        printf ("\n");
        for (i = 0; i < SIZE; i++)
        {
        printf ("%d ", array2[i]);
        }
        printf ("\n");
        combine(max);
        for (i = 0; i <2*SIZE; i++)
        {
        printf ("%d ", array6[i]);
        }
        printf ("\n");
t= clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC;
printf("Time taken from Thread create till mearge %f \n",time_taken);
t1= clock();
for (i=0; i<SIZE; i++)
	{
        temp1[i]=array3[i];
    } 
sort1(0,SIZE-1);
for(i=0; i<SIZE;i++)
{
    array3[i]=temp1[i];
}
for (i = 0; i < SIZE; i++)
{
    printf ("%d ", array3[i]);
}
printf("\n");
for (i=0; i<SIZE; i++)
{
    temp1[i]=array4[i];
} 
sort1(0,SIZE-1);
for(i=0; i<SIZE;i++)
{
    array4[i]=temp1[i];
}
for (i = 0; i < SIZE; i++)
{
    printf ("%d ", array4[i]);
}
printf("\n");
combine1(max);
for (i = 0; i <2*SIZE; i++)
{
   printf ("%d ", array7[i]);
}
printf ("\n");
t1= clock()-t1;
double time_taken1 = ((double)t1)/CLOCKS_PER_SEC;
printf("Time taken from 1st sort till mearge %f \n",time_taken1);
t2= clock();
for (i=0; i<2*SIZE; i++)
{
    temp1[i]=array5[i];
} 
sort1(0,2*SIZE-1);
for(i=0; i<2*SIZE;i++)
{
    array5[i]=temp1[i];
}
for (i = 0; i < 2*SIZE; i++)
{
    printf ("%d ", array5[i]);
}
printf("\n");
t2= clock()-t2;
double time_taken2 = ((double)t2)/CLOCKS_PER_SEC;
printf("Time taken from 1st sort till mearge %f \n",time_taken2);
//pthread_exit(NULL);
return 0;
}
