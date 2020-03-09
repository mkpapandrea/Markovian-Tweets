/*Mary Papandea
Markovian tweets
word class defines a word and a vector of followers


*/




#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
using namespace std;


class Word{
    public:
        string word;
        vector<string> followers;
        
        Word(string wrd, string follower){
            word = wrd;
            followers.push_back(follower);
        }

        //cpp errors when default constructor destructor defined idk why
};


vector<Word> MC;              // vector of words
string tweet = "";                      // empty string for the tweet



int get_index(string word){
    for(int i = 0; i < MC.size(); i++){
        if(MC.at(i).word.compare(word) == 0){
            return i;
        }
    }
    return -1;
}


void add_word(string word, string follower){
    int index = get_index(word);
    
    if(index == -1){        //if doesnt exist add word to chain
        MC.push_back(Word(word, follower));
    }
    else{
        MC.at(index).followers.push_back(follower);     // if exists add followers to follow vector
    }
}


void parse_line(string line){
    size_t word_start = 0;
    size_t word_end;
    size_t follower_start;
    size_t follower_end;
    size_t word_len;
    size_t follower_len;
    string word = "";       // blank strings
    string follower = "";
    ////////////////////////////////////////////////////////////////////////////////////
    while(word_start != string::npos){      //npos description http://www.cplusplus.com/reference/string/string/npos/
        word_end = line.find(" ", word_start);  // find spaces and switch indexes
        word_len = word_end - word_start;
       ///////////////////////////////////////////////////////////// 
        while(word_len == 0){       // look for substring
            word_start++;
            word_end = line.find(" ", word_start);
            word_len = word_end - word_start;
            
            if(word_start >= line.length()){
                word_start = line.length(); 
                break;
            }
        }
        
        word = line.substr(word_start, word_len); 
        
        if(word_end != string::npos){       // looks for first substring after the end or word_end
            follower_start = word_end + 1;
            follower_end = line.find(" ", follower_start);
            follower_len = follower_end - follower_start;
            
            while(follower_len == 0){
                follower_start++;
                follower_end = line.find(" ", follower_start);
                follower_len = follower_end- follower_start;
                if(follower_start>= line.length()){
                    follower_start= line.length();  
                    break;
                }
            }
            
            word = line.substr(word_start, word_len);
            follower = line.substr(follower_start, follower_len); 
            word_start = follower_start;    
        }
        else{
            follower = "";  //set as ending condition for words with no followers. in make_tweet if =0
            word_start = string::npos;
        }
        
        add_word(word, follower);   
                                    
    }
}


int parse_file(string filename){    //parses line by line. line is considered tweet so as to not fuck up senstences
    string line;
    cout<< "parse file"<< endl;
    ifstream myfile(filename.c_str());
    if (myfile.is_open()){
        while(getline (myfile,line)){
            parse_line(line);
        }
        myfile.close();
        return 1;
    }
    else{
        return 0;
    }
}




int get_rand_index(int choices){    //in a function cause it needs to repeatedly randomize
    return rand() % choices;
}


void make_tweet(){         //random first word. in while it picks from followers then goes follower->word.
    //cout<<"    in make_tweet"<< endl;
    bool finished=false;
    string tweet= "";
    int follower_count;
    int follower_index;

    string wrd;
    int index= get_rand_index(MC.size());
    
    tweet= MC.at(index).word;
    wrd=tweet;


    /////////////////////////////////////////////////////////////////////////
    while(!finished){
        index= get_index(wrd);
        Word current= MC.at(index);
        follower_count=current.followers.size();
        follower_index=get_rand_index(follower_count);

        wrd= current.followers.at(follower_index);
        if(wrd.length()==0){        //if length =0, means not a word. no followers
            finished=true;
        }
        else{
             if(tweet.length()+ wrd.length()>280){      // doesnt go over 280
                finished=true;
            }
            else{
                tweet= tweet+" " +wrd;
            }  
        }
    }
        
    if(finished=true){
        cout<< tweet<< endl;
        }
 
}

void print_some_tweets(int amount){
    for(int i = 0; i < amount; i++){
        make_tweet();
        cout << endl;
    }
}






/////////////////////////////////////////main///////////////////////////////////////
int main(int argc, char* argv[]){               // run by adding text file name after ./excname
    //cout<< "being main";
    string arguement(argv[1]);
    srand(time(NULL));


    int amount;
    //cout<< "look";
    if(parse_file(arguement)){
        cout<< " how many tweets yall want?  ";
        cin >> amount;
        cout<< "**********Tweets**************"<< endl;
        print_some_tweets(amount);   
    }

    
    return 0;
}