/*! \file	symboltable.h
 *  \author	CrLF0710
 *  \date	2011-04-15
 */

#pragma once

#include "common/universal/lachesis.h"

namespace lachesis
{

namespace common
{

namespace utils
{

namespace SymbolTable_impl
{
	class SymbolTableImpl;
}

//! Basic symbol<->string conversion facilities.
class SymbolTable
{
public:
	//! Retrieve the symbol corresponding to a given UTF-8 string.
	/*! If there's no such symbol, create one.
		This function should return zero from both NULL and ""
		\param	symbol_string 			The string to be converted into a symbol.
		\sa		getStringFromSymbol()	
	*/
	static const lc_symbol getSymbolFromString(lc_byte* symbol_string);

	//! Retrieve the UTF-8 string corresponding to a given symbol.
	/*! If symbol==0, the return value is "".
		Note that for efficiency reasons, the returned string might be the raw data
		in the table and should NEVER be MODIFIED!
		To ensure this, you'd better duplicate it if you need to store it.(Or store the
		lc_symbol value for efficiency).
		\param	symbol					The symbol to be converted into a string.
		\sa		getSymbolFromString()
	*/
	static const lc_byte * getStringFromSymbol(const lc_symbol symbol);
private:
	//! Class Implementation
	/*! \internal
	*/
	static SymbolTable_impl::SymbolTableImpl* impl;
};

}
}
}