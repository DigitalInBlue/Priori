#ifndef H_PRIORI_H
#define H_PRIORI_H

// www.helleboreconsulting.com

///
/// \namespace priori
///
/// \author	John Farrier
///
/// \copyright Copyright 2013 John Farrier 
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// 
/// http://www.apache.org/licenses/LICENSE-2.0
/// 
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///

#include <priori/export.h>
#include <string>
#include <cassert>
#include <iostream>

namespace priori
{
	///
	/// \class Base
	///
	/// \author	John Farrier
	///
	/// A base class required to inherit from to use priori_cast<>
	///
	class PRIORI_EXPORT Base
	{
	public:
		///
		/// Default constructor.
		///
		Base();

		///
		/// Copy constructor.
		///
		Base(Base& other);

		///
		/// Move constructor
		///
		Base(Base&& other);

		///
		/// Trivial destructor
		///
		virtual ~Base() throw();

		///
		/// Test to determine if this class can cast to the type passed in.
		///
		/// \param	x	The priorifactor to test for inheritance.
		///
		/// \return	True if this class can cast to the type passed in.
		///
		bool priori(const uint64_t x) const;

	protected:
		///
		/// Convert a Base pointer
		///
		void priori(const Base* const x);

	private:
		/// The secret sauce which stores our type information.
		uint64_t prioriFactor{ 0 };
	};

	PRIORI_EXPORT extern uint64_t get(const priori::Base* const x);
	PRIORI_EXPORT extern uint64_t get(const std::type_info& x);
}

///
/// \brief priori_cast
///
/// Built a template that looks like standard c++ casts (static_cast, const_cast, etc.)
///
template<class T, class V> T priori_cast(V base)
{
	if (base == nullptr)
	{
		return nullptr;
	}

	// If it is convertable to the base class or to itself, return
	if (std::is_convertible<typename std::remove_pointer<V>::type, typename std::remove_pointer<T>::type>::value == true)
	{
		return reinterpret_cast<T>(base);
	}

	const auto factor = priori::get(typeid(typename std::remove_pointer<T>::type));

	if ((factor != 0) && (base->priori(factor) == true))
	{
		return reinterpret_cast<T>(base);
	}

	return nullptr;
}

#endif
