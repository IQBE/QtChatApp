#include "chatdialog.h"

#include <QApplication>
#include <QLocale>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ChatDialog chatDialog;
    chatDialog.show();
    return app.exec();
}
