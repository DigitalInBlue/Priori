#ifndef H_PRIORI_EXPORT_H
#define H_PRIORI_EXPORT_H

// www.helleboreconsulting.com

///
///	\author	John Farrier
///

#ifdef PRIORI_STATIC
	#define PRIORI_EXPORT
	#define	PRIORI_EXPORT_C
#else
	#ifdef WIN32
		#if defined PRIORI_EXPORTS
			#define PRIORI_EXPORT _declspec(dllexport)
			#define PRIORI_EXPORT_C extern "C" _declspec(dllexport)
		#else
			#define PRIORI_EXPORT _declspec(dllimport)
			#define PRIORI_EXPORT_C extern "C" _declspec(dllimport)
		#endif
	#else
		#define PRIORI_EXPORT
		#define PRIORI_EXPORT_C extern "C"
	#endif
#endif

#endif
