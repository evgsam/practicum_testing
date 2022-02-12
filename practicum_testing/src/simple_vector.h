#pragma once

#include <cassert>
#include <initializer_list>
#include <array>
#include <iterator>
#include "array_ptr.h"

template<typename Type>
class SimpleVector {
public:
	using Iterator = Type*;
	using ConstIterator = const Type*;

	SimpleVector() noexcept = default;

	// Создаёт вектор из size элементов, инициализированных значением по умолчанию
	explicit SimpleVector(size_t size) :
			SimpleVector(size, Type()) {
		// Напишите тело конструктора самостоятельно
	}

	// Создаёт вектор из size элементов, инициализированных значением value
	SimpleVector(size_t size, const Type &value) :
			symple_vector_(size), size_(size), capacity_(size) {
		std::fill(symple_vector_.Get(), symple_vector_.Get() + size, value);

	}

	// Создаёт вектор из std::initializer_list
	SimpleVector(std::initializer_list<Type> init) :
			symple_vector_(init.size()), size_(init.size()), capacity_(init.size()) {
		//std::fill(items_.Get(), items_.Get() + size, init.begin());
	}

	// Возвращает количество элементов в массиве
	size_t GetSize() const noexcept {
		return size_;
	}

	// Возвращает вместимость массива
	size_t GetCapacity() const noexcept {
		// Напишите тело самостоятельно
		return capacity_;
	}

	// Сообщает, пустой ли массив
	bool IsEmpty() const noexcept {
		return true;
	}

	// Возвращает ссылку на элемент с индексом index
	Type& operator[](size_t index) noexcept {
		return *(symple_vector_.Get()+index);
		// Напишите тело самостоятельно
	}

	// Возвращает константную ссылку на элемент с индексом index
	const Type& operator[](size_t index) const noexcept {
		// Напишите тело самостоятельно
	}

	// Возвращает константную ссылку на элемент с индексом index
	// Выбрасывает исключение std::out_of_range, если index >= size
	Type& At(size_t index) {
		// Напишите тело самостоятельно
	}

	// Возвращает константную ссылку на элемент с индексом index
	// Выбрасывает исключение std::out_of_range, если index >= size
	const Type& At(size_t index) const {
		// Напишите тело самостоятельно
	}

	// Обнуляет размер массива, не изменяя его вместимость
	void Clear() noexcept {
		size_=0;
		// Напишите тело самостоятельно
	}

	// Изменяет размер массива.
	// При увеличении размера новые элементы получают значение по умолчанию для типа Type
	void Resize(size_t new_size) {
		// Напишите тело самостоятельно
	}

	/*
	  void Resize(size_t new_size) {
        Type t{};
        if (size_ < new_size) {

            if (new_size <= capacity_) {
                std::fill(items_.Get() + size_, items_.Get() + new_size, t);

            } else if (new_size > capacity_) {
                capacity_ *= 2;
                ArrayPtr<Type> tmp_items = items_;
                tmp_items = new ArrayPtr<Type>[capacity_];

                std::copy(items_.Get(), items_.Get() + size_, tmp_items.Get());
                std::fill(tmp_items.Get() + size_ + 1, tmp_items.Get() + new_size, t);

                delete[] items_;
            }
        }
        size_ = new_size;
    }
	 */
	// Возвращает итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	Iterator begin() noexcept {
		// Напишите тело самостоятельно
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	Iterator end() noexcept {
		// Напишите тело самостоятельно
	}

	// Возвращает константный итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator begin() const noexcept {
		// Напишите тело самостоятельно
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator end() const noexcept {
		// Напишите тело самостоятельно
	}

	// Возвращает константный итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator cbegin() const noexcept {
		// Напишите тело самостоятельно
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator cend() const noexcept {
		// Напишите тело самостоятельно
	}
private:
	size_t size_ { };
	size_t capacity_ { };
	ArrayPtr<Type> symple_vector_;
};
