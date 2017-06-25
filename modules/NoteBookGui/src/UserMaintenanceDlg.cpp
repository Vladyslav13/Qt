#include "pch.h"

#include "UserMaintenanceDlg.h"

namespace notebook
{

const QString defaultUserName = QObject::tr("Default user");

//
// Definition of the UserMaintenanceDlg class.
//

UserMaintenanceDlg::UserMaintenanceDlg(QWidget *parent, Qt::WindowFlags f)
	: QDialog{ parent, f }
	, configFile_{ tr("Users") }
	, currentUser_{ 0 }
	, usersNames_ { new QComboBox { this } }
{
	if (configFile_.open(QIODevice::ReadOnly) && configFile_.size() != 0)
	{
		QTextStream in(&configFile_);
		QFileInfo fI;
		while (!in.atEnd())
		{
			fI.setFile(in.readLine());
			usersNames_->addItem(fI.fileName());
			usersPaths_ << new QFile{ fI.filePath() };
		}
	}
	else
	{
		usersNames_->addItem(defaultUserName);
		usersPaths_ << new QFile{ defaultUserName };
	}
	configFile_.close();

	Configure();
}

UserMaintenanceDlg::~UserMaintenanceDlg()
{
	if (configFile_.open(QIODevice::WriteOnly))
	{
		usersPaths_.swap(currentUser_, 0);
		QTextStream out(&configFile_);
		for (const auto& val : usersPaths_)
		{
			out << val->fileName() << "\r\n";
		}
	}

	qDeleteAll(usersPaths_);
}

void UserMaintenanceDlg::Configure()
{
	connect(this, &UserMaintenanceDlg::rejected,[this]()
	{
		usersNames_->setCurrentIndex(currentUser_);
	});

	QPushButton* addUser = new QPushButton{ "Add" };
	connect(addUser, &QPushButton::clicked, this,
		&UserMaintenanceDlg::OnAddButtonSlot);

	QPushButton* cancel = new QPushButton{ "Cancel" };
	connect(cancel, &QPushButton::clicked, this, &UserMaintenanceDlg::reject);

	QPushButton* del = new QPushButton{ "Delete" };
	connect(del, &QPushButton::clicked, this,
		&UserMaintenanceDlg::OnDeleteButtonSlot);

	QPushButton* ok = new QPushButton{ "Ok" };
	connect(ok, &QPushButton::clicked, [this]()
	{
		currentUser_ = usersNames_->currentIndex();
		accept();
	});

	QHBoxLayout* buttnLay = new QHBoxLayout;
	buttnLay->addStretch(0);
	buttnLay->addWidget(ok, 0, Qt::AlignCenter);
	buttnLay->addWidget(cancel, 0, Qt::AlignCenter);
	buttnLay->addWidget(addUser, 0, Qt::AlignCenter);
	buttnLay->addWidget(del, 0, Qt::AlignCenter);
	buttnLay->addStretch(0);

	QVBoxLayout* mainLay = new QVBoxLayout;
	mainLay->addWidget(usersNames_, 1, Qt::AlignCenter);
	mainLay->addLayout(buttnLay);

	setLayout(mainLay);
	setFixedSize(280, 100);
	usersNames_->setFixedWidth(width() - mainLay->spacing() * buttnLay->count());
}

QString UserMaintenanceDlg::GetCurrentUserFile() const
{
	if (!usersPaths_.isEmpty())
	{
		return usersPaths_[currentUser_]->fileName();
	}
	else
	{
		BOOST_THROW_EXCEPTION(std::runtime_error{ "User paths list is empty." });
	}
}

QString UserMaintenanceDlg::GetCurrentUserName() const
{
	if (usersNames_->count() != 0)
	{
		usersNames_->setCurrentIndex(currentUser_);

		return usersNames_->currentText();
	}
	else
	{
		BOOST_THROW_EXCEPTION(std::runtime_error{ "User names list is empty." });
	}
}

void UserMaintenanceDlg::OnAddButtonSlot()
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("Adding user"),
		tr("User name:"), QLineEdit::Normal, tr("User name"), &ok);

	if (ok && !text.isEmpty())
	{
		if (usersNames_->findText(text) == -1)
		{
			usersNames_->addItem(text);
			usersPaths_ << new QFile{ text };
		}
		else
		{
			QMessageBox::information(this, tr("Adding user"),
				tr("Such user is already exist."));
		}
	}
}

void UserMaintenanceDlg::OnDeleteButtonSlot()
{
	QString msg = tr("Do you really want do delete "
		"user: \"%1\"?").arg(usersNames_->currentText());
	QMessageBox::StandardButton reply = QMessageBox::question(this,
		tr("Deleting user."), msg, QMessageBox::Yes | QMessageBox::No);

	if (reply == QMessageBox::Yes)
	{
		auto ind = usersNames_->currentIndex();
		if (ind == currentUser_)
		{
			currentUser_ = 0;
		}
		usersPaths_[ind]->remove();
		usersPaths_.removeAt(ind);
		usersNames_->removeItem(ind);

		if (usersPaths_.isEmpty())
		{
			emit UserListEmpty();
			usersNames_->addItem(defaultUserName);
			usersPaths_ << new QFile{ defaultUserName };
		}
	}
}

} // namespace notebook
