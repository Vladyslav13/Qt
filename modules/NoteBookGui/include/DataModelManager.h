#pragma once

#include "DataModel.h"

namespace notebook
{

//
// Definition of DataModelManager.
//

class DataModelManager
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	DataModelManager(const QFile& filename);

	//
	// Public interface.
	//
public:
	//! Adds new person.
	void AddPerson(const QStringList& personParam);
	//! Deletes all data form data model.
	void Clear();
	//! Deletes person, returns true if deleting succeed.
	bool DeletePerson(const QModelIndex& rowInd);
	//! Returns address of the person by index.
	QString GetAddress(const QModelIndex& rowInd) const;
	//! Returns birthday of the person by index.
	QString GetBirthday(const QModelIndex& rowInd) const;
	//! Returns name of the person by index.
	QString GetName(const QModelIndex& rowInd) const;
	//! Returns phone of the person by index.
	QString GetPhone(const QModelIndex& rowInd) const;
	//! Returns pointer on data model.
	std::shared_ptr<DataModel> GetModel();
	//! Load data from file.
	void Load(const QFile& filename);
	//! OnSaveSlot data of current session.
	void Save(const QFile& filename);
	//! Changes address of person, returns true if changing succeed.
	bool SetAddress(const QModelIndex& rowInd, const QString& newBrth);
	//! Changes birthday date of person, returns true if changing succeed.
	bool SetBirthday(const QModelIndex& rowInd, const QString& newBrth);
	//! Changes name date of person, returns true if changing succeed.
	bool SetName(const QModelIndex& rowInd, const QString& newName);
	//! Changes phone date of person, returns true if changing succeed.
	bool SetPhone(const QModelIndex& rowInd, const QString& newPhone);

	//
	// Private data members.
	//
private:
	//! Stores notebook data model.
	std::shared_ptr<DataModel> data_;
};

//
// Inline implementation.
//

inline std::shared_ptr<DataModel> DataModelManager::GetModel()
{
	return data_;
}

} // namespace notebook
