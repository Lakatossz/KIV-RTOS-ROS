/*#include <gtest/gtest.h>
#include "../../../include/insulin_pump/pid_regulator/pid_regulator.hpp" 

// Test pid_integral
TEST(PIDTest, IntegralBasic) {
	std::vector<float> values = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
	EXPECT_FLOAT_EQ(pid_integral(values), 15.0f); // 1+2+3+4+5 = 15
}

TEST(PIDTest, IntegralEmpty) {
	std::vector<float> values = {};
	EXPECT_FLOAT_EQ(pid_integral(values), 0.0f);
}

TEST(PIDTest, IntegralNegativeValues) {
	std::vector<float> values = { -1.0f, -2.0f, -3.0f };
	EXPECT_FLOAT_EQ(pid_integral(values), -6.0f);
}

// Test pid_derivative
TEST(PIDTest, DerivativeBasic) {
	std::vector<float> values = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
	EXPECT_FLOAT_EQ(pid_derivative(values, 4), 4.0f); // 5 - 1 = 4
}

TEST(PIDTest, DerivativeSameValues) {
	std::vector<float> values = { 10.0f, 10.0f, 10.0f, 10.0f };
	EXPECT_FLOAT_EQ(pid_derivative(values, 3), 0.0f);
}

TEST(PIDTest, DerivativeNegativeValues) {
	std::vector<float> values = { -5.0f, -3.0f, -1.0f, 1.0f };
	EXPECT_FLOAT_EQ(pid_derivative(values, 3), 6.0f); // 1 - (-5) = 6
}

TEST(PIDTest, DerivativeOutOfBounds) {
	std::vector<float> values = { 1.0f, 2.0f, 3.0f };
	EXPECT_DEATH(pid_derivative(values, 5), ""); // Mìl by spadnout, index mimo rozsah
}*/
