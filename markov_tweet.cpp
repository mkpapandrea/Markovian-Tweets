/* mary papandrea
takes in a text file of tweets or a twitter handle 
and reproduces a 280 character tweet approximation using markov chains
*/


#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include "markov_tweet.h"
using namespace std;

//////////////////////////main/////////////////////////
//takes in tweetstuff.txt
//calls parse pair
//print tweet with how ever many tweets wanted

int main(){
   int i;
   string f= "tweetstuff.txt";
   parse_pair(f);

    cout<< "how many tweets y'all want?"<< endl;
    cin>>i;
    //print_some_tweets(i);
    


    return 0;

}