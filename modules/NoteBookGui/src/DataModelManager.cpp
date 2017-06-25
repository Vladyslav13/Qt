#include "pch.h"

#include "DataModelManager.h"

namespace notebook
{

//
// Definition of the DataModelManager class.
//

DataModelManager::DataModelManager(const QFile& filename)
	: data_{ new DataModel{ filename } }
{
}

void DataModelManager::AddPerson(const QStringList& personParam)
{
	if (personParam.size() != 6)
	{
		const auto msg = boost::str(boost::format{ "Wrong count of parameters "
			"passed for creating a new person. Needs: %1, passed: %2." } % 6 %
			personParam.size());
		BOOST_THROW_EXCEPTION(std::runtime_error{ msg });
	}

	Person newPer;
	newPer.SetAddress(personParam[0].toStdString());
	newPer.SetBirthday(personParam[1].toStdString());
	newPer.SetName(personParam[2].toStdString());
	newPer.SetPatronymic(personParam[3].toStdString());
	newPer.SetPhone(personParam[4].toStdString());
	newPer.SetSurname(personParam[5].toStdString());
	data_->InsertPerson(newPer);
}

bool DataModelManager::DeletePerson(const QModelIndex& rowInd)
{
	return data_->removePerson(rowInd.row());
}

void DataModelManager::Clear()
{
	data_->Clear();
}

QString DataModelManager::GetAddress(const QModelIndex& rowInd) const
{
	return data_->index(rowInd.row(), 2).data().toString();
}

QString DataModelManager::GetBirthday(const QModelIndex& rowInd) const
{
	return data_->index(rowInd.row(), 3).data().toString();
}

QString DataModelManager::GetName(const QModelIndex& rowInd) const
{
	return data_->index(rowInd.row(), 0).data().toString();
}

QString DataModelManager::GetPhone(const QModelIndex& rowInd) const
{
	return data_->index(rowInd.row(), 1).data().toString();
}

void DataModelManager::Load(const QFile& filename)
{
	Clear();
	data_->Load(filename);
}

void DataModelManager::Save(const QFile& filename)
{
	data_->Save(filename);
}

bool DataModelManager::SetAddress(const QModelIndex& rowInd,
	const QString& newAddress)
{
	auto adrInd = data_->index(rowInd.row(), 2);

	return data_->setData(adrInd, newAddress, Qt::EditRole);
}

bool DataModelManager::SetBirthday(const QModelIndex& rowInd,
	const QString& newBrth)
{
	auto brthdInd = data_->index(rowInd.row(), 3);

	return data_->setData(brthdInd, newBrth, Qt::EditRole);
}

bool DataModelManager::SetName(const QModelIndex& rowInd,
	const QString& newName)
{
	auto nameInd = data_->index(rowInd.row(), 0);

	return data_->setData(nameInd, newName, Qt::EditRole);
}

bool DataModelManager::SetPhone(const QModelIndex& rowInd,
	const QString& newPhone)
{
	auto phoneInd = data_->index(rowInd.row(), 1);

	return data_->setData(phoneInd, newPhone, Qt::EditRole);
}

} // namespace notebook
