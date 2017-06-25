#include "pch.h"

#include "Person.h"

namespace notebook
{

//
// Definition of non member functions.
//

bool operator< (const Person& left, const Person& right)
{
	std::string l = left.GetFullName();
	std::string r = right.GetFullName();
	auto lIt = l.begin();
	auto rIt = r.begin();
	std::locale lc;
	// Skipping all equal symbols.
	while (std::tolower(*lIt, lc) == std::tolower(*rIt, lc) && lIt != l.end()
		&& rIt != r.end())
	{
		++lIt;
		++rIt;
	}

	if (lIt == l.end() || rIt == r.end())
	{
		// If end reached, then the largest word is the short one.
		return l.size() > r.size();
	}
	else
	{
		return std::tolower(*lIt, lc) > std::tolower(*rIt, lc);
	}
}

bool operator== (const Person& left, const Person& right)
{
	return !(left < right || right < left);
}

bool operator!= (const Person& left, const Person& right)
{
	return !(left == right);
}

//
// Definition of the Person class,
//

Person::Person()
	: phone_{ boost::make_shared<PhoneParser>() }
{
}

std::string Person::GetFullName() const
{
	std::list<std::string> fullName = { surname_, name_, patronymic_ };

	return boost::algorithm::join_if(fullName, " ", [](const std::string& str)
	{
		return !str.empty();
	});
}

void Person::SetBirthday(const std::string& birthday)
{
	birthday_ = Date{ boost::gregorian::from_simple_string(birthday) };
}

void Person::SetFullName(const std::string& fullName)
{
	std::vector<std::string> res;
	boost::split(res, fullName, boost::is_any_of(" "));

	if ( res.size() > 3 || res.empty())
	{
		BOOST_THROW_EXCEPTION(std::logic_error{ "wrong full name: " + fullName });
	}

	// if res don't storage surname or patronymic, it adds them as empty strings.
	res.resize(3);

	SetName(res[0]);
	SetSurname(res[1]);
	SetPatronymic(res[2]);
}

} // namespace notebook
