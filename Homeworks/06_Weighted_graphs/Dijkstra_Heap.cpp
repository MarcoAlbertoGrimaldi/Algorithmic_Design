
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

struct Adj_List_Node 
{ 
	int dest; 
	int weight; 
	Adj_List_Node* next; 
}; 

struct Adj_List 
{ 
	Adj_List_Node *head; 
}; 

struct Graph 
{ 
	int V; 
	Adj_List* array; 
}; 

Adj_List_Node* new_adj_node(int dest, int weight) 
{ 
	Adj_List_Node* newNode = 
			(Adj_List_Node*) malloc(sizeof(Adj_List_Node)); 
	newNode->dest = dest; 
	newNode->weight = weight; 
	newNode->next = nullptr; 
	return newNode; 
} 

Graph* create_graph(int V) 
{ 
	Graph* graph = (Graph*) malloc(sizeof(Graph)); 
	graph->V = V; 

	graph->array = (Adj_List*) malloc(V * sizeof(Adj_List)); 

	for (int i = 0; i < V; ++i) 
		graph->array[i].head = nullptr; 

	return graph; 
} 

void add_edge(Graph* graph, int src, int dest, int weight) 
{ 
	Adj_List_Node* newNode = new_adj_node(dest, weight); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode; 

	newNode = new_adj_node(src, weight); 
	newNode->next = graph->array[dest].head; 
	graph->array[dest].head = newNode; 
} 
struct MinHeapNode 
{ 
	int v; 
	int dist; 
}; 

struct MinHeap 
{ 
	int size;	 
	int capacity; 
	int *pos;	 
	MinHeapNode **array; 
}; 

MinHeapNode* New_Min_Heap_Node(int v, int dist) 
{ 
	MinHeapNode* minHeapNode = 
		(MinHeapNode*) malloc(sizeof(MinHeapNode)); 
	minHeapNode->v = v; 
	minHeapNode->dist = dist; 
	return minHeapNode; 
} 

MinHeap* createMinHeap(int capacity) 
{ 
	MinHeap* minHeap = 
		(MinHeap*) malloc(sizeof(MinHeap)); 
	minHeap->pos = (int *)malloc(capacity * sizeof(int)); 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = 
		(MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*)); 
	return minHeap; 
} 

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) 
{ 
	MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

void minHeapify(MinHeap* minHeap, int idx) 
{ 
	int smallest, left, right; 
	smallest = idx; 
	left = 2 * idx + 1; 
	right = 2 * idx + 2; 

	if (left < minHeap->size && 
		minHeap->array[left]->dist < minHeap->array[smallest]->dist ) 
	smallest = left; 

	if (right < minHeap->size && 
		minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
	smallest = right; 

	if (smallest != idx) 
	{ 
		MinHeapNode *smallestNode = minHeap->array[smallest]; 
		MinHeapNode *idxNode = minHeap->array[idx]; 

		minHeap->pos[smallestNode->v] = idx; 
		minHeap->pos[idxNode->v] = smallest; 

		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 

		minHeapify(minHeap, smallest); 
	} 
} 

int Is_Empty(MinHeap* minHeap) 
{ 
	return minHeap->size == 0; 
} 

MinHeapNode* Extract_Min(MinHeap* minHeap) 
{ 
	if (Is_Empty(minHeap)) 
		return nullptr; 

	MinHeapNode* root = minHeap->array[0]; 

	MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
	minHeap->array[0] = lastNode; 

	minHeap->pos[root->v] = minHeap->size-1; 
	minHeap->pos[lastNode->v] = 0; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return root; 
} 

void decreaseKey(MinHeap* minHeap, int v, int dist) 
{ 
	int i = minHeap->pos[v]; 

	minHeap->array[i]->dist = dist; 

	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
	{ 
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 

		i = (i - 1) / 2; 
	} 
} 

bool Is_Min_Heap(MinHeap *minHeap, int v) 
{ 
if (minHeap->pos[v] < minHeap->size) 
	return true; 
return false; 
} 

void printArr(int dist[], int n) 
{ 
	printf("Vertex Distance from Source\n"); 
	for (int i = 0; i < n; ++i) 
		printf("%d \t\t %d\n", i, dist[i]); 
} 

void dijkstra(Graph* graph, int src) 
{ 
	int V = graph->V;
	int dist[V];	 

	MinHeap* minHeap = createMinHeap(V); 

	for (int v = 0; v < V; ++v) 
	{ 
		dist[v] = INT_MAX; 
		minHeap->array[v] = New_Min_Heap_Node(v, dist[v]); 
		minHeap->pos[v] = v; 
	} 

	minHeap->array[src] = New_Min_Heap_Node(src, dist[src]); 
	minHeap->pos[src] = src; 
	dist[src] = 0; 
	decreaseKey(minHeap, src, dist[src]); 

	minHeap->size = V; 

	while (!Is_Empty(minHeap)) 
	{ 
		MinHeapNode* minHeapNode = Extract_Min(minHeap); 
		int u = minHeapNode->v; 

		Adj_List_Node* pCrawl = graph->array[u].head; 
		while (pCrawl != nullptr) 
		{ 
			int v = pCrawl->dest; 

			if (Is_Min_Heap(minHeap, v) && dist[u] != INT_MAX && 
										pCrawl->weight + dist[u] < dist[v]) 
			{ 
				dist[v] = dist[u] + pCrawl->weight; 

				decreaseKey(minHeap, v, dist[v]); 
			} 
			pCrawl = pCrawl->next; 
		} 
	} 

	printArr(dist, V); 
} 


int main() 
{ 
	
	int V = 9; 
	Graph* graph = create_graph(V); 
	add_edge(graph, 0, 1, 4); 
	add_edge(graph, 0, 7, 8); 
	add_edge(graph, 1, 2, 8); 
	add_edge(graph, 1, 7, 11); 
	add_edge(graph, 2, 3, 7); 
	add_edge(graph, 2, 8, 2); 
	add_edge(graph, 2, 5, 4); 
	add_edge(graph, 3, 4, 9); 
	add_edge(graph, 3, 5, 14); 
	add_edge(graph, 4, 5, 10); 
	add_edge(graph, 5, 6, 2); 
	add_edge(graph, 6, 7, 1); 
	add_edge(graph, 6, 8, 6); 
	add_edge(graph, 7, 8, 7); 

	dijkstra(graph, 0); 

	return 0; 
} 
