#pragma once

#include "NotebookWidget.h"
#include "UserMaintenanceDlg.h"

namespace notebook
{

//
// Definition of MainNotebookWindow class.
//

class MainNotebookWindow : public QMainWindow
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	MainNotebookWindow(QWidget *parent = Q_NULLPTR);

	//
	// Private slots.
	//
private slots:
	//! Perform exiting from application.
	void closeEvent (QCloseEvent* event) override;
	//! OmOpenSlot file dialog for saving data.
	void OnChangeUserSlot();
	//! Saves data.
	void OnSaveSlot();
	//! Shows about dialog.
	void OnAboutInformSlot();

	//
	// Private members.
	//
private:
	//! Asks if user want save data and save it.
	QMessageBox::StandardButton AskForSave();
	//! Creates menus.
	void CreateMenus();
	//! Sets window title with current file name.
	void SetWindowTitle();

	//
	// Private data members.
	//
private:
	//! Stores main widget with all person information.
	NotebookWidget* notebookWgt_;
	//! Stores user and manages users.
	UserMaintenanceDlg usersConfig_;
	//! True if data was changed.
	bool isNeedToSave_;
};

} // namespace notebook
