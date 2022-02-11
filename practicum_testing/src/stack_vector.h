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
	explicit StackVector(size_t a_size = 0);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	//? ? ? begin();? ? ? end();? ? ? begin() const;? ? ? end() const;

	size_t Size() const;
	size_t Capacity() const;

	void PushBack(const T &value);
	T PopBack();
};
