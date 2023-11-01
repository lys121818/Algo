#pragma once

#include <iostream>

typedef unsigned int uint_32;

namespace FNV
{
	// Most used default values for Prime and hash
	static constexpr uint_32 s_kPrime = 0x01000193;
	static constexpr uint_32 s_kSeed = 0x811C9DC5;


	// Hashing Single Bite (8 bit)
	uint_32 Fnv_1a(unsigned char singleBite, uint_32 hash = s_kSeed)
	{
		return (singleBite ^ hash) * s_kPrime;
	}

	// Hashing Double Bites (16 bit)
	uint_32 Fnv_1a(unsigned short doubleBites, uint_32 hash = s_kSeed)
	{

		const unsigned char* ptr = (const unsigned char*)&doubleBites;

		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr, hash);

		return hash;

	}

	// Hashing Four Bites (32 bit)
	uint_32 Fnv_1a(uint_32 fourBites, uint_32 hash = s_kSeed)
	{

		const unsigned char* ptr = (const unsigned char*)&fourBites;

		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr, hash);

		return hash;
	}

	// Hashing Multiple Bites
	uint_32 Fnv_1a(const void* multiBites, size_t sizeOfBites, uint_32 hash = s_kSeed)
	{
		if (sizeOfBites <= 0)
			return hash;

		const unsigned char* ptr = (const unsigned char*)&multiBites;

		Fnv_1a(++ptr, --sizeOfBites, hash);

		return Fnv_1a(*ptr, hash);

	}


	/// Hashing a string
	uint32_t Fnv_1a(const char* text, uint32_t hash = s_kSeed)
	{
		assert(text);
		const unsigned char* ptr = (const unsigned char*)text;
		while (*ptr)
			hash = (*ptr++ ^ hash) * s_kPrime;
		// same as hash = fnv1a(*ptr++, hash); but much faster in debug mode
		return hash;
	}

}