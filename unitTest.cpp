#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "NorVector.h"
#include "MockNorVector.h"

#include <vector>

TEST(ConstructorTests, SelfCopy) {
	// Arrange
	NorVector<int> a(10);

	for (int i = 0; i < a.size(); i++)
		a[i] = i + 1;

	// Act + Assert
	NorVector<int> b(a);

	EXPECT_EQ(a.size(), b.size());

	for (int i = 0; i < b.size(); i++) {
		EXPECT_EQ(a[i], b[i]);
	}
}

TEST(ConstructorTests, Std_VectorCopy) {
	// Arrange
	const int SIZE = 10;
	std::vector<int> a(SIZE);
	NorVector<int> b(a);
	int actualSize = b.size();

	// Act + Assert
	EXPECT_EQ(SIZE, b.size());

	for (int i = 0; i < b.size(); i++)
		EXPECT_EQ(a[i], b[i]);
}

TEST(Operators, Index) {
	// Arrange
	const int SIZE = 10;
	std::vector<int> a(SIZE);

	for (int i = 0; i < a.size(); i++)
		a[i] = i + 1;

	MockNorVector<int> vec(SIZE);
	int index = 2;
	int value = a[index];

	// Act + Assert
	EXPECT_CALL(vec, operatorIndex(index))
		.WillOnce(testing::Return(value));
	
	int result = vec.operatorIndex(index);

	EXPECT_EQ(result, value);
}

TEST(Operators, IndexException) {
	// Arrange
	const int SIZE = 10;
	MockNorVector<int> vec(SIZE);
	int index = 1000;

	// Act + Assert
	EXPECT_CALL(vec, operatorIndex(index))
		.Times(1)
		.WillRepeatedly(
			testing::Throw(std::runtime_error("Index out of range"))
		);

	EXPECT_THROW({
		try {
			vec.operatorIndex(index);
		} catch (const std::runtime_error &e) {
			EXPECT_STREQ("Index out of range", e.what());
			throw e;
		}
	}, std::runtime_error);
}

TEST(Methods, push_back) {
	MockNorVector<int> vec;
	int value = 13;
	
	EXPECT_CALL(vec, push_back(value))
		.WillOnce(testing::Return());
	
	EXPECT_CALL(vec, operatorIndex(0))
		.WillOnce(testing::Return(value));
	
	vec.push_back(value);

	int result = vec.operatorIndex(0);
	
	EXPECT_EQ(result, value);
}

TEST(Methods, make_size) {
	const int SIZE_1 = 10;
	const int SIZE_2 = 20;
	MockNorVector<int> vec(SIZE_1);

	EXPECT_CALL(vec, make_size(testing::_))
		.Times(2);
	
	EXPECT_CALL(vec, size())
		.Times(2)
		.WillOnce(testing::Return(SIZE_2))
		.WillOnce(testing::Return(SIZE_1));
	
	vec.make_size(SIZE_2);

	int actualSize = vec.size();

	EXPECT_EQ(SIZE_2, actualSize);

	vec.make_size(SIZE_1);

	actualSize = vec.size();

	EXPECT_EQ(SIZE_1, actualSize);
}

TEST(Methods, reverse) {
	std::vector<int> vec{ 1, 2, 3, 4, 5, 6 };
	MockNorVector<int> a;

	EXPECT_CALL(a, push_back)
		.Times(6);

	EXPECT_CALL(a, reverse)
		.Times(1);
	
	for (int i = 0; i < 6; i++) {
		EXPECT_CALL(a, operatorIndex(i))
			.WillOnce(testing::Return(6 - i));
	}
	
	for (int i = 0; i < 6; i++)
		a.push_back(i + 1);
	
	a.reverse();
	
	for (int i = 0; i < vec.size(); i++) {
		int value = a.operatorIndex(vec.size() - 1 - i);
		EXPECT_EQ(vec[i], value);
	}
}