#include<bits/stdc++.h>
using namespace std;
@Getter
@Setter
class User {
public:
    long id;
    string name;
    string email;
    string mobileNumber;
    string password;
    pair<int, int> currLoc; // this will get auto fetched when login is success!
};

class Order {
public:
    long id;
    string description;
    long amount;
    bool isPrePaid;
    pair<int, int> destinationLoc;
};

class Dish {
public:
    long id;
    string name;
    bool isVeg;
    string description;
};

class Menu {
public:
    string hotelName;
    map<Dish, int> menuCard;
};

class Restraunt {
public:
    long id;
    string name;
    string email;
    string landLineNumber;
    Menu menu;
    pair<int, int> location = {a, b};
};

class Bike {
public:
    long id;
    string regNumber;
    pair<int, int> delPartLoc;
};

class DeliveryPartner {
public:
    long id;
    string name;
    string mobileNumber;
    string email;
    Bike bike;
    bool isAvailable;
};

class Zomato {
public:
    map<string, User> userDb;
    vector<DeliveryPartner> dpDb;
    vector<Restraunt> restrauntDb;
    long userIdCounter = 1;
    int failedLoginCount = 0;

    void verifyCredentials(User user) {
        if (userDb.count(user.getMobileNumber()) > 0) {
            login(user);
            return;
        }
        signUp(user);
        return;
    }

    void signUp(User user) {
        user.setId(userIdCounter++);
        userDb[user.getMobileNumber()] = user;
        cout << "signUp Success!" << endl;
        firstPage(user);
        return;
    }

    void login(User user) {
        string dbPassword = userDb[user.getMobileNumber()].getPassword();
        if (dbPassword == user.getPassword()) {
            cout << "Login success!" << endl;
            firstPage(user);
            return;
        }
        failedLoginCount++;
        if (failedLoginCount <= 5) {
            string newPassword;
            cout << "Enter Correct password : " << endl;
            cin >> newPassword;
            user.setPassword(newPassword);
            login(user);
        } else {
            cout << "Try Again after some time" << endl;
        }
    }

    void firstPage(User user) {
        pair<int, int> userCurrLoc = user.getCurrLoc();

        sort(restrauntDb.begin(), restrauntDb.end(), [&](Restraunt a, Restraunt b) {
            pair<int, int> locOfA = a.getLocation();
            pair<int, int> locOfB = b.getLocation();

            int distOfAFromRestro = calcDistance(locOfA, userCurrLoc);
            int distOfBFromRestro = calcDistance(locOfB, userCurrLoc);

            return distOfAFromRestro < distOfBFromRestro;
        });

        int i = 0;
        for (; i < 10; i++) {
            Restraunt restraunt = restrauntDb[i];
            map<Dish, int> menuCard = restraunt.getMenuCard();
            show(menuCard);
        }
    }

    void assignDeliveryPartner(pair<int, int>& restroLoc, Order order) {
        sort(dpDb.begin(), dpDb.end(), [&](DeliveryPartner a, DeliveryPartner b) {
            pair<int, int> locOfA = a.getLocation();
            pair<int, int> locOfB = b.getLocation();

            int distOfAFromRestro = calcDistance(locOfA, userCurrLoc);
            int distOfBFromRestro = calcDistance(locOfB, userCurrLoc);

            return distOfAFromRestro < distOfBFromRestro;
        });

        bool isOrderAcceptedByDeliveryPartner = false;
        for (DeliveryPartner deliveryPartner : dpDb) {
            if (isOrderAcceptedByDeliveryPartner == true) {
                break;
            }
            if (deliveryPartner.getIsAvailable() == true) {
                isOrderAcceptedByDeliveryPartner = request(deliveryPartner, order);
            }
        }
    }

    bool request(DeliveryPartner& deliveryPartner, Order order) {
        string input; // it should be YES or NO  
        cout << "Do you wish to take this order for delivery :" << endl;
        cin >> input;

        if (input == "YES") {
            deliveryPartner.setIsAvaiable(false);
            return true;
        }

        return false;
    }
};
