#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <climits>
#include <algorithm>
#include <time.h>
using namespace std;

int val = INT_MIN;
int start_ind = 1;
int temp_start = 1;
int end_ind = 1;

//Task1 Give an implementation of Alg1. - Ummay Sumaya Khan
int Task1(int A[], int n, int* start, int* end){
    int max_sum = INT_MIN;
    *start= 0;
    *end= 0; 
    for (int i = 0; i < n; i++){
        for (int j= i; j< n; j++){
            int sum = 0;
            for (int k= i; k< j+1; k++){
                sum = sum + A[k];
            }
            if (sum > max_sum){
                max_sum = sum;
                *start = i+1;
                *end = j+1;
            }
        }
    }
    return max_sum;
}
//Task2 Give an implementation of Alg2. - Stefan Pessolano
int Task2(int arr[], int n, int* start, int* end){
    int max_sum = arr[0];
    *start = 0;
    *end = 0;
    for (int i = 0; i < n; i++) {
        int sums[n];
        for(int j = i; j < n; j++){
            sums[j] = (j == i) ? arr[j]: sums[j-1] + arr[j];
            if (sums[j] > max_sum){
                max_sum = sums[j];
                *start = i;
                *end = j;
            }

        }
    }
    return max_sum;
}
//Task3a Give a recursive implementation of Alg3 using Memoization. - Ummay Sumaya Khan
int Task3a(int A[], int n, int index){
    int sum;
    // Base case
    if (index == 0){
        sum = A[0];
        return A[0];
    }
    sum = Task3a(A, n, index-1);
	if (sum == A[index-1]) temp_start = index;

    if (sum > val) {
        val = sum;
        start_ind = temp_start;
        end_ind = index;
    }
    return max(A[index], A[index] + sum);

}
//Task3b Give an iterative BottomUp implementation of Alg3. - Ummay Sumaya Khan
int Task3b(int A[], int n, int* start, int* end ){
    int sum;
    *start = 1;
    *end = 1;
    int temp_start=1, max_sum= INT_MIN;
    // Base case
    sum = A[0];
	max_sum = sum;
    for (int i= 1; i< n; i++)
    {
        sum = max(A[i]+sum, A[i]);
        if (sum == A[i]) temp_start = i+1;
        if (sum > max_sum)
        {
            max_sum = sum;
            *start = temp_start;
            *end = i+1;
        }
    }
    return max_sum;
}
//Task4 Give an implementation of Alg4 using O(1) extra space. - Ummay Sumaya Khan
int Task4(int **A, int m, int n, int* s_row, int* e_row, int* s_col, int* e_col){
    int max_sum= INT_MIN;
    *s_row= 0; 
    *e_row= 0; 
    *s_col= 0; 
    *e_col= 0; 
    for (int i1= 0; i1< m; i1++){
        for (int j1= 0; j1<n; j1++){
            for (int i2= i1; i2< m; i2++){
                for (int j2= j1; j2< n; j2++){
                    int sum= 0;
                    for (int k1= i1; k1< i2+1; k1++){
                        for (int k2= j1; k2< j2+1; k2++){
                            sum= sum + A[k1][k2];
                        }
                    }
                    if (sum > max_sum){
                        max_sum = sum;
                        *s_row = i1+1;
                        *s_col = i2+1;
                        *e_row = j1+1;
                        *e_col = j2+1;
                    }
                }
            }
        }
    }
    return max_sum;
}
//Task5 Give an implementation of Alg5 using O(mn) extra space. - Stefan Pessolano
int Task5(int **arr, int m, int n, int* x1, int* y1, int* x2, int* y2){
    int max_sum = arr[0][0];
    for(int i = 0; i < n; i++){
        int sums[m][n];

        for(int j = i; j < n; j++){
            for(int k = 0; k < m; k++){
                if(i == j)
                    sums[k][j] = arr[k][j];
                else  
                    sums[k][j] = arr[k][j] + sums[k][j-1];
            }
            int sums_arr[m];
            for(int k = 0; k < m; k++){
                sums_arr[k] = sums[k][j];
            }
            int start, end;
            int sum = Task2(sums_arr, m, &start, &end);
            if (sum > max_sum){
                max_sum = sum;
                *y1 = i;
                *y2 = j;
                *x1 = start;
                *x2 = end;
            }
        }
    }
    return max_sum;
}
//Task6 Give an implementation of Alg6 using O(mn) extra space. - Ummay Sumaya Khan
int Task6(int **A, int m, int n, int* x1, int* y1, int* x2, int* y2){
    int aux[m][n];
    int sum[m];
    *x1= 0;
    *x2= 0;
    *y1=0;
    *y2 =0;
    int temp_sum= INT_MIN, max_sum= INT_MIN;
    for (int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            aux[i][j] = 0;
        }
    }
    for (int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            //base case
            if (j == 0) aux[i][j] = A[i][j];
            else aux[i][j] = A[i][j] + aux[i][j-1];
        }
    }
    for (int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            int temp[m];
            for (int k=0; k<m; k++){
                if (i == 0) temp[k]= aux[k][j];
                else temp[k]= aux[k][j]- aux[k][i-1];
            }
            // int val= temp[0];
            // temp_sum = val;
            // for (int x=1; x<m; x++){
            //     val = max(temp[x]+val, temp[x]);
            //     if (val > temp_sum){
            //         temp_sum = val;
            //         x1 = temp_start;
            //         x2 = x;
            //     }
            // }
            int start, end;
            int temp_sum = Task3b(temp, m, &start, &end);
            if(temp_sum > max_sum){
                max_sum = temp_sum;
                *y1 = i+1;
                *y2 = j+1;
                *x1 = start;
                *x2 = end;
            }
        }
    }
    return max_sum;
}

int main(int argc, char **argv) {
    string problem = argv[1];
    int num = (int)problem[0] - '0';
    if(num <= 3){
        int n;
        cout << "Enter size of array (n):" << endl;
        cin >> n;

        cout << "Enter the array elements:" << endl;
        int arr[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        // Run the right function
        int start, end, sum;
        if(problem == "1"){
            sum = Task1(arr, n, &start, &end);
        }
        if(problem == "2"){
            sum = Task2(arr, n, &start, &end);
            start += 1;
            end += 1;
        }
        if(problem == "3a" || problem == "3A"){ 
            Task3a(arr, n, n);
            sum = val;
            start = start_ind;
            end = end_ind;
        }
        if(problem == "3b" || problem == "3B"){   
            sum = Task3b(arr, n, &start, &end);
        }
        cout << start << ' ' << end << ' ' << sum << endl;
    }
    else{
        int m, n;
        cout << "Enter size of array (m x n):" << endl;
        cin >> m >> n;

        // Initialize new 2D array of size m x n
        int **arr=new int*[m];
        for(int i=0;i<m;i++)
        {
            arr[i]=new int[n];
        }
        cout << "Enter the array elements:" << endl;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                cin >> arr[i][j];
            }
        }
        // Run the right function
        int max_sum, x1 =0, y1=0, x2=0, y2=0;
        if(problem == "4"){
            max_sum = Task4(arr, m, n, &x1, &y1, &x2, &y2);
        }
        if(problem == "5"){
            max_sum = Task5(arr, m, n, &x1, &y1, &x2, &y2);
            x1 += 1;
            y1 += 1;
            x2 += 1;
            y2 += 1;
        }
        if(problem == "6"){
           max_sum = Task6(arr, m, n, &x1, &y1, &x2, &y2);
        }
        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << max_sum << endl;
    }
    return 0;
}