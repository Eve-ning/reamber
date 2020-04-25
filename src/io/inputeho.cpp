#include "include/io/inputeho.h"
#include "object/multiple/hitobjectv.h"

InputEHO::InputEHO(QWidget *parent) : InputHO(parent) {
    setTitle("input");
    setPlaceholderText("Editor Hit Object Input");
}
InputEHO::~InputEHO() {}

HitObjectV InputEHO::read() const {
    return HitObjectV(toPlainText(), HitObject::TYPE::EDITOR, key());
}
