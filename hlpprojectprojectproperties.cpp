#include "hlpprojectprojectproperties.h"
#include "ui_hlpprojectprojectproperties.h"

HlpProjectProjectProperties::HlpProjectProjectProperties(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::HlpProjectProjectProperties)
{
  ui->setupUi(this);
}

HlpProjectProjectProperties::~HlpProjectProjectProperties()
{
  delete ui;
}
