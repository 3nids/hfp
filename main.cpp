#include <QApplication>

#include "app/hlpflightplannerapp.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  HlpFlightPlannerApp w;
  w.show();

  return a.exec();
}
