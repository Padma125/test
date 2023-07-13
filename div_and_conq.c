#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int printarr(int, int*);

int N;

void merge(int arr[], int l, int m, int r){
    int n1, n2;
    n1 = m-l+1;
    n2 = r-m;
    int L[n1], R[n2];
    int i=0,j=0, k;
    for(i=0;i<n1;i++){
        L[i] = arr[l+i];
    }
    for(j=0; j<n2; j++){
        R[j] = arr[m+j+1];
    }
    i=0,j=0, k=l;
    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
            arr[k] = L[i];
            i++;
        }    
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while(i<n1){
        arr[k] = L[i++];
        k++;
    }
    while(j<n2){
        arr[k] = R[j++];
        k++;
    }
}

void mergesort(int arr[], int l, int r){

	if(l<r){

	    int m;
        m = l+(r-l)/2;
	    pid_t  pid1,pid2;
	    pid1 = fork();
	    int x=getpid();  
	
     	if (pid1 == 0) {
			printf("child1-- parent : %d process: %d\n\n", getppid(),getpid()); 	
			mergesort(arr, l, m);
			//printf("---------------------------------------\n");
			printarr(N,arr);
			//printf("---------------------------------------\n");
			exit(0);
     	}
		else{
			waitpid(pid1,NULL,0);	
			pid2=fork();
			if (pid2 == 0) {
				printf("child2-- parent : %d process: %d\n\n", getppid(),getpid());
		    	mergesort(arr, m+1, r);
				//printf("---------------------------------------\n");
				printarr(N,arr);
				//printf("---------------------------------------\n");
				exit(0);
		    	}
			else{ 
				wait(NULL);
				printf("parent-- parent : %d process: %d\n\n", getppid(),getpid());
		        merge(arr, l, m, r);
				//printf("---------------------------------------\n");
				printarr(N,arr);
				//printf("----------------------------------------\n");
			}
		}
    }
}

int printarr(int len, int* arr){
    int i;
    for(i=0;i<len;i++){
        printf("%d\t", *(arr+i));
    }
    printf("\n");
}

int main(){

	printf("Enter length of array: ");
	scanf("%d", &N);
	int *arr = mmap ( NULL, N*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0 );
	printf("main function-- parent : %d process: %d\n\n", getppid(),getpid());
	if(arr == MAP_FAILED){
	    printf("Mapping Failed\n");
    	return 1;
	}
	int i;
	for (i=0; i<N; i++){
		printf("Enter %d: ", i+1);
		scanf("%d",&arr[i]);
	}
	//arr[6] = {9,3,45,4,8,5}
	printf("Initial array: \n");
	printarr(N, arr);

	mergesort(arr, 0, N-1);
	printf("-----------------Sorted array----------------------\n");
	printarr(N, arr);
	printf("main function-- parent : %d process: %d\n\n", getppid(),getpid());
}
