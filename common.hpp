#ifndef _COMMON_
#define _COMMON_
/*********************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy	 *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell	 *
 * copies of the Software, and to permit persons to whom the Software is		 *
 * furnished to do so, subject to the following conditions:			 *
 * 										 *
 * The above copyright notice and this permission notice shall be included in	 *
 * all copies or substantial portions of the Software.				 *
 * 										 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,	 *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE	 *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	 *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN	 *	
 * THE SOFTWARE.									 *
 **********************************************************************************/

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

int primes[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

enum sequence { one=1, three=3, two=2 } seq;


struct Node {
	int zero;
	vector<int> digits;
	Node* next;
};

namespace common {

unsigned long long int reverse_number(unsigned long long int n) {
	if (n < 10) return n*10;
	unsigned long long int t = n;
	unsigned long long int sum = 0;
	while (t > 0 ){
		sum = sum*10 + (t % 10);
		t /= 10;
	}
	return sum;
}

int roundOff(long double x ) {
	long double y = x + .5;
	if ( y >= (floor(x) + 1)) {
		y = x + 1;
	} else {
		y = x;
	}
	return floor(y);
}

bool _isPrime(int x) {
	switch (x) {
		case 2:
		case 3:
		case 5:
		case 7:
		case 11:
		case 13:
		case 17:
		case 19:
		case 23:
		case 29:
		case 31:
		case 37:
		case 41:
		case 43:
		case 47:
		case 53:
		case 59:
		case 61:
		case 67:
		case 71:
		case 73:
		case 79:
		case 83:
		case 89:
		case 97:
			return true;
		default:
			return false;
	}
	return false;
}


#if 0
int countPrimes(int x, int y) {
	int count = 0;
	for (int i = x + 1; i < y; ++i) {
		if (isPrime(i)) ++count;
	}
#ifdef _DEBUG
	cout <<"\nx:\t"<<x<<"\t,\ty:\t"<<y<<"\t,\tcount:\t"<<count<<"\n";
#endif
	return count;
}
#endif

char* reverse_string(char* t) {
	char* s = strdup(t); 
	for (int i = 0; i < floor(strlen(s)/2.0); ++i) {
		char tmp = s[i];
		s[i] = s[strlen(s) - i - 1];
		s[strlen(s) - i - 1] = tmp;
	}
	return s;
}

int specials[10][2] = {
	{2, 3},
	{1, 3},
	{3, 0},
	{1, 2},
	{1, 3},
	{3, 0},
	{1, 0},
	{1, 3},
	{3, 0},
	{1, 2}
};

int riemann_zeros[29] = { 14, 21, 25, 30, 32, 37, 40, 43, 48, 49, 52, 56, 59, 60, 65, 67, 69, 72, 75, 77, 79, 82, 84, 87, 88, 92, 94, 95, 98 };

bool _riemannExists(int x) {
	switch (x) {
		case 14:
		case 21:
		case 25:
		case 30:
		case 32:
		case 37:
		case 40:
		case 43:
		case 48:
		case 49:
		case 52:
		case 56:
		case 59:
		case 60:
		case 65:
		case 67:
		case 69:
		case 72:
		case 75:
		case 77:
		case 79:
		case 82:
		case 84:
		case 87:
		case 88:
		case 92:
		case 94:
		case 95:
		case 98:
			return true;
		default:
			return false;
	}
	return false;
}

#endif
}
