
#include<bits/stdc++.h>
using namespace std;
// Entities
class User{
   private:
   long id;// primary key
   string name;
   string phoneNumber;
   string password;
   string email;
   public:
   long totalProblemSolved;
   long EasySolved;
   long mediumSolved;
   long hardSolved;
   long rating;

    // Getters (used)
    string getPhoneNumber() const { return phoneNumber; }
    string getPassword() const { return password; }
    long getEasySolved() const { return EasySolved; }
    long getMediumSolved() const { return mediumSolved; }
    long getHardSolved() const { return hardSolved; }
    long getTotalProblemSolved() const { return totalProblemSolved; }

    // Setters (used)
    void setEasySolved(long val) { EasySolved = val; }
    void setMediumSolved(long val) { mediumSolved = val; }
    void setHardSolved(long val) { hardSolved = val; }
    void setTotalProblemSolved(long val) { totalProblemSolved = val; }
};
class ContestUsers{
   public:
   long id;
   long  user_id;// foriegn key;
   long solvedProblem;
   long timetaken;
       // Getters (used in sorting)
    long getProblemSolved() const { return solvedProblem; }
    long getTimeTaken() const { return timetaken; }
};
class Problem{
   public:
   long id;// primary key
   bool isSolved;
   string Description;
   string Editorial;
   vector<string>testCases;
   string level;
   long totalAccepted;
   long totalSubmission;

       // Getters (used)
    bool getIsSolved() const { return isSolved; }
    string getLevel() const { return level; }

    // Setters (used)
    void setIsSolved(bool s) { isSolved = s; }
   
};
class Contest{
   public:
   long id; // primary key
   string contestName;
   bool isAttempted;
   vector<Problem>problemList;
    // Getters (used)
    bool getIsAttempted() const { return isAttempted; }
    vector<Problem> getContestProblems() const { return problemList; }
};
class Topic{
   public:
   long id; // primary key
   string name;
   vector<Problem>topicProblem;
       // Getter (used)
    vector<Problem> getProblemList() const { return topicProblem; }
};

// Main Class...
class Leetcode{
   private:
   map<string,User>userDB;
   map<string,Topic>topicDB;
   vector<Problem>problemDB;
   vector<Contest>contestDB;
   long  failed;
   public:
   void checkCred(User user){
      string phoneNumber=user.getPhoneNumber();
      if(userDB.find(phoneNumber)==userDB.end()){
         signUp(user);
         return;
      }
      loginPage(user);
   }

   void loginPage(User user){
      string userGivenPass=user.getPassword();
      string dbPassword=userDB[user.getPhoneNumber()].getPassword();
      if(userGivenPass==dbPassword){
         cout<<"Login Success!!";
         return;
      }
      failed++;
      if(failed>5){
         cout<<"Try Again after Sometime"<<endl;
         return;
      }else{
         cout<<"Wrong Password Please  Enter Correct Password"<<endl;
         loginPage(user);
      }
   }
   // New User Signup
   void signUp(User user){
      string phoneNumber=user.getPhoneNumber();
      userDB[phoneNumber]=user;
      cout<<"SignUp Success!!"<<endl;
      user.setEasySolved(0);
      user.setHardSolved(0);
      user.setMediumSolved(0);
      user.setTotalProblemSolved(0);
   }
   // search Problem By Ropic Name..
   vector<Problem>searchProblemsBytopic(User user ,string topic){
      if(topicDB.find(topic)==topicDB.end()){
         return {};
      }
      vector<Problem>problems=topicDB[topic].getProblemList();
      return problems;
   }
   // All the  Problems that user not solved..
   vector<Problem>showAllProblemsthatUserNotSolved(User user){
      vector<Problem>unsolvedProblemList;
      for(Problem problem:problemDB){
         if(problem.getIsSolved()==true){
            continue;
         }
         unsolvedProblemList.push_back(problem);
      }
      return unsolvedProblemList;
   }
   // All UnAttempted Contests..
   vector<Contest>showAllUnattemptedContest(User user){
      vector<Contest>contests;
      for(Contest contest:contestDB){
         if(contest.getIsAttempted()==true){
            continue;
         }
         contests.push_back(contest);
      }
      return contests;
   }
   // All attempted Contests..
   vector<Contest>showAllattemptedContest(User user){
      vector<Contest>contests;
      for(Contest contest:contestDB){
         if(contest.getIsAttempted()==false){
            continue;
         }
         contests.push_back(contest);
      }
      return contests;
   }
   // sort Problem By Difficulty..
   vector<Problem>showProblemsByDifficulty(string level){
      vector<Problem>givenLevelProblems;
      for(Problem problem:problemDB){
         if(problem.getLevel()==level){
            continue;
         }
         givenLevelProblems.push_back(problem);
      }
      return givenLevelProblems;
   }
   //Solving Problem..
   void solveProblem(Problem problem,User user){
      problem.setIsSolved(true);
      string level=problem.getLevel();
      if(level=="Easy"){
         user.setEasySolved(user.getEasySolved()+1);
      }
      if(level=="Medium"){
         user.setMediumSolved(user.getMediumSolved()+1);
      }
      if(level=="Hard"){
         user.setHardSolved(user.getHardSolved()+1);
      }
      user.setTotalProblemSolved(user.getTotalProblemSolved()+1);
   }
   //Contest Ranking..
   vector<pair<long,ContestUsers>>ContestRanking(vector<ContestUsers>users){ // sort by nnumber of problem solved and time taken
      vector<pair<long,ContestUsers>>rankings;
      sort(users.begin(),users.end(),[&](auto &a,auto &b){
         if(a.getProblemSolved()==b.getProblemSolved()){
            return a.getTimeTaken<b.getTimeTaken;
         }
         return a.getProblemSolved()<b.getProblemSolved();
      });
      int totalUserParticipated=users.size();
      for(int i=0;i<totalUserParticipated;i++){
         rankings.push_back({i+1,users[i]});
      }
      return rankings;
   }
   //Attempt Contest..
   void AttemptContest(Contest contest,User user){
      vector<Problem>contestProblem=contest.getContestProblems();
      vector<Problem>easyProblem=showProblemsByDifficulty("Easy");
      vector<Problem>mediumProblem=showProblemsByDifficulty("Medium");
      vector<Problem>hardProblem=showProblemsByDifficulty("Hard");
      for(Problem easy:easyProblem){
         solveProblem(easy,user);
      }
      for(Problem medium:mediumProblem){
         solveProblem(medium,user);
      }
      for(Problem hard:hardProblem){
         solveProblem(hard,user);
      }
   }
};
