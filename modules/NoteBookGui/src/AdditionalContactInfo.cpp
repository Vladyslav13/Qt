#include "pch.h"

#include "AdditionalContactInfo.h"

namespace notebook
{

//
// Definition of the AdditionalContactInfo class.
//

AdditionalContactInfo::AdditionalContactInfo(QWidget *parent)
	: QGroupBox{ parent }
	, address_{ new QTextEdit }
	, birthday_{ new QDateEdit }
	, cancelButton_{ new QPushButton{ tr("Cancel") } }
	, okButton_{ new QPushButton{ tr("Ok") } }
{
	ConfigureView();

	connect(okButton_, &QPushButton::clicked, [this]()
		{
			emit OkButtonClicked();
		});

	connect(cancelButton_, &QPushButton::clicked, [this]()
		{
			emit CancelButtonClicked();
		});

	connect(address_, &QTextEdit::textChanged, this,
		&AdditionalContactInfo::OnChangeAddressSlot);
}

void AdditionalContactInfo::OnChangeAddressSlot()
{
	QFontMetrics fm{ address_->font() };

	if(fm.width(address_->toPlainText()) >= address_->width())
	{
		address_->setFixedSize(200, fm.height() + 10 +
			address_->horizontalScrollBar()->height());
	}
	else
	{
		address_->setFixedSize(200, fm.height() + 10);
	}
}

void AdditionalContactInfo::ConfigureView()
{
	// configuration of text box with address of person.
	QLabel* birthdayLbl = new QLabel{ tr("&Birthday.") };
	birthdayLbl->setBuddy(birthday_);
	birthday_->setFixedSize(200, 25);
	birthday_->setLocale(QLocale::English);
	birthday_->setDisplayFormat(tr("dd-MMM-yyyy"));
	birthday_->setInputMethodHints(Qt::ImhDate);

	// configuration of text box with birthday of person.
	QLabel* addressLbl = new QLabel{ tr("&Address.") };
	addressLbl->setBuddy(address_);
	address_->setFixedSize(200, 25);
	address_->setLineWrapMode(QTextEdit::NoWrap);

	// configuration of button layout.
	QHBoxLayout* buttnLay = new QHBoxLayout;
	buttnLay->addWidget(okButton_, 0, Qt::AlignRight);
	buttnLay->addWidget(cancelButton_, 0, Qt::AlignRight);

	// Configuration main layout of widget.
	QVBoxLayout* vLay = new QVBoxLayout;
	vLay->addStretch(1);
	vLay->addWidget(addressLbl, 0, Qt::AlignLeft);
	vLay->addWidget(address_);
	vLay->addWidget(birthdayLbl, 0, Qt::AlignLeft);
	vLay->addWidget(birthday_);
	vLay->addLayout(buttnLay);
	vLay->setSpacing(10);

	// Configuration of widget.
	setTitle(tr("Extra information"));
	setLayout(vLay);
	setAlignment(Qt::AlignCenter | Qt::AlignBottom);
	setFixedSize(220, 200);
	setEnabled(false);
}

QString AdditionalContactInfo::GetAddress() const
{
	return address_->toPlainText();
}

QString AdditionalContactInfo::GetBirthday(const QString& format) const
{
	return birthday_->date().toString(format);
}

void AdditionalContactInfo::SetAddress(const QVariant& adr)
{
	address_->setText(adr.toString());
}

void AdditionalContactInfo::SetBirthday(const QVariant& brthd)
{
	birthday_->setDate(brthd.toDate());
}

void AdditionalContactInfo::SetEnabled(bool flag)
{
	setEnabled(flag);

	if (!flag)
	{
		address_->clear();
		birthday_->clear();
	}
}

} // namespace notebook
