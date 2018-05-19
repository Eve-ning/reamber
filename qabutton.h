//#ifndef QABUTTON_H
//#define QABUTTON_H

//// Reference: https://stackoverflow.com/questions/34445507/change-background-color-of-qwidget-using-animation

//#include <QtWidgets>
//#include <QWidget>

//#include <QtCore/qvariantanimation.h>
//#include <QtCore/qvariant.h>

//class QAButton : public QPushButton
//{

//  Q_OBJECT
//  Q_PROPERTY(QColor bgColor READ bgColor WRITE setBGColor)
//  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

//public:
//    QAButton(QWidget *parent = 0)
//    {
//        Q_UNUSED(parent)
//        setMouseTracking(true);
//    }
//    void setBGColor (QColor bgColor){

//        setStyleSheet(styleSheet().append(
//                      QString("background-color: rgb(%1, %2, %3);")
//                      .arg(bgColor.red())
//                      .arg(bgColor.green())
//                      .arg(bgColor.blue())));

//    }
//    void setTextColor (QColor textColor){

//        setStyleSheet(styleSheet().append(
//                      QString("color: rgb(%1, %2, %3);")
//                      .arg(textColor.red())
//                      .arg(textColor.green())
//                      .arg(textColor.blue())));

//    }
//    QColor bgColor(){
//        return Qt::black;
//    }
//    QColor textColor(){
//        return Qt::black;
//    }


//Q_SIGNALS:
//    void hovered();
//    void unhovered();

//public slots:
//    void animateChecked()
//    {
//        QPropertyAnimation *bgColor = new QPropertyAnimation(this, "bgColor");
//        bgColor->setDuration(500);
//        bgColor->setStartValue(QColor("#444"));
//        bgColor->setEndValue(QColor("#d68a26"));
//        bgColor->start();
//        QPropertyAnimation *textColor = new QPropertyAnimation(this, "textColor");
//        textColor->setDuration(500);
//        textColor->setStartValue(QColor("#FFF"));
//        textColor->setEndValue(QColor("#d68a26"));
//        textColor->start();
//    }

//  void animateUnchecked()
//  {
//      QPropertyAnimation *bgColor = new QPropertyAnimation(this, "bgColor");
//      bgColor->setDuration(500);
//      bgColor->setStartValue(QColor("#d68a26"));
//      bgColor->setEndValue(QColor("#444"));
//      bgColor->start();
//      QPropertyAnimation *textColor = new QPropertyAnimation(this, "textColor");
//      textColor->setDuration(500);
//      textColor->setStartValue(QColor("#d68a26"));
//      textColor->setEndValue(QColor("#FFF"));
//      textColor->start();
//  }

//protected:
//  virtual void leaveEvent( QEvent* e )
//  {
//      Q_EMIT unhovered();
//      QWidget::enterEvent( e );

//  }

//  virtual void enterEvent( QEvent* e )
//  {
//      Q_EMIT hovered();
//      QWidget::enterEvent( e );
//  }




//};

//#endif // QABUTTON_H
