#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>

template<typename norVec_Ty>
class NorVectorInterface {
public:
	virtual ~NorVectorInterface() = default;

	virtual void push_back(const norVec_Ty& value) = 0;
	virtual norVec_Ty pop_back() = 0;
	virtual void make_size(const size_t size) = 0;

	virtual norVec_Ty operatorIndex(const size_t index) = 0;

	virtual void reverse() = 0;
	virtual size_t size() = 0;
};

template<typename norVec_Ty>
class NorVector : public NorVectorInterface<norVec_Ty> {
private:
	size_t 		N;
	size_t 		capacity;
	norVec_Ty*  	norVec;
	norVec_Ty* 	arr;

public:
	NorVector() {
		capacity = N = 0;
		norVec = new norVec_Ty[N];
		arr = nullptr;
	}
	NorVector(const size_t size) {
		capacity = N = size;
		norVec = new norVec_Ty[capacity];
		arr = nullptr;
	}
	NorVector(const NorVector<norVec_Ty>& other) {
		capacity = other.capacity;
		N = other.N;
		norVec = new norVec_Ty[capacity];
		arr = nullptr;

		for (size_t i = 0; i < N; i++)
			norVec[i] = other.norVec[i];
	}
	NorVector(const std::vector<norVec_Ty>& vec) {
		capacity = N = vec.size();
		norVec = new norVec_Ty[capacity];
		arr = nullptr;

		for (size_t i = 0; i < N; i++)
			norVec[i] = vec[i];
	}

	~NorVector() {
		delete[] norVec;
		delete[] arr;
	}

	void push_back(const norVec_Ty& value) override {
		if (this->N < this->capacity) {
			this->norVec[this->N++] = value;
		} else {
			if (this->capacity < 100) {
				this->capacity = 100;
			} else if (this->capacity < 1000) {
				this->capacity *= 2;
			} else {
				this->capacity *= 1.2;
			}

			this->arr = this->norVec;
			this->norVec = new norVec_Ty[this->capacity];

			for (size_t i = 0; i < this->N; i++)
				this->norVec[i] = this->arr[i];

			this->norVec[this->N++] = value;

			delete[] this->arr;
			this->arr = nullptr;
		}
	}

	norVec_Ty pop_back() override {
		if (this->N == 0)
			throw std::runtime_error("NorVector is empty");
		
		return this->norVec[--N];
	}

	void make_size(const size_t size) override {
		if (this->capacity < size) {
			this->arr = norVec;

			this->norVec = new norVec_Ty[size];

			for (size_t i = 0; i < this->N; i++)
				this->norVec[i] - this->arr[i];

			this->capacity = this->N = size;

			delete this->arr;
			this->arr = nullptr;
		} else {
			this->N = size;
		}
	}

	norVec_Ty operatorIndex(const size_t index) override {
		return operator[](index);
	}

	norVec_Ty& operator[](const size_t index) {
		if (index >= N)
			throw std::runtime_error("Index out of range");
		return this->norVec[index];
	}

	norVec_Ty& operator()(const size_t indexFromEnd) {
		return this->norVec[N - 1 - indexFromEnd];
	}

	NorVector& operator=(const NorVector& other) = delete;

	bool operator==(const NorVector& other) {
		if (this == *other)
			return true;

		if (this->N != other.N)
			return false;

		for (size_t i = 0; i < this->N; i++)
			if (this->norVec[i] != other.norVec[i])
				return false;

		return true;
	}

	norVec_Ty& last() {
		return this->norVec[N - 1];
	}

	void copy(const NorVector<norVec_Ty>& other) {
		if (this == *other)
			return;

		capacity = other.capacity;
		N = other.N;
		norVec = new norVec_Ty[capacity];

		for (int i = 0; i < N; i++)
			norVec[i] = other[i];
	}

	bool isEmpty() {
		return N == 0;
	}

	void show() {
		for (size_t i = 0; i < this->N; i++)
			std::cout << norVec[i] << ' ';
		std::cout << "\n";
	}

	void reverse() override {
		for (size_t i = 0; i < this->N / 2; i++)
			std::swap(norVec[i], norVec[N - i - 1]);
	}

	size_t size() override {
		return this->N;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const NorVector<T>& vec) {
	for (size_t i = 0; i < vec.size(); i++)
		out << vec[i] << ' ';
	return out;
}
