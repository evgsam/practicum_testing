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
	ArrayPtr<Type> symple_vector_;

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
			symple_vector_(init.size()), size_(init.size()), capacity_(
					init.size()) {
		auto begin = symple_vector_.Get();
		auto end = symple_vector_.Get() + 1;
		auto value = init.begin();
		std::fill(begin, end, *value);
		while (end != symple_vector_.Get() + size_) {
			++begin;
			++end;
			++value;
			std::fill(begin, end, *value);
		}
		//std::fill(symple_vector_.Get(), symple_vector_.Get() + size_, 3);
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
		if (size_ == 0) {
			return true;
		}
		return false;

	}

	// Возвращает ссылку на элемент с индексом index
	Type& operator[](size_t index) noexcept {
		return *(symple_vector_.Get() + index);
		// Напишите тело самостоятельно
	}

	// Возвращает константную ссылку на элемент с индексом index
	const Type& operator[](size_t index) const noexcept {
		return *(symple_vector_.Get() + index);
	}

	// Возвращает константную ссылку на элемент с индексом index
	// Выбрасывает исключение std::out_of_range, если index >= size
	Type& At(size_t index) {
		if (index >= size_) {
			throw std::out_of_range("out_of_range");
		} else {
			return *(symple_vector_.Get() + index);;
		}
	}

	// Возвращает константную ссылку на элемент с индексом index
	// Выбрасывает исключение std::out_of_range, если index >= size
	const Type& At(size_t index) const {
		return At(index);
	}

	// Обнуляет размер массива, не изменяя его вместимость
	void Clear() noexcept {
		size_ = 0;
		// Напишите тело самостоятельно
	}

	// Изменяет размер массива.
	// При увеличении размера новые элементы получают значение по умолчанию для типа Type

	void Resize(size_t new_size) {
		Type t { };
		if (size_ < new_size) {
			if (new_size <= capacity_) {
				std::fill(symple_vector_.Get() + size_,
						symple_vector_.Get() + new_size, t);
			} else if (new_size > capacity_) {
				capacity_ = new_size * 2;

				//ArrayPtr<Type> tmp_symple_vector=new Type[capacity_]{};
				//ArrayPtr<Type> tmp_symple_vector = symple_vector_;
				// ArrayPtr<Type> *tmp_symple_vector = &symple_vector_;
				ArrayPtr<Type> *tmp_symple_vector =	new ArrayPtr<Type> [capacity_] { };
				tmp_symple_vector = &symple_vector_;

				std::copy(symple_vector_.Get(), symple_vector_.Get() + size_,
						tmp_symple_vector->Get());
				std::fill(tmp_symple_vector->Get() + size_ + 1,
						tmp_symple_vector->Get() + new_size, t);

				//symple_vector_.~ArrayPtr();
			//	&symple_vector_ = *tmp_symple_vector;

			}
		}
		size_ = new_size;
	}

	// Возвращает итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	Iterator begin() noexcept {
		return symple_vector_.Get();
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	Iterator end() noexcept {
		return symple_vector_.Get() + size_;
		// Напишите тело самостоятельно
	}

	// Возвращает константный итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator begin() const noexcept {
		return symple_vector_.Get();
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator end() const noexcept {
		return symple_vector_.Get() + size_;
	}

	// Возвращает константный итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator cbegin() const noexcept {
		return symple_vector_.Get();
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator cend() const noexcept {
		return symple_vector_.Get() + size_;
	}
private:
	size_t size_ { };
	size_t capacity_ { };
};

