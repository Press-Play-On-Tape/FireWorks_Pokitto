#pragma once


// Extract individual digits of a uint8_t -------------------------------------

template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint8_t value) {

	for(uint8_t i = 0; i < size; ++i) {
		buffer[i] = value % 10;
		value /= 10;
	}

}

// Extract individual digits of a uint16_t
template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint16_t value) {

	for(uint8_t i = 0; i < size; ++i) {
		buffer[i] = value % 10;
		value /= 10;
	}
  
}

// Extract individual digits of a uint16_t
template< size_t size > void extractDigits(uint8_t (&buffer)[size], uint32_t value) {

	for(uint8_t i = 0; i < size; ++i) {
		buffer[i] = value % 10;
		value /= 10;
	}
  
}


// ----------------------------------------------------------------------------
//  Swap two elements .. 
//
template <typename T> void swap(T& x,T& y) {
	T temp;
	temp = x;
	x = y;
	y = temp;
}


// ----------------------------------------------------------------------------
//  A better absolute as it uses less memory than the standard one .. 
//
template<typename T> T absT(const T & v) {
  
	return (v < 0) ? -v : v;

}


// ----------------------------------------------------------------------------
//  Clamp the value within the range .. 
//
template <typename T> inline T clamp(const T& value, const T& low, const T& high) {

	return (value < low) ? low : (value > high) ? high : value; 

}


// This gets the length of an array at compile time
template< typename T, size_t N > constexpr size_t ArrayLength(T (&)[N]) {

	return N;

}
