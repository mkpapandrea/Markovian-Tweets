/* heared file for me code
class word defines a word and a vector of all potential followers
class markov chain defines a vector of words. duplicate words get their followers added to the follower vector
*/
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;


class Word{
    public:
    string wrd;
    vector<string> followers;


    Word(string w, string follow){
    wrd=w;
    followers.push_back(follow);
    }

    Word();

    void print_current(){
        cout<< "Word is:"<< wrd<< endl;
        for(int i=0; i< followers.size(); i++){
            cout<< "Followers"<< followers.at(i);
        }
    }

};


    vector<Word> Markov_Chain;



    void add_word(string word, string follow){
        //bool found=false;
        for(int i=0; i< Markov_Chain.size(); i++){
            if( word == Markov_Chain.at(i).wrd){
                //found=true;
                Markov_Chain.at(i).followers.push_back(follow);
            }//endif
            else{
                Word w(word, follow);
                Markov_Chain.push_back(w);
            }
        }

    }//end

    



int rand_index(int thingsize){       //picks random index for first word or from choice of followers
    return rand()% thingsize;
}


void make_tweet(){      //picks first word and then picks followers. then goes to follower word. stops at 280 charaters
    string tweet= "";
    bool finished= false;
    int mcsize= Markov_Chain.size();
    Word current;
    int current_index;

    Word firstword= Markov_Chain.at.rand_index(mcsize);  //randomized first word

    for(int i=0; i< Markov_Chain.size(); i++){               //needs first index to pass in
        if( firstword.wrd == Markov_Chain.at(i).wrd){
            current_index=i;
        }
    }

   

    tweet= tweet +firstword.wrd;
     current=firstword;


////////////////////////////////////////////////begin while////////////////////////////////////
    while(finished !=true){

        int follow_index= rand_index(current.followers.size());         //pick random follower
        string follow_word= current.followers.at(follow_index);         // not neccessary but simpler to check size

        if(sizeof(tweet+follow_word)< 280){     // twwet end condition. stops from getting cut off
            tweet = tweet+follow_word;
        }
        else{
            finished= true; 
        }


        for(int i=0; i<mcsize; i++){        // update follow_word to current
            if(follow_word== Markov_Chain.at(i).wrd){
                current= Markov_Chain.at(i);
            }
        }
        for(int i=0; i<Markov_Chain.size(); i++){        // get updated index of current
            if(current.wrd== Markov_Chain.at(i).wrd){
                current_index=i;
            }
        }



        if(finished=true){
            cout<< tweet<< endl;
        }

    }

}


void parse_pair(string filename){       //pasre txt file into an array. makes word follower pair using i, i+1
    string linearr[200];
    
    fstream file(filename);
    if(file.is_open){
        for(int i=0; i<200; i++){
            file>> linearr[i];
        }
    }
    file.close();

    for(int i=0; i<199;i++){
        Word w(linearr[i], linearr[i+1]);
        add_word(linearr[i], linearr[i+1]);

    }



}