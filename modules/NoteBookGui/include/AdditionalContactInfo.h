#pragma once

namespace notebook
{

//
// Declaration of the AdditionalContactInfo class.
//

class AdditionalContactInfo : public QGroupBox
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	AdditionalContactInfo(QWidget *parent = Q_NULLPTR);

	//
	// Public methods.
	//
public:
	//! Returns text from address box.
	QString GetAddress() const;
	//! Return date of birthday like a string.
	QString GetBirthday(const QString& format = tr("yyyy-MM-dd")) const;
	//! Sets address.
	void SetAddress(const QVariant& adr);
	//! Sets birthday.
	void SetBirthday(const QVariant& brthd);
	//! Sets widget enable flag.
	void SetEnabled(bool flag);


	//
	// Public slots.
	//
public slots:
	//! Resize box in depends of scroll bar visible.
	void OnChangeAddressSlot();

	//
	// Signals.
	//
signals:
	//! Send signal of cancel button clicked.
	void CancelButtonClicked();
	//! Send signal of ok button clicked.
	void OkButtonClicked();

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
	//! Display address of person.
	QTextEdit* address_;
	//! Display birthday of the person.
	QDateEdit* birthday_;
	//! Reverse user changes.
	QPushButton* cancelButton_;
	//! Ok button.
	QPushButton* okButton_;
};

} // namespace notebook
