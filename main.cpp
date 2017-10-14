#include <QtWidgets>
#include <QtSql>
#include <QTableView>
#include <ASL485AND422.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);





    ASL485AND422 asl422;
    asl422.show();

    return a.exec();
}
