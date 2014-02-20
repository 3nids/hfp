#include "hlpflightplannerapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  HlpFlightPlannerApp w;
  w.show();

  return a.exec();
}
