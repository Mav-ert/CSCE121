#include <iostream>
#include "functions.h"
using namespace std;

int main (){
	int a = 0, b = 0;
	cout << "Enter numbers a <= b:" << endl;
	cin >> a >> b;
	bool isRepeat = true;
	int count=0;
	
	if ((b < a) || (b > 10000) || (a <= 0) || (b < 0)){
		cout << "Invalid input" << endl;
	
	}else{
		
		for(int i=a; i<=b ; i++){
			// runs this for each number
			
			for(int i2=0; i2 <= 9; i2++){
				//checks for repeat of digits
			
				if (countDigitOccurrences(i,i2)<=1){
				isRepeat=false;
				}else{
					isRepeat=true;
					break;//stops once there is repeat
				}
			}
			//tallies the count of numbers that have no repeats
			if (isRepeat==false){
				count+=1;
				isRepeat=true;
			}
		}
		
		cout << "There are " << count << " valid numbers between " << a <<" and "<< b << endl;  
	}
    return 0;
}