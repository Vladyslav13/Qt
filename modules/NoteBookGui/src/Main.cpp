#include "pch.h"

#include "MainNotebookWindow.h"

int main(int a, char** v)
{
	QApplication app{ a, v };
	notebook::MainNotebookWindow nbw;
	nbw.show();
	return app.exec();
}
