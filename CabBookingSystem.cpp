// LLd Of Cab Booking System
#include<bits/stdc++.h>
using namespace std;
// Entities
class User{
   private:
   int id;
   string name;
   string phoneNumber;
   string email;
   string password;
   pair<int,int>userLocation;
   public:
   pair<int,int>getUserLocation(){
      return this->userLocation;
   }
   string getPassword(){
      return this->password;
   }
   void setPassWord(string &newPassword){
      this->password=newPassword;
   }

   void setId(int idCount){
      this->id=idCount;
   }
   string getEmail(){
      return this->email;
   }
   void setEmail(string &newEmail){
      this->email=newEmail;
   }

   string getPhoneNumber(){
      return this->phoneNumber;
   }
   void setPhoneNumber(string &newPhoneNumber){
      this->phoneNumber=newPhoneNumber;
   }

};
class Vehicle {

};
class BikeRiders{
private:
    int id;
    string bikeRiderName;
    string mobileNumber;
    bool isAvailable;
    pair<int, int> riderLocation;
    Vehicle vehicle;

public:
    int getId()  {
        return this->id;
    }
    void setId(int id){
        this->id=id;
    }
    string getBikeRiderName(){
        return this->bikeRiderName;
    }
    void setBikeRiderName(string& bikeRiderName) {
        this->bikeRiderName=bikeRiderName;
    }
    string getMobileNumber(){
        return this->mobileNumber;
    }
    void setMobileNumber(string& mobileNumber) {
        this->mobileNumber=mobileNumber;
    }
    bool getIsAvailable() {
        return this->isAvailable;
    }
    void setIsAvailable(bool isAvailable) {
        this->isAvailable=isAvailable;
    }
    pair<int, int> getRiderLocation() {
        return this->riderLocation;
    }
    void setRiderLocation(pair<int,int>&riderLocation){
        this->riderLocation=riderLocation;
    }
    void setRiderLocation(int x,int y){
        this->riderLocation=make_pair(x,y);
    }
};

class ThreeWheelerRiders {
private:
    int id;
    string ThreeWheelerRiders;
    string ThreewheelerRidermobileNumber;
    bool IsAvailable;
    pair<int, int> ThreewheelerRiderLoction;

public:
   string getName(){
      return this->ThreeWheelerRiders;
    }
    int getId(){
      return this->id;
    }
    bool getIsAvailable(){
      return this->IsAvailable;
    }
    void setIsAvailable(bool isAvailable){
       this->IsAvailable=isAvailable;
    }
    pair<int,int>getThreewheelerRiderLoction() {
        return this->ThreewheelerRiderLoction;
    }
    void setThreewheelerRiderLoction(pair<int,int>&location) {
        this->ThreewheelerRiderLoction=location;
    }
    void setThreewheelerRiderLoction(int x, int y) {
        this->ThreewheelerRiderLoction = make_pair(x, y);
    }
};
class CabRiders{
      long id;
      string cabRiderName;
      string CabMobileNumber;
      bool IsAvailable;
      pair<int,int>CabRiderLoction;
   public:
    bool getIsAvailable(){
      return this->IsAvailable;
    }
    string getName(){
      return this->cabRiderName;
    }
    int getId(){
      return this->id;
    }
    void setIsAvailable(bool isAvailable){
       this->IsAvailable=isAvailable;
    }
    pair<int,int>getCabRiderLoctaion() {
        return this->CabRiderLoction;
    }
    void setCabRiderLocation(pair<int,int>&location) {
        this->CabRiderLoction=location;
    }
    void setCabRiderLocation(int x, int y) {
        this->CabRiderLoction = make_pair(x, y);
    }
};
/// MAIN CLASS ////
class CabBookingSystem{
   public:
   map<string,User>userDB;
   vector<ThreeWheelerRiders>threeWheelerRider;
   vector<CabRiders>cabRider;
   vector<BikeRiders>bikeRider;
   int failed=0;
   int idCounter=0;
   void checkCredential(User user){
      if(userDB.find(user.getPhoneNumber())!=userDB.end()){
         cout<<"User Alread Exist!"<<'\n';
         loginPage(user);
         return ;
      }
      signUp(user);
   }
   void loginPage(User user){
      string DbPassword=userDB[user.getPhoneNumber()].getPassword();
      if(user.getPassword()==DbPassword){
         cout<<"Login Success"<<'\n';
         UserInterface(user);
         return;
      }
      cout<<"Write the correct Password !!"<<'\n';
      failed++;
      if(failed<=5){
         string retryPassword;
         cout<<"Write Password Again"<<'\n';
         cin>>retryPassword;
         user.setPassWord(retryPassword);
         loginPage(user);
      }else{
         cout<<"Your Have Tried Many Times Kindly Try again later";
      }
   }
   void signUp(User user){
      user.setId(idCounter++);
      userDB[user.getPhoneNumber()]=user;
      cout<<"signUp successfull"<<endl;
      UserInterface(user);
   }
   int manhattenDistance(pair<int,int>userLoctation,pair<int,int>riderLocation){
      return abs(userLoctation.first-riderLocation.first)+abs(userLoctation.second-riderLocation.second);
   }
   void threeWheelerShow(User user){
      sort(threeWheelerRider.begin(),threeWheelerRider.end(),[&](ThreeWheelerRiders a,ThreeWheelerRiders b){
         pair<int,int>location1=a.getThreewheelerRiderLoction();
         pair<int,int>location2=b.getThreewheelerRiderLoction();
         int distance1=manhattenDistance(user.getUserLocation(),location1);
         int distance2=manhattenDistance(user.getUserLocation(),location2);
         return distance1<distance2;
      });
      for(int i=0;i<11;i++){
         if(threeWheelerRider[i].getIsAvailable()){
         cout<<"ThreeWheeler Rider is Available"<<endl;
         cout<<threeWheelerRider[i].getThreewheelerRiderLoction().first<<' '<<threeWheelerRider[i].getThreewheelerRiderLoction().second;
         }
      }
   }
   void bikeRiderShow(User user){
      // same as threewheeler
       sort(bikeRider.begin(),bikeRider.end(),[&](BikeRiders a,BikeRiders b){
         pair<int,int>location1=a.getRiderLocation();
         pair<int,int>location2=b.getRiderLocation();
         int distance1=manhattenDistance(user.getUserLocation(),location1);
         int distance2=manhattenDistance(user.getUserLocation(),location2);
         return distance1<distance2;
      });
      for(int i=0;i<11;i++){
         if(bikeRider[i].getIsAvailable()){
         cout<<"ThreeWheeler Rider is Available"<<endl;
         cout<<bikeRider[i].getRiderLocation().first<<' '<<bikeRider[i].getRiderLocation().second;
         }
      }
   }
   void cabShow(User user){
      // same as Bike rider
      // same as threewheeler
       sort(cabRider.begin(),cabRider.end(),[&](CabRiders a,CabRiders b){
         pair<int,int>location1=a.getCabRiderLoctaion();
         pair<int,int>location2=b.getCabRiderLoctaion();
         int distance1=manhattenDistance(user.getUserLocation(),location1);
         int distance2=manhattenDistance(user.getUserLocation(),location2);
         return distance1<distance2;
      });
      for(int i=0;i<11;i++){
         if(cabRider[i].getIsAvailable()){
         cout<<"ThreeWheeler Rider is Available"<<endl;
         cout<<cabRider[i].getCabRiderLoctaion().first<<' '<<cabRider[i].getCabRiderLoctaion().second;
         }
      }
   }
   void displayCost(User user,pair<int,int>dropCoordinates){
      pair<int,int>usercurrLoction;
      int distance=manhattenDistance(usercurrLoction,dropCoordinates);
      int cost=distance*10;// cost per km is 10rs
      cout<<"Ride Fare:"<<cost<<endl;
   }
   void showBookedDetailsCab(User user,CabRiders cabRider,pair<int,int>dropCoordinates){
      cabRider.setIsAvailable(false);
      cout<<"Ride Booked Successfully"<<'\n';
      cout<<"RiderId"<<cabRider.getId()<<endl;
      cout<<"Riders Name"<<cabRider.getName()<<endl;
      cout<<"Pick Up Location"<<user.getUserLocation().first<<' '<<user.getUserLocation().second<<endl;
      cout<<"Drop Location"<<dropCoordinates.first<<' '<<dropCoordinates.second<<endl;

   }
      void showBookedDetailsAuto(User user,ThreeWheelerRiders Autoo,pair<int,int>dropCoordinates){
      Autoo.setIsAvailable(false);
      cout<<"Ride Booked Successfully"<<'\n';
      cout<<"RiderId"<<Autoo.getId()<<endl;
      cout<<"Riders Name"<<Autoo.getName()<<endl;
      cout<<"Pick Up Location"<<user.getUserLocation().first<<' '<<user.getUserLocation().second<<endl;
      cout<<"Drop Location"<<dropCoordinates.first<<' '<<dropCoordinates.second<<endl;

   }
      void showBookedDetailsBike(User user,BikeRiders bikeRidee,pair<int,int>dropCoordinates){
      bikeRidee.setIsAvailable(false);
      cout<<"Ride Booked Successfully"<<'\n';
      cout<<"RiderId"<<bikeRidee.getId()<<endl;
      cout<<"Riders Name"<<bikeRidee.getBikeRiderName()<<endl;
      cout<<"Pick Up Location"<<user.getUserLocation().first<<' '<<user.getUserLocation().second<<endl;
      cout<<"Drop Location"<<dropCoordinates.first<<' '<<dropCoordinates.second<<endl;

   }
   void BookRideforCustomer(User user,bool isThreeW,bool isBike,bool isCab){
      cout<<"Give Drop Coordinates"<<'\n';
      pair<int,int>dropCoordinates;
      cin>>dropCoordinates.first>>dropCoordinates.second;;
      displayCost(user,dropCoordinates);
      bool bookRide;
      cin>>bookRide;
      if(bookRide){
         if(isCab){
            for(int i=0;i<20;i++){// request send to Cabrider is still not done
               if(cabRider[i].getIsAvailable()){
                  showBookedDetailsCab(user,cabRider[i],dropCoordinates);
                  break;
               }
            }
         }else if(isBike){
            for(int i=0;i<20;i++){// request send to Bikerider is still not done
               if(bikeRider[i].getIsAvailable()){
                  showBookedDetailsBike(user,bikeRider[i],dropCoordinates);
                  break;
               }
            }
         }else{
            for(int i=0;i<20;i++){// request send to Autorider is still not done
               if(threeWheelerRider[i].getIsAvailable()){
                  showBookedDetailsAuto(user,threeWheelerRider[i],dropCoordinates);
                  break;
               }
            }
         }
      }
   }
   void UserInterface(User user){
      pair<int,int>userCurrentLoction=user.getUserLocation();
      cout<<"Select One Vehicle Type"<<'\n';
      bool ThreeW,BikeR,Cab;
      cin>>ThreeW>>BikeR>>Cab;
      if(ThreeW){
         threeWheelerShow(user);
         BookRideforCustomer(user,true,false,false);
      }else if(BikeR){
          bikeRiderShow(user);
          BookRideforCustomer(user,false,true,false);
      }else{
         cabShow(user);
         BookRideforCustomer(user,false,false,true);
      }
   }
};