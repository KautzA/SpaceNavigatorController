//Menu Variables
#define NUM_MENUS 8

#define MENU_RUN 0
#define MENU_ROOT 1
#define MENU_SETTINGS 2
#define MENU_CONTROLLER 3
#define MENU_XBEE 4
#define MENU_BLUETOOTH 5
#define MENU_USBH 6
#define MENU_USBD 7

volatile uint8_t MenuSelect = 0; // Active menu
volatile uint8_t MenuItem = 0; // item of active menu
volatile boolean MenuItemSelect = 0; // select item from menu or modify item


//Controller Settings Menu Variables
volatile boolean CommanderPacketMode = COMMANNDER_MODE_EXTEND;
#define COMMANDER_MODE_DEFAULT 0
#define COMMANDER_MODE_EXTEND 1
volatile uint8_t CommandMap = COMMAND_MAP_DEFAULT;
#define COMMAND_MAP_MAX 0
#define COMMAND_MAP_DEFAULT 0

//Xbee Settings Menu Variables
volatile uint32_t XBmyAddrLow = 0;
volatile uint32_t XBmyAddrHigh = 0;
volatile uint32_t XBDestAddrLow = 0;
volatile uint32_t XBDestAddrHigh = 0;

volatile unsigned long PreviousUp = 0;
volatile unsigned long PreviousDown = 0;
volatile unsigned long PreviousLeft = 0;
volatile unsigned long PreviousRight = 0;
volatile unsigned long PreviousSelect = 0;

const String RUN_ENTRIES[1] = {
  "<-"};
const String ROOT_ENTRIES[2] = {
  "Run", "Settings"};
const String SETTINGS_ENTRIES[6] = {
  "<-", "Command", "Xbee", "Bluetooth", "USB-H", "USB-D"};
const String CONTROLLER_SETTINGS[3] = {
  "<-", "Extended?", "Map"};
const String XBEE_ENTRIES[8] = {
  "<-", "Test", "ID", "Address", "Destination", "Baudrate",  "Write", "SysBaud"};
const String BLUETOOTH_ENTRIES[7] = {
  "<-", "Test", "UpdateFields", "power", "Baudrate", "Connect?", "SysBaud"};
const String USBH_ENTRIES[4] = {
  "<-", "Reset", "Device"};
const String USBD_ENTRIES[3] = {
  "<-", "Serial", "Joystick"};



volatile uint8_t BluetoothPower = 0;
volatile uint8_t USBDeviceSerial;
volatile uint8_t USBDeviceJoystick;
volatile uint8_t ControllerCommanderMode;


const int MenuLimit[NUM_MENUS] = {
  0,//Run
  1,//Root
  5,//Settings
  2,//Controller
  7,//Xbee
  6,//Bluetooth
  2,//UsbH
  2//UsbD
};

//const int MenuLimit[NUM_MENUS] = {0, 1, 5, 2, 7, 6, 2, 2};//Run//Root//Settings//Controller//Xbee//Bluetooth//UsbH//UsbD


//Locations for EEPROM variables
#define CONTROLLER_COMMAND_MODE 0
#define USB_DEVICE_SERIAL 1
#define USB_DEVICE_JOYSTICK 2

/*
void TempValsReset(){
 ControllerCommanderMode = EEPROM.read(CONTROLLER_COMMANDER_MODE);
 USBDeviceSerial = EEPROM.read(USB_DEVICE_SERIAL);
 USBDeviceJoystick = EEPROM.read(USB_DEVICE_SERIAL);
 }
 */

void HandleUp(){
  if (PreviousUp - millis() > 100){
    PreviousUp = millis();
    if (MenuItemSelect == 0){//change item of menu
      if(MenuItem < MenuLimit[MenuSelect]){
        MenuItem += 1;
      }
      else{
        MenuItem = 0;
      }
    }
    else{//Change value of item
      HandleRight();//needs to be written
    }
  }
}

void HandleDown(){
  if (PreviousDown - millis() > 100){
    PreviousDown = millis();
    if (MenuItemSelect == 0){//change item of menu
      if(MenuItem > 0){
        MenuItem -= 1;
      }
      else{
        MenuItem = MenuLimit[MenuSelect];
      }
    }
    else{
      HandleLeft();// needs to be written
    }
  }
}

void HandleSelect(){
  if (PreviousSelect - millis() > 100){
    PreviousSelect = millis();
    HandleItem(0, 0, 1)
    }
  }

  void HandleLeft(){
    if (PreviousLeft - millis() > 100){
      PreviousLeft = millis();
      HandleItem(1, 0, 0)
      }
    }

  void HandleRight(){
    if (PreviousRight - millis() > 100){
      PreviousRight = millis();
      HandleItem(0, 1, 0)
      }
    }


    void HandleItem(boolean Left, boolean Right, boolean Select){
      switch (MenuSelect) {
      case MENU_RUN:
        RunItem(Left, Right, Select);
        break;
      case MENU_ROOT:
        RootItem(Left, Right, Select);
        break;
      case MENU_SETTINGS:
        SettingsItem(Left, Right, Select);
        break;
      case MENU_CONTROLLER:
        ControllerItem(Left, Right, Select);
        break;
      case MENU_XBEE:
        XbeeItem(Left, Right, Select);
        break;
      case MENU_BLUETOOTH:
        BluetoothItem(Left, Right, Select);
        break;
      case MENU_USBH:
        UsbHItem(Left, Right, Select);
        break;
      case MENU_USBD:
        UsbDItem(Left, Right, Select);
        break;
      }
  }

void RunItem(boolean Left, boolean Right, boolean Select){
  switch (MenuItem) {
  case 0://Return to root
    if(Right || Select){
      MenuSelect = MENU_ROOT;
    }
    break;
  }
}

void RootItem (boolean Left, boolean Right, boolean Select){
  switch (MenuItem) {
  case 0://go to run
    if(Right || Select){
      MenuSelect = MENU_RUN;
    }
    break;
  case 1://go to Settings
    if(Right || Select){
      MenuSelect = MENU_SETTINGS;
    }
    break;
  }
}

void SettingsItem (boolean Left, boolean Right, boolean Select){
  switch (MenuItem) {
  case 0://go to root
    if(Right || Select){
      MenuSelect = MENU_ROOT;
    }
    break;
  case 1://go to Controller
    if(Right || Select){
      MenuSelect = MENU_CONTROLLER;
    }
    break;
  case 2://go to XBee
    if(Right || Select){
      MenuSelect = MENU_XBEE;
    }
    break;
  case 3://go to Bluetooth
    if(Right || Select){
      MenuSelect = MENU_BLUETOOTH;
    }
    break;
  case 4://go to USB host
    if(Right || Select){
      MenuSelect = MENU_USBH;
    }
    break;
  case 5://go to USB device
    if(Right || Select){
      MenuSelect = MENU_USBD;
    }
    break;
  }
}

void ControllerItem (boolean Left, boolean Right, boolean Select){
  switch (MenuItem) {
  case 0://Settings
    if(Right || Select){
      MenuSelect = MENU_SETTINGS;
    }
    break;
  case 1://Extended Mode?
    if(Select){//switch to and from modifying item
      MenuItemSelect = !MenuItemSelect;
    }
    if(Left || Right){
      CommanderPacketMode = !CommanderPacketMode;
    }
    break;
  case 2://Control Map
    if(Select){
      MenuItemSelect = !MenuItemSelect;
    }
    if(Left){
      if(CommandMap == COMMAND_MAP_MAX){
        CommandMap = 0;
      }
      else{
        CommandMap += 1;
      }
    }
    if(Right){
      if(CommandMap == 0){
        CommandMap = COMMAND_MAP_MAX;
      }
      else{
        CommamdMap -= 1;
      }
    }
    break;
  }
}

void XbeeItem (boolean Left, boolean Right, boolean Select){
  switch (MenuItem) {
  case 0://Settings
    if(Right || Select){
      MenuSelect = MENU_SETTINGS;
    }
    break;
  case 1://test
    if(Left || Right || Select){//check for response
      //Thing here that tests for response and updates other variables
      MenuItemSelect = !MenuItemSelect; // used to display device ID
    }
    break;
  case 2://my ID?
    if(Left || Right || Select){//display last read ID
      MenuItemSelect = !MenuItemSelect; // used to display device ID
    }
    break;
  case 3://change destination address
    if(Select){//check for response
      MenuItemSelect = !MenuItemSelect;
    }
    if(Left){
      
    }
    if(Right){
      
    }
    break;
  }
}





