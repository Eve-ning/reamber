#pragma once
#include <QWidget>
#include <QPlainTextEdit>
#include <QSharedPointer>
#include "object/multiple/hitobjectv.h"
#include "object/multiple/timingpointv.h"
#include "object/multiple/osuobjectv.h"

class QGridLayout;
class QSpinBox;

namespace Ui {
class IO;
}

class IO : public QWidget
{
    Q_OBJECT

public:
    explicit IO(QWidget *parent = nullptr);
    ~IO();

    QString toPlainText() const;
    QPlainTextEdit* textWidget() const;
    QGridLayout* layout() const;

    void setTitle(const QString &title);
    void setPlaceholderText(const QString &placeholder);

    void setPlainText(const QString &s);

    virtual QVector<double> readOffsets(bool makeUnique = true) const;
    QSize sizeHint() const override;
    void addKeyWidget();
    void hideKeyWidget();

    uint key() const;

    static const int KEY_DEFAULT = 4;
    static const int KEY_MIN = 1;
    static const int KEY_MAX = 99;

signals:
    void textChanged(QString);

private slots:
    void on_text_textChanged();

private:
    QSpinBox *keySb;
    Ui::IO *ui;

public:
    QVariant read() const;
    void write(const HitObjectV & o);
    void write(const TimingPointV & o);
};

Q_DECLARE_METATYPE(HitObjectV)
Q_DECLARE_METATYPE(TimingPointV)


