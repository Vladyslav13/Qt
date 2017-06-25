#pragma once

#include "PhoneEdit.h"

namespace notebook
{

//
// Declaration of the EditMainContactInfoDlg class.
//

class EditMainContactInfoDlg : public QDialog
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	EditMainContactInfoDlg(const QString& name, const QString& phone,
		QWidget *parent = Q_NULLPTR);

	//
	// Public interface.
	//
public:
	//! Return name of person.
	QString GetName() const;
	//! Return phone of person.
	QString GetPhone() const;

	//
	// Public slots.
	//
public slots:
	//! Checks entered data.
	void OnConfirmSlot();

	//
	// Private data members.
	//
private:
	QPushButton* cancelButton_;
	//! Box for entering name of person.
	QLineEdit* name_;
	//! Button to confirm creating of person.
	QPushButton* okButton_;
	//! Box for entering phone of person.
	PhoneEdit* phone_;
};

} // namespace notebook
