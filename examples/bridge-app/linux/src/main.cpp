/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <AppMain.h>
#include <platform/CHIPDeviceLayer.h>
#include <platform/PlatformManager.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Events.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/ConcreteAttributePath.h>
#include <app/EventLogging.h>
#include <app/clusters/network-commissioning/network-commissioning.h>
#include <app/reporting/reporting.h>
#include <app/util/af-types.h>
#include <app/util/attribute-storage.h>
#include <app/util/util.h>
#include <credentials/DeviceAttestationCredsProvider.h>
#include <credentials/examples/DeviceAttestationCredsExample.h>
#include <lib/core/CHIPError.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/ZclString.h>
#include <platform/CommissionableDataProvider.h>
#include <setup_payload/QRCodeSetupPayloadGenerator.h>
#include <setup_payload/SetupPayload.h>

#include <pthread.h>
#include <sys/ioctl.h>
#include "CommissionableInit.h"
#include "main.h"
#include <app/server/Server.h>

/*----------------------------------------------------------------
------------------------------- Dev-----------------------------
----------------------------------------------------------------*/


#include <app/clusters/switch-server/switch-server.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/cluster-objects.h>
#include <cassert>
#include <iostream>
#include <vector>
#include "LightSwitchMgr.h"
#include <app/AttributeAccessInterface.h>
#include <app/util/binding-table.h>
#include <cstring>
#include "DeviceRD.h"
#include "Mqtt.h"
#include "OTA.h"
#include "DeviceMatter.h"

using namespace chip;
using namespace chip::app;
using namespace chip::Credentials;
using namespace chip::Inet;
using namespace chip::Transport;
using namespace chip::DeviceLayer;
using namespace chip::app::Clusters;
using namespace MatterDevice;

#define TEST_DEVICE 1
#define HC_RANGDONG 1

#if HC_RANGDONG
    static struct mosquitto *mosq;
    DeviceRD deviceRD;
#endif


// REVISION DEFINITIONS:
// =================================================================================

#define ZCL_DESCRIPTOR_CLUSTER_REVISION (1u)
#define ZCL_IDENTIFY_CLUSTER_REVISION (4u)
#define ZCL_BRIDGED_DEVICE_BASIC_INFORMATION_CLUSTER_REVISION (1u)
#define ZCL_BRIDGED_DEVICE_BASIC_INFORMATION_FEATURE_MAP (0u)
#define ZCL_FIXED_LABEL_CLUSTER_REVISION (1u)

#define ZCL_ON_OFF_CLUSTER_REVISION (4u)
#define ZCL_ON_OFF_CLUSTER_FEATURE_MAP (0u)

#define ZCL_DIM_CLUSTER_REVISION (5u)
#define ZCL_SWITCH_CLUSTER_REVISION (1u)
#define ZCL_BINDING_CLUSTER_REVISION (1u)
#define ZCL_COLOR_CLUSTER_REVISION (5u)
#define ZCL_GROUPS_CLUSTER_REVISION (4u)
#define ZCL_SCENES_CLUSTER_REVISION (4u)
// ---------------------------------------------------------------------------


/*----------------------------------------------------------------
-----------------------------Rand Dong Dev-----------------------------
----------------------------------------------------------------*/

/*
    Add Endpoints to the Bridge
*/
int AddDeviceEndpoint(EmberAfEndpointType * ep, const Span<const EmberAfDeviceType> & deviceTypeList,
                      const Span<DataVersion> & dataVersionStorage, chip::EndpointId parentEndpointId = chip::kInvalidEndpointId, 
                      bool autoFind = true, unsigned int FixEndpoint = 0)
{

    EndpointId endpoint = 0;
    CHIP_ERROR ret;

    if(autoFind == true){
        for(endpoint = 0; endpoint < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT; endpoint++){
            if(emberAfEndpointIndexIsEnabled(endpoint) == false && endpoint >= FIXED_ENDPOINT_COUNT){
                break;
            }
        }
    }
    else{

        endpoint = (EndpointId) FixEndpoint;
    }

    if(endpoint == CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT){
        ChipLogProgress(DeviceLayer, "Failed to add dynamic endpoint %d == %d", endpoint, CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT);
        return 0;
    }

    DeviceLayer::StackLock lock;

    ret = emberAfSetDynamicEndpoint((uint16_t)(endpoint - FIXED_ENDPOINT_COUNT), endpoint, ep, dataVersionStorage, deviceTypeList, parentEndpointId);

    if (ret == CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "Added dynamic endpoint %d --- index = %d", endpoint, (uint16_t)(endpoint - FIXED_ENDPOINT_COUNT));
        return (int)endpoint;
    }
    ChipLogProgress(DeviceLayer, "Failed to add dynamic endpoint %d", ret.AsInteger());
    return -1;
}

/*
    Remove Endpoint from Bridge
*/
int RemoveDeviceEndpoint(EndpointId endpoint)
{
    if(emberAfEndpointIndexIsEnabled(endpoint) == false){
        ChipLogProgress(DeviceLayer, "Removed dynamic endpoint %d failed --- Endpoint is not enable ", endpoint);
    }
    DeviceLayer::StackLock lock;
    ChipLogProgress(DeviceLayer, "Removed dynamic endpoint %d", endpoint);
    emberAfClearDynamicEndpoint((uint16_t)(endpoint - FIXED_ENDPOINT_COUNT));
    return -1;
}

Protocols::InteractionModel::Status HandleReadBridgedDeviceBasicAttribute(chip::AttributeId attributeId, uint8_t * buffer,  uint16_t maxReadLength, EndpointId endpoint){
    using namespace BridgedDeviceBasicInformation::Attributes;

    ChipLogProgress(DeviceLayer, "HandleReadBridgedDeviceBasicAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);
    
    DeviceInformation * device = deviceRD.GetDeviceWithEndpoint(endpoint);

    if ((attributeId == Reachable::Id))
    {
        *buffer = (uint8_t) device->reachable;
    }
    else if ((attributeId == NodeLabel::Id))
    {        
        MutableByteSpan zclNameSpan(buffer, 50);
        MakeZclCharString(zclNameSpan, device->NodeLabel.c_str());      
    }
    else if ((attributeId == VendorName::Id)) {
        memcpy(buffer + 1, device->VendorName.c_str(), sizeof(device->VendorName));
        *buffer = sizeof(device->VendorName);
    }
    else if ((attributeId == VendorID::Id)) {
        memcpy(buffer  +1, &(device->VendorID), sizeof(device->VendorID));
        *buffer = sizeof(device->VendorID);
    }
    else if ((attributeId == ProductName::Id)) {
        memcpy(buffer + 1, device->ProductName.c_str(), sizeof(device->ProductName));
        *buffer = sizeof(device->ProductName);
    }
    else if ((attributeId == SerialNumber::Id)) {
        memcpy(buffer + 1, device->SerialNumber.c_str(), sizeof(device->SerialNumber));
        *buffer = sizeof(device->SerialNumber);    
    }
    else if((attributeId == SoftwareVersionString::Id)){
        memcpy(buffer + 1, device->Version.c_str(), sizeof(device->Version));
        *buffer = sizeof(device->Version); 
    }
    else if((attributeId == HardwareVersionString::Id)){
        memcpy(buffer + 1, device->Version.c_str(), sizeof(device->Version));
        *buffer = sizeof(device->Version); 
    }
    else if ((attributeId == ClusterRevision::Id))
    {
        *buffer = (uint16_t) ZCL_BRIDGED_DEVICE_BASIC_INFORMATION_CLUSTER_REVISION;
    }
    else if ((attributeId == FeatureMap::Id))
    {
        *buffer = (uint32_t) ZCL_BRIDGED_DEVICE_BASIC_INFORMATION_FEATURE_MAP;
    }
    else if (attributeId == BridgedDeviceBasicInformation::Attributes::GeneratedCommandList::Id){

    }
    else if (attributeId == BridgedDeviceBasicInformation::Attributes::AcceptedCommandList::Id){

    }
    else if (attributeId == BridgedDeviceBasicInformation::Attributes::AttributeList::Id){

    }
    else if (attributeId == BridgedDeviceBasicInformation::Attributes::EventList::Id){

    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadSwitchAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength, EndpointId endpoint){
    // ChipLogProgress(DeviceLayer, "HandleReadOnOffAttribute: attrId=%d, maxReadLength=%d", attributeId, maxReadLength);
    
    if (attributeId == Switch::Attributes::CurrentPosition::Id && maxReadLength == 1){
        *buffer = deviceRD.GetOnOffSwitch(endpoint);
    }
    else if(attributeId == Switch::Attributes::NumberOfPositions::Id && maxReadLength == 1){
        *buffer = 2;
    }
    else if (attributeId == OnOff::Attributes::ClusterRevision::Id)
    {
        *buffer = (uint16_t) ZCL_SWITCH_CLUSTER_REVISION;
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
        *buffer = (uint8_t)deviceRD.GetOnOffLight(endpoint);
    }
    else if (attributeId == OnOff::Attributes::ClusterRevision::Id)
    {
        *buffer = (uint16_t) ZCL_ON_OFF_CLUSTER_REVISION;
    }
    else if (attributeId == OnOff::Attributes::FeatureMap::Id){
        *buffer = ZCL_ON_OFF_CLUSTER_FEATURE_MAP;
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
#if HC_RANGDONG
        MqttControllOnOff(
            deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID,
            (bool) (*buffer)
        );
        deviceRD.UpdateOnOffLight(deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID, (bool) (*buffer));
#endif
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
        *buffer = (uint8_t)deviceRD.GetCctLight(endpoint);
    }
    else if(attributeId == ColorControl::Attributes::ColorTempPhysicalMinMireds::Id){
        *buffer = 0;
    }
    else if(attributeId == ColorControl::Attributes::ColorTempPhysicalMaxMireds::Id){
        *buffer = 255;
    }
    else if(attributeId == ColorControl::Attributes::CurrentHue::Id){
        *buffer = (uint8_t)deviceRD.GetHueLight(endpoint);
    }
    else if(attributeId == ColorControl::Attributes::CurrentSaturation::Id ){
        *buffer = (uint8_t)deviceRD.GetSaturationLight(endpoint);
    }
    else if(attributeId == ColorControl::Attributes::ClusterRevision::Id){
        *buffer = (uint16_t) ZCL_COLOR_CLUSTER_REVISION;
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
    string deviceID = deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID;
    if (attributeId == ColorControl::Attributes::RemainingTime::Id){

    }
    if (attributeId == ColorControl::Attributes::ColorTemperatureMireds::Id){
#if HC_RANGDONG
        MqttControllCct(
            deviceID,
            *buffer
        );
        deviceRD.UpdateCctLight(deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID, *buffer);
#endif        
    }
    if (attributeId == ColorControl::Attributes::CurrentHue::Id){
#if HC_RANGDONG
        MqttControllHSV(
            deviceID,
            *buffer,
            (uint8_t)deviceRD.GetSaturationLight(endpoint),
            (uint8_t)deviceRD.GetLightnessLight(endpoint),
            (uint8_t)deviceRD.GetDimLight(endpoint)
        );
        deviceRD.UpdateHueLight(deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID, *buffer);
#endif       
    }
    if (attributeId == ColorControl::Attributes::CurrentSaturation::Id){
#if HC_RANGDONG
        MqttControllHSV(
            deviceID,
            (uint8_t)deviceRD.GetHueLight(endpoint),
            *buffer,
            (uint8_t)deviceRD.GetLightnessLight(endpoint),
            (uint8_t)deviceRD.GetDimLight(endpoint)
        );
        deviceRD.UpdateSaturationLight(deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID, *buffer);
#endif
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
        
        *buffer = (uint8_t)deviceRD.GetDimLight(endpoint);
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
        *buffer = (uint16_t) ZCL_DIM_CLUSTER_REVISION;
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
#if HC_RANGDONG
        MqttControllDim(
            deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID,
            *buffer
        );
        deviceRD.UpdateDimLight(
            deviceRD.GetDeviceWithEndpoint(endpoint)->DeviceID,
            (unsigned int)*buffer
        );
#endif
    }
    else{
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadBindingAttribute(chip::AttributeId attributeId, uint8_t * buffer, uint16_t maxReadLength)
{

    if ((attributeId == Binding::Attributes::ClusterRevision::Id) && (maxReadLength == 2))
    {
        *buffer = (uint16_t)ZCL_BINDING_CLUSTER_REVISION;
      
    }  
    else if ((attributeId == Binding::Attributes::FeatureMap::Id))
    {
        uint16_t featureMap = 0;
        memcpy(buffer, &featureMap, sizeof(featureMap));
    }
    else if (attributeId == Binding::Attributes::GeneratedCommandList::Id){

    }
    else if (attributeId == Binding::Attributes::AcceptedCommandList::Id){

    }
    else if (attributeId == Binding::Attributes::AttributeList::Id){
        
    }
    else if (attributeId == Binding::Attributes::EventList::Id){
        
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status HandleReadIdentifyAttribute(chip::AttributeId attributeId, uint8_t * buffer,
                                                 uint16_t maxReadLength)
{
    // printf("HandleReadIdentifyAttribute %d\n", attributeId);
    if ((attributeId == Identify::Attributes::ClusterRevision::Id))
    {
       *buffer = (uint16_t)ZCL_IDENTIFY_CLUSTER_REVISION;
    }  
    else if ((attributeId == Identify::Attributes::FeatureMap::Id))
    {

    }
    else if ((attributeId == Identify::Attributes::IdentifyTime::Id)){
        *buffer = 0;
    }
    else if (attributeId == Identify::Attributes::IdentifyType::Id){

    }
    else if (attributeId == Identify::Attributes::GeneratedCommandList::Id){

    }
    else if (attributeId == Identify::Attributes::AcceptedCommandList::Id){

    }
    else if (attributeId == Identify::Attributes::AttributeList::Id){
        
    }
    else if (attributeId == Identify::Attributes::EventList::Id){
        
    }
    else
    {
        return Protocols::InteractionModel::Status::Failure;
    }

    return Protocols::InteractionModel::Status::Success;
}

Protocols::InteractionModel::Status emberAfExternalAttributeReadCallback(EndpointId endpoint, ClusterId clusterId,
                                                   const EmberAfAttributeMetadata * attributeMetadata, uint8_t * buffer,
                                                   uint16_t maxReadLength)
{
    uint16_t endpointIndex = emberAfGetDynamicIndexFromEndpoint(endpoint);

    ChipLogProgress(DeviceLayer, "emberAfExternalAttributeReadCallback: ep=%d -- clusterId = %d --- endpointIndex=%d", endpoint, clusterId, endpointIndex);

    Protocols::InteractionModel::Status ret = Protocols::InteractionModel::Status::Failure;

    if ((endpointIndex < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT))
    {
        // Device * dev = gDevices[endpointIndex];

        if (clusterId == BridgedDeviceBasicInformation::Id)
        {
            ret = HandleReadBridgedDeviceBasicAttribute(attributeMetadata->attributeId, buffer, maxReadLength, endpoint);
        }
        else if (clusterId == OnOff::Id)
        {
            ret = HandleReadOnOffAttribute(attributeMetadata->attributeId, buffer, maxReadLength, endpoint);
        }
        else if (clusterId == Binding::Id)
        {
            ret  = HandleReadBindingAttribute(attributeMetadata->attributeId, buffer, maxReadLength);
        }
        else if(clusterId == LevelControl::Id){
            ret  = HandleReadLevelControlAttribute(attributeMetadata->attributeId, buffer, maxReadLength, endpoint);
        }
        else if(clusterId == ColorControl::Id){            
            ret = HandleReadColorControlAttribute(attributeMetadata->attributeId, buffer, maxReadLength, endpoint);
        }
        else if(clusterId == Identify::Id){
            ret = HandleReadIdentifyAttribute(attributeMetadata->attributeId, buffer, maxReadLength);
        }
        else if(clusterId == Switch::Id){
            ret = HandleReadSwitchAttribute(attributeMetadata->attributeId, buffer, maxReadLength, endpoint);
        }

    }

    return ret;
}

Protocols::InteractionModel::Status emberAfExternalAttributeWriteCallback(EndpointId endpoint, ClusterId clusterId,
                                                    const EmberAfAttributeMetadata * attributeMetadata, uint8_t * buffer)
{
    uint16_t endpointIndex = emberAfGetDynamicIndexFromEndpoint(endpoint);

    Protocols::InteractionModel::Status ret = Protocols::InteractionModel::Status::Failure;

    // ChipLogProgress(DeviceLayer, "emberAfExternalAttributeWriteCallback: ep=%d", endpoint);

    if (endpointIndex < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT)
    {
        if (clusterId == OnOff::Id)
        {
            ret = HandleWriteOnOffAttribute(attributeMetadata->attributeId, buffer, endpoint);
        }
        else if(clusterId == ColorControl::Id){
            ret = HandleWriteColorControlAttribute(attributeMetadata->attributeId, buffer, endpoint);
        }
        else if(clusterId == LevelControl::Id){
            ret = HandleWriteLevelControlAttribute( attributeMetadata->attributeId, buffer, endpoint);
        }
    }

    return ret;
}


void ApplicationInit()
{
    sEthernetNetworkCommissioningInstance.Init();
    InitOTARequestor();
}

const EmberAfDeviceType gBridgedTempLightDeviceTypes[] = {  { DEVICE_TYPE_COLOR_TEMPERATURE_LIGHT, DEVICE_VERSION_DEFAULT },
                                                            { DEVICE_TYPE_BRIDGED_NODE, DEVICE_VERSION_DEFAULT } };

const EmberAfDeviceType gBridgedExtendedLightDeviceTypes[] = {  {DEVICE_TYPE_EXTENAL_LIGHT, DEVICE_VERSION_DEFAULT },
                                                                {DEVICE_TYPE_BRIDGED_NODE, DEVICE_VERSION_DEFAULT } };

const EmberAfDeviceType gBridgedOnOffSwitchDeviceTypes[] = {{DEVICE_TYPE_LO_SWITCH_LIGHT, DEVICE_VERSION_DEFAULT },
                                                            {DEVICE_TYPE_BRIDGED_NODE, DEVICE_VERSION_DEFAULT }};

const EmberAfDeviceType gBridgedColorDimmerSwitchDeviceTypes[] = {{ DEVICE_TYPE_COLOR_DIMMER_SWITCH, DEVICE_VERSION_DEFAULT},
                                                                  { DEVICE_TYPE_BRIDGED_NODE, DEVICE_VERSION_DEFAULT }};

/***********************************************MQTT Rang Dong Processing**********************************************************/
#if HC_RANGDONG

static void AddOnOffSwitch(string deviceID, string mac, string version, unsigned int hcID){

    DeviceInformation deviceBase;
    deviceBase.DeviceTypeID                 = 0x103;
    deviceBase.DeviceID                     = deviceID;
    deviceBase.SerialNumber                 = mac;
    deviceBase.Version                      = version;  
    deviceBase.HomeCenterID                 = hcID;
    deviceBase.NodeLabel                    = "OnOff Switch";

    int endpoint = AddDeviceEndpoint(
        &bridgedOnOffSwitchEndpoint, 
        Span<const EmberAfDeviceType>(gBridgedOnOffSwitchDeviceTypes), 
        Span<DataVersion>(gOnOffSwitchDataVersions), 
        1, 
        true, 
        0
    );

    if(endpoint != -1){
        deviceBase.EndpointID = endpoint;
        deviceRD.AddDevice(deviceBase);
    }
}

static void AddTempLight(string deviceID, string mac, string version, unsigned int hcID){
    DeviceInformation deviceBase;
    deviceBase.DeviceTypeID                 = 0x10C;
    deviceBase.DeviceID                     = deviceID;
    deviceBase.SerialNumber                 = mac;
    deviceBase.Version                      = version;  
    deviceBase.HomeCenterID                 = hcID;
    deviceBase.NodeLabel                    = "Color Temperature Light";

    int endpoint = AddDeviceEndpoint(
        &bridgedTempLightEndpoint, 
        Span<const EmberAfDeviceType>(gBridgedTempLightDeviceTypes), 
        Span<DataVersion>(gTempLightDataVersions), 
        1, 
        true, 
        0
    );
    if(endpoint != -1){
        deviceBase.EndpointID = endpoint;
        deviceRD.AddDevice(deviceBase);
    }

}

static void AddExtendedLight(string deviceID, string mac, string version, unsigned int hcID){
    DeviceInformation deviceBase;
    deviceBase.DeviceTypeID                 = 0x10D;
    deviceBase.DeviceID                     = deviceID;
    deviceBase.SerialNumber                 = mac;
    deviceBase.Version                      = version;  
    deviceBase.HomeCenterID                 = hcID;
    deviceBase.NodeLabel                    = "RGB Light";

    int endpoint = AddDeviceEndpoint(
        &bridgedExtendedLightEndpoint, 
        Span<const EmberAfDeviceType>(gBridgedExtendedLightDeviceTypes), 
        Span<DataVersion>(gExtendedLightDataVersions), 
        1, 
        true, 
        0
    );
    if(endpoint != -1){
        deviceBase.EndpointID = endpoint;
        deviceRD.AddDevice(deviceBase);
    }

}

static void RemoveDevice(string deviceID){
    
    DeviceInformation * device = deviceRD.GetDeviceWithID(deviceID);

    if(device == nullptr)
        return;

    if(deviceRD.isTripleSwitch(device->HomeCenterID)){
        RemoveDeviceEndpoint((short unsigned int) device->EndpointID);
        deviceRD.RemoveDeviceWithEndpoint((short unsigned int) device->EndpointID);

        device = deviceRD.GetDeviceWithID(deviceID + "_2");
        RemoveDeviceEndpoint((short unsigned int) device->EndpointID);
        deviceRD.RemoveDeviceWithEndpoint((short unsigned int) device->EndpointID);

        device = deviceRD.GetDeviceWithID(deviceID + "_3");
    }
    else if(deviceRD.isQuadraSwitch(device->HomeCenterID)){
        RemoveDeviceEndpoint((short unsigned int) device->EndpointID);
        deviceRD.RemoveDeviceWithEndpoint((short unsigned int) device->EndpointID);

        device = deviceRD.GetDeviceWithID(deviceID + "_2");
        RemoveDeviceEndpoint((short unsigned int) device->EndpointID);
        deviceRD.RemoveDeviceWithEndpoint((short unsigned int) device->EndpointID);

        device = deviceRD.GetDeviceWithID(deviceID + "_3");
        RemoveDeviceEndpoint((short unsigned int) device->EndpointID);
        deviceRD.RemoveDeviceWithEndpoint((short unsigned int) device->EndpointID);

        device = deviceRD.GetDeviceWithID(deviceID + "_4");

    }
    else if(deviceRD.isDoubleSwitch(device->HomeCenterID)){
        RemoveDeviceEndpoint((short unsigned int) device->EndpointID);
        deviceRD.RemoveDeviceWithEndpoint((short unsigned int) device->EndpointID);

        device = deviceRD.GetDeviceWithID(deviceID + "_2");
    }

    RemoveDeviceEndpoint((short unsigned int) device->EndpointID);
    deviceRD.RemoveDeviceWithEndpoint((short unsigned int) device->EndpointID);
    
    // deviceRD.GetAllDevice();
}

static void UpdateOnOffSwitch(DeviceInformation * device, Json::Value * data){

    if((*data).isMember("bt")){
        deviceRD.UpdateOnOffSwitch(device->DeviceID, (bool)(*data)["bt"].asInt());
        if((*data)["bt"].asInt() == 1){
            LightSwitchMgr::GetInstance().TriggerLightSwitchAction(LightSwitchMgr::LightSwitchAction::On, false, (short unsigned int)device->EndpointID, OnOff::Id);
            Clusters::SwitchServer::Instance().OnSwitchLatch((short unsigned int)device->EndpointID, 1);
        }
        else{
            LightSwitchMgr::GetInstance().TriggerLightSwitchAction(LightSwitchMgr::LightSwitchAction::Off, false, (short unsigned int)device->EndpointID, OnOff::Id);
            Clusters::SwitchServer::Instance().OnSwitchLatch((short unsigned int)device->EndpointID, 0);
        }
    }

    if((*data).isMember("bt2")){
        printf("BT2");
    }

    if((*data).isMember("bt3")){
        printf("BT3");
    }   

    if((*data).isMember("bt4")){
        printf("BT4");
    } 
}

static void UpdateColorTempLight(string deviceID, Json::Value * data){
    // printf("Update Color Temperature Light\n");

    if((*data)["onoff"].isObject()){
        deviceRD.UpdateOnOffLight(deviceID, (bool)(*data)["onoff"].asInt());
    }
    else if((*data)["dim"].isObject()){
        deviceRD.UpdateDimLight(deviceID, (uint8_t)(*data)["dim"].asInt());
    }
    else if((*data)["cct"].isObject()){
        deviceRD.UpdateCctLight(deviceID, (uint8_t)(*data)["cct"].asInt());
    }
}

static void UpdateExtendedLight(string deviceID, Json::Value * data){
    // printf("Update Extended light \n");

    if((*data)["onoff"].isObject()){
        deviceRD.UpdateOnOffLight(deviceID, (bool)(*data)["onoff"].asInt());
    }
    else if((*data)["dim"].isObject()){
        deviceRD.UpdateDimLight(deviceID, (uint8_t)(*data)["dim"].asInt());
    }
    else if((*data)["h"].isObject()){
        deviceRD.UpdateHueLight(deviceID, (uint8_t)(*data)["h"].asInt());
    }
    else if((*data)["s"].isObject()){
        deviceRD.UpdateSaturationLight(deviceID, (uint8_t)(*data)["s"].asInt());
    }
    else if((*data)["l"].isObject()){
        deviceRD.UpdateLightnessLight(deviceID, (uint8_t)(*data)["l"].asInt());
    }
}

static void UpdateNameDevice(string deviceID, string name){
    DeviceInformation * device = deviceRD.GetDeviceWithID(deviceID);

    if(device == nullptr)
        return;

    deviceRD.UpdateNameWithID(deviceID, name);

    if(deviceRD.isTripleSwitch(device->HomeCenterID)){
        deviceRD.UpdateNameWithID(deviceID + "_2", name);
        deviceRD.UpdateNameWithID(deviceID + "_3", name);
    }
    else if(deviceRD.isQuadraSwitch(device->HomeCenterID)){
        deviceRD.UpdateNameWithID(deviceID + "_2", name);
        deviceRD.UpdateNameWithID(deviceID + "_3", name);
        deviceRD.UpdateNameWithID(deviceID + "_4", name);
    }
    else if(deviceRD.isDoubleSwitch(device->HomeCenterID)){
        deviceRD.UpdateNameWithID(deviceID + "_2", name);
    }

}

static void message_callback(struct mosquitto *_mosq, void *obj, const struct mosquitto_message *message){
	// printf("got message '%s' for topic '%s'\n", (char*) message->payload, message->topic);

    string messageStr;
    Json::Reader readerJson;
    Json::Value messageJson;
    messageStr.assign((const char*)message->payload, message->payloadlen);
    readerJson.parse(messageStr, messageJson);

    if(messageJson["cmd"].compare("newDev") == 0)
    {
        int deviceTypeID            = messageJson["data"]["device"][0]["type"].asInt();
        string deviceID             = messageJson["data"]["device"][0]["id"].asString();
        string mac                  = messageJson["data"]["device"][0]["mac"].asString();
        string version              = messageJson["data"]["device"][0]["ver"].asString();

        if(deviceRD.isTripleSwitch(deviceTypeID)){
            AddOnOffSwitch(deviceID, mac, version, deviceTypeID);
            AddOnOffSwitch(deviceID + "_2", mac, version, deviceTypeID);
            AddOnOffSwitch(deviceID + "_3", mac, version, deviceTypeID);
        }
        else if(deviceRD.isQuadraSwitch(deviceTypeID)){
            AddOnOffSwitch(deviceID, mac, version, deviceTypeID);
            AddOnOffSwitch(deviceID + "_2", mac, version, deviceTypeID);
            AddOnOffSwitch(deviceID + "_3", mac, version, deviceTypeID);
            AddOnOffSwitch(deviceID + "_4", mac, version, deviceTypeID);
        }
        else if(deviceRD.isDoubleSwitch(deviceTypeID)){
            AddOnOffSwitch(deviceID, mac, version, deviceTypeID);
            AddOnOffSwitch(deviceID + "_2", mac, version, deviceTypeID);
        }
        else if(deviceRD.isSingleSwitch(deviceTypeID)){
            AddOnOffSwitch(deviceID, mac, version, deviceTypeID);
        }
        else if(deviceRD.isExtendedLight(deviceTypeID)){
            AddExtendedLight(deviceID, mac, version, deviceTypeID);
        }
        else if(deviceRD.isColorTempLight(deviceTypeID)){
            AddTempLight(deviceID, mac, version, deviceTypeID);
        }
    }
    else if(messageJson["cmd"].compare("updateDeviceName") == 0){

        UpdateNameDevice(
            messageJson["data"]["id"].asString(),
            messageJson["data"]["name"].asString()
        );
    }
    else if(messageJson["cmd"].compare("delDevRsp") == 0){
        for(unsigned int i = 0; i < messageJson["data"]["success"].size(); i++){
            string deviceID = messageJson["data"]["success"][i].asString();
            RemoveDevice(deviceID);
        }
    }
    else if(messageJson["cmd"].compare("deviceUpdate") == 0){
        string deviceID             = messageJson["data"]["device"][0]["id"].asString();
        Json::Value data            = messageJson["data"]["device"][0]["data"];
        DeviceInformation * device    = deviceRD.GetDeviceWithID(deviceID);

        if(device == nullptr)
            return;

        if(device->reachable == false){
            EventNumber eventNumber;
            Clusters::BridgedDeviceBasicInformation::Events::ReachableChanged::Type event{1};
            device->reachable = true;
            LogEvent(event, (short unsigned int)device->EndpointID, eventNumber);
        }
            
        if(device->DeviceTypeID == 0x10C){
            UpdateColorTempLight(deviceID, &data);
        }
        else if(device->DeviceTypeID == 0x10D){
            UpdateExtendedLight(deviceID, &data);
        }
        else if(device->DeviceTypeID == 0x103){
            UpdateOnOffSwitch(device, &data);
        }
    }
    else if(messageJson["cmd"].compare("resetHcRsp") == 0 ){
        if(messageJson["data"]["code"].asInt() == 0){
            deviceRD.Reset();
        }
    }
}

#endif
/***********************************************MQTT Rang Dong Processing**********************************************************/

#define POLL_INTERVAL_MS (100)
uint8_t poll_prescale = 0;

bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

const int16_t oneDegree = 100;

void * bridge_polling_thread(void * context)
{
    bool light1_added = true;
    if(deviceRD.GetDeviceWithEndpoint(3) == nullptr)
        light1_added = false;
    bool light2_added = false;
    while (true)
    {
        if (kbhit())
        {
            int ch = getchar();

            // Commands used for the actions bridge test plan.
            if (ch == '2' && light2_added == false)
            {
                AddTempLight("a99ec455-7522-d43b-9fab-acd567d02a81", "502C3038C1A1", "1.1", 12001);
                light2_added = true;
            }
            else if (ch == '4' && light1_added == true)
            {
                // TC-BR-2 step 4, Remove Light 1
                RemoveDevice("7657a122-ec31-7338-ac12-25c481cb17eb");
                light1_added = false;
            }
            else if (ch == '5' && light1_added == false)
            {
                // TC-BR-2 step 5, Add Light 1 back
                AddTempLight("7657a122-ec31-7338-ac12-25c481cb17eb", "502C3038C1A2", "1.1", 12001);
                light1_added = true;
            }
            else if (ch == 'b')
            {
                // TC-BR-3 step 1b, rename lights
                if (light1_added)
                    deviceRD.UpdateNodeLabelWithEndpoint(3, "Light 1b");
            }
            else if (ch == 'c')
            {
                // TC-BR-3 step 2c, change the state of the lights
                if (light1_added)
                {
                    bool state = !deviceRD.GetOnOffLight(3);
                    deviceRD.UpdateOnOffLight(deviceRD.GetDeviceWithEndpoint(3)->DeviceID, state);
                }
            }
            else if(ch == 'v'){
                DeviceInformation * device = deviceRD.GetDeviceWithEndpoint(3);
                device->reachable = true;
                EventNumber eventNumber;
                Clusters::BridgedDeviceBasicInformation::Events::ReachableChanged::Type event{1};
                if (CHIP_NO_ERROR != LogEvent(event, (short unsigned int)device->EndpointID, eventNumber))
                {
                    ChipLogError(Zcl, "Failed to record ReachableChanged event");
                }
            }
            else if(ch == 'u'){
                DeviceInformation * device = deviceRD.GetDeviceWithEndpoint(3);
                device->reachable = false;
                EventNumber eventNumber;
                Clusters::BridgedDeviceBasicInformation::Events::ReachableChanged::Type event{0};
                if (CHIP_NO_ERROR != LogEvent(event, (short unsigned int)device->EndpointID, eventNumber))
                {
                    ChipLogError(Zcl, "Failed to record ReachableChanged event");
                }
            }
            else if(ch == 'e'){
                // Clusters::Switch::Attributes::CurrentPosition::Set(6, 1);
                // Trigger event
                Clusters::SwitchServer::Instance().OnSwitchLatch(6, 1);
            }
            else if(ch == 'r'){
                // Clusters::Switch::Attributes::CurrentPosition::Set(6, 0);
                // Trigger event
                Clusters::SwitchServer::Instance().OnSwitchLatch(6, 0);
            }
            else if(ch == 't'){
                EventNumber eventNumber;
                Clusters::BridgedDeviceBasicInformation::Events::StartUp::Type event;
                if (CHIP_NO_ERROR != LogEvent(event, 0, eventNumber))
                {
                    ChipLogError(Zcl, "Failed to record ReachableChanged event");
                }
            }
            else if(ch == 'y'){
                EventNumber eventNumber;
                Clusters::BridgedDeviceBasicInformation::Events::ReachableChanged::Type event{1};
                if (CHIP_NO_ERROR != LogEvent(event, 3, eventNumber))
                {
                    ChipLogError(Zcl, "Failed to record ReachableChanged event");
                }
            }
            continue;
        }
        // Sleep to avoid tight loop reading commands
        usleep(POLL_INTERVAL_MS * 1000);
    }

    return nullptr;
}

int main(int argc, char * argv[])
{
    // printf("Starting+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++!");
#if HC_RANGDONG
    deviceRD.Init();
    mosq = MqttConnect();
    mosquitto_message_callback_set(mosq, message_callback);
#endif
    
    if (ChipLinuxAppInit(argc, argv) != 0)
    {
        return -1;
    }
    // Init Data Model and CHIP App Server
    static chip::CommonCaseDeviceServerInitParams initParams;
    (void) initParams.InitializeStaticResourcesBeforeServerInit();

    initParams.interfaceId = LinuxDeviceOptions::GetInstance().interfaceId;
    chip::Server::GetInstance().Init(initParams);
    RunOTARequestor();

    // gExampleDeviceInfoProvider.SetStorageDelegate(&Server::GetInstance().GetPersistentStorage());
    // chip::DeviceLayer::SetDeviceInfoProvider(&gExampleDeviceInfoProvider);

    // Initialize device attestation config
    SetDeviceAttestationCredentialsProvider(Examples::GetExampleDACProvider());
    CHIP_ERROR err = LightSwitchMgr::GetInstance().Init(kLightSwitchEndpoint, kGenericSwitchEndpoint);


    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "LightSwitchMgr Init failed!");
    }

    emberAfEndpointEnableDisable(emberAfEndpointFromIndex(static_cast<uint16_t>(emberAfFixedEndpointCount() - 1)), false);

#if TEST_DEVICE

    AddDeviceEndpoint(
        &bridgedTempLightEndpoint, 
        Span<const EmberAfDeviceType>(gBridgedTempLightDeviceTypes), 
        Span<DataVersion>(gTempLightDataVersions), 
        1, 
        false, 
        3
    );

    AddDeviceEndpoint(
        &bridgedExtendedLightEndpoint, 
        Span<const EmberAfDeviceType>(gBridgedExtendedLightDeviceTypes), 
        Span<DataVersion>(gExtendedLightDataVersions), 
        1, 
        false, 
        4
    );

    AddDeviceEndpoint(
        &bridgedOnOffSwitchEndpoint, 
        Span<const EmberAfDeviceType>(gBridgedOnOffSwitchDeviceTypes),
        Span<DataVersion>(gOnOffSwitchDataVersions), 
        1, 
        false, 
        5
    );

#endif

#if HC_RANGDONG

    // Test Device
    //

    DeviceInformation * device;
    for(unsigned int i=0; i < deviceRD.GetNumberDevices(); i++){
        device = deviceRD.GetDeviceWithIndex(i);
        if(device->DeviceTypeID == 0x10C)
        {
            AddDeviceEndpoint(
                &bridgedTempLightEndpoint, 
                Span<const EmberAfDeviceType>(gBridgedTempLightDeviceTypes), 
                Span<DataVersion>(gTempLightDataVersions), 
                1, 
                false, 
                device->EndpointID
            );

        }
        else if(device->DeviceTypeID == 0x10D){
            AddDeviceEndpoint(
                &bridgedExtendedLightEndpoint, 
                Span<const EmberAfDeviceType>(gBridgedExtendedLightDeviceTypes), 
                Span<DataVersion>(gExtendedLightDataVersions), 
                1, 
                false, 
                device->EndpointID
            );
        }
        else if(device->DeviceTypeID == 0x103){
            AddDeviceEndpoint(
                &bridgedOnOffSwitchEndpoint, 
                Span<const EmberAfDeviceType>(gBridgedOnOffSwitchDeviceTypes),
                Span<DataVersion>(gOnOffSwitchDataVersions), 
                1, 
                false, 
                device->EndpointID
            );
        }
        else if(device->DeviceTypeID == 0x105){
            AddDeviceEndpoint(
                &bridgedColorDimmerSwitchEndpoint, 
                Span<const EmberAfDeviceType>(gBridgedColorDimmerSwitchDeviceTypes), 
                Span<DataVersion>(gColorDimmerSwitchDataVersions), 
                1, 
                false, 
                device->EndpointID
            );
        }
    }

    // AddDeviceEndpoint(
    //     &bridgedOnOffSwitchEndpoint, 
    //     Span<const EmberAfDeviceType>(gBridgedOnOffSwitchDeviceTypes),
    //     Span<DataVersion>(gOnOffSwitchDataVersions), 
    //     1, 
    //     true, 
    //     0
    // );
#endif
    EventNumber eventNumber;
    Clusters::BridgedDeviceBasicInformation::Events::StartUp::Type event;
    LogEvent(event, 0, eventNumber);
    {
        pthread_t poll_thread;
        int res = pthread_create(&poll_thread, nullptr, bridge_polling_thread, nullptr);
        if (res)
        {
            printf("Error creating polling thread: %d\n", res);
            exit(1);
        }
    }

    ApplicationInit();
    chip::DeviceLayer::PlatformMgr().RunEventLoop();
#if HC_RANGDONG
    mosquitto_destroy(mosq);
#endif
    return 0;
}
