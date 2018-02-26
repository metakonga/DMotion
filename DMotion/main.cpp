#include "dmotion.h"
#include <QtWidgets/QApplication>
#include <crtdbg.h>

int main(int argc, char *argv[])
{
// 	if (AllocConsole())
// 	{
// 		freopen("CONIN$", "rb", stdin);
// 		freopen("CONOUT$", "wb", stdout);
// 		freopen("CONOUT$", "wb", stderr);
// // 	}
// 	if (AllocConsole())
// 	{
// 		freopen("CONIN$", "rb", stdin);
// 		freopen("CONOUT$", "wb", stdout);
// 		freopen("CONOUT$", "wb", stderr);
// 	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	QApplication a(argc, argv);
	DMotion w;
	w.show();
	return a.exec();
}
