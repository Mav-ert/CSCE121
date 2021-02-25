#include <iostream>
#include "functions.h"
int countDigitOccurrences(int n, int digit){
	int c = 0; 
    while (n > 0) { 
        if (n % 10 == digit) 
            c++; 
        n = n / 10; 
    } 
      
    return c; 
}
