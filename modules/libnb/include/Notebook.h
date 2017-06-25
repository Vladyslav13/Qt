#pragma once

#include "Person.h"

namespace notebook
{

//
// Declaration of the Notebook class.
//

class Notebook
{
	//
	// Type aliases.
	//
public:
	using PersonsList = std::list<PersonShrPtr>;
	using SizeType = std::list<PersonShrPtr>::size_type;

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	Notebook(const bfs::path& file);

	//
	// Public interface.
	//
public:
	//! Adds person and return iterator on added person.
	Notebook::PersonsList::const_iterator AddPerson(const Person& newPer);
	//! Returns constant iterator on the begin of persons list.
	PersonsList::const_iterator CBegin() const;
	//! Clears person storage.
	void Clear();
	//! Changes person address.
	void ChangePrsnAddress(const SizeType prsnInd, std::string adr);
	//! Changes person birthday.
	void ChangePrsnBirthday(const SizeType prsnInd, std::string fullName);
	//! Changes person fullname.
	void ChangePrsnFullName(const SizeType prsnInd, std::string fullName);
	//! Changes phone fullname.
	void ChangePrsnPhone(const SizeType prsnInd, std::string phone);
	//! Delete person by index.
	void DeletePerson(const SizeType index);
	//! Deserialize data.
	void Deserialize(const bfs::path& filename);
	//! Returns constant iterator on the end of persons list.
	PersonsList::const_iterator CEnd() const;
	//! Returns index of person.
	SizeType GetPersonIndex(const Person& p);
	//! Returns constant iterator on person.
	PersonsList::const_iterator GetPersonCIterator(const SizeType index) const;
	//! Returns person by index.
	const Person& operator[] (const SizeType index) const;
	//! Serialize data.
	void Serialize(const bfs::path& filename);
	//! Returns count of persons in notebook.
	const SizeType Size() const;

	//
	// Private methods.
	//
private:
	//! Returns iterator on the begin of persons list.
	PersonsList::iterator Begin();
	//! Returns iterator on the end of persons list.
	PersonsList::iterator End();
	//! Returns iterator on person.
	PersonsList::iterator GetPersonIterator(const SizeType index);

	//
	// Private data members.
	//
private:
	//! Stores persons.
	PersonsList data_;
};

//
// Inline implementation of the Notebook class.
//

inline Notebook::PersonsList::iterator Notebook::Begin()
{
	return data_.begin();
}

inline Notebook::PersonsList::const_iterator Notebook::CBegin() const
{
	return data_.cbegin();
}

inline void Notebook::Clear()
{
	data_.clear();
}

inline Notebook::PersonsList::iterator Notebook::End()
{
	return data_.end();
}

inline Notebook::PersonsList::const_iterator Notebook::CEnd() const
{
	return data_.cend();
}

inline const Notebook::PersonsList::size_type Notebook::Size() const
{
	return data_.size();
}

} // namespace notebook
