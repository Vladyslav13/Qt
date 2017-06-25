#include "PhoneParser.h"

namespace notebook
{

//
// Definition of the PhoneParser class.
//

std::string PhoneParser::Make(const PhoneType type, const std::string& countryCode,
	const std::string& phoneCode, const std::string& number)
{
	const auto country = '+' + countryCode;
	const auto code = " (" + phoneCode + ") ";

	// Length of regular part of  the number.
	std::size_t pOfN = number.length() / 3;
	// Length of the first part of the number (before first separator).
	std::size_t fPart = pOfN + number.length() % 3;

	return country + code + number.substr(0, fPart) + separators[0] +
		number.substr(fPart, pOfN) + separators[0] +
		number.substr(fPart + pOfN, number.length());
}

PhoneParams PhoneParser::Parse(const PhoneType type, const std::string& nmbr)
{
	std::string number = nmbr;
	number.erase(boost::remove_if(number, boost::is_any_of(separators)),
		number.end());

	if (number.length() == 15)
	{
		const auto start = number.find('(');
		const auto end = number.find(')');
		const auto diff = end - start - 1;
		const auto countryCode = number.substr(1, 3);
		const auto phoneCode = number.substr(start + 1, diff);
		std::string num = number.substr(end + 1, number.size());

		auto isDigits = [](const std::string& str)
		{
			return std::all_of(str.begin(), str.end(), ::isdigit);
		};

		if (isDigits(countryCode) || isDigits(phoneCode) || isDigits(num))
		{
			return std::make_tuple(type, countryCode, phoneCode, num);
		}
	}

	BOOST_THROW_EXCEPTION(std::logic_error{ "Invalid phone number " + number });
}

} // namespace notebook
