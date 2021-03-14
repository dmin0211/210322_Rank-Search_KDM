#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> indexVector;
vector<int> score;
vector<vector<int>> scoreVector(24);

void switchStringToBit(string str, int index ){
    char *buffer = new char[1000];
    strcpy(buffer, str.c_str());
    string temp = strtok(buffer, " ");
    if(temp=="java")
        indexVector[index].push_back(8);
    else if(temp=="python")
        indexVector[index].push_back(16);
    else if(temp=="cpp")
        indexVector[index].push_back(0);
    else if(temp=="-"){
        indexVector[index].push_back(0);
        indexVector[index].push_back(8);
        indexVector[index].push_back(16);
    }
    for(int i=1;i<4;i++){
        int loop;
        temp=strtok(NULL," ");
        if(temp=="and") temp=strtok(NULL," ");
        if(i==1) {
            loop=indexVector[index].size();
            if(temp == "backend")
                for(int j=0;j<loop;j++)
                    indexVector[index][j]+=4;
            else if(temp == "-"){// if -
                for(int j=0;j<loop;j++){
                    indexVector[index].push_back(indexVector[index][j]+4);
                }
            }
        }else if(i==2){
            loop=indexVector[index].size();
            if(temp == "senior")
                for(int j=0;j<loop;j++)
                    indexVector[index][j]+=2;
            else if(temp == "-"){// if -
                for(int j=0;j<loop;j++){
                    indexVector[index].push_back(indexVector[index][j]+2);
                }
            }
        }else {
            loop=indexVector[index].size();
            if(temp == "pizza")
                for(int j=0;j<loop;j++)
                    indexVector[index][j]+=1;
            else if(temp == "-"){// if -
                for(int j=0;j<loop;j++){
                    indexVector[index].push_back(indexVector[index][j]+1);
                }
            }
        }
    }
    temp=strtok(NULL," ");
    score[index]=stoi(temp);
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer(query.size());
    indexVector.resize(info.size());
    score.resize(info.size());
    for(int i=0;i<info.size();i++){
        switchStringToBit(info[i],i);
    }
    for(int i=0;i<info.size();i++){
        for(int j=0;j<indexVector[i].size();j++) {
            scoreVector[indexVector[i][j]].push_back(score[i]);
        }
    }
    for(int i=0;i<24;i++) {
        sort(scoreVector[i].begin(),scoreVector[i].end());
    }
    indexVector.clear();
    score.clear();
    indexVector.resize(query.size());
    score.resize(query.size());
    for(int i=0;i<query.size();i++){
        switchStringToBit(query[i],i);
    }
    for(int i=0;i<query.size();i++){
        for(int j=0;j<indexVector[i].size();j++){
            vector<int>::iterator low=lower_bound(scoreVector[indexVector[i][j]].begin(),scoreVector[indexVector[i][j]].end(),score[i]);
            answer[i]=answer[i]+scoreVector[indexVector[i][j]].size()-(low-scoreVector[indexVector[i][j]].begin());
        }
    }
    return answer;
}
int main(){
    vector<string> information={"java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50"};
    vector<string> query={"java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"};
    solution(information,query);
}