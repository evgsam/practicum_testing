#include <iostream>
#include <vector>

using namespace std;

template<typename It>
void PrintRange(It range_begin, It range_end) {
	for (auto it = range_begin; it != range_end; ++it) {
		cout << *it << " "s;
	}
	cout << endl;
}

template<typename Type>
class Stack {
public:
	void Push(const Type &element) {
		elements_.push_back(element);
		// напишите реализацию
	}
	void Pop() {
		elements_.pop_back();
		// напишите реализацию
	}
	const Type& Peek() const {
		return elements_.back();
	}
	Type& Peek() {
		return elements_.back();
		// напишите реализацию
	}
	void Print() const {
		PrintRange(elements_.begin(),elements_.end());
	}
	uint64_t Size() const {
		return static_cast<int64_t>(elements_.size());
	}
	bool IsEmpty() const {
		if(elements_.empty()){
			return true;
		}
		return false;
	}

private:
	vector<Type> elements_;
};

int main() {
    Stack<int> stack;
    for (uint32_t i = 0; i < 10; ++i) {
        stack.Push(i);
        stack.Print();
    }
    while (!stack.IsEmpty()) {
        stack.Pop();
        stack.Print();
    }

}
