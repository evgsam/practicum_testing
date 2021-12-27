#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

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
		PrintRange(elements_.begin(), elements_.end());
	}
	uint64_t Size() const {
		return static_cast<int64_t>(elements_.size());
	}
	bool IsEmpty() const {
		return elements_.empty();
	}

private:
	vector<Type> elements_;
};

template<typename Type>
class StackMin {
public:
	void Push(const Type &element) {
		elements_.Push(element);
		elements_minimum_.insert(make_pair(element, static_cast<int>(Size() - 1)));
	}
	void Pop() {
		pair<int, int> position;
		elements_minimum_.erase(Peek());
		elements_.Pop();
	}
	const Type& Peek() const {
		return elements_.Peek();
	}
	Type& Peek() {
		return elements_.Peek();
	}
	void Print() const {
		elements_.Print();
	}
	uint64_t Size() const {
		return elements_.Size();
	}
	bool IsEmpty() const {
		return elements_.IsEmpty();
	}
	const Type& PeekMin() const {
		return elements_minimum_.begin()->first;
	}

private:
	Stack<Type> elements_;
	map<Type, int> elements_minimum_;
};

int main() {

	StackMin<int> stack;
	vector<int> values(5);

	// заполняем вектор для тестирования нашего стека
	iota(values.begin(), values.end(), 1);
	// перемешиваем значения
	random_shuffle(values.begin(), values.end());

	// заполняем стек
	for (int i = 0; i < 5; ++i) {
		stack.Push(values[i]);
	}

	// печатаем стек и его минимум, постепенно убирая из стека элементы
	while (!stack.IsEmpty()) {
		stack.Print();
		cout << "Минимум = "s << stack.PeekMin() << endl;
		stack.Pop();
	}
}
