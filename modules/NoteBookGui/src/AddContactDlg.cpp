#include "pch.h"

#include "AddContactDlg.h"

namespace notebook
{

//
// Definition of the AddContactDlg class.
//

AddContactDlg::AddContactDlg(QWidget *parent)
	: QDialog{ parent }
	, address_{ new QLineEdit }
	, birthday_{ new QDateEdit }
	, cancelButton_{ new QPushButton{ tr("Cancel") } }
	, name_{ new QLineEdit }
	, okButton_{ new QPushButton{ tr("Ok") } }
	, patronymic_{ new QLineEdit }
	, phone_{ new PhoneEdit }
	, surname_{ new QLineEdit }
{
	ConfigureView();

	connect(okButton_, &QPushButton::clicked, this,
		&AddContactDlg::OnConfirmSlot);
	connect(cancelButton_, &QPushButton::clicked, this, &AddContactDlg::reject);
}

void AddContactDlg::OnConfirmSlot()
{
	if (name_->text().isEmpty() || phone_->text().isEmpty())
	{
		QMessageBox::information(this, tr("Not all boxes are filled."),
			tr("Please fill all boxes that marked with a star."));
	}
	else
	{
		accept();
	}
}

void AddContactDlg::ConfigureView()
{
	address_->setPlaceholderText(tr("Enter an Address."));
	birthday_->setLocale(QLocale::English);
	birthday_->setDisplayFormat(tr("dd-MMM-yyyy"));
	birthday_->setInputMethodHints(Qt::ImhDate);
	name_->setPlaceholderText(tr("*Enter a Name."));
	patronymic_->setPlaceholderText(tr("Enter a Patronymic."));
	phone_->setPlaceholderText(tr("*Enter a Phone."));
	surname_->setPlaceholderText(tr("Enter a Surname."));

	QHBoxLayout* hLay = new QHBoxLayout;
	hLay->addWidget(cancelButton_, 0, Qt::AlignLeft);
	hLay->addWidget(okButton_, 0, Qt::AlignRight);

	QVBoxLayout* vLay = new QVBoxLayout;
	vLay->addWidget(name_);
	vLay->addWidget(phone_);
	vLay->addWidget(surname_);
	vLay->addWidget(patronymic_);
	vLay->addWidget(address_);
	vLay->addWidget(birthday_);
	vLay->addLayout(hLay);

	setWindowTitle(tr("Adding new person."));
	setLayout(vLay);
}

QString AddContactDlg::GetAddress() const
{
	return address_->text();
}

QString AddContactDlg::GetBirthday() const
{
	return birthday_->date().toString(tr("yyyy-MM-dd"));
}

QString AddContactDlg::GetName() const
{
	return name_->text();
}

QString AddContactDlg::GetPatronymic() const
{
	return patronymic_->text();
}

QString AddContactDlg::GetPhone() const
{
	return phone_->text();
}

QString AddContactDlg::GetSurname() const
{
	return surname_->text();
}

} // namespace notebook
