 class Customer {
     public:
     int id;
     string mobileNumber;
     string name;
     string password;
     Vehicle vehicle;
 };
 class Vehicle {
     public:
     int id;
     string number;
     int length;
     int width;
 };
 class Floor {
     public:
     int id;
     int floorNumber;
     vector<Slot> slots;
     int x;
     int y;
 };
 class Slot {
     public:
     int id;
     bool isAvailable;
     int length;
     int width;
     int customerId;
     int floorNumber;
     int pricePerHour;
     int x;
     int y;
 };
 class ParkingLotSystem {
     public:

     map<string, Customer> customerDb;
     vector<Floor>floors;
     map<int, Slot>slotDb;
     map<int,int>slotPrice;

     ParkingLotSystem() {
         customerDb = map<string, Customer> ();
     }
     // login/signup service;

     void checkAuth(string mobileNumer) {
         if (customerDb.count(mobileNumer) > 0) {
             login(mobileNumer);
             return;
         }
         signup(mobileNumer);
     }

     string login(string mobileNumer, int cnt = 5) {
         if (cnt < 0) {
             return "Try again after some time";
         }
         string pass;
         cout<<"Enter Password : "<<endl;
         cin>>pass;

         Customer customer = customerDb[mobileNumer];

         if (customer.getPassword() == pass) {
             return "Login Successful!!";
         }

         return login(mobileNumer, cnt - 1);
     }

     string signup(string mobileNumber) {
         Customer customer;
         customer.setMobileNumber(mobileNumber);
         cout<<"Enter Your Name: "<<endl;
         string name;
         cin>>name;
         customer.setName(name);
         cout<<"Set Password: "<<endl;
         string pass;
         cin>>pass;
         customer.setPassword(pass);
         Vehicle vehicle;
         cout<<"Enter Vehicle Number: "<<endl;
         string vehicleNumber;
         cin>>vehicleNumber;
         vehicle.setVehicleNumber(vehicleNumber);
         cout<<"Enter Vehicle Length And Width: "<<endl;
         int l,w;
         cin>>l>>w;
         vehicle.setLength(l);
         vehicle.setWidth(w);
         customer.setVehicle(vehicle);
         customerDb[mobileNumber]=customer;
         return "Sign Up Successful ";
     }
     map<Slot, int> showAvailableSlots(Customer customer){
         cout<<"In Which Floor You Want to see Slots: "<<endl;
         int floorNumber;
         cin>>floorNumber;
         cout<<"Number of hours for parking :"<<endl;
         int numberOfHours;
         cin>>numberOfHours;
         vector<Slot>slots=floors[floorNumber].getSlots();

         map<Slot, int> availableSlotsWithPrice;

         for (auto slot : slots) {
             if (!slot.getIsAvailable) continue;

             int vehicleLen = customer.getVehicle().getLength();
             int vehiclewidth = customer.getVehicle().getWidth();
             int slotLen = slot.getLength();
             int slotWidth = slot.getWidth();

             if (slotLen >= vehicleLen && slotWidth >= vehiclewidth) {
                 availableSlotsWithPrice[slot] = slot.getPricePerHour() * numberOfHours;
                 slotPrice[slot.getSlotId] = slot.getPricePerHour() * numberOfHours;
             }
         }
         return availableSlotsWithPrice;
     }

     string book(int slotId,int customerId){
         Slot slot=slotDb[slotId];
         slotDb.erase(slotId);
         slot.setIsAvailable(false);
         slot.setCustomerId(customerId);
         slotDb[slotId]=slot;
         return "Slot Booked Successfully";
     }
     string checkoutSlot(int slotId,int customerId){
         Slot slot=slotDb[slotId];
         slotDb.erase(slotId);
         slot.setIsAvailable(true);
         slot.setCustomerId(NULL);
         slotDb[slotId]=slot;
         int price=slotPrice[slotId];
         slotPrice.erase(slotId);
         return "Checkout Successfully : Total Amount to Pay"+to_string(price);
     }

 };
