#include "pch.h"

#include "AddContactDlg.h"
#include "EditMainContactInfoDlg.h"
#include "NotebookWidget.h"

namespace notebook
{

//
// Definition of the NotebookWidget class.
//

NotebookWidget::NotebookWidget(const QFile& filename, QWidget *parent)
	: QWidget{ parent }
	, additionalInfo_{ new AdditionalContactInfo }
	, modelManager_{ filename }
	, mainContactInfo_{ new MainContactInfo{ tr("Main information.") } }
{
	mainContactInfo_->SetModel(modelManager_.GetModel().get());

	QHBoxLayout* mainLay = new QHBoxLayout;
	mainLay->addWidget(mainContactInfo_);
	mainLay->addWidget(additionalInfo_, 0, Qt::AlignRight | Qt::AlignCenter);
	mainLay->setSpacing(30);
	setLayout(mainLay);

	Connect();
}

void NotebookWidget::Clear()
{
	modelManager_.Clear();
}

bool NotebookWidget::ChangeAddress(const QString& adr)
{
	if(adr != modelManager_.GetAddress(selectedInd_))
	{
		return modelManager_.SetAddress(selectedInd_, adr);
	}
	else
	{
		return false;
	}
}

bool NotebookWidget::ChangeBirthday(const QString& date)
{
	if(date != modelManager_.GetBirthday(selectedInd_))
	{
		return modelManager_.SetBirthday(selectedInd_, date);
	}
	else
	{
		return false;
	}
}

void NotebookWidget::Connect()
{
	connect(additionalInfo_, &AdditionalContactInfo::OkButtonClicked, this,
		&NotebookWidget::OnChangeAdditionalInfoSlot);
	connect(additionalInfo_, &AdditionalContactInfo::CancelButtonClicked,
		[this]()
		{
			ClearSelection();
		});
	QObject::connect(mainContactInfo_, &MainContactInfo::ChooseChanged,
		this, &NotebookWidget::OnChooseChangedSlot);
	QObject::connect(mainContactInfo_, &MainContactInfo::AddButtnClicked,
		this, &NotebookWidget::OnAddPersonSlot);
	QObject::connect(mainContactInfo_, &MainContactInfo::DeleteButtnClicked,
		this, &NotebookWidget::OnDeletePersonSlot);
	QObject::connect(mainContactInfo_, &MainContactInfo::EditButtnClicked,
		this, &NotebookWidget::OnEditButtonClickedSlot);
}

void NotebookWidget::ClearSelection()
{
	mainContactInfo_->ClearSelection();
	additionalInfo_->SetEnabled(false);
}

void NotebookWidget::OnAddPersonSlot()
{
	AddContactDlg addDialog;

	if (addDialog.exec())
	{
		try
		{
			QStringList newPer;
			newPer << addDialog.GetAddress();
			newPer << addDialog.GetBirthday();
			newPer << addDialog.GetName();
			newPer << addDialog.GetPatronymic();
			newPer << addDialog.GetPhone();
			newPer << addDialog.GetSurname();
			modelManager_.AddPerson(newPer);
			ClearSelection();
			emit DataChanged();
		}
		catch(const std::logic_error& ex)
		{
			 QMessageBox::information(this, tr("Ooops! Can't add new person."),
				ex.what());
		}
		catch(const std::exception ex)
		{
			QMessageBox::information(this, tr("Ooops! Can't add new person."),
				ex.what());
		}
		catch(...)
		{
			QMessageBox::information(this, tr("Ooops! Can't add new person."),
				tr("Something goes wrong!"));
		}
	}
}

void NotebookWidget::OnChangeAdditionalInfoSlot()
{
	if (!selectedInd_.isValid())
	{
		return;
	}

	try
	{
		bool adrChanged = ChangeAddress(additionalInfo_->GetAddress());
		bool brthChanged = ChangeBirthday(additionalInfo_->GetBirthday());

		if (adrChanged || brthChanged)
		{
			QMessageBox::information(this, tr("Changing person."),
				tr("Changes successfully applied."));
			emit DataChanged();
		}
	}
	catch(const std::runtime_error& ex)
	{
		QMessageBox::warning(this, tr("Changing person."),
			ex.what());
	}
}

void NotebookWidget::OnChooseChangedSlot(const QModelIndex& ind)
{
	if(!ind.isValid())
	{
		return;
	}

	selectedInd_ = ind;
	additionalInfo_->SetEnabled(true);
	additionalInfo_->SetAddress(modelManager_.GetAddress(selectedInd_));
	additionalInfo_->SetBirthday(modelManager_.GetBirthday(selectedInd_));
}

void NotebookWidget::OnDeletePersonSlot()
{
	QString personName = modelManager_.GetName(selectedInd_);
	QString msg = tr("Do you really want to delete person: ") + personName;
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, tr("Deleting a person."), msg,
		QMessageBox::Yes|QMessageBox::No);

	if (reply == QMessageBox::Yes)
	{
		if (modelManager_.DeletePerson(selectedInd_))
		{
			QMessageBox::information(this, tr("Deleting a person"),
				tr("Person was successfully deleted."));
			ClearSelection();
			emit DataChanged();
		}
		else
		{
			QMessageBox::information(this, tr("Deleting a person."),
				tr("Error: can't delete person."));
		}
	}
	else
	{
		return;
	}
}

void NotebookWidget::OnEditButtonClickedSlot()
{
	QString oldName = modelManager_.GetName(selectedInd_);
	QString oldPhone = modelManager_.GetPhone(selectedInd_);
	EditMainContactInfoDlg dlg{ oldName, oldPhone };

	if (dlg.exec())
	{
		try
		{
			auto newName = dlg.GetName();
			auto newPhone = dlg.GetPhone();

			if (newName != oldName)
			{
				modelManager_.SetName(selectedInd_, newName);
			}

			if (newPhone != oldPhone)
			{
				modelManager_.SetPhone(selectedInd_, newPhone);
			}
		}
		catch(const std::runtime_error& ex)
		{
			QMessageBox::warning(this, tr("Changing person."),
				ex.what());
		}

		emit DataChanged();
	}
}

void NotebookWidget::Load(const QFile& filename)
{
	modelManager_.Load(filename);
	ClearSelection();
}

void NotebookWidget::Save(const QFile& filename)
{
	modelManager_.Save(filename);
}

} // namespace notebook
