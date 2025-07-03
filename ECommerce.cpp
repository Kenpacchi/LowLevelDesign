#include <bits/stdc++.h>
using namespace std;

class User{
   private :
   long id;
   string name;
   string phoneNumber;
   string password;
   string Email;
   vector<Product>orders;
   // Getters
   public:
   vector<Product> getOrders(){
      return orders;
   }
   string getPhoneNumber(){
      return phoneNumber;
   }
   string getName(){
      return name;
   }
   string getPassword(){
      return password;
   }
   // Setter

   void setPassword(string password){
      this->password=password;
   }

   void setOrders(Product product){
      orders.push_back(product);
   }
};
class Product{
   private:
   long id;
   string productName;
   string productType;
   long stock;
   long price;
   long rating;
   vector<string> reviews;
   long deliverydays;

   public:
   //Getters
   long getStock(){
      return stock;
   }
   string getProductName(){
      return productName;
   }
   string getProductType(){
      return productType;
   }
   vector<string> getReviews(){
      return reviews;
   }
   long getPrice(){
      return price;
   }
   long getRating(){
      return price;
   }
   long getTime(){
      return deliverydays;
   }

   // Setters

   void setStock(long stock){
      this->stock=stock;
   }
};
class Electronic{
   private:
   vector<Product>products;
   public:
   vector<Product>getProducts(){
      return products;
   }
};
class Cosmetic{
   private:
   vector<Product>products;
   public:
   vector<Product>getProducts(){
      return products;
   }
};
class Clothing{
   private:
   vector<Product>products;
   public:
   vector<Product>getProducts(){
      return products;
   }
};
class Appliances{
   private:
   vector<Product>products;
   public:
   vector<Product>getProducts(){
      return products;
   }
};

// main Ecommerce..
class ECommerceApplication{
   private :
   map<string,User>userDb;
   vector<Product>productDb;
   long failedCounter=0;
   public:

      // User Services..

   string Authentication(User user){
      string phoneNumber=user.getPhoneNumber();
      if(userDb.find(phoneNumber)!=userDb.end()){
         return loginPage(user);
      }
      return signUp(user);
   }
   string loginPage(User user){
      string userGivenPassword=user.getPassword();
      string password=userDb[user.getPhoneNumber()].getPassword();
      if(password==userGivenPassword){
         return "Login Success !!";
      }
      failedCounter++;
      if(failedCounter>5){
         return "Try Again After Some Time !";
      }else{
         cout<<"ReEnter Password !!";
         string password;
         cin>>password;
         user.setPassword(password);
         loginPage(user);
      }
   }

   string signUp(User user){
      string phoneNumber=user.getPhoneNumber();
      userDb[phoneNumber]=user;
      return "Sign Up Success !!";
   }
   // Reccomendation 

   vector<Product> Recommendations(User user){
      vector<Product>products(user.getOrders().begin(),user.getOrders().end());
      if(products.empty()){
         products=productDb;
         sort(products.begin(),products.end(),[&](Product &product1,Product &product2){
            if(product1.getRating()==product2.getRating()){
               return product1.getPrice()<product2.getPrice();
            }
            return product1.getRating()>product2.getRating();
         });
         return products;
      }
      int electronicsCounter=0;
      int cosmaticCounter=0;
      int clothingCounter=0;
      for(Product product:products){
         if(product.getProductType()=="Electronics"){
            electronicsCounter++;
         }else if(product.getProductType()=="Clothing"){
            clothingCounter++;
         }else if(product.getProductType()=="Cosmatic"){
            cosmaticCounter++;
         }
      }
      int maximumTypeOrdered=max({electronicsCounter,cosmaticCounter,clothingCounter});
      if(maximumTypeOrdered==electronicsCounter){
         Electronic electronic;
         return electronic.getProducts(); 
      }
      if(maximumTypeOrdered==clothingCounter){
         Clothing clothing;
         return clothing.getProducts(); 
      }
      Cosmetic cosmatic;
      return cosmatic.getProducts(); 
   }

   // find By Name with low-high price
   vector<Product> findProductByNamePriceSorted(string name){
      vector<Product> productByNamePriceSorted;

      for(Product product:productDb){
         if(product.getProductName()==name&&product.getStock()>0){
            productByNamePriceSorted.push_back(product);
         }
      }
      sort(productByNamePriceSorted.begin(),productByNamePriceSorted.end(),[&](Product &product1,Product &product2){
         if(product1.getPrice()==product2.getPrice()){
            return product1.getRating()>product2.getRating();
         }
      });
      return productByNamePriceSorted;
   }
   // find By name with Best rating..
   vector<Product> findProductByNamewithBestRatingSorted(string name){
      vector<Product> productByNameBestRating;

      for(Product product:productDb){
         if(product.getProductName()==name&&product.getStock()>0){
            productByNameBestRating.push_back(product);
         }
      }
      sort(productByNameBestRating.begin(),productByNameBestRating.end(),[&](Product &product1,Product &product2){
         if(product1.getPrice()==product2.getPrice()){
            return product1.getRating()>product2.getRating();
         }
      });
      return productByNameBestRating;
   }
   //find Product by type ..{electronic,cosmatic,appliances,clothing}
   vector<Product> findProductByProductType(string type){
      vector<Product> productByType;
      for(Product product:productDb){
         if(product.getProductType()==type&&product.getStock()>0){
            productByType.push_back(product);
         }
      }
      return productByType;
   }

   // Placing Order...

   string placeOrder(User user, Product product){
      if(product.getStock()==0){
         return "Product Is Out of Stock !!";
      }
      user.setOrders(product);
      product.setStock(product.getStock()-1);
      return "Order PLaced SuccessFully";
   }

   // All the orders Placed By User..
   vector<Product> showallOrderPlaced(User user){
      return user.getOrders();
   }

};

int main(){
    ECommerceApplication app;

    // Create products
    Product p1, p2;
    // Set fields of p1 and p2 using setters

    // Add products to app.productDb
    app.findProductByNamePriceSorted("Phone");

    // Create user
    User u1;
    // Set fields of u1
    app.Authentication(u1);

    // Place order
    app.placeOrder(u1, p1);

    return 0;
}
