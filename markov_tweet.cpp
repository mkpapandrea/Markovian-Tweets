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

// Analyzes a single tweet (1 line from a text file)
// This breaks up the tweet into base words and the word following it.
void parse_line(string line){
    size_t word_start_index = 0;
    size_t word_end_index;
    
    size_t follower_start_index;
    size_t follower_end_index;
    
    size_t word_len;
    size_t follower_len;
    
    string word = "";
    string follower = "";
    
    // Goes through all the words in the tweet
    while(word_start_index != string::npos){
        word_end_index = line.find(" ", word_start_index);
        word_len = word_end_index - word_start_index;
        
        // Find the next base word
        while(word_len == 0){
            word_start_index++;
            word_end_index = line.find(" ", word_start_index);
            word_len = word_end_index - word_start_index;
            
            // Case where the last word in the tweet has been reached
            if(word_start_index >= line.length()){
                word_start_index = line.length(); // Should always be the length anyway due to logic of the find function, but set in case of boundary conditions 
                break;
            }
        }
        
        word = line.substr(word_start_index, word_len); // Now holds a single word from the tweet.
        
        // Now find the following word (if there is one)
        if(word_end_index != string::npos){
            follower_start_index = word_end_index + 1;
            follower_end_index = line.find(" ", follower_start_index);
            follower_len = follower_end_index - follower_start_index;
            
            while(follower_len == 0){
                follower_start_index++;
                follower_end_index = line.find(" ", follower_start_index);
                follower_len = follower_end_index - follower_start_index;
                if(follower_start_index >= line.length()){
                    follower_start_index = line.length(); // should always be the length anyway due to logic of the find function, but set in case of boundary conditions 
                    break;
                }
            }
            
            word = line.substr(word_start_index, word_len);
            follower = line.substr(follower_start_index, follower_len); // Now contains the word right after the base word
            
            word_start_index = follower_start_index;    // The next base word will be the current base word's follower
        }
        else{
            follower = "";  // If the base word is that last word in the tweet, then it does not have a following word
            word_start_index = string::npos;
        }
        
        add_word(word, follower);   // Add the base word and its follower to the vector of Markov links
                                    // or update the base word's vector of followers if there is already a record
    }
}


int parse_file(string filename){    //parses line by line. line is considered tweet so as to not fuck up senstences
    string line;
    
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


void write_tweet(){
    
    int word_index = get_rand_index(MC.size()); // Randomly select the first word of the tweet
    int follower_index = 0;
    int follower_num = 0;
    
    bool tweet_done = false;
    string last_word = ""; // most recent word added, used to search vector
    
    tweet = "";
    tweet = MC.at(word_index).word; // First word of the tweet
    last_word = tweet;  // Since the tweet is only 1 word long right now, first word = last word
    
    while(!tweet_done){
        word_index = get_index(last_word);
        Word temp = MC.at(word_index);
        
        follower_num = temp.followers.size();
        follower_index = get_rand_index(follower_num);  // Randomly select the next word. Because of word distribution in sentences,
                                                        // the follower word, on average, should be the most frequent word seen after a given base word
        last_word = temp.followers.at(follower_index);
        
        if(last_word.length() == 0){    // If the last "word" is an empty string, then the tweet is complete.
            tweet_done = true;
        }
        else{
            if(tweet.length() + last_word.length() > 279){ // If adding the next word makes the tweet longer than 279 characters, don't add it to the tweet.
                tweet_done = true;
            }
            else{
                tweet = tweet + " " + last_word;    // Add the next word to the tweet with a space between the words. (This space is why we use the 279 above, instead of 280)
            }
        }
    }
    cout << tweet << endl;
}

void print_some_tweets(int amount){
    for(int i = 0; i < amount; i++){
        write_tweet();
        cout << endl;
    }
}






/////////////////////////////////////////main///////////////////////////////////////
int main(int argc, char* argv[]){               // run by adding text file name after ./excname
    string arguement(argv[1]);
    srand(time(NULL));


    int amount;
    if(parse_file(arguement)){
        cout<< " how many tweets yall want?  ";
        cin >> amount;
        cout<< "**********Tweets**************"<< endl;
        print_some_tweets(amount);   
    }

    
    return 0;
}