#include <QApplication>
#include <QCoreApplication>

#include "app/hlpflightplannerapp.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("3nids");
  QCoreApplication::setOrganizationDomain("https://github.com/3nids/hfp");
  QCoreApplication::setApplicationName("hfp");

  QApplication a(argc, argv);
  HlpFlightPlannerApp w;
  w.show();

  return a.exec();
}
