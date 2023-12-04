#include "stdafx.h"
#include "mirrorreflector.h"

void MirrorReflector::setupUi() {
    mirrorButton = new QPushButton("Mirror image");
    mirrorButton->setMaximumSize(QSize(100, 16777215));
    mirrorButton->setMinimumWidth(80);
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
        Point reflectedPoint = reflectPoint(point, coeffA, coeffB, coeffC);
        combinedPoints.append(reflectedPoint);
    }
    combinedPoints.last().setAsEndPoint();
    reflectedShape->setPoints(combinedPoints);
}

float MirrorReflector::findCoefficientA(const Point& point1, const Point& point2) {
    return static_cast<float>(point2.y() - point1.y()) 
         / static_cast<float>(point2.x() - point1.x());
}

float MirrorReflector::findCoefficientC(const Point& point1, const Point& point2) {
    return static_cast<float>(point2.x() * point1.y() - point1.x() * point2.y()) 
                    / static_cast<float>(point2.x() - point1.x());
}

Point MirrorReflector::reflectPoint(const Point& point,
                                    float mirrorCoeffA, float mirrorCoeffB, float mirrorCoeffC) {
    float temp = -2 * (mirrorCoeffA * point.x() + mirrorCoeffB * point.y() + mirrorCoeffC) 
                         / (mirrorCoeffA * mirrorCoeffA + mirrorCoeffB * mirrorCoeffB);
    int mirroredPointX = static_cast<int>(round(temp * mirrorCoeffA + point.x()));
    int mirroredPointY = static_cast<int>(round(temp * mirrorCoeffB + point.y()));
    Point mirroredPoint(mirroredPointX, mirroredPointY);
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
