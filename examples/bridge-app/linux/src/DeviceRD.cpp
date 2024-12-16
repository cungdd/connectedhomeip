#include "DeviceRD.h"

void DeviceRD::addDeviceWithType(DeviceInformation * deviceInformation){

  if(deviceInformation->DeviceTypeID == 0x010C){ 
    ColorTemperatureLight _colorTemperatureLight;
    _colorTemperatureLight.Endpoint = deviceInformation->EndpointID;
    this->colorTemperatureLight.push_back(_colorTemperatureLight);
  }
  else if(deviceInformation->DeviceTypeID == 0x10D){
    ExtendedLight _extendedLight;
    _extendedLight.Endpoint = deviceInformation->EndpointID;
    this->extendedLight.push_back(_extendedLight);
  }
  else if(deviceInformation->DeviceTypeID == 0x103){
    OnOffSwitch _lightSwitch;
    _lightSwitch.Endpoint = deviceInformation->EndpointID;
    this->onoffSwitch.push_back(_lightSwitch);
  }
  else if(deviceInformation->DeviceTypeID == 0x104){
    DimmerSwitch _dimmerSwitch;
    _dimmerSwitch.Endpoint = deviceInformation->EndpointID;
    this->dimmerSwitch.push_back(_dimmerSwitch);
  }
  else if(deviceInformation->DeviceTypeID == 0x105){
    ColorDimmerSwitch _colorDimmerSwitch;
    _colorDimmerSwitch.Endpoint = deviceInformation->EndpointID;
    this->colorDimmerSwitch.push_back(_colorDimmerSwitch);
  }

}

bool DeviceRD::readFile(Json::Value * _value, string path){
  ifstream fileJson(path, ifstream::binary);
  
  if(!fileJson.is_open())
    return false;

  fileJson >> (*_value);
  fileJson.close();
  return true;
}

Json::Value DeviceRD::deviceToJson(DeviceInformation * device){
  Json::Value deviceJson;
  deviceJson["VendorName"] = device->VendorName;
  deviceJson["VendorID"] = device->VendorID;
  deviceJson["ProductName"] = device->ProductName;
  deviceJson["SerialNumber"] = device->SerialNumber; 
  deviceJson["EndpointID"] = device->EndpointID;
  deviceJson["DeviceTypeID"] = device->DeviceTypeID;
  deviceJson["DeviceID"] = device->DeviceID;
  deviceJson["Version"] = device->Version;
  deviceJson["HomeCenterID"] = device->HomeCenterID;
  deviceJson["NodeLabel"] = device->NodeLabel;
  return deviceJson;
}

void DeviceRD::removeDeviceWithType(DeviceInformation * deviceInformation){

  if(deviceInformation->DeviceTypeID == 0x010C){ 

    for(auto j = this->colorTemperatureLight.begin(); j != this->colorTemperatureLight.end(); ++j){
      if((*j).Endpoint == deviceInformation->EndpointID){
        this->colorTemperatureLight.erase(j);
        break;
      }
    }

  }
  else if(deviceInformation->DeviceTypeID == 0x10D){
    for(auto j = this->extendedLight.begin(); j != this->extendedLight.end(); ++j){
      if((*j).Endpoint == deviceInformation->EndpointID){
        this->extendedLight.erase(j);
        break;
      }
    }
  }
  else if(deviceInformation->DeviceTypeID == 0x103){

    for(auto j = this->onoffSwitch.begin(); j != this->onoffSwitch.end(); ++j){
      if((*j).Endpoint == deviceInformation->EndpointID){
   
        this->onoffSwitch.erase(j);
        break;
          
      }
    }

  }
  else if(deviceInformation->DeviceTypeID == 0x104){

    for(auto j = this->dimmerSwitch.begin(); j != this->dimmerSwitch.end(); ++j){
   
      if( (*j).Endpoint == deviceInformation->EndpointID){
      
        this->dimmerSwitch.erase(j);
        break;
      }
    }

  }
  else if(deviceInformation->DeviceTypeID == 0x105){
    
    for(auto j = this->colorDimmerSwitch.begin(); j != this->colorDimmerSwitch.end(); ++j){
      if( (*j).Endpoint == deviceInformation->EndpointID){

        this->colorDimmerSwitch.erase(j);
        break;
      }
    }

  }
}

void DeviceRD::jsonToDevice(Json::Value * _value, DeviceInformation * device){
  device->DeviceTypeID = (*_value)["DeviceTypeID"].asInt();
  device->EndpointID = (*_value)["EndpointID"].asInt();
  device->ProductName = (*_value)["ProductName"].asString();
  device->SerialNumber = (*_value)["SerialNumber"].asString();
  device->VendorName = (*_value)["VendorName"].asString();
  device->VendorID = (*_value)["VendorID"].asInt();
  device->DeviceID = (*_value)["DeviceID"].asString();
  device->Version = (*_value)["Version"].asString();
  device->NodeLabel = (*_value)["NodeLabel"].asString();
  device->HomeCenterID = (*_value)["HomeCenterID"].asUInt();
}

bool DeviceRD::writeFile(void){
  ofstream file(PATH_DEVICE_LIST);
  if(!file.is_open())
    return false;
  Json::StyledWriter styleWriter;

  Json::Value value;

  for(unsigned int i = 0; i < this->devices.size(); i++){
    value.append(this->deviceToJson(&this->devices[i]));
  }

  file << styleWriter.write(value);
  file.close();

  return true;
}

void DeviceRD::GetAllDevice(void){

  for(unsigned int i = 0; i < this->colorTemperatureLight.size(); i++){
    cout << "" << endl;
    cout << "Endpoint:" << this->colorTemperatureLight[i].Endpoint << endl;
    cout << "OnOff:" << this->colorTemperatureLight[i].OnOff << endl;
    cout << "Dim:" << this->colorTemperatureLight[i].Dim << endl;
    cout << "CTT:" << this->colorTemperatureLight[i].CCT << endl;
    cout << "" << endl;
  }

  for(unsigned int i = 0; i < this->extendedLight.size(); i++){
    cout << "" << endl;
    cout << "Endpoint:" << this->extendedLight[i].Endpoint << endl;
    cout << "OnOff:" << this->extendedLight[i].OnOff << endl;
    cout << "Dim:" << this->extendedLight[i].Dim << endl;
    cout << "Hue:" << this->extendedLight[i].Hue << endl;
    cout << "Saturation:" << this->extendedLight[i].Saturation << endl;
    cout << "Lightness:" << this->extendedLight[i].Lightness << endl;
    cout << "" << endl;
  }

  for(unsigned int i = 0; i < this->onoffSwitch.size(); i++){
    cout << "" << endl;
    cout << "Endpoint:" << this->onoffSwitch[i].Endpoint << endl;
    cout << "OnOff:" << this->onoffSwitch[i].OnOff << endl;
    cout << "" << endl;
  }

  for(unsigned int i = 0; i < this->dimmerSwitch.size(); i++){
    cout << "" << endl;
    cout << "Endpoint:" << this->dimmerSwitch[i].Endpoint << endl;
    cout << "Dim:" << this->dimmerSwitch[i].Dim << endl;
    cout << "" << endl;
  }

  for(unsigned int i = 0; i < this->colorDimmerSwitch.size(); i++){
    cout << "" << endl;
    cout << "Endpoint:" << this->colorDimmerSwitch[i].Endpoint << endl;
    cout << "Color:" << this->colorDimmerSwitch[i].Color << endl;
    cout << "Dimmer:" << this->colorDimmerSwitch[i].Dim << endl;
    cout << "OnOff:" << this->colorDimmerSwitch[i].OnOff << endl;
    cout << "" << endl;
  }
}

bool DeviceRD::Init(void){
  Json::Value value; 
  DeviceInformation deviceInformation;
  if(this->readFile(&value, PATH_DEVICE_LIST)){
    for(unsigned int i = 0; i < value.size(); i++){
      this->jsonToDevice(&value[i], &deviceInformation);
      this->addDeviceWithType(&deviceInformation);
      this->devices.push_back(deviceInformation);
    }
  }
   
  this->GetAllDevice();

  if(!this->readFile(&value, PATH_DEVICE_ID))
    return false;

  for(unsigned int i = 0; i < value["ColorTemperatureLight"].size() ; i++){
    this->colorTempLightListID.push_back(value["ColorTemperatureLight"][i].asInt());
  }

  for(unsigned int i = 0; i < value["RGBLight"].size() ; i++){
    this->colorRGBLightListID.push_back(value["RGBLight"][i].asInt());
  }

  for(unsigned int i = 0; i < value["SingleSwitch"].size() ; i++){
    this->singleSwitchListID.push_back(value["SingleSwitch"][i].asInt());
  }

  for(unsigned int i = 0; i < value["DoubleSwitch"].size() ; i++){
    this->doubleSwitchListID .push_back(value["DoubleSwitch"][i].asInt());
  }

  for(unsigned int i = 0; i < value["TripleSwitch"].size() ; i++){
    this->tripleSwitchListID.push_back(value["TripleSwitch"][i].asInt());
  }

  for(unsigned int i = 0; i < value["QuadraSwitch"].size() ; i++){
    this->quadraSwitchListID.push_back(value["QuadraSwitch"][i].asInt());
  }

  for(unsigned int i = 0; i < value["ColorDimmerSwitch"].size() ; i++){
    this->colordimmerSwitchListID.push_back(value["ColorDimmerSwitch"][i].asInt());
  }

  if(!this->readFile(&value, PATH_HC_INFORMATION))
    return false;
  
  return true;
}

bool DeviceRD::AddDevice(DeviceInformation deviceInformation){
  this->addDeviceWithType(&deviceInformation);
  devices.push_back(deviceInformation);
  // this->GetAllDevice();
  return this->writeFile();  
}

bool DeviceRD::RemoveDeviceWithEndpoint(unsigned int endpoint){
  for(auto i = this->devices.begin(); i != this->devices.end(); ++i){
    if( (*i).EndpointID == endpoint){
      this->removeDeviceWithType( &(*i));
      this->devices.erase(i);
      break;
    }
  }
  return this->writeFile();
}

void DeviceRD::Reset(void){
  this->devices.clear();
  this->writeFile();
}

DeviceInformation * DeviceRD::GetDeviceWithEndpoint(unsigned int endpoint){
  for(unsigned  int i = 0; i < this->devices.size(); i++){
    if(this->devices[i].EndpointID == endpoint){
      return &this->devices[i];
    }
  }

  return nullptr;
}

DeviceInformation * DeviceRD::GetDeviceWithIndex(unsigned int index){
  return &this->devices[index];
}

DeviceInformation * DeviceRD::GetDeviceWithID(string deviceID){
  for( unsigned int i = 0; i < this->devices.size(); i++){
    if(this->devices[i].DeviceID.compare(deviceID) == 0){
      return &(this->devices[i]);
    }
  }
  return nullptr;
}

unsigned int DeviceRD::GetNumberDevices(void){
  return (unsigned int)this->devices.size();
}

void DeviceRD::UpdateNameWithID(string deviceID, string name){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;
  _deviceInformation->ProductName = name;
  this->writeFile();
}

void DeviceRD::UpdateNodeLabelWithEndpoint(unsigned int endpoint, string name){
  DeviceInformation * _deviceInformation = this->GetDeviceWithEndpoint(endpoint);
  if(_deviceInformation == nullptr) 
    return;
  _deviceInformation->NodeLabel = name;
  this->writeFile();
}

void DeviceRD::UpdateOnOffLight(string deviceID, bool onOff){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;

  if(_deviceInformation->DeviceTypeID == 0x10C){
    ColorTemperatureLight * _colorTemperatureLight = this->findColorTemperatureLight(_deviceInformation->EndpointID);
    _colorTemperatureLight->OnOff = onOff;
  }
  else if(_deviceInformation->DeviceTypeID == 0x10D){
    ExtendedLight * _extendedLight = this->findExtendedLight(_deviceInformation->EndpointID);
    _extendedLight->OnOff = onOff;
  }

  _deviceInformation->reachable = true;
}

void DeviceRD::UpdateDimLight(string deviceID, unsigned int dim){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;
  if(_deviceInformation->DeviceTypeID == 0x10C){
    ColorTemperatureLight * _colorTemperatureLight = this->findColorTemperatureLight(_deviceInformation->EndpointID);
    _colorTemperatureLight->Dim = dim;
  }
  else if(_deviceInformation->DeviceTypeID == 0x10D){
    ExtendedLight * _extendedLight = this->findExtendedLight(_deviceInformation->EndpointID);
    _extendedLight->Dim = dim;
  }

  _deviceInformation->reachable = true;
}

void DeviceRD::UpdateCctLight(string deviceID, unsigned int cct){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;
  ColorTemperatureLight * _colorTemperatureLight = this->findColorTemperatureLight(_deviceInformation->EndpointID);
  _colorTemperatureLight->CCT = cct;

  _deviceInformation->reachable = true;
}

void DeviceRD::UpdateHueLight(string deviceID, unsigned int hue){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;
  ExtendedLight * _extendedLight = this->findExtendedLight(_deviceInformation->EndpointID);
  _extendedLight->Hue = hue;
  _deviceInformation->reachable = true;
}

void DeviceRD::UpdateSaturationLight(string deviceID, unsigned int saturation){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;
  ExtendedLight * _extendedLight = this->findExtendedLight(_deviceInformation->EndpointID);
  _extendedLight->Saturation = saturation;
  _deviceInformation->reachable = true;
}

void DeviceRD::UpdateLightnessLight(string deviceID, unsigned int lightness){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;
  ExtendedLight * _extendedLight = this->findExtendedLight(_deviceInformation->EndpointID);
  _extendedLight->Lightness = lightness;
  _deviceInformation->reachable = true;
}

void DeviceRD::UpdateOnOffSwitch(string deviceID, bool currentPosition){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;

  if(_deviceInformation->DeviceTypeID == 0x105){
    ColorDimmerSwitch * _colorDimmerSwitch = this->findColorDimmerSwitch(_deviceInformation->EndpointID);
    _colorDimmerSwitch->OnOff = currentPosition;
  }
  else if(_deviceInformation->DeviceTypeID == 0x103){
    OnOffSwitch * _onoffSwitch = this->findLightSwitch(_deviceInformation->EndpointID);
    _onoffSwitch->OnOff = currentPosition;
  }
  _deviceInformation->reachable = true;
}

void DeviceRD::UpdateDimmerSwitch(string deviceID, unsigned int dim){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;

  if(_deviceInformation->DeviceTypeID == 0x105){
    ColorDimmerSwitch * _colorDimmerSwitch = this->findColorDimmerSwitch(_deviceInformation->EndpointID);
    _colorDimmerSwitch->Dim = dim;
  }
  else if(_deviceInformation->DeviceTypeID == 0x104){
    DimmerSwitch * _dimSwitch = this->findDimmerSwitch(_deviceInformation->EndpointID);
    _dimSwitch->Dim = dim;
  }
  _deviceInformation->reachable = true;
}

void DeviceRD::UpdateColorDimmerSwitch(string deviceID, unsigned int color){
  DeviceInformation * _deviceInformation = this->GetDeviceWithID(deviceID);
  if(_deviceInformation == nullptr) 
    return;
  ColorDimmerSwitch * _colorSwitch = this->findColorDimmerSwitch(_deviceInformation->EndpointID);
  _colorSwitch->Color = color;
  _deviceInformation->reachable = true;
}

bool DeviceRD::GetOnOffSwitch(unsigned int endpoint){
  DeviceInformation * _deviceInformation = this->GetDeviceWithEndpoint(endpoint);

  uint8_t onoff  = 0;
  if(_deviceInformation->DeviceTypeID == 0x103){
    OnOffSwitch * _onoffSwitch = this->findLightSwitch(endpoint);
    onoff = _onoffSwitch->OnOff;
  }
  else if(_deviceInformation->DeviceTypeID == 0x104){
    DimmerSwitch * _dimmerSwitch = this->findDimmerSwitch(endpoint);
    onoff = _dimmerSwitch->OnOff;
  }
  else if(_deviceInformation->DeviceTypeID == 0x105){
    ColorDimmerSwitch * _colordimmerSwitch = this->findColorDimmerSwitch(endpoint);
    onoff = _colordimmerSwitch->OnOff;
  }
  
  return onoff;
}

unsigned int DeviceRD::GetDimmerSwitch(unsigned int endpoint){
  DeviceInformation * _deviceInformation = this->GetDeviceWithEndpoint(endpoint);

  unsigned int dim = 0;
  if(_deviceInformation->DeviceTypeID == 0x104){
    DimmerSwitch * _dimmerSwitch = this->findDimmerSwitch(endpoint);
    dim = _dimmerSwitch->Dim;
  }
  else if(_deviceInformation->DeviceTypeID == 0x105){
    ColorDimmerSwitch * _colordimmerSwitch = this->findColorDimmerSwitch(endpoint);
    dim = _colordimmerSwitch->Dim;
  }
  return dim;
}

unsigned int DeviceRD::GetColorDimmerSwitch(unsigned int endpoint){
  ColorDimmerSwitch * _colorSwitch = this->findColorDimmerSwitch(endpoint);
  return _colorSwitch->Color;
}

bool DeviceRD::GetOnOffLight(unsigned int endpoint){
  DeviceInformation * _deviceInformation = this->GetDeviceWithEndpoint(endpoint);
  bool onoff = 0;
  if(_deviceInformation->DeviceTypeID == 0x10C){
    onoff = this->findColorTemperatureLight(endpoint)->OnOff;
  }
  else if(_deviceInformation->DeviceTypeID == 0x10D){
    onoff = this->findExtendedLight(endpoint)->OnOff;
  }

  return onoff;
}

unsigned int DeviceRD::GetDimLight(unsigned int endpoint){
  DeviceInformation * _deviceInformation = this->GetDeviceWithEndpoint(endpoint);
  unsigned int dim = 0;
  if(_deviceInformation->DeviceTypeID == 0x10C){
    dim = this->findColorTemperatureLight(endpoint)->Dim;
  }
  else if(_deviceInformation->DeviceTypeID == 0x10D){
    dim = this->findExtendedLight(endpoint)->Dim;
  }
  return dim;
}

unsigned int DeviceRD::GetCctLight(unsigned int endpoint){
  return this->findColorTemperatureLight(endpoint)->CCT;
}

unsigned int DeviceRD::GetHueLight(unsigned int endpoint){
  return this->findExtendedLight(endpoint)->Hue;
}

unsigned int DeviceRD::GetSaturationLight(unsigned int endpoint){
  return this->findExtendedLight(endpoint)->Saturation;
}

unsigned int DeviceRD::GetLightnessLight(unsigned int endpoint){
  return this->findExtendedLight(endpoint)->Lightness;
}

ColorTemperatureLight * DeviceRD::findColorTemperatureLight(unsigned int endpoint){
  for(unsigned int i = 0; i < this->colorTemperatureLight.size(); i++){
    if(this->colorTemperatureLight[i].Endpoint == endpoint)
    {
      return &this->colorTemperatureLight[i];
    }
  }
  return nullptr;
}

ExtendedLight * DeviceRD::findExtendedLight(unsigned int endpoint){
  for(unsigned int i = 0; i < this->extendedLight.size(); i++){
    if(this->extendedLight[i].Endpoint == endpoint)
    {
      return &this->extendedLight[i];
    }
  }
  return nullptr;
}

OnOffSwitch * DeviceRD::findLightSwitch(unsigned int endpoint){
  for(unsigned int i = 0; i < this->onoffSwitch.size(); i++){
    if(this->onoffSwitch[i].Endpoint == endpoint)
    {
      return &this->onoffSwitch[i];
    }
  }
  return nullptr;
}

DimmerSwitch * DeviceRD::findDimmerSwitch(unsigned int endpoint){
  for(unsigned int i = 0; i < this->dimmerSwitch.size(); i++){
    if(this->dimmerSwitch[i].Endpoint == endpoint)
    {
      return &this->dimmerSwitch[i];
    }
  }
  return nullptr;
}

ColorDimmerSwitch * DeviceRD::findColorDimmerSwitch(unsigned int endpoint){
  for( unsigned int i = 0; i < this->colorDimmerSwitch.size(); i++){
    if(this->colorDimmerSwitch[i].Endpoint == endpoint)
    {
      return &this->colorDimmerSwitch[i];
    }
  }
  return nullptr;
}

bool DeviceRD::isColorTempLight(unsigned int deviceTypeID){
  for(unsigned int i = 0; i < this->colorTempLightListID.size(); i++){
    if(this->colorTempLightListID[i] == deviceTypeID)
      return true;
  }
  return false;
}

bool DeviceRD::isExtendedLight(unsigned int deviceTypeID){
  for(unsigned int i = 0; i < this->colorRGBLightListID.size(); i++){
    if(this->colorRGBLightListID[i] == deviceTypeID)
      return true;
  }
  return false;
}

bool DeviceRD::isTripleSwitch(unsigned int deviceTypeID){
  for(unsigned int i = 0; i < this->tripleSwitchListID.size(); i++){
    if(this->tripleSwitchListID[i] == deviceTypeID)
      return true;
  }
  return false;
}

bool DeviceRD::isSingleSwitch(unsigned int deviceTypeID){
  for(unsigned int i = 0; i < this->singleSwitchListID.size(); i++){
    if(this->singleSwitchListID[i] == deviceTypeID)
      return true;
  }
  return false;
}

bool DeviceRD::isDoubleSwitch(unsigned int deviceTypeID){
  for(unsigned int i = 0; i < this->doubleSwitchListID.size(); i++){
    if(this->doubleSwitchListID[i] == deviceTypeID)
      return true;
  }
  return false;
}

bool DeviceRD::isQuadraSwitch(unsigned int deviceTypeID){
  for(unsigned int i = 0; i < this->quadraSwitchListID.size(); i++){
    if(this->quadraSwitchListID[i] == deviceTypeID)
      return true;
  }
  return false;
}

bool DeviceRD::isColorDimmerSwitch(unsigned int deviceTypeID){
  for(unsigned int i = 0; i < this->colordimmerSwitchListID.size(); i++){
    if(this->colordimmerSwitchListID[i] == deviceTypeID)
      return true;
  }
  return false;
}