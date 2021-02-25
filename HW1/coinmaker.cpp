#include <iostream>
using namespace std;
int main (){
	int dollars, cents;
	int p = 0; 
	int n = 0; 
	int d = 0; 
	int q = 0;
	
	cout << "Enter dollars: ";
	cin >> dollars;
	cout << "Enter cents: ";
	cin >> cents;
	
	q += dollars*4;
	q += (cents/25);
	cents = cents%25;
	d += (cents/10);
	cents = cents%10;
	n += (cents/5);
	cents = cents%5;
	p += cents;
	
	cout << "Pennies: " << p << endl << "Nickels: " << n << endl
	<< "Dimes: " << d << endl << "Quarters: " << q << endl << endl << "Total coins used: " << p+q+n+d << endl;
	
    return 0;
}