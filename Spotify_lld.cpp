#include <bits/stdc++.h>
using namespace std;
class User{
   private:
   long id ;// primary key
   string userName;
   string userPhoneNumber;
   string userEmail;
   string userPassword;
   vector<Songs>userPlaylist;
   public:
    // Getters
    long getId() const { return id; }
    string getUserName() const { return userName; }
    string getPhoneNumber() const { return userPhoneNumber; }
    string getEmail() const { return userEmail; }
    string getPassword() const { return userPassword; }
    vector<Songs>& getPlaylist() { return userPlaylist; }

    // Setters
    void setId(long i) { id = i; }
    void setUserName(const string& name) { userName = name; }
    void setPhoneNumber(const string& phone) { userPhoneNumber = phone; }
    void setEmail(const string& email) { userEmail = email; }
    void setPassword(const string& password) { userPassword = password; }
    void setPlaylist(const vector<Songs>& playlist) { userPlaylist = playlist; }
};
class Songs{
   private:
   long songId; // primary key
   long artistId;
   long movieId;// foriegn Key
   string songName;
   long views;
   string songArtistName;
   string uploadDate;
   public:
    // Getters
    long getSongId() const { return songId; }
    string getSongName() const { return songName; }
    long getSongViews() const { return views; }
    string getArtistName() const { return songArtistName; }
    string getUploadDate() const { return uploadDate; }

    // Setters
    void setSongId(long id) { songId = id; }
    void setSongName(const string& name) { songName = name; }
    void setSongViews(long v) { views = v; }
    void setArtistName(const string& name) { songArtistName = name; }
    void setUploadDate(const string& date) { uploadDate = date; }
};
class Artist{
   private:
   long artistId; // primary key
   string artistName;
   vector<Songs>artistSongs;
   public:
    // Getters
    long getArtistId() const { return artistId; }
    string getArtistName() const { return artistName; }
    vector<Songs>& getArtistSongs() { return artistSongs; }

    // Setters
    void setArtistId(long id) { artistId = id; }
    void setArtistName(const string& name) { artistName = name; }
    void setArtistSongs(const vector<Songs>& songs) { artistSongs = songs; }
};
class Movie{
   private:
   long movieId;// primary key
   vector<Songs>movieSongs;
   public:
    // Getters
    long getMovieId() const { return movieId; }
    vector<Songs>& getMovieSongs() { return movieSongs; }

    // Setters
    void setMovieId(long id) { movieId = id; }
    void setMovieSongs(const vector<Songs>& songs) { movieSongs = songs; }
};
// Main Class
class Spotify{
   public:
   map<string,User>userDb;  //USER DATABASE
   vector<Songs>songDb;     //SONG DATABASE
   map<string,Artist>artistDb;
   map<string,Movie>movieDb;
   map<string,Songs>songS;
   long failed;
   Spotify(){
      failed=0;
   }
   public:
   void checkCredential(User user){
      if(userDb.find(user.getPhoneNumber())!=userDb.end()){
         cout<<"User Exist Login please:"<<endl;
         loginPage(user);
         return;
      }
      signUpPage(user);
   }
   void loginPage(User user){
      string actualPass=userDb[user.getPhoneNumber()].getPassword();
      if(actualPass==user.getPassword()){
         cout<<"Login Success!!"<<endl;
         userInterface(user);
         return;
      }
      failed++;
      if(failed<=5){
         cout<<"Please Enter Correct Password"<<'\n';
         string password;
         cin>>password;
         user.setPassword(password);
         loginPage(user);
         return;
      }else{
         cout<<"Login Failed Try again after 24 Hours"<<endl;
      }
   }
   void signUpPage(User user){
      string phoneNumber = user.getPhoneNumber();
      userDb[phoneNumber]=user;
      cout<<"SignUp  Success"<<endl;
   }
   void streamSong(Songs song){
      // we will use audio player here....
   }
   void showSongs(Songs song){
      cout<<song.getSongName()<<endl;
      cout<<song.getArtistName()<<endl;
      cout<<song.getSongViews()<<endl;
      cout<<song.getUploadDate()<<endl;
      streamSong(song);
   }
   vector<Songs> trendingSongs(){
      // trending page
      vector<Songs>trending=songDb;
      sort(trending.begin(),trending.end(),[&](auto &a,auto&b){
         if(a.getSongViews()==b.getSongViews){
            return a.getUploadDate()<b.getUploadDate();
         }
         return a.getSongViews()<b.getSongViews;
      });
      return trending;
   }
   vector<Songs>recommendations(User user,string artistName ){
            // Recommendation
      vector<Songs>userPlaylist=user.getPlaylist();
      map<string,bool>checkAlreadyShown;
      for(auto userSong:userPlaylist){
         string artistName=userSong.getArtistName();
         if(checkAlreadyShown.find(artistName)!=checkAlreadyShown.end()){
            continue;
         }
         checkAlreadyShown[artistName]=true;
      }
      return artistDb[artistName].getArtistSongs();
   }
   void userInterface(User user){
      // User searching
      string name;
      cin>>name;
      vector<Songs>listOfSongsOfMovie=searchSongByMovieName(name);
      vector<Songs>listOfSongsbyArtist=searchSongByArtistName(name);
      Songs songByName=searchSongByName(name);

      // playlist Creation
      vector<Songs>newUserPlaylist;
      user.setPlaylist(newUserPlaylist);

      // Add Songs To Playlist
      for(int i=0;i<100;i++){// limit of playlist size...
      string songName;
      cin>>songName;
      user.getPlaylist().push_back(songS[songName]);
      }
   }
   Songs searchSongByName(string name){
      if(songS.find(name)!=songS.end()){
            return songS[name];
      }
      return {};
   }
   vector<Songs>searchSongByMovieName(string name){
      if(movieDb.find(name)!=movieDb.end()){
         vector<Songs>byMovieName=movieDb[name].getMovieSongs();
         return byMovieName;
      }
      return {};
   }
   vector<Songs> searchSongByArtistName(string name){
      if(artistDb.find(name)!=artistDb.end()){
         vector<Songs>byArtistName=artistDb[name].getArtistSongs();
         return byArtistName;
      }
      return {};
  }
};
int main() {
    Spotify  app;

    // Sample Data Initialization
    Songs song1;
    song1.setSongId(1);
    song1.setSongName("SongA");
    song1.setArtistName("ArtistX");
    song1.setSongViews(1000);
    song1.setUploadDate("2025-06-01");

    Songs song2;
    song2.setSongId(2);
    song2.setSongName("SongB");
    song2.setArtistName("ArtistX");
    song2.setSongViews(2000);
    song2.setUploadDate("2025-06-15");

    Artist artist;
    artist.setArtistId(101);
    artist.setArtistName("ArtistX");
    artist.setArtistSongs({song1, song2});

    Movie movie;
    movie.setMovieId(201);
    movie.setMovieSongs({song1});

    // Manually inserting into DB
    app.songS["SongA"] = song1;
    app.songS["SongB"] = song2;
    app.artistDb["ArtistX"] = artist;
    app.movieDb["MovieMovie"] = movie;
    app.songDb.push_back(song1);
    app.songDb.push_back(song2);

    // Creating a new user
    User newUser;
    newUser.setId(1);
    newUser.setUserName("Ajay");
    newUser.setPhoneNumber("1234567890");
    newUser.setEmail("ajay@example.com");
    newUser.setPassword("pass123");

    // Signup/Login flow
    app.checkCredential(newUser);

    return 0;
}
