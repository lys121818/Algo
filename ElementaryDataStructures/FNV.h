#pragma once

#include <assert.h>
#include <iostream>

typedef unsigned int uint_32;

namespace FNV
{
	// Most used default values for Prime and hash on 32bit
	static constexpr uint_32 s_kPrime = 0x01000193;
	static constexpr uint_32 s_kSeed = 0x811C9DC5;


	// Hashing Single Byte (8 bit)
	uint_32 Fnv_1a(unsigned char singleByte, uint_32 hash = s_kSeed)
	{
		return (singleByte ^ hash) * s_kPrime;
	}

	// Hashing Double Bytes (16 bit)
	uint_32 Fnv_1a(const unsigned short* doubleBytes, uint_32 hash = s_kSeed)
	{

		const unsigned char* ptr = (const unsigned char*)doubleBytes;

		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr, hash);

		return hash;

	}

	// Hashing Four Bytes (32 bit)
	uint_32 Fnv_1a(const uint_32* fourBytes, uint_32 hash = s_kSeed)
	{

		const unsigned char* ptr = (const unsigned char*)fourBytes;

		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr, hash);

		return hash;
	}

	// Hashing Four Bytes (32 bit)
	uint_32 Fnv_1a(const unsigned long* fourBytes, uint_32 hash = s_kSeed)
	{
		const unsigned char* ptr = (const unsigned char*)fourBytes;

		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr, hash);

		return hash;
	}

	// Hashing Multiple Bytes
	uint_32 Fnv_1a(const void* multiBytes, uint_32 hash = s_kSeed)
	{
		// if void is valid value
		assert(multiBytes);

		size_t size = sizeof(multiBytes);

		// runs through every signle byte on hash
		const unsigned char* ptr = (const unsigned char*)multiBytes;

		while (size--)
			hash = Fnv_1a(*ptr++, hash);

		return hash;

	}


	// Hashing Four Bytes (32 bit)
	uint_32 Fnv_1a(float* floatValue, uint_32 hash = s_kSeed)
	{
		size_t size = sizeof(*floatValue);

		const unsigned char* ptr = (const unsigned char*)floatValue;

		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr, hash);


		// Run with Multiple Bytes
		return hash;
	}

	// Hashing Eight Bytes (64 bit)
	uint_32 Fnv_1a(double* doubleValue, uint_32 hash = s_kSeed)
	{
		size_t size = sizeof(*doubleValue);
		const unsigned char* ptr = (const unsigned char*)doubleValue;

		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr++, hash);
		hash = Fnv_1a(*ptr, hash);

		return hash;
	}


	/// Hashing a string
	uint32_t Fnv_1a(const char* text, uint32_t hash = s_kSeed)
	{
		// if the text is valid value
		assert(text);

		// hash from first index of string
		const unsigned char* ptr = (const unsigned char*)text;
		while (*ptr)
			hash = Fnv_1a(*ptr++, hash);

		return hash;
	}

}