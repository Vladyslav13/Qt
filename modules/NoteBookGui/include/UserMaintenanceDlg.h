#pragma once

namespace notebook
{

//
// Declaration of the UserMaintenanceDlg class.
//

class UserMaintenanceDlg : public QDialog
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	UserMaintenanceDlg(QWidget* parent = Q_NULLPTR,
		Qt::WindowFlags f = Qt::WindowFlags());
	//! Destructor.
	~UserMaintenanceDlg();

	//
	// Public interface.
	//
public:
	//! Returns path to current user file.
	QString GetCurrentUserFile() const;
	//! Returns current user name.
	QString GetCurrentUserName() const;

	//
	// Private methods.
	//
private:
	//! Configures the dialog view.
	void Configure();

	//
	// Public signals.
	//
signals:
	//! Sends signal when all users was deleted.
	void UserListEmpty();

	//
	// Private slots.
	//
private slots:
	//! Closes window without saving changes.
	void OnAddButtonSlot();
	//! Deletes chosen user.
	void OnDeleteButtonSlot();

	//
	// Private data members.
	//
private:
	//! stores path to config file.
	QFile configFile_;
	//! Stores index of current user.
	int currentUser_;
	//! Stores paths to users files.
	QList<QFile*> usersPaths_;
	//! Stores user names.
	QComboBox* usersNames_;
};

} // namespace notebook
