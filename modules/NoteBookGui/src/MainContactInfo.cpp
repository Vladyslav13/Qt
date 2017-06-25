#include "pch.h"

#include "MainContactInfo.h"

namespace notebook
{

//
// Definition of MainContactInfo class.
//

MainContactInfo::MainContactInfo(const QString& title, QWidget *parent)
	: QGroupBox{ title, parent }
	, addButtn_{ new QPushButton{ tr("&Add") } }
	, deleteButton_{ new QPushButton{ tr("&Delete") } }
	, editButton_{ new QPushButton{ tr("&Edit") } }
	, mainContactInfo_{ new QTableView }
{
	Configure();
	Connect();
}

void MainContactInfo::Configure()
{
	mainContactInfo_->verticalHeader()->setHidden(true);
	mainContactInfo_->setShowGrid(false);
	mainContactInfo_->setSelectionBehavior( QAbstractItemView::SelectRows);
	mainContactInfo_->setSelectionMode(QAbstractItemView::SingleSelection);
	mainContactInfo_->verticalHeader()->setSectionResizeMode(
		QHeaderView::ResizeToContents);
	editButton_->setEnabled(false);
	deleteButton_->setEnabled(false);

	QHBoxLayout* buttnLay = new QHBoxLayout;
	buttnLay->addStretch(1);
	buttnLay->addWidget(deleteButton_, 0, Qt::AlignRight);
	buttnLay->addWidget(editButton_, 0, Qt::AlignRight);
	buttnLay->addWidget(addButtn_, 0, Qt::AlignRight);

	QVBoxLayout* mainInformLay = new QVBoxLayout;
	mainInformLay->addWidget(mainContactInfo_);
	mainInformLay->addLayout(buttnLay);

	setLayout(mainInformLay);
	setAlignment(Qt::AlignCenter | Qt::AlignBottom);
}

void MainContactInfo::Connect()
{
	connect(mainContactInfo_, &QTableView::clicked, [this](
		const QModelIndex& ind)
		{
			emit ChooseChanged(ind);
			editButton_->setEnabled(true);
			deleteButton_->setEnabled(true);
		});
	connect(addButtn_, &QPushButton::clicked, [this]()
		{
			emit AddButtnClicked();
		});
	connect(deleteButton_, &QPushButton::clicked, [this]()
		{
			emit DeleteButtnClicked();
		});
	connect(editButton_, &QPushButton::clicked, [this]()
	{
		emit EditButtnClicked();
		emit ChooseChanged(mainContactInfo_->currentIndex());
	});
}

void MainContactInfo::SetModel(QAbstractItemModel* model)
{
	mainContactInfo_->setModel(model);
	mainContactInfo_->horizontalHeader()->setSectionResizeMode(1,
		QHeaderView::Stretch);
	mainContactInfo_->horizontalHeader()->setSectionResizeMode(0,
		QHeaderView::Interactive);
	for (int i = 2; i <= model->columnCount(QModelIndex{}); ++i)
	{
		mainContactInfo_->hideColumn(i);
	}
	mainContactInfo_->selectionModel()->clearSelection();
	mainContactInfo_->resizeColumnsToContents();
	mainContactInfo_->horizontalHeader()->setMinimumSectionSize(150);

	connect(mainContactInfo_->model(), &QAbstractTableModel::rowsRemoved,
	[this](const QModelIndex &parent, int first, int last)
	{
		mainContactInfo_->selectionModel()->clearSelection();
		deleteButton_->setEnabled(false);
		editButton_->setEnabled(false);
	});

	connect(mainContactInfo_->model(), &QAbstractTableModel::rowsInserted,
	[this]()
	{
		mainContactInfo_->resizeColumnsToContents();
	});
}

void MainContactInfo::ClearSelection()
{
	mainContactInfo_->clearSelection();
}

} // namespace notebook
