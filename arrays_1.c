#include <stdio.h> 
#include <stdbool.h> 

#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[],int length, int pos, int value);

int main() {
    int arr[SIZE] = {10, 20, 30, 40, 50}; 
    int arr2d[nRows][nCols] = {1};
    print_array(arr, 5);
    puts("");
    remove_element(arr, 5, 2);
    print_array(arr, 5);
print_matrix(arr2d,nRows);
return 0;
}

void print_array(int array[], int length){
   for(int i=0;i<length; i++)
      printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<rows; i++){
    for(int j=0;j<nCols; j++)
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");     
   }     
}

//FUNCTION DEFINITIONS

bool isValid(const int arr[], int length, int pos) {
    // Check if the position is within valid bounds
    return pos >= 0 && pos < length;
}
    void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
    printf("Invalid position\n");
    return;
    }
    
}
