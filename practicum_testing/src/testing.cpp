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
		return elements_.empty();
	}

private:
	vector<Type> elements_;
};

template <typename Type>
class StackMin {
public:
    void Push(const Type& element) {
    // напишите реализацию метода
    }
    void Pop() {
    // напишите реализацию метода
    }
    const Type& Peek() const {
        return elements_.Peek();
    }
    Type& Peek() {
        return elements_.Peek();
    }
    void Print() const {
        // работу этого метода мы проверять не будем,
        // но если он вам нужен, то можете его реализовать
        elements_.Print();
    }
    uint64_t Size() const {
        return elements_.size();
    }
    bool IsEmpty() const {
        return elements_.IsEmpty();
    }
    const Type& PeekMin() const {
    // напишите реализацию метода
    }
    Type& PeekMin() {
    // напишите реализацию метода
    }
private:
    Stack<Type> elements_;
    // возможно, здесь вам понадобится что-то изменить
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
