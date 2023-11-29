#pragma once
#include <qmenu.h>
#include "../shapes/shape.h"

class SMenuBar : public QMenuBar {

    Q_OBJECT

public:
    SMenuBar(QWidget* parent, QString objectName, int width);

public slots:
    void handleOpenFile();
    void handleSaveFile();

private:
    void createFileSubmenu();
    void addSubmenu(QMenu** submenu, const QString& submenuName, const QString& title);
    void addSubmenuAction(QMenu* submenu, QAction** action, const QString& actionName,
                          QWidget* parent, const QString& title, const QString& shortcut);
    void deserializeShapesList(QDataStream& inputStream, QVector<Shape*>& shapesList);
    void serializeShapesList(QDataStream& outputStream, const QVector<Shape*>& shapesList);

    QMenu* menuFile = nullptr;
    QAction* openAction = nullptr;
    QAction* saveAction = nullptr;
};
