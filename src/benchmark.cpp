#include <celero/Celero.h>
#include <priori/priori.h>

CELERO_MAIN;

#define INHERIT_ME(baseClass, newClass) class newClass : public baseClass { public: newClass() : baseClass() { priori(this); } };

using namespace priori;

INHERIT_ME(Base, Wide0);
INHERIT_ME(Wide0, Wide1);
INHERIT_ME(Wide1, Wide2);
INHERIT_ME(Wide2, Wide3);
INHERIT_ME(Wide3, Wide4);
INHERIT_ME(Wide4, Wide5);
INHERIT_ME(Wide5, Wide6);
INHERIT_ME(Wide6, Wide7);
INHERIT_ME(Wide7, Wide8);
INHERIT_ME(Wide8, Wide9);
INHERIT_ME(Wide9, WideFinal);

INHERIT_ME(Base, Deep0);
INHERIT_ME(Deep0, Deep1);
INHERIT_ME(Deep1, Deep2);
INHERIT_ME(Deep2, Deep3);
INHERIT_ME(Deep3, Deep4);
INHERIT_ME(Deep4, Deep5);
INHERIT_ME(Deep5, Deep6);
INHERIT_ME(Deep6, Deep7);
INHERIT_ME(Deep7, Deep8);
INHERIT_ME(Deep8, Deep9);
INHERIT_ME(Deep9, DeepFinal);


class InheritanceFixture : public celero::TestFixture
{
	public:
		InheritanceFixture() : 
			deep(nullptr),
			wide(nullptr)
		{
		}

		/// Before each run, build a vector of random integers.
		virtual void SetUp()
		{
			this->deep = new DeepFinal;
			this->deepBase = this->deep;

			this->wide = new WideFinal;
			this->wideBase = this->wide;
		}

		/// After each run, clear the vector of random integers.
		virtual void TearDown()
		{
			delete this->deep;
			delete this->wide;
		}

		DeepFinal* deep;
		Base* deepBase;

		WideFinal* wide;
		Base* wideBase;
 };

// ----------------------------------------------------------------------------
// Cast from a base to the derrived type.
// ----------------------------------------------------------------------------
BASELINE_F(priori_deep_fromBase, dynamic_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(dynamic_cast<DeepFinal*>(this->deepBase));
}

BENCHMARK_F(priori_deep_fromBase, priori_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(priori_cast<DeepFinal*>(this->deepBase));
}

// ----------------------------------------------------------------------------
// Cast from a base to the derrived type.
// ----------------------------------------------------------------------------
BASELINE_F(priori_wide_fromBase, dynamic_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(dynamic_cast<WideFinal*>(this->wideBase));
}

BENCHMARK_F(priori_wide_fromBase, priori_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(priori_cast<WideFinal*>(this->wideBase));
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the base type.
// ----------------------------------------------------------------------------
BASELINE_F(priori_deep_toBase, dynamic_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(dynamic_cast<Base*>(this->deep));
}

BENCHMARK_F(priori_deep_toBase, priori_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(priori_cast<Base*>(this->deep));
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the base type.
// ----------------------------------------------------------------------------
BASELINE_F(priori_wide_toBase, dynamic_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(dynamic_cast<Base*>(this->wide));
}

BENCHMARK_F(priori_wide_toBase, priori_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(priori_cast<Base*>(this->wide));
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the same derrived type.
// ----------------------------------------------------------------------------
BASELINE_F(priori_deep_toSelf, dynamic_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(dynamic_cast<DeepFinal*>(this->deep));
}

BENCHMARK_F(priori_deep_toSelf, priori_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(priori_cast<DeepFinal*>(this->deep));
}

// ----------------------------------------------------------------------------
// Cast from a derrived type to the same derrived type.
// ----------------------------------------------------------------------------
BASELINE_F(priori_wide_toSelf, dynamic_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(dynamic_cast<WideFinal*>(this->wide));
}

BENCHMARK_F(priori_wide_toSelf, priori_cast, InheritanceFixture, 70, 1000000)
{
	celero::DoNotOptimizeAway(priori_cast<WideFinal*>(this->wide));
}

// ----------------------------------------------------------------------------
// Experiments for rtti operations costs.
// ----------------------------------------------------------------------------
BASELINE(rttiCosts, typeinfo, 70, 1000000)
{
	celero::DoNotOptimizeAway(typeid(WideFinal));
}

BENCHMARK(rttiCosts, typeinfoHash, 70, 1000000)
{
	celero::DoNotOptimizeAway(typeid(WideFinal).hash_code());
}

BENCHMARK(rttiCosts, typeinfoName, 70, 1000000)
{
	celero::DoNotOptimizeAway(typeid(WideFinal).name());
}

