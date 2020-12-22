#include<stdio.h>
#include<stdlib.h>
#define MAX 40

int n;

void bubble_sort(int arr[MAX])                  // 1. BUBBLE SORT
{
	int temp, i, j;
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;			
			}
		}
	}
}

void selection_sort(int arr[MAX])               // 2. SELCTION SORT
{
	int min, temp, j, i;
	
	for(i=0; i<n; i++)                    // LOOP FOR TRAVERSING ARRAY...
	{
		min = i;
		
		for(j=i+1; j<n; j++)              // LOOP FOR FINDING MINIMUM VALUE INDEX...
		{
			if(arr[j] < arr[min])
				min = j;
		}
		
		if(min != i)
		{
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

void insertion_sort(int arr[MAX])             // 3. INSERTION SORT
{
	int i, j, temp;
	
	for(i=1; i<n; i++)
	{
		temp = arr[i];
		j = i-1;
		
		while(j >= 0 && arr[j] > temp)
		{
			arr[j+1] = arr[j];
			--j;
		}
		
		arr[j+1] = temp;
	}
}

void merge(int arr[MAX], int p, int q, int r)         // 4. MERGE SORT
{                                                 // MERGE THE LEFT & RIGHT HALVES...
	int i, j , k, c[MAX] = {0};
	
	i = p;
	j = q+1;
	k = 0;
	
	while(i <= q && j <= r)
	{
		if(arr[i] < arr[j])
		{
			c[k] = arr[i];
			++i;
			++k;
		}
		else
		{
			c[k] = arr[j];
			++k;
			++j;
		}
	}
	
	// LOOPS TO COPY THE REMAINING ELEMENTS...
	
	while(i <= q)
	{
		c[k] = arr[i];
		++k;
		++i;
	}
	
	while(j <= r)
	{
		c[k] = arr[j];
		++k;
		++j;
	}
	
	for(i=p, j=0; i<=r; i++, j++)                // COPY THE ELEMENTS TO ORIGINAL ARRAY... 
	 arr[i] = c[j];
}

void merge_sort(int arr[MAX], int p, int r)    
{
	int q;
	if(p < r) 
	{
		q = (p+r)/2;                            // FINDING THE MIDDLE INDEX...
		
		merge_sort(arr, p, q);                    // SORTING THE LEFT HALF...
		merge_sort(arr, q+1, r);                  // SORTING THE RIGHT HALF...
		
		merge(arr, p, q, r);                 
    } 
}

void swap(int *b, int *c)
{
	int temp;
	temp = *b;
	*b = *c;
	*c = temp;
}

int partition(int arr[MAX], int p, int r)         // 5. QUICK SORT
{                                              // PARTITION FUNCTION
	int i, j;
  	i = p-1;
  	
	//             Here arr[r] is the PIVOT element...
	
	for(j=p; j<=r-1; j++)          // traversing j from 1st element to pivot-1 element...
	{
		if(arr[j] <= arr[r])
		{
			i = i+1;
			swap(arr+i, arr+j);       // swap function call by address...
		}
	}
	
	//   Now, placing PIVOT at the correct position...
	
	i = i+1;
	swap(arr+i, arr+r);
	
	return i;                   // RETURNING THE INDEX OF THE PIVOT...
}

void quick_sort(int arr[MAX], int p, int r)        // QUICK SORT FUNCTION
{
	int q;
	
	if(p < r)
	{
		q = partition(arr, p, r);     /* q is the partitioning index, 
		                               a[q] element is at right place... */
		
		quick_sort(arr, p, q-1);      // Sorting the array before patitioning index...
		quick_sort(arr, q+1, r);           // Sorting the array after partitioning index...
	}
}

void counting_sort(int arr[MAX], int s, int min)       // 6. COUNTING SORT
{
	int c[s], i, b[MAX];
		
	for(i=0; i<s; i++)                     // INITIALISING THE COUNT ARRAY TO 0...
		c[i] = 0;
	
	for(i=0; i<n; i++)
		++c[arr[i]-min];		
	
	for(i=1; i<s; i++)
	{
		c[i] = c[i] + c[i-1];
	}
	
	for(i=n-1; i>=0; i--)
	{
		b[c[arr[i] - min]-1] = arr[i];
		--c[arr[i] - min];
	}
	
	for(i=0; i<n; i++)
		arr[i] = b[i];
}

void maxHeapify(int arr[MAX], int n, int i)              // 7. HEAP SORT
{                                                   // MAX HEAPIFY FUNCTION
	int largest, left, right;
	largest = i;
	left = 2*i + 1;             // Left child index
	right = 2*i + 2;   	       // Right child index
	
	if(left < n && arr[left] > arr[largest])
		largest = left;
	
	if(right < n && arr[right] > arr[largest])
		largest = right;
		
	if(largest != i)
	{
		swap(&arr[i], &arr[largest]);
		maxHeapify(arr, n, largest);    // To check whether the child nodes satisfy the max heap property
	}
}

void heap_sort(int arr[MAX], int n)           // HEAP SORT FUNCTION
{
	int i;
	
	for(i=n/2 - 1; i>=0; i--)
		maxHeapify(arr, n, i);
	
	for(i=n-1; i>=0; i--)
	{
		swap(&arr[0], &arr[i]);
		maxHeapify(arr, i, 0);
	}
}

void input_arr(int arr[MAX])                           // INPUT ARRAY FUNCTION...
{
	int i;
	
	printf("Enter the size of array: ");
	scanf("%d", &n);
	printf("Enter the array: \n");
	for(i=0; i<n; i++)
		scanf("%d", &arr[i]);
}

void print_arr(int arr[MAX])                         // PRINT ARRAY FUNCTION...
{
	int i;
	for(i=0; i<n; i++)
		printf("%d ", arr[i]);
}

int main()                                          // MAIN BLOCK...
{
	char choice;
	int i, a, arr[MAX];
	
	do 
	{	
		system("cls");
		
		printf("\t *** SORTING MENU *** \n\n");
		printf("1. BUBBLE SORT \n");
		printf("2. SELECTION SORT \n");
		printf("3. INSERTION SORT \n");
		printf("4. MERGE SORT \n");
		printf("5. QUICK SORT \n");
		printf("6. COUNTING SORT \n");
		printf("7. HEAP SORT \n");
		printf("Enter your choice: ");
		scanf("%d", &a);
		
		switch(a)
		{
			case 1:
				input_arr(arr);
				
				printf("Entered elements are: \n");
				print_arr(arr);
				
				bubble_sort(arr);
				
				printf("\n\nSorted elements are: \n");
				print_arr(arr);
				
				printf("\n\nTime Complexity: O(n^2)");
				
				break;
			
			case 2:
				input_arr(arr);
				
				printf("Entered elements are: \n");
				print_arr(arr);
				
				selection_sort(arr);
				
				printf("\n\nSorted elements are: \n");
				print_arr(arr);
				
				printf("\n\nTime Complexity: O(n^2)");
				
				break;
				
			case 3:
				input_arr(arr);
				
				printf("Entered elements are: \n");
				print_arr(arr);
				
				insertion_sort(arr);
				
				printf("\n\nSorted elements are: \n");
				print_arr(arr);
				
				printf("\n\nTime Complexity: O(n^2)");
				
				break;
				
			case 4:
				input_arr(arr);
				
				printf("Entered elements are: \n");
				print_arr(arr);
				
				merge_sort(arr, 0, n-1);
				
				printf("\n\nSorted elements are: \n");
				print_arr(arr);
				
				printf("\n\nTime Complexity: O(nlog(n) (base 2))");
				
				break;
				
			case 5:
				input_arr(arr);
				
				printf("Entered elements are: \n");
				print_arr(arr);
				
				quick_sort(arr, 0, n-1);
				
				printf("\n\nSorted elements are: \n");
				print_arr(arr);
				
				printf("\n\nTime Complexity: O(nlog(n) (base 2))");
				
				break;
			
			case 6:
				printf("Enter the size of array: ");
				scanf("%d", &n);
				
				int max=0, min, s;
	
				printf("Enter the array: \n");
				for(i=0; i<n; i++)
				{
					scanf("%d", &arr[i]);
					if(arr[i] > max)
						max = arr[i];
				}
				
				min = arr[0];
				for(i=1; i<n; i++)
				{
					if(arr[i] < min)
						min = arr[i];	
				}
				
				s = max - min + 1;             // SIZE OF COUNT ARRAY...
				
				printf("Entered elements are: \n");
				print_arr(arr);
				
				counting_sort(arr, s, min);
				
				printf("\n\nSorted elements are: \n");
				print_arr(arr);
				
				printf("\n\nTime Complexity: O(nlog(n) (base 2))");
				
				break;
				
			case 7:
				input_arr(arr);
				
				printf("Entered elements are: \n");
				print_arr(arr);
				
				heap_sort(arr, n);
				
				printf("\n\nSorted elements are: \n");
				print_arr(arr);
				
				printf("\n\nTime Complexity: O(nlog(n) (base 2))");
				
				break;
							
			default:
				printf("\nWrong Choice! Enter Again!");
		}	
		
		printf("\n\nDo you wish to enter again (Press 'y' or 'Y' for 'yes')?: ");
		fflush(stdin);
		scanf("%c", &choice);
	
	} while(choice == 'y' || choice == 'Y');	
	
	return 0;
}
