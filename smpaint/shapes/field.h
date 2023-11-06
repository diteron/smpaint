#pragma once

class Field {
public:
    Field(const char* labelText, int defaultValue, int maxValue)
        : _labelText(labelText), _defaultValue(defaultValue), _maxValue(maxValue) {};
    const char* getLabelText() { return _labelText; };
    int getDefaultValue() { return _defaultValue; };
    int getMaxValue() { return _maxValue; };
    
private:
    const char* _labelText;
    int _defaultValue;
    int _maxValue;
};
