#include "HandleAttributeSensor.h"


Protocols::InteractionModel::Status HandleReadBooleanStateAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint){
    
    // ChipLogProgress(DeviceLayer, "HandleReadLevelControlAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);

    if( attributeId ==BooleanState::Attributes::StateValue::Id && maxReadLength == 1){
        
        *buffer = (bool)0;
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }
    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadTemperatureMeasurementAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint){
    
    ChipLogProgress(DeviceLayer, "HandleReadTemperatureMeasurementAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);

    if( attributeId ==TemperatureMeasurement::Attributes::MeasuredValue::Id && maxReadLength == 2){
        *buffer = 0;
        *(buffer + 1) = 20;
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }
    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadRelativeHumidityMeasurementAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint){
    
    // ChipLogProgress(DeviceLayer, "HandleReadLevelControlAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);

    if( attributeId ==RelativeHumidityMeasurement::Attributes::MeasuredValue::Id && maxReadLength == 1){
        
        *buffer = 90;
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }
    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadIlluminanceMeasurementAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint){
    
    // ChipLogProgress(DeviceLayer, "HandleReadLevelControlAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);

    if( attributeId ==IlluminanceMeasurement::Attributes::MeasuredValue::Id && maxReadLength == 2){
        
        *buffer = 250;
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }
    return Protocols::InteractionModel::Status::Success;
}
