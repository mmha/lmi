#include <gtest/gtest.h>
#include <lmi/iostream_support.h>
#include <lmi/lmi.h>

TEST(EmptyTest, nothing)
{
	lmi::vec3 a(1, 2, 3), b(4, 5, 6);
	auto c = lmi::cross(a, b);

	lmi::mat3 scale = lmi::scale(2.0f, 2.0f, 2.0f);
	lmi::mat3 rotate = lmi::rotateAngles(90.0f, 0.0f, 0.0f);

	(void)c;
	(void)scale;
	(void)rotate;

	// std::cout << scale * rotate * c << std::endl;
}

template <int x>
struct CompiletimeValue
{
	const static int value = x;
};

// clang-format off
static_assert(CompiletimeValue<
		static_cast<int>(
			lmi::length(
					lmi::vec2(10, 10) +
					lmi::vec2(20, 20)
			)
		)
		>::value == 42, "");
// clang-format on
