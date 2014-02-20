#ifndef HLPMAPMANAGER_H
#define HLPMAPMANAGER_H

#include <QDockWidget>

namespace Ui {
  class HlpMapManager;
  }

class HlpMapManager : public QDockWidget
{
  Q_OBJECT

  public:
    explicit HlpMapManager(QWidget *parent = 0);
    ~HlpMapManager();

  public slots:
    void addMap();

  private:
    Ui::HlpMapManager *ui;
};

#endif // HLPMAPMANAGER_H
