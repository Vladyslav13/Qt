#pragma once

#include "AdditionalContactInfo.h"
#include "DataModel.h"
#include "DataModelManager.h"
#include "MainContactInfo.h"

namespace notebook
{

//
// Declaration of the NotebookWidget class.
//

class NotebookWidget : public QWidget
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	NotebookWidget(const QFile& filename = { tr("") },
		QWidget* parent = Q_NULLPTR);

	//
	// Public interface.
	//
public:
	//! Deletes all data form data model.
	void Clear();
	//! Load data from file.
	void Load(const QFile& filename);
	//! OnSaveSlot data of current session.
	void Save(const QFile& filename);

	//
	// Private methods.
	//
private:
	//! Changes address of person.
	bool ChangeAddress(const QString& adr);
	//! Changes birthday date of person.
	bool ChangeBirthday(const QString& date);
	//! Sets additional information widget unable and clears selection.
	void ClearSelection();
	//! Connect view of name and address of person.
	void Connect();

	//
	// Public slots.
	//
public slots:
	//! Create dialog window for adding person and ads it to model.
	void OnAddPersonSlot();
	//! Synchronize selection of personnel and filing address and birthday boxes.
	void OnChooseChangedSlot(const QModelIndex& ind);
	//! Change data in model.
	void OnChangeAdditionalInfoSlot();
	//! Deletes person from notepad.
	void OnDeletePersonSlot();
	//! Changes main information about person.
	void OnEditButtonClickedSlot();

	//
	// Public signals.
	//
signals:
	//! Sends signal that data was changed.
	void DataChanged();

	//
	// Private data members.
	//
private:
	//! Displays addition information about person.
	AdditionalContactInfo* additionalInfo_;
	//! Stores data model manager.
	DataModelManager modelManager_;
	//! Display address and name of person.
	MainContactInfo* mainContactInfo_;
	//! Stores current selected index.
	QModelIndex selectedInd_;
};

} // namespace notebook
