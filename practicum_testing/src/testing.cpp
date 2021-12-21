// авторское решение - https://www.onlinegdb.com/BkY1XyRPD

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

template<typename Container, typename Separator>
void FindAndPrint(Container cont, Separator sep){
	auto it=find_if(cont.begin(),cont.end(),[sep](const Separator &item){
		return item==sep;
	});
		PrintRange(cont.begin(), it);
		PrintRange(it, cont.end());
}

int main() {
    set<int> test = {1, 1, 1, 2, 3, 4, 5, 5};
    FindAndPrint(test, 3);
    FindAndPrint(test, 0);
    return 0;
}
