/*
 * DistanceCalculator.hpp
 *
 *  Created on: Feb 13, 2016
 *      Author: michel
 */

#ifndef DISTANCECALCULATOR_HPP
#define DISTANCECALCULATOR_HPP

#include "ExceptionHandler.hpp"
#include <math.h>

#include <xmmintrin.h>		/* SSE  */
#include <emmintrin.h>		/* SSE2 */
#include <tmmintrin.h>      /* SSE3 */
#include <stdint.h>

#include <omp.h>


class DistanceCalculator{
		const float bl45[20][20];
	public:


		enum CorrectionType {not_assigned, none, JukesCantor/*DNA*/, Kimura2/*DNA*/, FastTree /*amino*/};
		enum AlphabetType {dna, amino, null};

		DistanceCalculator (std::string** A /*alignment*/, AlphabetType alphType, CorrectionType corrType, int numberOfSequences);
		~DistanceCalculator();

		AlphabetType   alph_type;
		CorrectionType corr_type;

		std::string dna_chars;
		std::string aa_chars;
		int *inv_alph;
		std::string** A;

		int numberOfSequences;
		int lengthOfSequences;

		const bool newCalculation = true;


		double calc (int a, int b);
		double newCalc(int a, int b);
		inline void count128(register __m128i &seq1, register __m128i &seq2, register __m128i &gap1, register __m128i &gap2, register __m128i &tmp, register __m128i &tmp2, register __m128i &tmp3, register __m128i &count_transversions, register __m128i &count_transitions, register __m128i &count_gaps);

		int* getInverseAlphabet (std::string alph, int length);


		void getBits(char* seq, int* size, unsigned int *seqOut, unsigned int *gapOut);

		unsigned int** convertedSequences;
		unsigned int** gapInTheSequences;

		void convertAll();

		__m128i x128;
		__m128i zero;
		__m128i GAPS_COUNT_MASK;

		//left to initialize TODO:
		__m128i DECOMPRESSED_GAPS;
		__m128i COUNTS_MASK;
		__m128i TRANSITIONS_MASK;
		__m128i TRANSVERSIONS_MASK;

};

#endif

