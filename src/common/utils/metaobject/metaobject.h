/*! \file	metaobject.h
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

namespace MetaObject_impl
{
	class MetaObjectImpl;
}

//! Basic data modeling facilities.
class MetaObject
{
public:
	//! Retrieve the value of a field from the object.
	/*! If there's no such field, return the symbol 0 (for "").
		\param 	fieldName		The name of the field.
		\sa		setField
	*/
	lc_value getField(const lc_symbol fieldName);

	//! Update the value of a field from the object.
	/*! The return value is the old value in that field. 
		If such field has no value yet, the return value such be the symbol 0(for "").
		\param	fieldName		The name of the field.
		\param	newValue		The value to be written.
	*/
	lc_value setField(const lc_symbol fieldName, lc_value newValue);
	
private:
	//! Class Implementation
	/*! \internal
	*/
	MetaObject_impl::SymbolTableImpl* impl;
};

}
}

}