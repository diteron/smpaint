#include "stdafx.h"
#include "../mainwidget.h"
#include "menu.h"

SMenuBar::SMenuBar(QWidget* parent, QString objectName, int width) : QMenuBar(parent) {
    setObjectName(objectName);
    setGeometry(QRect(0, 0, width, 22));
    createFileSubmenu();
}

void SMenuBar::handleOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this, nullptr, nullptr, "Simple Paint File (*.smp)");
    QFile file(fileName);
    QDataStream stream(&file);
    file.open(QIODevice::ReadOnly);

    if (file.size() == 0) {
        file.close();
        return;
    }

    QVector<Shape*>& shapesList = MainWidget::instance()->getShapesList();
    if (shapesList.size() > 0) { MainWidget::instance()->removeDrawnShapes(); }

    deserializeShapesList(stream, shapesList);
    file.close();
}

void SMenuBar::handleSaveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, nullptr, "Untitled.smp", "Simple Paint File (*.smp)");
    QFile file(fileName);
    QDataStream stream(&file);
    file.open(QIODevice::WriteOnly);

    QVector<Shape*>& shapesList = MainWidget::instance()->getShapesList();

    if (shapesList.isEmpty()) {
        file.close();
        return;
    }

    serializeShapesList(stream, shapesList);
    file.close();
}

void SMenuBar::createFileSubmenu() {
    addSubmenu(&menuFile, "menuFile", "File");
    addSubmenuAction(menuFile, &openAction, "openAction",
                     this, "Open", "Ctrl+O");
    openAction->connect(openAction, &QAction::triggered,
                        this, &SMenuBar::handleOpenFile);
    addSubmenuAction(menuFile, &saveAction, "saveAction",
                     this, "Save", "Ctrl+S");
    saveAction->connect(saveAction, &QAction::triggered,
                        this, &SMenuBar::handleSaveFile);
}

void SMenuBar::addSubmenu(QMenu** submenu, const QString& submenuName, const QString& title) {
    *submenu = new QMenu(this);
    (*submenu)->setObjectName(submenuName);
    this->addAction((*submenu)->menuAction());
    (*submenu)->setTitle(title);
}

void SMenuBar::addSubmenuAction(QMenu* submenu, QAction** action, const QString& actionName,
                                QWidget* parent, const QString& title, const QString& shortcut) {
    (*action) = new QAction(parent);
    (*action)->setObjectName(actionName);
    submenu->addAction(*action);
    (*action)->setText(title);
    (*action)->setShortcut(QKeySequence(shortcut));
}

void SMenuBar::deserializeShapesList(QDataStream& inputStream, QVector<Shape*>& shapesList) {
    QString shapeName;

    while (!inputStream.atEnd()) {
        // Read shape name and build a corresponding new blank shape
        inputStream >> shapeName;   
        Shape* newShape = ShapeFactory::instance()->buildShape(shapeName);

        if (newShape == nullptr) {
            QApplication::beep();
            QMessageBox::critical(0, "Error", "Incorrect file format!");
            if (shapesList.size() > 0) { MainWidget::instance()->removeDrawnShapes(); }
            return;
        }
        // Write shape data from a file to the new shape
        inputStream >> *newShape;   
        MainWidget::instance()->addNewShape(newShape);
    }

    MainWidget::instance()->updateDrawCanvas();
}

void SMenuBar::serializeShapesList(QDataStream& outputStream, const QVector<Shape*>& shapesList) {
    for (const Shape* shape : shapesList) {
        outputStream << *shape;
    }
}
