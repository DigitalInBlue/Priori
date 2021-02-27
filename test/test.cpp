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

class Beta : public Alpha
{
public:
	Beta()
	{
		this->priori(this);
	};
};

class Beta2 : public Alpha
{
public:
	Beta2()
	{
		this->priori(this);
	}
};

class Gamma : public Beta
{
public:
	Gamma()
	{
		this->priori(this);
	};
};

class Delta : public Gamma
{
public:
	Delta()
	{
		this->priori(this);
	};
};

class Epsilon : public Delta
{
public:
	Epsilon()
	{
		this->priori(this);
	};
};

class Zeta : public Epsilon
{
public:
	Zeta()
	{
		this->priori(this);
	};
};

class Eta : public Zeta
{
public:
	Eta()
	{
		this->priori(this);
	};
};

class Theta : public Eta
{
public:
	Theta()
	{
		this->priori(this);
	};
};

/// Test the old fashioned dynamic_cast
TEST(priori, dynamicCast)
{
	Alpha a;
	Beta b;
	Beta2 c;
	Alpha* aPrime = &b;

	// Ensure both a and b derrive from priori::Base
	EXPECT_TRUE(dynamic_cast<priori::Base*>(&a) != nullptr);
	EXPECT_TRUE(dynamic_cast<priori::Base*>(&b) != nullptr);

	EXPECT_TRUE(dynamic_cast<priori::Base*>(&b) != nullptr);
	EXPECT_TRUE(dynamic_cast<Alpha*>(&b) != nullptr);

	EXPECT_TRUE(dynamic_cast<priori::Base*>(aPrime) != nullptr);
	EXPECT_TRUE(dynamic_cast<Alpha*>(aPrime) != nullptr);
	EXPECT_TRUE(dynamic_cast<Beta*>(aPrime) != nullptr);

	EXPECT_TRUE(dynamic_cast<priori::Base*>(&c) != nullptr);
	EXPECT_TRUE(dynamic_cast<Alpha*>(&c) != nullptr);
	EXPECT_TRUE(dynamic_cast<Beta*>(&c) == nullptr);
	EXPECT_TRUE(dynamic_cast<Beta2*>(&c) != nullptr);
}

/// Test the quick/dirty priori_cast
TEST(priori, prioriCast)
{
	priori::Base x;
	Alpha a;
	Beta b;
	Beta2 c;
	Alpha* aPrime = &b;

	// Ensure both a and b derrive from priori::Base
	EXPECT_TRUE(priori_cast<priori::Base*>(&a) != nullptr);
	EXPECT_TRUE(priori_cast<priori::Base*>(&b) != nullptr);

	EXPECT_TRUE(priori_cast<priori::Base*>(&b) != nullptr);
	EXPECT_TRUE(priori_cast<Alpha*>(&b) != nullptr);

	EXPECT_TRUE(priori_cast<priori::Base*>(aPrime) != nullptr);
	EXPECT_TRUE(priori_cast<Alpha*>(aPrime) != nullptr);
	EXPECT_TRUE(priori_cast<Beta*>(aPrime) != nullptr);

	EXPECT_TRUE(priori_cast<priori::Base*>(&c) != nullptr);
	EXPECT_TRUE(priori_cast<Alpha*>(&c) != nullptr);
	EXPECT_TRUE(priori_cast<Beta*>(&c) == nullptr);
	EXPECT_TRUE(priori_cast<Beta2*>(&c) != nullptr);
}