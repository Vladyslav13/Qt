#include "pch.h"

#include "EditMainContactInfoDlg.h"

namespace notebook
{

//
// Definition of the EditMainContactInfoDlg class.
//

EditMainContactInfoDlg::EditMainContactInfoDlg(const QString& name,
	const QString& phone, QWidget *parent)
	: QDialog{ parent }
	, cancelButton_{ new QPushButton{ tr("Cancel") } }
	, name_{ new QLineEdit{ name } }
	, okButton_{ new QPushButton{ tr("Ok") } }
	, phone_{ new PhoneEdit{ phone } }
{
	name_->setPlaceholderText(tr("*Enter a Name."));
	phone_->setPlaceholderText(tr("*Enter phone"));

	QHBoxLayout* hLay = new QHBoxLayout;
	hLay->addWidget(cancelButton_, 0, Qt::AlignLeft);
	hLay->addWidget(okButton_, 0, Qt::AlignRight);

	QVBoxLayout* vLay = new QVBoxLayout;
	vLay->addWidget(new QLabel{ tr("Name") }, 0, Qt::AlignLeft);
	vLay->addWidget(name_);
	vLay->addWidget(new QLabel{ tr("Phone") }, 0, Qt::AlignLeft);
	vLay->addWidget(phone_);
	vLay->addLayout(hLay);
	setWindowTitle(tr("Editing person"));
	setLayout(vLay);

	connect(okButton_, &QPushButton::clicked, this,
		&EditMainContactInfoDlg::OnConfirmSlot);
	connect(cancelButton_, &QPushButton::clicked, this,
		&EditMainContactInfoDlg::reject);
}

QString EditMainContactInfoDlg::GetName() const
{
	return name_->text();
}

QString EditMainContactInfoDlg::GetPhone() const
{
	return phone_->text();
}

void EditMainContactInfoDlg::OnConfirmSlot()
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

} // namespace notebook
