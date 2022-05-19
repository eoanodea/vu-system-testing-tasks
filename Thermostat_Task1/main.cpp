
int main(){
    initDisplay();
    DigitalOut redLed(PTB2);
    DigitalOut greenLed(PTB3);
    PwmOut heaterPower(PTC2);

    while (true){
        float const temperature = readTemperature(); //reading temperature by converting 16 bit value

        if temperature >= -10
            bool sensorPresent = true;
        else
            bool sensorPresent = false;
        constexpr float minAllowedTemp = 30.0f;
        constexpr float minAllowedTemp = 35.0f;
        if (sensorPresent && temperature >= minAllowedTemp && temperature <= minAllowedTemp) // both 30 and 35 also include in bindery  30<= temperature <=35
            bool isTemperatureRange = true;
        else
            bool isTemperatureRange = false;
        constexpr float averageRangeTemperature = 32.5f; // This number use to keep temperature in the middle of allowed range

        if (sensorPresent && temperature < averageRangeTemperature)
           heaterPower = true;
        else
           heaterPower = false;

        if (temperature>35)
            bool overHeating  = true;
        else
            bool overHeating  = false;


        if(heaterPower == true) ////The red LED is ON when heating system is working.
            redLed = true;
        else //The red LED is PFF when heating systme is not working
            redLed = false;
        if(isTemperatureRange == true) //The green LED is ON when the measured temperature is in the specified range.
            greenLed = true;
        else //The green LED is OFF when the measured temperature is in not the specified range.
            greenLed = false;
        if(overHeating == true)
            heaterPower = false;

        if (temperature>=-10.0f)  //FR-02-Display Temperature: The program has an option to show the plate's temperature with a heating sensor and display it on an LCD display for users.
            displaySensorTemperature(temperature);
        else //FR-07-Heating Sensor: It is expected that the system will be protected for the condition that the heating sensors is absent.
            displayErrorMessage("Temperature sensor is absent.");
        ThisThread::sleep_for(500ms);
    }
}
