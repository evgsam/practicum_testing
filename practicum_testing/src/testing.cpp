#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

template<typename Type>
class SingleLinkedList {
	struct Node {
		Node() = default;
		Node(const Type &val, Node *next) :
				value(val), next_node(next) {
		}
		Type value;
		Node *next_node = nullptr;
	};

public:
	 ~SingleLinkedList(){
		 Clear();
	 }

	// Возвращает количество элементов в списке за время O(1)
	size_t GetSize() const noexcept {
		return size_;
	}

	// Сообщает, пустой ли список за время O(1)
	bool IsEmpty() const noexcept {
		if (size_ == 0) {
			return true;
		} else {
			return false;
		}
	}

	void PushFront(const Type &value) {
		head_.next_node = new Node(value, head_.next_node);
		++size_;
	}

	// Очищает список за время O(N)
	void Clear() noexcept {
		while (head_.next_node != nullptr) {
			Node *new_head = head_.next_node->next_node;
			delete head_.next_node;
			head_.next_node = new_head;
		}
		size_ = 0;
	}

private:
	// Фиктивный узел, используется для вставки "перед первым элементом"
	Node head_;
	size_t size_ = 0;
}
;

// Эта функция тестирует работу SingleLinkedList
void Test2() {
    // Итерирование по пустому списку
    {
        SingleLinkedList<int> list;
        // Константная ссылка для доступа к константным версиям begin()/end()
        const auto& const_list = list;

        // Итераторы begine и end у пустого диапазона равны друг другу
        assert(list.begin() == list.end());
        assert(const_list.begin() == const_list.end());
        assert(list.cbegin() == list.cend());
        assert(list.cbegin() == const_list.begin());
        assert(list.cend() == const_list.end());
    }

    // Итерирование по непустому списку
    {
        SingleLinkedList<int> list;
        const auto& const_list = list;

        list.PushFront(1);
        assert(list.GetSize() == 1u);
        assert(!list.IsEmpty());

        assert(const_list.begin() != const_list.end());
        assert(const_list.cbegin() != const_list.cend());
        assert(list.begin() != list.end());

        assert(const_list.begin() == const_list.cbegin());

        assert(*list.cbegin() == 1);
        *list.begin() = -1;
        assert(*list.cbegin() == -1);

        const auto old_begin = list.cbegin();
        list.PushFront(2);
        assert(list.GetSize() == 2);

        const auto new_begin = list.cbegin();
        assert(new_begin != old_begin);
        // Проверка прединкремента
        {
            auto new_begin_copy(new_begin);
            assert((++(new_begin_copy)) == old_begin);
        }
        // Проверка постинкремента
        {
            auto new_begin_copy(new_begin);
            assert(((new_begin_copy)++) == new_begin);
            assert(new_begin_copy == old_begin);
        }
        // Итератор, указывающий на позицию после последнего элемента равен итератору end()
        {
            auto old_begin_copy(old_begin);
            assert((++old_begin_copy) == list.end());
        }
    }
    // Преобразование итераторов
    {
        SingleLinkedList<int> list;
        list.PushFront(1);
        // Конструирование ConstItrator из Iterator
        SingleLinkedList<int>::ConstIterator const_it(list.begin());
        assert(const_it == list.cbegin());
        assert(*const_it == *list.cbegin());

        SingleLinkedList<int>::ConstIterator const_it1;
        // Присваивание ConstIterator-у значения Iterator
        const_it1 = list.begin();
        assert(const_it1 == const_it);
    }
    // Проверка оператора ->
    {
        using namespace std;
        SingleLinkedList<std::string> string_list;

        string_list.PushFront("one"s);
        assert(string_list.cbegin()->length() == 3u);
        string_list.begin()->push_back('!');
        assert(*string_list.begin() == "one!"s);
    }
}

int main() {
    Test2();
}
