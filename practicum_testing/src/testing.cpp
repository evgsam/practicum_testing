#include <stack>
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
class Queue {
public:
	void Push(const Type &element) {
		stack1_.push(element);
		// напишите реализацию
	}
	void Pop() {
		stack2_.pop();
		// напишите реализацию
	}

	void Reconstr(void) {
		if (!stack2_.empty()) {
			stack1_.push(stack2_.top());
			stack2_.pop();
			Reconstr();
		}
	}

	Type& SearchFront(Type res) {
		if (!IsEmpty()) {
			stack2_.push(stack1_.top());
			res = stack2_.top();
			stack1_.pop();
			SearchFront(res);
			return res;
		}

	}
	Type& Front() {
		Type res;
		if (Size() == 1) {
			return stack1_.top();
		} else {
			return SearchFront(res);
		}

		// напишите реализацию
	}
	const Type& Front() const {
		return SearchFront();
		// напишите реализацию
	}

	uint64_t Size() const {
		return static_cast<int64_t>(stack1_.size());
		// напишите реализацию
	}
	bool IsEmpty() const {
		return stack1_.empty();
		// напишите реализацию
	}

private:
	stack<Type> stack1_;
	stack<Type> stack2_;
};

int main() {
	Queue<int> queue;
	vector<int> values(5);

	// заполняем вектор для тестирования очереди
	iota(values.begin(), values.end(), 1);
	// перемешиваем значения
	random_shuffle(values.begin(), values.end());

	PrintRange(values.begin(), values.end());

	cout << "Заполняем очередь"s << endl;

	// заполняем очередь и выводим элемент в начале очереди
	for (int i = 0; i < 5; ++i) {
		queue.Push(values[i]);
		cout << "Вставленный элемент "s << values[i] << endl;
		cout << "Первый элемент очереди "s << queue.Front() << endl;
	}

	cout << "Вынимаем элементы из очереди"s << endl;

	// выводим элемент в начале очереди и вытаскиваем элементы по одному
	while (!queue.IsEmpty()) {
		// сначала будем проверять начальный элемент, а потом вытаскивать,
		// так как операция Front на пустой очереди не определена
		cout << "Будем вынимать элемент "s << queue.Front() << endl;
		queue.Pop();
	}
	return 0;
}
