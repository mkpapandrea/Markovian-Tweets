/* heared file for me code
class word defines a word and a vector of all potential followers
class markov chain defines a vector of words. duplicate words get their followers added to the follower vector
*/
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;


class Word{
    public:
    string wrd;
    vector<string> followers;


    Word(string w, string follow){
    wrd=w;
    followers.push_back(follow);
    }

    void print_current(){
        cout<< "Word is:"<< wrd<< endl;
        for(int i=0; i< followers.size(); i++){
            cout<< "Followers"<< followers.at(i);
        }
    }

};

class Chain{            //should it be a class
    vector<Word> Markov_Chain;



    void add_word(string word, string follow){
        bool found=false;
        for(int i=0; i< Markov_Chain.size(); i++){
            if( word == Markov_Chain.at(i).wrd){
                found=true;
                Markov_Chain.at(i).followers.push_back(follow);


            }//endif
        }
        if(found=true){
            Word w= new Word(word, follow);
            Markov_chain.push_back(Word);
        }
    }//end

    

};


int get_index(int thingsize){       //picks random index for first word or from choice of followers
    return rand()% thingsize;
}


void make_tweet(Chain mc){      //picks first word and then picks followers. then goes to follower word. stops at 280 charaters
    string tweet;
    int chain_size= mc.size();

    string tmp_word= mc.at(get_index(chain_size));
    tweet= tweet + " ";


}