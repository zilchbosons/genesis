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

#include <stdio.h>
#include <iostream>
#include <string>
#include <gmp.h>
#include <mpfr.h>
#include <vector>
#include "common.hpp"
#include "pi.hpp"
#include "e.hpp"

using namespace std;
int sequence[4] = {1, 3, 1, 2};

void print(vector<int> passage) {
	for (int i = 0; i < passage.size(); ++i ) {
		cout << passage[i]<<"\t,\t";
	}
	cout << "\n";
}

int contains(int nk, int& c) {
	int pk = sequence[c];
	if (pk == nk) {
		c  =(c + 1) % 4;
		return pk;
	} else {
		int acc = 0;
		int c1 = c; 
		int seq = 0;
		while ( acc < nk) {
			int  pk2 = sequence[c1];
			acc += pk2;
			seq = seq*10 + pk2;
			c1 = (c1 + 1) % 4;
		}
		if (acc == nk)  {
			c = c1;
			return seq;
		} else {
			return 0;
		}
	}
}

char* _Factor(char* nn)  {
	int idx = 0;
	int l = strlen(nn);
	vector<int> passage;
	int c = 0;
	while (idx < l) {
		int nk = nn[idx] - '0';
		if (nk == 0) nk =7;
		int pass = 0;
		if ((pass = contains(nk, c))) {
			passage.push_back(pass);
		} else {
			long long acc = nk;
			while (idx < l && !(pass= contains(acc, c))) {
				++idx;
if ( idx >=l) break;
				c = (c+1) % 4;
				int pk = sequence[c];
nk = nn[idx]-'0';
				acc += (nk);
			}
			if (idx >=l) {
				passage.push_back(acc);
				print(passage);
				return "";
			} else {
				passage.push_back(pass);
			}
		}
		++idx;
	}
	print(passage);
	return "";
}

//#if 0
int main() {
	/* Step 1: Reading the Number to be factorized */
	FILE* fp = fopen("./input.txt", "r");
	std::string num = "";
	char n[1024];
	int ret = 0;
	while ((ret=fscanf(fp, "%s", n))!= EOF) {
		num += n;
	}
	cout << "\nNumber read was : \t" << num <<"\n";
	char* nn = strdup((char*) num.c_str());
	int l = strlen(nn);
	char* root = _Factor(nn);
	cout <<"\nRoot:\t"<<root<<"\n";
	fclose(fp);
	free(nn);
	return 0;
}
//#endif
