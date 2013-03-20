#ifndef _PRIORI_H_
#define _PRIORI_H_

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
	class Base
	{
		public:
			///
			///
			///
			Base();

			///
			///
			///
			Base(Base& other);

			///
			///
			///
			Base(Base&& other);
			
			///
			///
			///
			virtual ~Base() throw();

			///
			///
			///
			bool priori(const int x) const;

		protected:
			void priori(Base* x);

		private:
			int prioriFactor;
	};

	PRIORI_EXPORT int get(priori::Base* x);
	PRIORI_EXPORT int get(const std::type_info& x);
}

template<class T, class V> T priori_cast(V base) 
{ 
	if(base != nullptr)
	{
		const auto factor = priori::get(typeid(std::remove_pointer<T>::type));

		if((factor != 0) && (base->priori(factor) == true))
		{
			return reinterpret_cast<T>(base);
		}
	}

	return nullptr; 
}

#endif
