#pragma once

#include "AbstractPhoneParser.h"

namespace notebook
{

//! Stores separator for phone number.
const std::string separators = "- ";

using PhoneParserShPtr = boost::shared_ptr<AbstractPhoneParser>;

//
// Declaration of the PhoneParser class.
//

class PhoneParser : public AbstractPhoneParser
{
	//
	// Public interface.
	//
public:
	//! Makes valid phone number.
	std::string Make(const PhoneType type, const std::string& countryCode,
		const std::string& phoneCode, const std::string& number) override;
	//! Splits string on phone parameters.
	PhoneParams Parse(const PhoneType type, const std::string& nmbr) override;
};

} // namespace notebook
