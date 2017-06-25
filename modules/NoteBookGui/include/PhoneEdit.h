#pragma once

namespace notebook
{

//
// Declaration of the PhoneEdit class.
//

class PhoneEdit : public QLineEdit
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	PhoneEdit(QWidget* parent = Q_NULLPTR);
	//! Constructor.
	PhoneEdit(const QString& txt, QWidget* parent = Q_NULLPTR);

	//
	// Private slots.
	//
private slots:
	//! Reacts on editing text.
	void OnTextEditSlot(const QString& text);
};

} // namespace notebook
