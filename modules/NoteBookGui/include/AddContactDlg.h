#pragma once

#include "PhoneEdit.h"

namespace notebook
{

//
// Declaration of the AddContactDlg class.
//

class AddContactDlg : public QDialog
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	AddContactDlg(QWidget *parent = Q_NULLPTR);

	//
	// Public interface.
	//
public:
	//! Returns address of person.
	QString GetAddress() const;
	//! Returns birthday of person.
	QString GetBirthday() const;
	//! Returns name of person.
	QString GetName() const;
	//! Returns patronymic of person.
	QString GetPatronymic() const;
	//! Returns phone of person.
	QString GetPhone() const;
	//! Returns surname of person.
	QString GetSurname() const;

	//
	// Public slots.
	//
public slots:
	//! Checks entered data.
	void OnConfirmSlot();

	//
	// Private methods.
	//
private:
	//! Configuration view of widget.
	void ConfigureView();

	//
	// Private data members.
	//
private:
	//! Box for entering the address of person.
	QLineEdit* address_;
	//! Box for entering birthday of person.
	QDateEdit* birthday_;
	//! Button to exit without creating of person.
	QPushButton* cancelButton_;
	//! Box for entering name of person.
	QLineEdit* name_;
	//! Button to confirm creating of person.
	QPushButton* okButton_;
	//! Box for entering patronymic of person.
	QLineEdit* patronymic_;
	//! Box for entering phone of person.
	PhoneEdit* phone_;
	//! Box for entering surname of person.
	QLineEdit* surname_;
};

} // namespace notebook
