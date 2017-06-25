#include "PhoneNum.h"

namespace notebook
{

//
// Definition of PhoneNum class.
//

PhoneNum::PhoneNum(PhoneParserShPtr parser)
	: parser_{ parser }
{
}

std::string PhoneNum::Get() const
{
	return parser_->Make(type_, countryCode_, phoneCode_, number_);
}

void PhoneNum::Set(const std::string& number, const PhoneType type)
{
	auto params = parser_->Parse(type, number);
	std::tie(type_, countryCode_, phoneCode_, number_) = params;
}

} // namespace notebook
