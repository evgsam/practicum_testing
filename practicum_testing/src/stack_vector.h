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
		if (a_size > Capacity()) {
			throw std::invalid_argument("invalid_argument");
		}

		size_ = a_size;
		capacity_ = Capacity();
	}

	T& operator[](size_t index) {
		return array_.at(index);
	}
	const T& operator[](size_t index) const {
		return array_.at(index);
	}

	typename std::array<T, N>::iterator begin() {
		return array_.begin();
	}
	typename std::array<T, N>::iterator end() {
		auto it_first = array_.begin();
		auto it_last = size_;
		auto nx = std::next(it_first, it_last);
		return nx;
	}
	typename std::array<T, N>::const_iterator begin() const {
		return array_.begin();
	}
	typename std::array<T, N>::const_iterator end() const {
		auto it_first = array_.begin();
		auto it_last = size_;
		auto nx = std::next(it_first, it_last);
		return nx;
	}

	size_t Size() const {
		return size_;
	}
	size_t Capacity() const {
		return array_.max_size();
	}

	void PushBack(const T &value) {
		if (Size() == Capacity()) {
			throw std::overflow_error("overflow_error");
		} else {
			array_.at(size_) = value;
			++size_;
		}

	}
	T PopBack() {
		if (size_ == 0) {
			throw std::underflow_error("underflow_error");
		} else {
			--size_;
			return array_[size_];

		}
	}
private:
	std::array<T, N> array_;
	size_t size_ { };
	size_t capacity_ { };
};
