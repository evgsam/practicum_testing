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
	}

	// Создаёт вектор из size элементов, инициализированных значением value
	SimpleVector(size_t size, const Type &value) :
			symple_vector_(size), size_(size), capacity_(size) {
		std::fill(symple_vector_.Get(), symple_vector_.Get() + size, value);
	}

	// Создаёт вектор из std::initializer_list
	SimpleVector(std::initializer_list<Type> init) :
			symple_vector_(init.size()), size_(init.size()), capacity_(init.size()) {
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
	}

	SimpleVector(const SimpleVector &other) :
			size_(other.size_), capacity_(other.capacity_) {
		//SimpleVector tmp(other.size_);
		ArrayPtr<Type> tmp(capacity_);
		std::copy(other.begin(), other.end(), tmp.Get());
		symple_vector_.swap(tmp);
		//symple_vector_.swap(tmp);
		//tmp.swap(other);
		//other.swap(tmp);
	}

	SimpleVector& operator=(const SimpleVector &rhs) {
		size_ = rhs.size_;
		capacity_ = rhs.capacity_;
		if (this != &rhs) {
			auto rhs_copy(rhs);
			swap(rhs_copy);
		}
		return *this;
	}

	// Возвращает количество элементов в массиве
	size_t GetSize() const noexcept {
		return size_;
	}

	// Возвращает вместимость массива
	size_t GetCapacity() const noexcept {
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
		if (index >= size_) {
			throw std::out_of_range("out_of_range");
		} else {
			return *(symple_vector_.Get() + index);;
		}
	}

	// Обнуляет размер массива, не изменяя его вместимость
	void Clear() noexcept {
		size_ = 0;
	}

	// Изменяет размер массива.
	// При увеличении размера новые элементы получают значение по умолчанию для типа Type

	void Resize(size_t new_size) {
		Type t { };
		if (size_ < new_size) {
			if (new_size <= capacity_) {
				std::fill(symple_vector_.Get() + size_, symple_vector_.Get() + new_size, t);
			} else if (new_size > capacity_) {
				if (capacity_ * 2 < new_size) {
					capacity_ = new_size;
				} else {
					capacity_ *= 2;
				}
				ArrayPtr<Type> tmp_symple_vector(capacity_);
				std::copy(symple_vector_.Get(), symple_vector_.Get() + size_, tmp_symple_vector.Get());
				std::fill(tmp_symple_vector.Get() + size_, tmp_symple_vector.Get() + new_size, t);
				symple_vector_.swap(tmp_symple_vector);
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

	// Добавляет элемент в конец вектора
	// При нехватке места увеличивает вдвое вместимость вектора
	void PushBack(const Type &item) {
		auto old_size = GetSize();
		if (GetSize() == GetCapacity()) {
			Resize(size_ == 0 ? 1 : size_ * 2);
		}
		symple_vector_[old_size] = item;
		size_ = old_size + 1;
	}

	// Вставляет значение value в позицию pos.
	// Возвращает итератор на вставленное значение
	// Если перед вставкой значения вектор был заполнен полностью,
	// вместимость вектора должна увеличиться вдвое, а для вектора вместимостью 0 стать равной 1
	Iterator Insert(ConstIterator pos, const Type &value) {
		Type t { };
		if (GetSize() == GetCapacity()) {
			Resize(size_ == 0 ? 1 : size_ * 2);
		}
		size_t len = std::distance(begin(), Iterator(pos));
		ArrayPtr<Type> tmp_symple_vector(size_);
		std::copy(symple_vector_.Get(), symple_vector_.Get() + len, tmp_symple_vector.Get());
		tmp_symple_vector[len + 1] = value;
		std::copy(symple_vector_.Get() + len + 1, symple_vector_.Get() + size_, tmp_symple_vector.Get() + len + 1);
		symple_vector_.swap(tmp_symple_vector);
	}

	// "Удаляет" последний элемент вектора. Вектор не должен быть пустым
	void PopBack() noexcept {
		// Напишите тело самостоятельно
	}

	// Удаляет элемент вектора в указанной позиции
	Iterator Erase(ConstIterator pos) {
		// Напишите тело самостоятельно
	}

	// Обменивает значение с другим вектором
	void swap(SimpleVector &other) noexcept {
		// Напишите тело самостоятельно
	}

private:
	size_t size_ { };
	size_t capacity_ { };
};

template<typename Type>
inline bool operator==(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
	// Заглушка. Напишите тело самостоятельно
	return true;
}

template<typename Type>
inline bool operator!=(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
	// Заглушка. Напишите тело самостоятельно
	return true;
}

template<typename Type>
inline bool operator<(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
	// Заглушка. Напишите тело самостоятельно
	return true;
}
