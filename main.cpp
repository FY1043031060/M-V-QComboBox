#include <QtWidgets>
#include <QtSql>
#include <QTableView>
#include <ASL485AND422.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);





    ASL485AND422 asl422;
    asl422.show();
    asl422.setTable("RS422_1");

    ASL485AND422 asl422Duc;
    asl422Duc.show();
    asl422Duc.setTable("RS422_2");

    return a.exec();
}
