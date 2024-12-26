#pragma once

#include "gmock/gmock.h"

#include "NorVector.h"

template<typename norVec_Ty>
class MockNorVector : public NorVectorInterface<norVec_Ty> {
private:
	size_t 		N;
	size_t 		capacity;
	norVec_Ty* 	norVec;
	norVec_Ty* 	arr;

public:
    MockNorVector() {
        capacity = N = 0;
		norVec = new norVec_Ty[N];
		arr = nullptr;
    }
    MockNorVector(const size_t size) {
        capacity = N = size;
		norVec = new norVec_Ty[capacity];
		arr = nullptr;
    }
    MockNorVector(const MockNorVector<norVec_Ty>& other) {
		capacity = other.capacity;
		N = other.N;
		norVec = new norVec_Ty[capacity];
		arr = nullptr;

		for (int i = 0; i < N; i++)
			norVec[i] = other.norVec[i];
	}
	MockNorVector(const std::vector<norVec_Ty>& vec) {
		capacity = N = vec.size();
		norVec = new norVec_Ty[capacity];
		arr = nullptr;

		for (size_t i = 0; i < N; i++)
			norVec[i] = vec[i];
	}

    ~MockNorVector() {
        delete[] norVec;
        delete[] arr;
    }

    MOCK_METHOD1_T(push_back, void(const norVec_Ty& value));
	MOCK_METHOD0_T(pop_back, norVec_Ty());
    MOCK_METHOD1_T(make_size, void(const size_t size));

    MOCK_METHOD0_T(reverse, void());

	MOCK_METHOD1_T(operatorIndex, norVec_Ty(const size_t index));
	MOCK_METHOD0_T(size, size_t());
};

