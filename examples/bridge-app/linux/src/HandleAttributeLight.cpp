#include "HandleAttributeLight.h"

Protocols::InteractionModel::Status HandleReadSwitchAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint){
    // ChipLogProgress(DeviceLayer, "HandleReadOnOffAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);
    
    if (attributeId == Switch::Attributes::CurrentPosition::Id && maxReadLength == 1){
        // *buffer = deviceRD.GetOnOffSwitch(endpoint);
    }
    else if(attributeId == Switch::Attributes::NumberOfPositions::Id && maxReadLength == 1){
        *buffer = 2;
    }
    else if (attributeId == OnOff::Attributes::ClusterRevision::Id)
    {
        // *buffer = (uint16_t) ZCL_SWITCH_CLUSTER_REVISION;
    }
    else {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadOnOffAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint)
{
    // ChipLogProgress(DeviceLayer, "HandleReadOnOffAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);

    if ( attributeId == OnOff::Attributes::OnOff::Id && maxReadLength == 1)
    {
        // *buffer = (uint8_t)deviceRD.GetOnOffLight(endpoint);
    }
    else if (attributeId == OnOff::Attributes::ClusterRevision::Id)
    {
        // *buffer = (uint16_t) ZCL_ON_OFF_CLUSTER_REVISION;
    }
    else if (attributeId == OnOff::Attributes::FeatureMap::Id){
        // *buffer = ZCL_ON_OFF_CLUSTER_FEATURE_MAP;
    }
    else if (attributeId == OnOff::Attributes::GeneratedCommandList::Id){

    }
    else if (attributeId == OnOff::Attributes::AcceptedCommandList::Id){

    }
    else if (attributeId == OnOff::Attributes::AttributeList::Id){
        
    }
    else if (attributeId == OnOff::Attributes::EventList::Id){
        
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleWriteOnOffAttribute(chip::AttributeId attributeId, uint8_t * buffer, EndpointId endpoint)
{
    // ChipLogProgress(DeviceLayer, "HandleWriteOnOffAttribute: attrId=%d --- buffer=%d", attributeId, * buffer);

    if (attributeId == OnOff::Attributes::OnOff::Id)
    {
// #if HC_RANGDONG
//         MqttControllOnOff(
//             deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID,
//             (bool) (*buffer)
//         );
//         deviceRD.UpdateOnOffLight(deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID, (bool) (*buffer));
// #endif
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadColorControlAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint)
{
    // ChipLogProgress(DeviceLayer, "HandleReadColorControlAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);

    if(attributeId == ColorControl::Attributes::ColorTemperatureMireds::Id && maxReadLength == 1){
        // *buffer = (uint8_t)deviceRD.GetCctLight(endpoint);
    }
    else if(attributeId == ColorControl::Attributes::ColorTempPhysicalMinMireds::Id){
        *buffer = 0;
    }
    else if(attributeId == ColorControl::Attributes::ColorTempPhysicalMaxMireds::Id){
        *buffer = 255;
    }
    else if(attributeId == ColorControl::Attributes::CurrentHue::Id){
        // *buffer = (uint8_t)deviceRD.GetHueLight(endpoint);
    }
    else if(attributeId == ColorControl::Attributes::CurrentSaturation::Id ){
        // *buffer = (uint8_t)deviceRD.GetSaturationLight(endpoint);
    }
    else if(attributeId == ColorControl::Attributes::ClusterRevision::Id){
        // *buffer = (uint16_t) ZCL_COLOR_CLUSTER_REVISION;
    }
    else if (attributeId == ColorControl::Attributes::GeneratedCommandList::Id){

    }
    else if (attributeId == ColorControl::Attributes::AcceptedCommandList::Id){

    }
    else if (attributeId == ColorControl::Attributes::AttributeList::Id){
        
    }
    else if (attributeId == ColorControl::Attributes::EventList::Id){
        
    }
    else if ((attributeId == ColorControl::Attributes::FeatureMap::Id))
    {
        *buffer = 0;
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleWriteColorControlAttribute(chip::AttributeId attributeId, uint8_t * buffer,EndpointId endpoint)
{
    // ChipLogProgress(DeviceLayer, "HandleWriteControlAttribute: attrId=%d --- buffer=%d", attributeId, * buffer);
    // string deviceID = deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID;
    if (attributeId == ColorControl::Attributes::RemainingTime::Id){

    }
    if (attributeId == ColorControl::Attributes::ColorTemperatureMireds::Id){
// #if HC_RANGDONG
//         MqttControllCct(
//             deviceID,
//             *buffer
//         );
//         deviceRD.UpdateCctLight(deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID, *buffer);
// #endif        
    }
    if (attributeId == ColorControl::Attributes::CurrentHue::Id){
// #if HC_RANGDONG
//         MqttControllHSV(
//             deviceID,
//             *buffer,
//             (uint8_t)deviceRD.GetSaturationLight(endpoint),
//             (uint8_t)deviceRD.GetLightnessLight(endpoint),
//             (uint8_t)deviceRD.GetDimLight(endpoint)
//         );
//         deviceRD.UpdateHueLight(deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID, *buffer);
// #endif       
    }
    if (attributeId == ColorControl::Attributes::CurrentSaturation::Id){
// #if HC_RANGDONG
//         MqttControllHSV(
//             deviceID,
//             (uint8_t)deviceRD.GetHueLight(endpoint),
//             *buffer,
//             (uint8_t)deviceRD.GetLightnessLight(endpoint),
//             (uint8_t)deviceRD.GetDimLight(endpoint)
//         );
//         deviceRD.UpdateSaturationLight(deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID, *buffer);
// #endif
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadLevelControlAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint){
    
    // ChipLogProgress(DeviceLayer, "HandleReadLevelControlAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);

    if( attributeId ==LevelControl::Attributes::CurrentLevel::Id && maxReadLength == 1){
        
        // *buffer = (uint8_t)deviceRD.GetDimLight(endpoint);
    }
    else if(attributeId == LevelControl::Attributes::Options::Id && maxReadLength == 1){

    }
    else if(attributeId == LevelControl::Attributes::MinLevel::Id && maxReadLength == 1){
        *buffer = 0;
    }
    else if(attributeId == LevelControl::Attributes::MaxLevel::Id && maxReadLength == 1){
        *buffer = 100;
    }
    else if(attributeId == LevelControl::Attributes::ClusterRevision::Id){
        // *buffer = (uint16_t) ZCL_DIM_CLUSTER_REVISION;
    }
    else if (attributeId == LevelControl::Attributes::GeneratedCommandList::Id){

    }
    else if (attributeId == LevelControl::Attributes::AcceptedCommandList::Id){

    }
    else if (attributeId == LevelControl::Attributes::AttributeList::Id){
        
    }
    else if (attributeId == LevelControl::Attributes::EventList::Id){
        
    }
    else if ((attributeId == LevelControl::Attributes::FeatureMap::Id))
    {
        *buffer = 0;
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }
    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleWriteLevelControlAttribute(chip::AttributeId attributeId, uint8_t * buffer, EndpointId endpoint){
    
    // ChipLogProgress(DeviceLayer, "HandleWriteLevelControlAttribute: attrId=%d --- buffer=%d", attributeId, * buffer);
    
    if(attributeId == LevelControl::Attributes::CurrentLevel::Id){
// #if HC_RANGDONG
//         MqttControllDim(
//             deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID,
//             *buffer
//         );
//         deviceRD.UpdateDimLight(
//             deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID,
//             (unsigned int)*buffer
//         );
// #endif
    }
    else{
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}
