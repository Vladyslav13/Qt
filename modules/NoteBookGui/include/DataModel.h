#pragma once

namespace notebook
{

//
// Declaration of DataModel class.
//

class DataModel : public QAbstractTableModel
{
	Q_OBJECT

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	DataModel(const QFile& filename, QObject* parent = 0);

	//
	// Public interface.
	//
public:
	//! Clears data.
	void Clear();
	//! Returns count of columns.
	int columnCount(const QModelIndex&) const override;
	//! Returns data from table cell by index.
	QVariant data(const QModelIndex& index, int role) const override;
	//! Return status flag of table.
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	//! Return header name of list.
	QVariant headerData(int section, Qt::Orientation orientation,
		int role) const override;
	//! Called before new data is added, otherwise the data willn't be displayed.
	void InsertPerson(const Person& pers);
	//! Load data from file.
	void Load(const QFile& filename);
	//! Returns count of rows.
	int rowCount(const QModelIndex&) const override;
	//! Called to remove data.
	bool removePerson(const Notebook::SizeType& position);
	//! OnSaveSlot data of current session.
	void Save(const QFile& filename);
	//! Sets data int table cell by index.
	bool setData(const QModelIndex& index, const QVariant& value,
		int role) override;

	//
	// Private data members.
	//
private:
	//! Stores notebook data.
	Notebook data_;
	//! Stored numbers of columns in table.
	size_t columnsCount_;
};

//
// Inline implementation of the MyTableModel class,
//

inline int DataModel::columnCount(const QModelIndex&) const
{
	return columnsCount_;
}

} // namespace notebook
