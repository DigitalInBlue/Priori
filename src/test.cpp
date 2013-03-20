#include <priori/priori.h>
#include <gtest/gtest.h>

class Alpha : public priori::Base
{
	public:
		Alpha()
		{
			this->priori(this);
		};
};

class AlphaBeta : public Alpha
{
	public:
		AlphaBeta()
		{
			this->priori(this);
		};
};

class AlphaGamma : public Alpha
{
	public:
		AlphaGamma()
		{
			this->priori(this);
		}
};

/// Test the old fashioned dynamic_cast
TEST(priori, dynamicCast)
{
	Alpha a;
	AlphaBeta b;
	AlphaGamma c;
	Alpha* aPrime = &b;

	// Ensure both a and b derrive from priori::Base
	EXPECT_TRUE(dynamic_cast<priori::Base*>(&a) != nullptr);
	EXPECT_TRUE(dynamic_cast<priori::Base*>(&b) != nullptr);

	EXPECT_TRUE(dynamic_cast<priori::Base*>(&b) != nullptr);
	EXPECT_TRUE(dynamic_cast<Alpha*>(&b) != nullptr);

	EXPECT_TRUE(dynamic_cast<priori::Base*>(aPrime) != nullptr);
	EXPECT_TRUE(dynamic_cast<Alpha*>(aPrime) != nullptr);
	EXPECT_TRUE(dynamic_cast<AlphaBeta*>(aPrime) != nullptr);

	EXPECT_TRUE(dynamic_cast<priori::Base*>(&c) != nullptr);
	EXPECT_TRUE(dynamic_cast<Alpha*>(&c) != nullptr);
	EXPECT_TRUE(dynamic_cast<AlphaBeta*>(&c) == nullptr);
	EXPECT_TRUE(dynamic_cast<AlphaGamma*>(&c) != nullptr);
}

/// Test the quick/dirty priori_cast
TEST(priori, prioriCast)
{
	priori::Base x;
	Alpha a;
	AlphaBeta b;
	AlphaGamma c;
	Alpha* aPrime = &b;

	// Ensure both a and b derrive from priori::Base
	EXPECT_TRUE(priori_cast<priori::Base*>(&a) != nullptr);
	EXPECT_TRUE(priori_cast<priori::Base*>(&b) != nullptr);

	EXPECT_TRUE(priori_cast<priori::Base*>(&b) != nullptr);
	EXPECT_TRUE(priori_cast<Alpha*>(&b) != nullptr);

	EXPECT_TRUE(priori_cast<priori::Base*>(aPrime) != nullptr);
	EXPECT_TRUE(priori_cast<Alpha*>(aPrime) != nullptr);
	EXPECT_TRUE(priori_cast<AlphaBeta*>(aPrime) != nullptr);

	EXPECT_TRUE(priori_cast<priori::Base*>(&c) != nullptr);
	EXPECT_TRUE(priori_cast<Alpha*>(&c) != nullptr);
	EXPECT_TRUE(priori_cast<AlphaBeta*>(&c) == nullptr);
	EXPECT_TRUE(priori_cast<AlphaGamma*>(&c) != nullptr);
}