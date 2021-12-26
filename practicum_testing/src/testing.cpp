#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

void PrintSpacesPositions(string str) {
	auto it = str.find(" ");
	while (it!=string::npos){
		cout<<it;
		cout<<endl;
		it= str.find(" ", it+1);
	}
}

int main() {
	string str = "He said: one and one and one is three"s;
	PrintSpacesPositions(str);
	return 0;
}
