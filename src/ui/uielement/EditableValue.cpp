//
// Created by Thijs on 24/06/2023.
//

#include "EditableValue.h"

namespace PG {

template<typename T>
void EditableValue<T>::setValue(const T &value_) {
    value = value_;
    value = std::clamp(value, minValue, maxValue);
}

template<typename T>
void EditableValue<T>::setMinValue(const T &minValue_) {
    minValue = minValue_;
    value = std::clamp(value, minValue, maxValue);
}

template<typename T>
void EditableValue<T>::setMaxValue(const T &maxValue_) {
    maxValue = maxValue_;
    value = std::clamp(value, minValue, maxValue);
}

template<typename T>
const T &EditableValue<T>::getValue() const {
    return value;
}

template<typename T>
const T &EditableValue<T>::getMaxValue() const {
    return maxValue;
}

template<typename T>
const T &EditableValue<T>::getMinValue() const {
    return minValue;
}

template<>
void EditableValue<int>::setValue(const int &value_) {
    value = value_;
    value = std::clamp(value, minValue, maxValue);
}

template<>
void EditableValue<int>::setMinValue(const int &minValue_) {
    minValue = minValue_;
    value = std::clamp(value, minValue, maxValue);
}

template<>
void EditableValue<int>::setMaxValue(const int &maxValue_) {
    maxValue = maxValue_;
    value = std::clamp(value, minValue, maxValue);
}

template<>
const int &EditableValue<int>::getValue() const {
    return value;
}

template<>
const int &EditableValue<int>::getMaxValue() const {
    return maxValue;
}

template<>
const int &EditableValue<int>::getMinValue() const {
    return minValue;
}

} // PG