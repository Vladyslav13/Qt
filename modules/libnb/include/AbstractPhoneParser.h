#pragma once

namespace notebook
{

enum class PhoneType
{
	MOBILE_PHONE,
	HOME_PHONE
};

using PhoneParams = std::tuple<PhoneType, std::string, std::string, std::string>;

//
// Declaration of the AbstractPhoneParser class.
//

class AbstractPhoneParser
{
	//
	// Construction and destruction.
	//
public:
	//! Destructor.
	virtual ~AbstractPhoneParser() noexcept = default;

	//
	// Public interface.
	//
public:
	//! Makes valid phone number.
	virtual std::string Make(const PhoneType type,
		const std::string& countryCode, const std::string& phoneCode,
		const std::string& number) = 0;
	//! Splits string on phone parameters.
	virtual PhoneParams Parse(const PhoneType type, const std::string& number) = 0;
};

} // namespace notebook
