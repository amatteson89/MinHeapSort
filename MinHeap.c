/*
*	name: Andrew Matteson 00495489
*	date: May 25, 2013
*	CSCD 320 Algorithms
*
*	10000 item min heap
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MIN_HEAP_SIZE = 10000 + 1;  // We use +1 here because we want to make it a 1 based array
int NEG_INFINITY = -2147483648;

struct Node{
	int value;
	int index;
};

typedef struct Node Node;

void build_min_heap(Node * min_heap_array);
void min_heapify(Node * min_heap_array, int i);


int main(){
	time_t start,end;
	float diff = 0;
	FILE * fin = fopen("data.txt", "r");
	Node min_heap_array[MIN_HEAP_SIZE];
	int index_count = 1;

	start = clock();	

	for(int i = 1; i < MIN_HEAP_SIZE; i++ ){
		min_heap_array[i].value = NEG_INFINITY;
	}

	for(int i = 1; i < MIN_HEAP_SIZE; i++){
		fscanf(fin, "%d", &(min_heap_array[i].value) ) ;
		min_heap_array[index_count].index = index_count;
		index_count++;
	}

	build_min_heap(min_heap_array);

	while( !feof(fin)){
		int temp = 0;

		fscanf(fin, "%d", &temp);

		//See if the next number is bigger than smallest in the heap
		if(temp > min_heap_array[1].value){
			min_heap_array[1].value = temp; //replace the smallest in the heap
			min_heap_array[1].index = index_count;
			min_heapify(min_heap_array, 1);
		}
		index_count++;
	}
		

	//PRINT OUT THE HEAP
	//for(int i = MIN_HEAP_SIZE; i > 0; i--)
	//	printf("node %d: %d at index: %d\n", i, min_heap_array[i].value, min_heap_array[i].index);
	

	end = clock();
	diff = (float)end - (float)start;
	printf("Running time: %f\n", diff/ CLOCKS_PER_SEC);
	fclose(fin);

	return 0;
}


void build_min_heap(Node * min_heap_array){
	for(int i = (MIN_HEAP_SIZE / 2); i > 0; i--)
		min_heapify( min_heap_array, i);
}




void min_heapify(Node * min_heap_array, int i){
	int smallest_node = 0;

	int left_child_index = 2 * i;
	int right_child_index = 2 * i + 1;

	// Verify we don't go outside our array size
	// See if the left child is smaller than parent node
	if( left_child_index <= MIN_HEAP_SIZE && min_heap_array[left_child_index].value < min_heap_array[i].value){
		smallest_node = left_child_index;
	} else{
		smallest_node = i;
	}

	// Verify we don't go outside our array size
	// See if the right child is smaller than smallest node (either parent or left child) 
	if( right_child_index <= MIN_HEAP_SIZE && min_heap_array[right_child_index].value < min_heap_array[smallest_node].value){
		smallest_node = right_child_index;
	} 

	if( smallest_node != i){
		int temp_val = min_heap_array[i].value;
		int temp_index = min_heap_array[i].index;

		min_heap_array[i].value = min_heap_array[smallest_node].value;
		min_heap_array[i].index = min_heap_array[smallest_node].index;

		min_heap_array[smallest_node].value = temp_val;
		min_heap_array[smallest_node].index = temp_index;

		min_heapify(min_heap_array, smallest_node);
	}

}
