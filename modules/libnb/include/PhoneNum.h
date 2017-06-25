#pragma once

#include "PhoneParser.h"

namespace notebook
{

//
// Declaration of the PhoneNum class.
//

class PhoneNum
{
	friend class boost::serialization::access;

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	PhoneNum() = default;
	//! Constructor.
	explicit PhoneNum(PhoneParserShPtr parser);

	//
	// Public interface.
	//
public:
	//! Returns phone number.
	std::string Get() const;
	//! Sets phone number.
	void Set(const std::string& number, const PhoneType type);

	//
	// Private methods.
	//
private:
	//! Serialize data from class.
	template<class Archive>
	void serialize(Archive & ar, const unsigned int);

	//
	// Private data members.
	//
private:
	//! Parser to fork with phone numbers.
	PhoneParserShPtr parser_;
	//! Type of phone number.
	PhoneType type_;
	//! Code of country.
	std::string countryCode_;
	//! Code of operator if it's mobile phone and city code if it's home phone.
	std::string phoneCode_;
	//! Number of phone.
	std::string number_;
};

template<class Archive>
inline void PhoneNum::serialize(Archive & ar, const unsigned int)
{
	ar & bsrlz::make_nvp("phone_type", type_);
	ar & bsrlz::make_nvp("country_code", countryCode_);
	ar & bsrlz::make_nvp("phone_code", phoneCode_);
	ar & bsrlz::make_nvp("number", number_);
}

} // namespace notebook
