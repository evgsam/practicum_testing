/*
 * array_ptr.h
 *
 *  Created on: 12 февр. 2022 г.
 *      Author: user
 */

#pragma once

#include <cassert>
#include <cstdlib>
#include <utility>

template<typename Type>
class ArrayPtr {
public:
	// Инициализирует ArrayPtr нулевым указателем
	ArrayPtr() = default;

	// Создаёт в куче массив из size элементов типа Type.
	// Если size == 0, поле raw_ptr_ должно быть равно nullptr
	explicit ArrayPtr(size_t size) {
		if (size == 0) {
			raw_ptr_ = nullptr;
		} else {
			raw_ptr_ = new Type[size];
		}
	}

	// Конструктор из сырого указателя, хранящего адрес массива в куче либо nullptr
	explicit ArrayPtr(Type *raw_ptr) noexcept:raw_ptr_(raw_ptr) {
	}

	// Запрещаем копирование
	ArrayPtr(const ArrayPtr&) = delete;

	~ArrayPtr() {
		delete[] raw_ptr_;
		// Напишите деструктор самостоятельно
	}

	// Запрещаем присваивание
	ArrayPtr& operator=(const ArrayPtr&) = delete;

	// Прекращает владением массивом в памяти, возвращает значение адреса массива
	// После вызова метода указатель на массив должен обнулиться
	[[nodiscard]] Type* Release() noexcept {
		auto adr=Get();
		raw_ptr_=nullptr;
		return adr;
	}

	// Возвращает ссылку на элемент массива с индексом index
	Type& operator[](size_t index) noexcept {
		return raw_ptr_[index];
	}

	// Возвращает константную ссылку на элемент массива с индексом index
	const Type& operator[](size_t index) const noexcept {
		return raw_ptr_[index];
	}

	// Возвращает true, если указатель ненулевой, и false в противном случае
	explicit operator bool() const {
		if (raw_ptr_!=nullptr){
			return true;
		}
		return false;
	}

	// Возвращает значение сырого указателя, хранящего адрес начала массива
	Type* Get() const noexcept {
		return raw_ptr_;
	}

	// Обменивается значениям указателя на массив с объектом other
	void swap(ArrayPtr &other) noexcept {
		std::swap(other.raw_ptr_, raw_ptr_);
	}

private:
	Type *raw_ptr_ = nullptr;
};
