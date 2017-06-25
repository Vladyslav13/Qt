#include "pch.h"

#include "Notebook.h"

namespace notebook
{

//
// Definition of the Notebook class.
//

Notebook::Notebook(const bfs::path& file)
{
	if (!file.empty())
	{
		Deserialize(file);
	}
}

Notebook::PersonsList::const_iterator Notebook::AddPerson(const Person& newPer)
{
	for (auto it = Begin(); it != End(); ++it)
	{
		if (**it != newPer)
		{
			if (**it < newPer)
			{
				return data_.insert(it, boost::make_shared<Person>(newPer));
			}
		}
		else
		{
			const auto msg = boost::str(boost::format{ "Duplicate person. The "
				"name \"%1%\" is already exists." } % newPer.GetFullName());
			BOOST_THROW_EXCEPTION(std::logic_error{ msg });
		}
	}

	// Adds new person if we reached end of list.
	return data_.insert(End(), boost::make_shared<Person>(newPer));
}

void Notebook::ChangePrsnAddress(const SizeType prsnInd, std::string adr)
{
	auto prsn = GetPersonIterator(prsnInd);
	(*prsn)->SetAddress(adr);
}

void Notebook::ChangePrsnBirthday(const SizeType prsnInd, std::string brthday)
{
	auto prsn = GetPersonIterator(prsnInd);
	(*prsn)->SetBirthday(brthday);
}

void Notebook::ChangePrsnFullName(const SizeType prsnInd, std::string fullName)
{
	auto prsn = *GetPersonIterator(prsnInd);
	if (fullName != prsn->GetFullName())
	{
		prsn->SetFullName(fullName);
		DeletePerson(prsnInd);
		AddPerson(*prsn);
	}

}

void Notebook::ChangePrsnPhone(const SizeType prsnInd, std::string phone)
{
	auto prsn = GetPersonIterator(prsnInd);
	(*prsn)->SetPhone(phone);
}

void Notebook::DeletePerson(const SizeType index)
{
	data_.erase(GetPersonCIterator(index));
}

void Notebook::Deserialize(const bfs::path& filename)
{
	bfs::ifstream ifs(filename, std::ios::in);

	if (ifs)
	{
		boost::archive::xml_iarchive ia(ifs);
		ia >> boost::serialization::make_nvp("Notebook", data_);
	}
}

Notebook::SizeType Notebook::GetPersonIndex(const Person& per)
{
	SizeType ind = 0;
	for (auto it = CBegin(); it != CEnd(); ++it, ++ind)
	{
		if (!(**it < per) && !(per < **it))
		{
			break;
		}
	}

	return ind;
}

Notebook::PersonsList::const_iterator Notebook::GetPersonCIterator(
	const SizeType index) const
{
	if (Size() < index)
	{
		const auto msg = boost::str(boost::format{ "Out of bound exception. "
			"There is no person with number:\"%1%\"."} % index );
		BOOST_THROW_EXCEPTION( std::logic_error{ msg });
	}

	auto it = CBegin();
	std::advance(it, index);

	return it;
}

Notebook::PersonsList::iterator Notebook::GetPersonIterator(const SizeType index)
{
	if (Size() < index)
	{
		const auto msg = boost::str(boost::format{ "Out of bound exception. "
			"There is no person with number:\"%1%\"."} % index );
		BOOST_THROW_EXCEPTION( std::logic_error{ msg });
	}

	auto it = Begin();
	std::advance(it, index);

	return it;
}

const Person& Notebook::operator[] (const SizeType index) const
{
	return **GetPersonCIterator(index);
}

void Notebook::Serialize(const bfs::path& filename)
{
	bfs::ofstream ofs(filename, std::ios::out);

	if (ofs)
	{
		boost::archive::xml_oarchive oa(ofs);
		oa << boost::serialization::make_nvp("Notebook", data_);
	}
	else
	{
		const auto msg = boost::str(boost::format{ "Can't open file \"%1%\" "
			"for saving changes." } % filename.c_str());
		BOOST_THROW_EXCEPTION( std::runtime_error{ msg });
	}
}

} // namespace notebook
