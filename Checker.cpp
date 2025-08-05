#include <iostream>
#include <vector>
#include <functional>
#include <assert.h>
#include <cfloat>
using namespace std;

struct BatteryParameter {
    float value;
    bool checkMin;
    float min;
    bool checkMax;
    float max;
    const char* outOfRangeMsg;
};

bool checkParameter(const BatteryParameter& param) {
    if(param.checkMin) {
        if(param.value < param.min) {
            cout << param.outOfRangeMsg << endl;
            return false;
        }
    }
    if(param.checkMax) {
        if(param.value > param.max) {
            cout << param.outOfRangeMsg << endl;
            return false;
        }
    }
    return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    vector<BatteryParameter> params = {
        {temperature, true, 0, true, 45, "Temperature out of range!"},
        {soc, false, 0, true, 80, "State of Charge out of range"},
        {chargeRate, true, 0, true, 0.8, "Charge Rate out of range!"}
    };
    for(const auto& param : params) {
        if(!checkParameter(param)) {
            return false;
        }
    }
    return true;
}

int main() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
}
