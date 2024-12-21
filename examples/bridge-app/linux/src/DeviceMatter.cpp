



// namespace MatterDevice {

    // const int kDescriptorAttributeArraySize = 254;
    // // static chip::DeviceLayer::DeviceInfoProviderImpl gExampleDeviceInfoProvider;
    // constexpr chip::EndpointId kLightSwitchEndpoint   = 2;
    // constexpr chip::EndpointId kGenericSwitchEndpoint = 2;
    // DeviceLayer::NetworkCommissioning::LinuxEthernetDriver sEthernetDriver;
    // Clusters::NetworkCommissioning::Instance sEthernetNetworkCommissioningInstance(0, &sEthernetDriver);

    // // ENDPOINT DEFINITIONS:
    // // =================================================================================
    // //
    // // Endpoint definitions will be reused across multiple endpoints for every instance of the
    // // endpoint type.
    // // There will be no intrinsic storage for the endpoint attributes declared here.
    // // Instead, all attributes will be treated as EXTERNAL, and therefore all reads
    // // or writes to the attributes must be handled within the emberAfExternalAttributeWriteCallback
    // // and emberAfExternalAttributeReadCallback functions declared herein. This fits
    // // the typical model of a bridge, since a bridge typically maintains its own
    // // state database representing the devices connected to it.

    // // Device types for dynamic endpoints: TODO Need a generated file from ZAP to define these!

    // #define DEVICE_TYPE_BRIDGED_NODE                    0x0013

    // #define DEVICE_TYPE_LO_ON_OFF_LIGHT                 0x0100

    // #define DEVICE_TYPE_DIM_LIGHT                       0x0101

    // #define DEVICE_TYPE_COLOR_TEMPERATURE_LIGHT         0x010C

    // #define DEVICE_TYPE_LO_SWITCH_LIGHT                 0x0103

    // #define DEVICE_TYPE_DIMMER_SWITCH                   0x0104

    // #define DEVICE_TYPE_COLOR_DIMMER_SWITCH             0x0105

    // #define DEVICE_TYPE_EXTENAL_LIGHT                   0x010D

    // #define DEVICE_TYPE_TEMPERATURE_SENSOR              0x0302

    // #define DEVICE_TYPE_HUMIDITY_SENSOR                 0x0307

    // #define DEVICE_TYPE_CONTACT_SENSOR                  0x0015

    // #define DEVICE_TYPE_POWER_SOURCE                    0x0011

    // // #define DEVICE_TYPE_POWER_SOURCE 0x0011

    // // #define DEVICE_TYPE_TEMP_SENSOR 0x0302

    // // Device Version for dynamic endpoints:

    // #define DEVICE_VERSION_DEFAULT 1

    // // Declare On/Off cluster attributes
    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(onOffAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(OnOff::Attributes::OnOff::Id, BOOLEAN, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(OnOff::Attributes::GlobalSceneControl::Id, BOOLEAN, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(OnOff::Attributes::FeatureMap::Id, BITMAP32, 1, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(switchAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(Switch::Attributes::CurrentPosition::Id, INT8U, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(Switch::Attributes::NumberOfPositions::Id, INT8U, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(Switch::Attributes::FeatureMap::Id, BITMAP32, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(Switch::Attributes::EventList::Id, ARRAY, 4, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // // Dev Declare LevelControl cluster attributes
    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(levelControlAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(LevelControl::Attributes::CurrentLevel::Id, INT8U, 1, 0), 
    // DECLARE_DYNAMIC_ATTRIBUTE(LevelControl::Attributes::MinLevel::Id, INT8U, 1, 0), 
    // DECLARE_DYNAMIC_ATTRIBUTE(LevelControl::Attributes::MaxLevel::Id, INT8U, 1, 0), 
    // DECLARE_DYNAMIC_ATTRIBUTE(LevelControl::Attributes::FeatureMap::Id, BITMAP32, 1, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(tempColorControlAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(ColorControl::Attributes::ColorTemperatureMireds::Id, INT8U, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(ColorControl::Attributes::ColorTempPhysicalMinMireds::Id, INT8U, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(ColorControl::Attributes::ColorTempPhysicalMaxMireds::Id, INT8U, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(ColorControl::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(extendedColorControlAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(ColorControl::Attributes::CurrentHue::Id, INT8U, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(ColorControl::Attributes::CurrentSaturation::Id, INT8U, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(ColorControl::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();


    // // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(powerSourceAttrs)
    // // DECLARE_DYNAMIC_ATTRIBUTE(PowerSource::Attributes::BatChargeLevel::Id, ENUM8, 1, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE(PowerSource::Attributes::BatReplacementNeeded::Id, BOOLEAN, 1, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE(PowerSource::Attributes::BatReplaceability::Id, ENUM8, 1, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE(PowerSource::Attributes::Order::Id, INT8U, 1, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE(PowerSource::Attributes::Status::Id, ENUM8, 1, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE(PowerSource::Attributes::Description::Id, CHAR_STRING, 32, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE(PowerSource::Attributes::FeatureMap::Id, BITMAP32, 4, 0), 
    // //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(groupsAttrs)
    // // DECLARE_DYNAMIC_ATTRIBUTE(Groups::Attributes::NameSupport::Id, BITMAP8, 2, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Groups::Attributes::GeneratedCommandList::Id, ARRAY, 2, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Groups::Attributes::AcceptedCommandList::Id, ARRAY, 2, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Groups::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(scenesAttrs)
    // // DECLARE_DYNAMIC_ATTRIBUTE(Scenes::Attributes::SceneCount::Id, INT8U, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Scenes::Attributes::CurrentScene::Id, INT8U, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Scenes::Attributes::CurrentGroup::Id, GROUP_ID, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Scenes::Attributes::SceneValid::Id, BOOLEAN, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Scenes::Attributes::NameSupport::Id, BITMAP8, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Scenes::Attributes::LastConfiguredBy::Id, NODE_ID, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(Scenes::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(identifyAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(Identify::Attributes::IdentifyTime::Id, INT16U, 2, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(Identify::Attributes::IdentifyType::Id, ENUM8, 1, 0),
    // DECLARE_DYNAMIC_ATTRIBUTE(Identify::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // // Dev Declare Binding cluster attributes
    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(bindingAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(Binding::Attributes::Binding::Id, ARRAY, 256, 1),
    // DECLARE_DYNAMIC_ATTRIBUTE(Binding::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();


    // // Dev Declare Temperature cluster attributes
    // // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(temperatureAttrs)
    // // DECLARE_DYNAMIC_ATTRIBUTE(TemperatureMeasurement::Attributes::MeasuredValue::Id, INT16S, 2, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(TemperatureMeasurement::Attributes::MinMeasuredValue::Id, INT16S, 2, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(TemperatureMeasurement::Attributes::MaxMeasuredValue::Id, INT16S, 2, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(TemperatureMeasurement::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(TemperatureMeasurement::Attributes::EventList::Id, ARRAY, 4, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();


    // // Dev Declare Humidity cluster attributes
    // // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(humidityAttrs)
    // // DECLARE_DYNAMIC_ATTRIBUTE(RelativeHumidityMeasurement::Attributes::MeasuredValue::Id, INT8U, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(RelativeHumidityMeasurement::Attributes::MinMeasuredValue::Id, INT8U, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(RelativeHumidityMeasurement::Attributes::MaxMeasuredValue::Id, INT8U, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(RelativeHumidityMeasurement::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(RelativeHumidityMeasurement::Attributes::EventList::Id, ARRAY, 4, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();


    // // Dev Declare Door Look cluster attributes
    // // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(doorlockAttrs)
    // // DECLARE_DYNAMIC_ATTRIBUTE(DoorLock::Attributes::DoorState::Id, BOOLEAN, 1, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(RelativeHumidityMeasurement::Attributes::FeatureMap::Id, BITMAP32, 4, 0),
    // // DECLARE_DYNAMIC_ATTRIBUTE(RelativeHumidityMeasurement::Attributes::EventList::Id, ARRAY, 4, 0),
    // //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // // Declare Descriptor cluster attributes
    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(descriptorAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(Descriptor::Attributes::DeviceTypeList::Id, ARRAY, kDescriptorAttributeArraySize, 0), /* device list */
    //     DECLARE_DYNAMIC_ATTRIBUTE(Descriptor::Attributes::ServerList::Id, ARRAY, kDescriptorAttributeArraySize, 0), /* server list */
    //     DECLARE_DYNAMIC_ATTRIBUTE(Descriptor::Attributes::ClientList::Id, ARRAY, kDescriptorAttributeArraySize, 0), /* client list */
    //     DECLARE_DYNAMIC_ATTRIBUTE(Descriptor::Attributes::PartsList::Id, ARRAY, kDescriptorAttributeArraySize, 0),  /* parts list */
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();

    // // Declare Bridged Device Basic Information cluster attributes
    // DECLARE_DYNAMIC_ATTRIBUTE_LIST_BEGIN(bridgedDeviceBasicAttrs)
    // DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::NodeLabel::Id, CHAR_STRING, 10, 0), /* NodeLabel */
    //     DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::VendorName::Id, CHAR_STRING, 10, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::VendorID::Id, VENDOR_ID, 10, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::ProductName::Id, CHAR_STRING, 10, 0),
    //     // DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::HardwareVersion::Id, INT8U, 10, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::HardwareVersionString::Id, CHAR_STRING, 10, 0),
    //     // DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::SoftwareVersion::Id, INT8U, 10, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::SoftwareVersionString::Id, CHAR_STRING, 10, 0),
    //     // DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::PartNumber::Id, CHAR_STRING, 10, 0),
    //     // DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::ProductURL::Id, CHAR_STRING, 10, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::SerialNumber::Id, CHAR_STRING, 10, 0),
    //     // DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::UniqueID::Id, CHAR_STRING, 10, 0),
    //     // DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::ManufacturingDate::Id, CHAR_STRING, 10, 0),
    //     // DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::ProductLabel::Id, CHAR_STRING, 10, 0),
    //     DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::Reachable::Id, BOOLEAN, 1, 0),              /* Reachable */
    //     DECLARE_DYNAMIC_ATTRIBUTE(BridgedDeviceBasicInformation::Attributes::FeatureMap::Id, BITMAP32, 4, 0), /* feature map */
    //     DECLARE_DYNAMIC_ATTRIBUTE_LIST_END();


    // constexpr EventId eventsBrigde[] = {
    //     app::Clusters::BridgedDeviceBasicInformation::Events::ReachableChanged::Id,
    //     kInvalidEventId,
    // };

    // constexpr EventId eventsSwitch[] = {
    //     app::Clusters::Switch::Events::SwitchLatched::Id,
    //     kInvalidEventId,
    // };

    // constexpr EventId onOffCommands[] = {
    //     app::Clusters::OnOff::Commands::Off::Id,
    //     app::Clusters::OnOff::Commands::On::Id,
    //     app::Clusters::OnOff::Commands::Toggle::Id,
    //     kInvalidCommandId,
    // };

    // constexpr CommandId levelControlCommands[] = {
    //     app::Clusters::LevelControl::Commands::MoveToLevel::Id,
    //     kInvalidCommandId,
    // };

    // constexpr CommandId tempColorControlCommands[] = {
    //     app::Clusters::ColorControl::Commands::MoveToColorTemperature ::Id,
    //     kInvalidCommandId,
    // };

    // constexpr CommandId extendedColorControlCommands[] = {
    //     app::Clusters::ColorControl::Commands::MoveToHue::Id,
    //     app::Clusters::ColorControl::Commands::MoveToSaturation::Id,
    //     kInvalidCommandId,
    // };

    // // constexpr CommandId groupCommands[] = {
    // //     app::Clusters::Groups::Commands::AddGroupResponse::Id,
    // //     app::Clusters::Groups::Commands::ViewGroupResponse::Id,
    // //     app::Clusters::Groups::Commands::GetGroupMembershipResponse::Id,
    // //     app::Clusters::Groups::Commands::RemoveGroupResponse::Id,
    // //     kInvalidCommandId,
    // // };

    // // constexpr CommandId scenesCommands[] = {
    // //     app::Clusters::Scenes::Commands::AddScene::Id,
    // //     app::Clusters::Scenes::Commands::ViewScene::Id,
    // //     app::Clusters::Scenes::Commands::RemoveScene::Id,
    // //     app::Clusters::Scenes::Commands::RemoveAllScenes::Id,
    // //     app::Clusters::Scenes::Commands::StoreScene::Id,
    // //     app::Clusters::Scenes::Commands::RecallScene::Id,
    // //     app::Clusters::Scenes::Commands::GetSceneMembership::Id,
    // //     app::Clusters::Scenes::Commands::EnhancedAddScene::Id,
    // //     app::Clusters::Scenes::Commands::EnhancedViewScene::Id,
    // //     app::Clusters::Scenes::Commands::CopyScene::Id,
    // //     kInvalidCommandId,
    // // };

    // /*----------------------------------------------------------------
    // -----------------------------PTIT Dev-----------------------------
    // ----------------------------------------------------------------*/

    // DECLARE_DYNAMIC_CLUSTER_LIST_BEGIN(bridgedTempLightClusters)
    // DECLARE_DYNAMIC_CLUSTER(Identify::Id, identifyAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(Descriptor::Id, descriptorAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(BridgedDeviceBasicInformation::Id, bridgedDeviceBasicAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // // DECLARE_DYNAMIC_CLUSTER(Groups::Id, groupsAttrs, nullptr, nullptr, nullptr, 0),
    // // DECLARE_DYNAMIC_CLUSTER(Scenes::Id, scenesAttrs, nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(OnOff::Id, onOffAttrs, ZAP_CLUSTER_MASK(SERVER), onOffCommands, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(LevelControl::Id, levelControlAttrs, ZAP_CLUSTER_MASK(SERVER), levelControlCommands, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(ColorControl::Id, tempColorControlAttrs, ZAP_CLUSTER_MASK(SERVER), tempColorControlCommands, nullptr),
    //     DECLARE_DYNAMIC_CLUSTER_LIST_END;

    // DECLARE_DYNAMIC_CLUSTER_LIST_BEGIN(bridgedExtendedLightClusters)
    // DECLARE_DYNAMIC_CLUSTER(Identify::Id, identifyAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(Descriptor::Id, descriptorAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(BridgedDeviceBasicInformation::Id, bridgedDeviceBasicAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // // DECLARE_DYNAMIC_CLUSTER(Groups::Id, groupsAttrs, nullptr, nullptr, nullptr, 0),
    // // DECLARE_DYNAMIC_CLUSTER(Scenes::Id, scenesAttrs, nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(OnOff::Id, onOffAttrs, ZAP_CLUSTER_MASK(SERVER), onOffCommands, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(LevelControl::Id, levelControlAttrs, ZAP_CLUSTER_MASK(SERVER), levelControlCommands, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(ColorControl::Id, extendedColorControlAttrs, ZAP_CLUSTER_MASK(SERVER), extendedColorControlCommands, nullptr),
    //     DECLARE_DYNAMIC_CLUSTER_LIST_END;

    // DECLARE_DYNAMIC_CLUSTER_LIST_BEGIN(bridgedOnOffSwitchClusters)
    // DECLARE_DYNAMIC_CLUSTER(Identify::Id, identifyAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(Descriptor::Id, descriptorAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(BridgedDeviceBasicInformation::Id, bridgedDeviceBasicAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // // DECLARE_DYNAMIC_CLUSTER(Groups::Id, groupsAttrs, nullptr, nullptr, nullptr, 0),
    // DECLARE_DYNAMIC_CLUSTER(Switch::Id, switchAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // // DECLARE_DYNAMIC_CLUSTER_CLIENT(Scenes::Id, scenesAttrs, nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(OnOff::Id, onOffAttrs,ZAP_CLUSTER_MASK(CLIENT), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(Binding::Id, bindingAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    //     DECLARE_DYNAMIC_CLUSTER_LIST_END;


    // DECLARE_DYNAMIC_CLUSTER_LIST_BEGIN(bridgedColorDimmerSwitchClusters)
    // DECLARE_DYNAMIC_CLUSTER(Identify::Id, identifyAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(Descriptor::Id, descriptorAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(BridgedDeviceBasicInformation::Id, bridgedDeviceBasicAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    // // DECLARE_DYNAMIC_CLUSTER_CLIENT(Groups::Id, groupsAttrs, nullptr, nullptr),
    // // DECLARE_DYNAMIC_CLUSTER_CLIENT(Scenes::Id, scenesAttrs, nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(OnOff::Id, onOffAttrs, ZAP_CLUSTER_MASK(CLIENT), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(LevelControl::Id, levelControlAttrs, ZAP_CLUSTER_MASK(CLIENT), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(ColorControl::Id, tempColorControlAttrs, ZAP_CLUSTER_MASK(CLIENT), nullptr, nullptr),
    // DECLARE_DYNAMIC_CLUSTER(Binding::Id, bindingAttrs, ZAP_CLUSTER_MASK(SERVER), nullptr, nullptr),
    //     DECLARE_DYNAMIC_CLUSTER_LIST_END;


    // // DECLARE_DYNAMIC_CLUSTER_LIST_BEGIN(bridgedTemperatureClusters)
    // // DECLARE_DYNAMIC_CLUSTER(Identify::Id, identifyAttrs, nullptr, nullptr, nullptr, 0),
    // // DECLARE_DYNAMIC_CLUSTER(Descriptor::Id, descriptorAttrs, nullptr, nullptr, nullptr, 0),
    // // DECLARE_DYNAMIC_CLUSTER(BridgedDeviceBasicInformation::Id, bridgedDeviceBasicAttrs, nullptr, nullptr, eventsBrigde, ArraySize(eventsBrigde)),
    // // // DECLARE_DYNAMIC_CLUSTER_CLIENT(Groups::Id, groupsAttrs, nullptr, nullptr),
    // // // DECLARE_DYNAMIC_CLUSTER_CLIENT(Scenes::Id, scenesAttrs, nullptr, nullptr),
    // // DECLARE_DYNAMIC_CLUSTER(TemperatureMeasurement::Id, temperatureAttrs, nullptr, nullptr),
    // //     DECLARE_DYNAMIC_CLUSTER_LIST_END;


    // // DECLARE_DYNAMIC_CLUSTER_LIST_BEGIN(bridgedHumidityClusters)
    // // DECLARE_DYNAMIC_CLUSTER(Identify::Id, identifyAttrs, nullptr, nullptr, nullptr, 0),
    // // DECLARE_DYNAMIC_CLUSTER(Descriptor::Id, descriptorAttrs, nullptr, nullptr, nullptr, 0),
    // // DECLARE_DYNAMIC_CLUSTER(BridgedDeviceBasicInformation::Id, bridgedDeviceBasicAttrs, nullptr, nullptr, eventsBrigde, ArraySize(eventsBrigde)),
    // // // DECLARE_DYNAMIC_CLUSTER_CLIENT(Groups::Id, groupsAttrs, nullptr, nullptr),
    // // // DECLARE_DYNAMIC_CLUSTER_CLIENT(Scenes::Id, scenesAttrs, nullptr, nullptr),
    // // DECLARE_DYNAMIC_CLUSTER(RelativeHumidityMeasurement::Id, humidityAttrs, nullptr, nullptr),
    // //     DECLARE_DYNAMIC_CLUSTER_LIST_END;

    // /**
    //  * @brief Create Switchs Endpoint
    //  * 
    //  */
    // DECLARE_DYNAMIC_ENDPOINT(bridgedOnOffSwitchEndpoint, bridgedOnOffSwitchClusters);
    // DataVersion gOnOffSwitchDataVersions[ArraySize(bridgedOnOffSwitchClusters)];


    // DECLARE_DYNAMIC_ENDPOINT(bridgedColorDimmerSwitchEndpoint, bridgedColorDimmerSwitchClusters);
    // DataVersion gColorDimmerSwitchDataVersions[ArraySize(bridgedColorDimmerSwitchClusters)];

    // /**
    //  * @brief Create Lights Endpoint
    //  * 
    //  */
    // DECLARE_DYNAMIC_ENDPOINT(bridgedTempLightEndpoint, bridgedTempLightClusters);
    // DataVersion gTempLightDataVersions[ArraySize(bridgedTempLightClusters)];

    // DECLARE_DYNAMIC_ENDPOINT(bridgedExtendedLightEndpoint, bridgedExtendedLightClusters);
    // DataVersion gExtendedLightDataVersions[ArraySize(bridgedExtendedLightClusters)];

// } // namespace
