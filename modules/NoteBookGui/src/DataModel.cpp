#include "pch.h"

#include "DataModel.h"

namespace notebook
{

//
// Definition of the DataModel class.
//

DataModel::DataModel(const QFile& filename, QObject* parent)
	: QAbstractTableModel{ parent }
	, data_{ filename.fileName().toStdString() }
	, columnsCount_{ 4 }
{
}

void DataModel::Clear()
{
	beginRemoveRows(QModelIndex(), 0, data_.Size());
	data_.Clear();
	endRemoveRows();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant{};
	}

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch(index.column())
		{
		case 0:
			return data_[index.row()].GetFullName().c_str();

		case 1:
			return data_[index.row()].GetPhone().Get().c_str();

		case 2:
			return data_[index.row()].GetAddress().c_str();

		case 3:
			return boost::gregorian::to_iso_extended_string(
				data_[index.row()].GetBirthday()).c_str();

		default:
			return QVariant{};
		}
	}
	else
	{
		return QVariant{};
	}
}

Qt::ItemFlags DataModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);

	return flags;
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation,
	int role) const
{
	if (role != Qt::DisplayRole)
	{
		return QVariant{};
	}
	else if (orientation == Qt::Horizontal)
	{
		if (section == 0)
		{
			return  QString{ tr("Name") };
		}
		else if (section == 1)
		{
			return QString{ tr("Telephone") };
		}
	}

	return QString::number(section);
}

void DataModel::InsertPerson(const Person& pers)
{
		beginInsertRows(QModelIndex(), 0, 0);
		data_.AddPerson(pers);
		endInsertRows();
}

void DataModel::Load(const QFile& filename)
{
	data_.Deserialize(filename.fileName().toStdString());
	beginInsertRows(QModelIndex(), 0, data_.Size());
	endInsertRows();
}

bool DataModel::removePerson(const Notebook::SizeType& position)
{
	if (position > data_.Size())
	{
		return false;
	}
	else
	{
		beginRemoveRows(QModelIndex(), position, position);
		data_.DeletePerson(position);
		endRemoveRows();
		return true;
	}
}

int DataModel::rowCount(const QModelIndex&) const
{
	return data_.Size();
}

void DataModel::Save(const QFile& filename)
{
	data_.Serialize(filename.fileName().toStdString());
}

bool DataModel::setData(const QModelIndex& index, const QVariant& value,
int role)
{
	if (index.isValid() && role == Qt::EditRole)
	{
		QStringList fullName;
		switch(index.column())
		{
		case 0:
			data_.ChangePrsnFullName(index.row(), value.toString().toStdString());

			return true;
		case 1:
			data_.ChangePrsnPhone(index.row(), value.toString().toStdString());

			return true;
		case 2:
			data_.ChangePrsnAddress(index.row(), value.toString().toStdString());

			return true;
		case 3:
			data_.ChangePrsnBirthday(index.row(), value.toString().toStdString());

			return true;
		default:

			return false;
		}
	}
	else
	{
		const auto msg = tr("Can't change data!").toStdString();
		BOOST_THROW_EXCEPTION(std::runtime_error{ msg });
	}
}

} // namespace notebook
