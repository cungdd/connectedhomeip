
#include <iostream> 
#include <fstream>
#include <string.h>
#include <jsoncpp/json/json.h>
#include <vector>
#include <stdint.h>

#define PATH_DEVICE_LIST        "/var/tmp/list-device.json"
#define PATH_DEVICE_ID          "/var/tmp/device-type-id.json"
#define PATH_HC_INFORMATION     "/var/tmp/hc-infomation.json"

#define RD_SWITCH           22014
#define RD_LIGHTING         12013
#define RD_REMOTE           23001
#define RD_RGB_LIGHT        14001

using namespace std;

typedef struct
{ 
    string DeviceID = "";
	unsigned int EndpointID;
	unsigned int DeviceTypeID;
	string ProductName;
    string SerialNumber = "12345678";
    string VendorName = "Rang Dong";
    string Version = "1.0";
    string NodeLabel = "";
    bool reachable = false;
    unsigned int VendorID = 0x141B;
    unsigned int HomeCenterID = 0x0000;

}DeviceInformation;

struct ColorTemperatureLight
{
    unsigned int Endpoint = 0;
    bool OnOff = false;
    unsigned int Dim = 0;
    unsigned int CCT = 0;
};

struct ExtendedLight{
    unsigned int Endpoint = 0;
    bool OnOff = false;
    unsigned int Dim = 0;
    unsigned int Hue = 0;
    unsigned int Saturation = 0;
    unsigned int Lightness = 0;
};

struct OnOffSwitch
{
    unsigned int Endpoint = 0;
    bool OnOff = false;
};

struct DimmerSwitch{
    unsigned int Endpoint = 0;
    unsigned int Dim = 0;
    bool OnOff = false;
};

struct ColorDimmerSwitch
{
    unsigned int Endpoint = 0;
    bool OnOff = false;
    unsigned int Dim = 0;
    unsigned int Color = 0;
};


class DeviceRD
{
    private:
        /*
            Infomation Device Matter
        */
        vector <DeviceInformation> devices;
        // BridgedDeviceInformation bridgedevice;

        // Devices filtered by types
        vector <ColorTemperatureLight> colorTemperatureLight;
        vector <ExtendedLight> extendedLight;
        vector <DimmerSwitch> dimmerSwitch;
        vector <ColorDimmerSwitch> colorDimmerSwitch;
        vector <OnOffSwitch> onoffSwitch;
        
        // List ID Lighting
        vector <unsigned int> colorTempLightListID;
        vector <unsigned int> colorRGBLightListID;

        // List ID Switch
        vector <unsigned int> singleSwitchListID;
        vector <unsigned int> doubleSwitchListID;
        vector <unsigned int> tripleSwitchListID;
        vector <unsigned int> quadraSwitchListID;
        vector <unsigned int> colordimmerSwitchListID;

        bool readFile(Json::Value * _value, string path);
        bool writeFile(void); 

        Json::Value deviceToJson(DeviceInformation * device); 
        void jsonToDevice(Json::Value * value, DeviceInformation * device);

        // find type device by Endpoint
        ColorTemperatureLight * findColorTemperatureLight(unsigned int endpoint);
        ExtendedLight * findExtendedLight(unsigned int endpoint);

        OnOffSwitch * findLightSwitch(unsigned int endpoint);
        DimmerSwitch * findDimmerSwitch(unsigned int endpoint);
        ColorDimmerSwitch * findColorDimmerSwitch(unsigned int endpoint);
        
        void addDeviceWithType(DeviceInformation * deviceInformation);
        void removeDeviceWithType(DeviceInformation * deviceInformation);
    public:
        bool Init(void);
        void Reset(void);
        void GetAllDevice(void);
        unsigned int GetNumberDevices(void);
        bool AddDevice(DeviceInformation device);

        DeviceInformation * GetDeviceWithEndpoint(unsigned int endpoint);
        DeviceInformation * GetDeviceWithIndex(unsigned int index);
        DeviceInformation * GetDeviceWithID(string deviceID);

        // BridgedDeviceInformation * GetBridgedDevice(void);

        bool RemoveDeviceWithEndpoint(unsigned int endpoint);

        // Update value 
        void UpdateOnOffLight(string deviceID, bool onOff);
        void UpdateDimLight(string deviceID, unsigned int dim);
        void UpdateCctLight(string deviceID, unsigned int cct);
        void UpdateHueLight(string deviceID, unsigned int hue);
        void UpdateSaturationLight(string deviceID, unsigned int saturation);
        void UpdateLightnessLight(string deviceID, unsigned int lightness);
        void UpdateOnOffSwitch(string deviceID, bool onoff);
        void UpdateDimmerSwitch(string deviceID, unsigned int dim);
        void UpdateColorDimmerSwitch(string deviceID, unsigned int color);
        
        // Update name
        void UpdateNameWithID(string deviceID, string name);
        void UpdateNodeLabelWithEndpoint(unsigned int endpoint, string name);

        // Get value of Device
        bool            GetOnOffLight(unsigned int endpoint);
        unsigned int    GetDimLight(unsigned int endpoint); 
        unsigned int    GetCctLight(unsigned int endpoint);
        unsigned int    GetHueLight(unsigned int endpoint);
        unsigned int    GetSaturationLight(unsigned int endpoint);
        unsigned int    GetLightnessLight(unsigned int endpoint);
        bool            GetOnOffSwitch(unsigned int endpoint);
        unsigned int    GetDimmerSwitch(unsigned int endpoint);
        unsigned int    GetColorDimmerSwitch(unsigned int endpoint);

        // Check Device
        bool isColorTempLight(unsigned int deviceTypeID);
        bool isExtendedLight(unsigned int deviceTypeID);

        bool isSingleSwitch(unsigned int deviceTypeID);
        bool isDoubleSwitch(unsigned int deviceTypeID);
        bool isTripleSwitch(unsigned int deviceTypeID);
        bool isQuadraSwitch(unsigned int deviceTypeID);
        bool isColorDimmerSwitch(unsigned int deviceTypeID);
};
