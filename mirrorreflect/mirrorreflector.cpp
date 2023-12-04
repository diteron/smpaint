#include "stdafx.h"
#include "mirrorreflector.h"

void MirrorReflector::setupUi() {
    mirrorButton = new QPushButton("Mirror image");
    mirrorButton->setMaximumSize(QSize(100, 16777215));
    mirrorButton->connect(mirrorButton, &QPushButton::clicked,
                          this, &MirrorReflector::handleMirrorButtonClick);
}

void MirrorReflector::mousePress() {
    Shape* currentShape = mainWidgetInstance->getCurrentShape();
    if (currentShape->getName() != "Line") {
        QApplication::beep();
        QMessageBox::information(0, "Hint", "You should draw the line");
        mainWidgetInstance->setCurrentPlugin(nullptr);
        reflectedShape = nullptr;
        return;
    }
    calculateMirrorImage(currentShape);
    mainWidgetInstance->setCurrentPlugin(nullptr);
}

void MirrorReflector::calculateMirrorImage(Shape* mirror) {
    float coeffA, coeffB, coeffC;
    QVector<Point> mirrorPoints = mirror->getPoints();
    if (mirrorPoints[0].x() != mirrorPoints[1].x()) {
        coeffA = findCoefficientA(mirrorPoints[0], mirrorPoints[1]);
        coeffB = -1.0;
        coeffC = findCoefficientC(mirrorPoints[0], mirrorPoints[1]);
    }
    else {
        coeffA = 1.0;
        coeffB = 0.0;
        coeffC = -(mirror->getCenter().x());
    }
    
    QVector<Point> reflectedShapePoints = reflectedShape->getPoints();
    QVector<Point> combinedPoints = reflectedShapePoints;
    for (const Point& point : reflectedShapePoints) {
        Point mirroredPoint = reflectPoint(point, coeffA, coeffB, coeffC);
        combinedPoints.append(mirroredPoint);
    }
    combinedPoints.last().setAsEndPoint();
    reflectedShape->setPoints(combinedPoints);
    reflectedShape->setCenter(mirror->getCenter());
}

float MirrorReflector::findCoefficientA(const Point& point1, const Point& point2) {
    return static_cast<float>(point2.y() - point1.y()) 
         / static_cast<float>(point2.x() - point1.x());
}

float MirrorReflector::findCoefficientC(const Point& point1, const Point& point2) {
    return static_cast<float>(point2.x() * point1.y() - point1.x() * point2.y()) 
                    / static_cast<float>(point2.x() - point1.x());
}

Point MirrorReflector::reflectPoint(const Point& point, float a, float b, float c) {
    float temp = -2 * (a * point.x() + b * point.y() + c) / (a * a + b * b);
    float x = temp * a + point.x();
    float y = temp * b + point.y();
    Point mirroredPoint(static_cast<int>(round(x)), static_cast<int>(round(y)));
    return mirroredPoint;
}

void MirrorReflector::handleMirrorButtonClick() {
    reflectedShape = mainWidgetInstance->getCurrentShape();
    if (!reflectedShape->isDrawn()) {
        QApplication::beep();
        QMessageBox::information(0, QApplication::applicationName(), "Select the drawn shape");
        mainWidgetInstance->setCurrentPlugin(nullptr);
        reflectedShape = nullptr;
        return;
    }

    QApplication::beep();
    QMessageBox::information(0, QApplication::applicationName(), "Draw a line to create a mirror image");
    mainWidgetInstance->setCurrentPlugin(this);
}
