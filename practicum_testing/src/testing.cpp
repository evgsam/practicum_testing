#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

template<typename It>
void PrintRange(It begin, It end){
	for (auto i=begin;i!=end;i++){
		cout<<*i<<" "s;
	}
	cout<<endl;
}

int main() {
    set<int> test = {1, 1, 1, 2, 3, 4, 5, 5};
    PrintRange(test.begin(), test.end());
    return 0;
}
