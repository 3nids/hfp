#include "hlpmapmanager.h"
#include "ui_hlpmapmanager.h"

HlpMapManager::HlpMapManager(QWidget *parent) :
  QDockWidget(parent),
  ui(new Ui::HlpMapManager)
{
  ui->setupUi(this);
}

HlpMapManager::~HlpMapManager()
{
  delete ui;
}
