#ifndef HLPPROJECTPROJECTPROPERTIES_H
#define HLPPROJECTPROJECTPROPERTIES_H

#include <QDialog>

namespace Ui {
  class HlpProjectProjectProperties;
}

class HlpProjectProjectProperties : public QDialog
{
  Q_OBJECT

public:
  explicit HlpProjectProjectProperties(QWidget *parent = 0);
  ~HlpProjectProjectProperties();

private:
  Ui::HlpProjectProjectProperties *ui;
};

#endif // HLPPROJECTPROJECTPROPERTIES_H
