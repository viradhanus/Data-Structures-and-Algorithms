#include<stdio.h> 
  
//define total vertex count in the Graph
#define vert_count 7

// function to print Transitive closure Matrix   
void printMatrix(int reach[][vert_count]);

// function to find Transitive closure Matrix   
void transitiveClosure(int graph[][vert_count]);
  
int main() { 
    // Enter corresponding adjacency matrix of the graph
    int graph[vert_count][vert_count]= {{0, 1, 1, 0, 0, 0, 0}, 
                                        {0, 0, 0, 0, 1, 0, 0}, 
                                        {0, 0, 0, 0, 0, 1, 0}, 
                                        {0, 1, 0, 0, 1, 0, 1},
                                        {0, 0, 0, 0, 0, 0, 1},
                                        {0, 0, 0, 1, 0, 0, 0},
                                        {0, 1, 0, 0, 0, 0, 0}
                                       }; 
                      

    // find and print Transitive closure Matrix 
    transitiveClosure(graph); 
    return 0; 
} 

// function to find Transitive closure Matrix   
void transitiveClosure(int graph[][vert_count]){ 

    int reach[vert_count][vert_count], i, j, k; 
  
    for (i = 0; i < vert_count; i++){ 
        for (j = 0; j < vert_count; j++){ 
            reach[i][j] = graph[i][j];
        }
    }
    for (k = 0; k < vert_count; k++){ 
        for (i = 0; i < vert_count; i++){ 
            for (j = 0; j < vert_count; j++){ 
                if(i==j){
                   reach[i][j] = 1;
                }else{
                   reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]); 
                }
            } 
        } 
    } 
    // print Transitive closure Matrix 
    printMatrix(reach); 
} 

// function to print Transitive closure Matrix   
void printMatrix(int reach[][vert_count]){

    printf ("\nTransitive closure Matrix:\n"); 

    for (int i = 0; i < vert_count; i++) 
    { 
        for (int j = 0; j < vert_count; j++){ 
            printf ("%d ", reach[i][j]); 
        }
        printf("\n"); 
    } 
    printf("\n");
} 