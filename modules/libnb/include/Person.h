#pragma once

#include "PhoneNum.h"

namespace notebook
{

//
// Declaration of the Person class.
//

class Person
{
	friend class boost::serialization::access;

	//
	// Type aliases.
	//
public:
	using Date = boost::gregorian::date;

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	Person();

	//
	// Public interface.
	//
public:
	//! Returns address.
	std::string GetAddress() const;
	//! Returns birthday.
	Date GetBirthday() const;
	//! Returns full name of the person.
	std::string GetFullName() const;
	//! Returns name.
	std::string GetName() const;
	//! Returns patronymic.
	std::string GetPatronymic() const;
	//! Returns phone number.
	PhoneNum GetPhone() const;
	//! Returns surname.
	std::string GetSurname() const;
	//! Sets address.
	void SetAddress(const std::string& adr);
	//! Sets birthday.
	void SetBirthday(const std::string& birthday);
	//! Sets full name of person.
	void SetFullName(const std::string& fullName);
	//! Sets name.
	void SetName(const std::string& name);
	//! Sets patronymic.
	void SetPatronymic(const std::string& patronymic);
	//! Sets phone number.
	void SetPhone(const std::string& phoneNum,
		const PhoneType type = PhoneType::MOBILE_PHONE);
	//! Sets surname.
	void SetSurname(const std::string& surname);

	//
	// Private methods.
	//
private:
	//! Serialize data from class.
	template<class Arch>
	void serialize(Arch & ar, const unsigned int);

	//
	// Private data members.
	//
private:
	//! Stores address.
	std::string address_;
	//! Stores birthday date.
	Date birthday_;
	//! Stores name.
	std::string name_;
	//! Stores patronymic name.
	std::string patronymic_;
	//! Stores phone number.
	PhoneNum phone_;
	//! Stores surname.
	std::string surname_;
};

//
// Declaration of non member methods.
//

bool operator< (const Person& left, const Person& right);

bool operator== (const Person& left, const Person& right);

bool operator!= (const Person& left, const Person& right);

//
// Type aliases.
//

using PersonShrPtr = boost::shared_ptr<Person>;

//
// Inline implementation of the Person class.
//

inline std::string Person::GetAddress() const
{
	return address_;
}

inline Person::Date Person::GetBirthday() const
{
	return birthday_;
}

inline std::string Person::GetName() const
{
	return name_;
}

inline std::string Person::GetPatronymic() const
{
	return patronymic_;
}

inline PhoneNum Person::GetPhone() const
{
	return phone_;
}

inline std::string Person::GetSurname() const
{
	return surname_;
}

inline void Person::SetAddress(const std::string& adr)
{
	address_ = adr;
} 

inline void Person::SetName(const std::string& name)
{
	name_ = name;
}

inline void Person::SetPatronymic(const std::string& patronymic)
{
	patronymic_ = patronymic;
}

inline void Person::SetPhone(const std::string& phoneNum, const PhoneType type)
{
	phone_.Set(phoneNum, type);
}

inline void Person::SetSurname(const std::string& surname)
{
	surname_ = surname;
}

template<class Arch>
void Person::serialize(Arch & ar, const unsigned int)
{
	ar & bsrlz::make_nvp("address", address_);
	ar & bsrlz::make_nvp("birthday", birthday_);
	ar & bsrlz::make_nvp("name", name_);
	ar & bsrlz::make_nvp("patronymic", patronymic_);
	ar & bsrlz::make_nvp("phone", phone_);
	ar & bsrlz::make_nvp("surname", surname_);
}

} // namespace notebook
