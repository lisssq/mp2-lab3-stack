#include "../stack/stack.h"

#include "gtest.h"

TEST(TStack, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> m);
}

/*
TEST(TStack, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TStack<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TStack, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> m(-5));
}

TEST(TStack, can_create_copied_matrix)
{
  TStack<int> m(5);

  ASSERT_NO_THROW(TStack<int> m1(m));
}

TEST(TStack, copied_matrix_is_equal_to_source_one)
{
	TStack<int> m1(5);
	for (int i = 0; i < 5; i++)
	{
		m1[i][i] = i + 1;
	}

	TStack<int> m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(TStack, copied_matrix_has_its_own_memory)
{
	TStack<int> m1(3);
	m1[0][0] = 1;

	TStack<int> m2(m1);
	m2[0][0] = 100;

	EXPECT_NE(m1[0][0], m2[0][0]);
}

TEST(TStack, can_get_size)
{
	TStack<int> m(4);
	EXPECT_EQ(4, m.GetSize());
}

TEST(TStack, can_set_and_get_element)
{
	TStack<int> m(3);
	m[1][1] = 42;
	EXPECT_EQ(42, m[1][1]);
}

TEST(TStack, throws_when_set_element_with_negative_index)
{
	TStack<int> m(3);
	ASSERT_ANY_THROW(m[-1][-1] = 10);
}

TEST(TStack, throws_when_set_element_with_too_large_index)
{
	TStack<int> m(3);
	ASSERT_ANY_THROW(m[3][3] = 10);
}

TEST(TStack, can_assign_matrix_to_itself)
{
	TStack<int> m(3);
	ASSERT_NO_THROW(m = m);
}

TEST(TStack, can_assign_matrices_of_equal_size)
{
	TStack<int> m1(3);
	TStack<int> m2(3);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TStack, assign_operator_change_matrix_size)
{
	TStack<int> m1(3);
	TStack<int> m2(5);
	m1 = m2;
	EXPECT_EQ(m1.GetSize(), 5);
}

TEST(TStack, can_assign_matrices_of_different_size)
{
	TStack<int> m1(3);
	TStack<int> m2(5);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TStack, compare_equal_matrices_return_true)
{
	TStack<int> m1(3);
	TStack<int> m2(3);
	EXPECT_TRUE(m1 == m2);
}

TEST(TStack, compare_matrix_with_itself_return_true)
{
	TStack<int> m(3);
	EXPECT_TRUE(m == m);
}

TEST(TStack, matrices_with_different_size_are_not_equal)
{
	TStack<int> m1(3);
	TStack<int> m2(5);
	EXPECT_FALSE(m1 == m2);
}

TEST(TStack, can_add_matrices_with_equal_size)
{
	TStack<int> m1(3);
	TStack<int> m2(3);

	m1[0][0] = 1; m1[1][1] = 2; m1[2][2] = 3;
	m2[0][0] = 4; m2[1][1] = 5; m2[2][2] = 6;

	TStack<int> res = m1 + m2;

	EXPECT_EQ(res[0][0], 5);
	EXPECT_EQ(res[1][1], 7);
	EXPECT_EQ(res[2][2], 9);
}

TEST(TStack, cant_add_matrices_with_not_equal_size)
{
	TStack<int> m1(3);
	TStack<int> m2(5);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TStack, can_subtract_matrices_with_equal_size)
{
	TStack<int> m1(3);
	TStack<int> m2(3);

	m1[0][0] = 1; m1[1][1] = 2; m1[2][2] = 3;
	m2[0][0] = 4; m2[1][1] = 5; m2[2][2] = 16;

	TStack<int> res = m1 - m2;

	EXPECT_EQ(res[0][0], -3);
	EXPECT_EQ(res[1][1], -3);
	EXPECT_EQ(res[2][2], -13);
}

TEST(TStack, cant_subtract_matrixes_with_not_equal_size)
{
	TStack<int> m1(3);
	TStack<int> m2(5);

	ASSERT_ANY_THROW(m1 - m2);
}*/

