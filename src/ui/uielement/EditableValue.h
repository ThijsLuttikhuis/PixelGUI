//
// Created by Thijs on 24/06/2023.
//

#ifndef PIXELGUI_EDITABLEVALUE_H
#define PIXELGUI_EDITABLEVALUE_H

#include <memory>

namespace PG {

template<typename T>
class EditableValue {
private:
    T value;
    T minValue;
    T maxValue; 

public:
    EditableValue() = default;

    EditableValue(const T &value, const T &minValue, const T &maxValue)
          : value(value), minValue(minValue), maxValue(maxValue) {}

    void setValue(const T &value_);

    void setMinValue(const T &minValue_);

    void setMaxValue(const T &maxValue_);

    [[nodiscard]] const T &getMinValue() const;

    [[nodiscard]] const T &getMaxValue() const;

    [[nodiscard]] const T &getValue() const;
};

} // PG

#endif //PIXELGUI_EDITABLEVALUE_H
