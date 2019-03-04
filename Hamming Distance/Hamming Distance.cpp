#include <iostream>
#include <string>
#include <cmath>
using namespace std;


int main ()
{
	int x = 1;
	int y = 4; 
	const int size = 4; 
    int x_binary [size] = {0};
    int y_binary [size] = {0};
    int x_binary_counter = 0;
    int y_binary_counter = 0; 
    int hamming = 0;
        while (x > 0){
            x_binary [x_binary_counter] = x % 2;
            x = x/2;
            x_binary_counter ++;
        }
        while (y > 0){
            y_binary [y_binary_counter] = y % 2;
            y = y/2;
            y_binary_counter ++;
        }
        for (int i = size-1;i>-1;i--){
        	cout << "X is: " << x_binary[i] << endl;
        	cout << "Y is: " << y_binary[i] << endl;
            if (x_binary[i] != y_binary[i])
                hamming ++; 
        }
    for (int i = 0; i < size; i++)
		cout << x_binary[i];
	cout<< " " << endl; 
	for (int i = 0; i < size; i++)
		cout << y_binary[i];  
}
