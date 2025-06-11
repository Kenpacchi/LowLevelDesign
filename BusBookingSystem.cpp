#include <bits/stdc++.h>
using namespace std;
class User{
   private:
   long id;
   string userName;
   string gender;
   string userMobileNumber;
   string userEmail;
   string userPassword;
   public:
   string getUserMobileNumber(){
      return userMobileNumber;
   }
   string getUserName(){
      return userName;
   }
   string getUserPassword(){
      return userPassword;
   }
   string getUserEmail(){
      return userEmail;
   }
};
class Bus{
   private:
   long id;
   string busNumber;
   string busName;
   string busBoardingLocation;
   string bustDroppingLocation;
   long busFareCost;
   vector<pair<string,bool>>busSeatsNumber;
   string busBoardingTime;
   string busDroppingTime;
   public:
   string getBoardingLocation(){
      return busBoardingLocation;
   }
   string getBusDroppingLocation(){
      return bustDroppingLocation;
   }
   long getbusFareCost(){
      return busFareCost;
   }
   string getBoardingTime(){
      return busBoardingTime;
   }
   string getDroppingTime(){
      return busDroppingTime;
   }
   string getBusName(){
      return busName;
   }
   vector<pair<string,bool>>getBusSeat(){
      return busSeatsNumber;
   }
   string getBusNumber(){
      return busNumber;
   }
};
// Main Class
class BusTicketBookingSystem{
   public:
   map<string,User>userDb;
   map<pair<string,string>,vector<Bus>>buses;
   long idcounter=0;
   long failedCounter=0;
   //service :: Login?signup
   void checkIfUserExists(User user){
      string userGivenPhoneNumber=user.getUserMobileNumber();
      if(userDb.find(userGivenPhoneNumber)!=userDb.end()){
         cout<<"User Already Exist"<<'\n';
         loginPage(user,userGivenPhoneNumber);
         return;
      }
      signupPage(user,userGivenPhoneNumber);
   }
   void loginPage(User user,string phoneNumber){
      string userGivenPassword=user.getUserPassword();
      if(userDb[phoneNumber].getUserPassword()==userGivenPassword){
         cout<<"Success!!"<<'\n';
         userInterface(user);
         return;
      }
      failedCounter++;
      if(failedCounter<=5){
         cout<<"Enter Correct PassWord"<<endl;
         loginPage(user,phoneNumber);
      }else{
         cout<<"You Have Tried Many Time Please Try Again Later"<<endl;
      }
   }
   void signupPage(User user,string phoneNumber){
      userDb[phoneNumber]=user;
      cout<<"signUp success!!"<<endl;
      userInterface(user);
   }
   //User Interface
   void userInterface(User user){
      string userBoardingLoaction;
      string userDestination;
      cout<<"Enter Boarding Location"<<endl;
      cin>>userBoardingLoaction;
      cout<<"Enter Destination"<<endl;
      //
      cin>>userDestination;
      showBusesWithCost(user,userBoardingLoaction,userDestination);
   }
   // show buses with cost
   void showBusesWithCost(User user,string userBoardingLoaction,string userDestination){
      vector<Bus>busestoDestination=buses[{userBoardingLoaction,userDestination}];
      sort(busestoDestination.begin(),busestoDestination.end(),[&](Bus A,Bus B){
         long costA=A.getbusFareCost();
         long costB=B.getbusFareCost();
         return costA<costB;
      });
      bool seats=0;// seats
      for(Bus BusI:busestoDestination){
         cout<<"Bus Name:"<<BusI.getBusName()<<endl;
         cout<<"Bus From:"<<userBoardingLoaction<<endl;
         cout<<"To:"<<userDestination;
         cout<<"Bus ticket Cost:"<<BusI.getbusFareCost()<<'\n';
         cout<<"Bus Boarding Time:"<<BusI.getBoardingTime()<<endl;
         cout<<"Bus Dropping Time"<<BusI.getDroppingTime()<<endl;
         cout<<"See seats";
         cin>>seats;
         if(seats){
            showThisBusSeatsTicket(user,BusI);
            break;
         }
      }
   }
   void showThisBusSeatsTicket(User user,Bus bus){
      vector<pair<string,bool>>IsSeatAvailable=bus.getBusSeat();
      for(int i=0;i<IsSeatAvailable.size();i++){
         cout<<"Seat Number"<<IsSeatAvailable[i].first;
         cout<<"Availability"<<IsSeatAvailable[i].first;
         bool Book;
         cout<<"Bookseat";cin>>Book;
         if(Book){
            bookThisBusSeat(user,bus,i);
         }
      }
   }
   void showBusDetailToUser(User user,Bus bus,int i){
      vector<pair<string,bool>>IsSeatAvailable=bus.getBusSeat();
      cout<<"Bus Name:"<<bus.getBusName()<<endl;
      cout<<"Bus Number:"<<bus.getBusNumber()<<endl;
      cout<<"Seat Number:"<<IsSeatAvailable[i].first<<endl;
      cout<<"Booked By:"<<user.getUserName()<<endl;
      cout<<"Boarding Location:"<<bus.getBoardingLocation()<<"Timing:"<<bus.getBoardingTime();
      cout<<"Dropping Location:"<<bus.getBusDroppingLocation()<<"Timing:"<<bus.getDroppingTime();
      cout<<"Ticket Fare:"<<bus.getbusFareCost();
   }
   bool paymentGateWay(User user){
      return true;//assuming that payment get successfull
   }
   void bookThisBusSeat(User user,Bus bus,int i){
      vector<pair<string,bool>>IsSeatAvailable=bus.getBusSeat();
      cout<<"Pay The Bus seat ticket fare cost of :"<<bus.getbusFareCost()<<"Rupees"<<endl;
      bool paymentsuccess=paymentGateWay(user);
      if(paymentsuccess){
         //marked this Bus seat as Booked
         IsSeatAvailable[i].second=true;
         cout<<"Bus seat Booked successFull";
         showBusDetailToUser(user,bus,i);
      }else{
         cout<<"payment Failed Kindly retry"<<endl;
         bookThisBusSeat(user,bus,i);
      }
   }
};