#include <iostream>
#include <string>
#include <sstream>

class VideoGame
{
    public:
        VideoGame() {}

        // we do not need references to mutable objects as input to the constructor
        // either pass by value or pass by reference to const (const std::string&)
        // should this multi-arg constructor be explicit?
        /*explicit*/ VideoGame( std::string t, std::string g, char r, std::string d) : //constructor
            title(t), genre(g), rating(r), developer(d) { /* ... */ }
        // ...

        // read values typed in by the user, with prompts and error recovery
        bool read_from_stdin() ; // TODO

        friend std::ostream& operator<< ( std::ostream& out, const VideoGame& game ); // const
        friend std::istream& operator>> ( std::istream& in, VideoGame& game ) ;

    private:
        std::string title; // may contain white space
        std::string genre; // may contain white space
        char rating;
        std::string developer; // may contain white space

        static const char title_tag[] ;
        static const char genre_tag[] ;
        static const char rating_tag[] ;
        static const char developer_tag[] ;

}; //End VideoGame class

const char VideoGame::title_tag[] = "Title:" ;
const char VideoGame::genre_tag[] = "Genre:" ;
const char VideoGame::rating_tag[] = "Rating:" ;
const char VideoGame::developer_tag[] = "Developer:" ;

std::ostream& operator<< ( std::ostream& out, const VideoGame& game )
{
    return out << VideoGame::title_tag << ' ' << game.title << '\n' // first line
                << VideoGame::genre_tag << ' ' << game.genre << '\n' // second line
                << VideoGame::rating_tag << ' ' << game.rating << '\n' // third line
                << VideoGame::developer_tag << ' ' << game.developer << '\n' ; // last line
}

// helper function to consume and validate tags
// skips white space on either side of the tag
static bool consume( std::istream& in, const char* expected )
{
    std::string str ;
    return in >> std::ws >> str >> std::ws && str == expected ;
}

std::istream& operator>> ( std::istream& in, VideoGame& game )
{
    std::string title ;
    std::string genre ;
    char rating ;
    std::string developer ;

    if( consume( in, VideoGame::title_tag ) &&
        std::getline( in, title ) &&
        consume( in, VideoGame::genre_tag ) &&
        std::getline( in, genre ) &&
        consume( in, VideoGame::rating_tag ) &&
        in >> rating &&
        consume( in, VideoGame::developer_tag ) &&
        std::getline( in, developer ) )
    {
        // read everything succesfully, set the state of the game object
        game = { title, genre, rating, developer } ;
    }

    else
    {
        // read failed
        in.setstate( std::ios::failbit ) ; // indicate input failure
        game = {} ; // optional: clear all the fields in the the game object
    }

    return in ;
}

int main()
{
     VideoGame ernie { "Alpha Beam With Ernie", "Edutainment", 'B', "Michael Callahan" } ;
     VideoGame dogs { "Nintendogs", "Pet Simulation", 'A', "Kiyoshi Mizuki" } ;

     std::stringstream stm ;
     stm << ernie << '\n' << dogs << '\n' ;
     std::cout << "written out\n-----------\n" << stm.str() ;

     VideoGame games[2] ;
     if( stm >> games[0] >> games[1] )
        std::cout << "read back\n-----------\n" << games[0] << '\n' << games[1] << '\n' ;
}
// last line
