/*
 * stack_vector.h
 *
 *  Created on: 11 февр. 2022 г.
 *      Author: user
 */

#pragma once

#include <array>
#include <stdexcept>

template<typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        if (a_size > capacity_ ) {
            throw std::invalid_argument("invalid_argument");
        }

        capacity_ = a_size;
    }

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	typename std::array<T, N>::iterator begin();
	typename std::array<T, N>::iterator end();
	typename std::array<T, N>::iterator begin() const;
	typename std::array<T, N>::iterator end() const;

	//? ? ? begin();? ? ? end();? ? ? begin() const;? ? ? end() const;

	size_t Size() const;
	size_t Capacity() const;

	void PushBack(const T &value);
	T PopBack();
private:
	std::array<T, N> array_;
	size_t size_ { };
	size_t capacity_ { };
};
