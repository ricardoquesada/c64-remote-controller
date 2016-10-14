/****************************************************************************
Copyright 2016 Ricardo Quesada
http://github.com/ricardoquesada/unijoysticle

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMdiSubWindow>

#include "dpadwidget.h"
#include "commandowidget.h"
#include "linearform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pixmap(1,1);
    pixmap.fill(QColor(0,0,0,0));
    QIcon icon(pixmap);

    auto dpadWidget = new DpadWidget(this);
    auto subWindowDpad = ui->mdiArea->addSubWindow(dpadWidget, Qt::Widget);
    subWindowDpad->setWindowTitle(tr("D-Pad mode"));
    subWindowDpad->showMaximized();
    subWindowDpad->setWindowIcon(icon);

    auto commandoWidget = new CommandoWidget(this);
    auto subWindow = ui->mdiArea->addSubWindow(commandoWidget, Qt::Widget);
    subWindow->setWindowTitle(tr("Commando mode"));
    subWindow->showMaximized();
    subWindow->setWindowIcon(icon);

    auto linearWidget = new LinearForm(this);
    subWindow = ui->mdiArea->addSubWindow(linearWidget, Qt::Widget);
    subWindow->setWindowTitle(tr("Linear mode"));
    subWindow->showMaximized();
    subWindow->setWindowIcon(icon);

    ui->mdiArea->setActiveSubWindow(subWindowDpad);

    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::onSubWindowActivated);

    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSubWindowActivated(QMdiSubWindow* subwindow)
{
    // subwindow can be nullptr when closing the app
    if (subwindow)
    {
        auto widget = subwindow->widget();
        if (dynamic_cast<CommandoWidget*>(widget)) {
            ui->groupBox_joy->setEnabled(false);
        } else {
            ui->groupBox_joy->setEnabled(true);
        }
    }
}
