#pragma once

#include "DataModel.h"

namespace notebook
{

//
// Declaration of MainContactInfo class.
//

class MainContactInfo : public QGroupBox
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Construction.
	MainContactInfo(const QString& title, QWidget *parent = Q_NULLPTR);

	//
	// Public interface.
	//
public:
	//! Sets model for view.
	void SetModel(QAbstractItemModel* model);
	//! Selects row.
	void ClearSelection();

	//
	// Signals.
	//
signals:
	//! Sends when user clicked add person button.
	void AddButtnClicked();
	//! Sends when user clicked delete person button.
	void DeleteButtnClicked();
	//! Sends when user clicked change person button.
	void EditButtnClicked();
	//! Sends when user change row.
	void ChooseChanged(const QModelIndex& ind);

	//
	// Private methods.
	//
private:
	//! Configures view widget.
	void Configure();
	//! Makes all connections.
	void Connect();

	//
	// Private data members.
	//
private:
	//! Button for adding person.
	QPushButton* addButtn_;
	//! Button for deleting person.
	QPushButton* deleteButton_;
	//! Button for editing main information about person.
	QPushButton* editButton_;
	//! Display address and name of person.
	QTableView* mainContactInfo_;
};

} // namespace notebook
