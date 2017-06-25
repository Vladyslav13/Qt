#include "pch.h"

#include "MainNotebookWindow.h"

namespace notebook
{

const QString aboutMsg = QObject::tr("Notebook programme version-0.8.\n"
	"Created by Omelchenko V.");

//
// Definition of the MainNotebookWindow class.
//

MainNotebookWindow::MainNotebookWindow(QWidget *parent)
	: QMainWindow{ parent }
	, usersConfig_{ }
	, isNeedToSave_{ false }
{
	notebookWgt_ = new NotebookWidget{ usersConfig_.GetCurrentUserFile() };
	setCentralWidget(notebookWgt_);
	connect(notebookWgt_, &NotebookWidget::DataChanged, [this]()
	{
		isNeedToSave_ = true;
	});
	connect(&usersConfig_, &UserMaintenanceDlg::UserListEmpty, [this]()
	{
		notebookWgt_->Clear();
	});

	resize(notebookWgt_->width(), height());
	SetWindowTitle();
	CreateMenus();
}

QMessageBox::StandardButton MainNotebookWindow::AskForSave()
{
	QString msg = tr("Do you want to save changes?");
	QMessageBox::StandardButton reply = QMessageBox::question(this,
		tr("Closing program."), msg, QMessageBox::Yes | QMessageBox::No |
		QMessageBox::Cancel);

	if (reply == QMessageBox::Yes)
	{
		OnSaveSlot();
	}

	return reply;
}

void MainNotebookWindow::CreateMenus()
{
	// Creating and filling file menu menu.
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

	QAction* changeUserAct = new QAction{ tr("&Change user") };
	fileMenu->addAction(changeUserAct);
	QObject::connect(changeUserAct, &QAction::triggered, this,
		&MainNotebookWindow::OnChangeUserSlot);

	QAction* saveAct = new QAction{ tr("&Save") };
	fileMenu->addAction(saveAct);
	QObject::connect(saveAct, &QAction::triggered, this,
		&MainNotebookWindow::OnSaveSlot);

	fileMenu->addSeparator();

	QAction* exitAct = new QAction{ tr("&Exit") };
	fileMenu->addAction(exitAct);
	QObject::connect(exitAct, &QAction::triggered, this,
		&MainNotebookWindow::close);

	// Creating and filling help menu menu.
	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

	// Shows information about the program.
	QAction* aboutAct = new QAction{ tr("&About") };
	helpMenu->addAction(aboutAct);
	QObject::connect(aboutAct, &QAction::triggered, this,
		&MainNotebookWindow::OnAboutInformSlot);
}

void MainNotebookWindow::closeEvent (QCloseEvent *event)
{
	// If first true, AskForSave dialog called if it canceled, event is ignored.
	if (isNeedToSave_ && AskForSave() == QMessageBox::Cancel)
	{
		event->ignore();
	}
	else
	{
		return;
	}
}

void MainNotebookWindow::OnChangeUserSlot()
{
	// If first true, AskForSave dialog called if it canceled, do nothing.
	if (isNeedToSave_ && AskForSave() == QMessageBox::Cancel)
	{
		return;
	}

	if (QDialog::Accepted == usersConfig_.exec())
	{
		notebookWgt_->Load(usersConfig_.GetCurrentUserFile());
		SetWindowTitle();
		isNeedToSave_ = false;
	}
}

void MainNotebookWindow::OnSaveSlot()
{
	notebookWgt_->Save(usersConfig_.GetCurrentUserFile());
	isNeedToSave_ = false;
}

void MainNotebookWindow::OnAboutInformSlot()
{
	QMessageBox::information(this, "About", aboutMsg);
}

void MainNotebookWindow::SetWindowTitle()
{
	setWindowTitle(tr("Notebook Version-0.8 ") +
		usersConfig_.GetCurrentUserName());
}

} // namespace notebook
