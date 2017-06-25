#include "pch.h"

#include "PhoneEdit.h"

namespace notebook
{

//
// Definition of the PhoneEdit class.
//

PhoneEdit::PhoneEdit(QWidget* parent)
	: QLineEdit{ parent }
{
	setPlaceholderText(tr("Enter a Phone."));
	setMaxLength(19);

	connect(this, &QLineEdit::textEdited, this, &PhoneEdit::OnTextEditSlot);
}

PhoneEdit::PhoneEdit(const QString& txt, QWidget* parent)
	: PhoneEdit{ parent }
{
	setText(txt);
}

void PhoneEdit::OnTextEditSlot(const QString& text)
{
	const auto len = text.size();
	if (text[len - 1].isDigit())
	{
		if (len == 1 && text != "+")
		{
			setText("+" + text);
		}
		else if (len == 4)
		{
			setText(text + " (");
		}
		else if (len == 8)
		{
			setText(text + ") ");
		}
		else if (len == 13 || len == 16)
		{
			setText(text + '-');
		}
	}
	else
	{
		setText(text.left(len - 1));
	}
}

} // namespace notebook
