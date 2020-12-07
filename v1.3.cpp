 #include<iostream>
#include<algorithm>
#include<string>
#include<time.h>
#define m 4
using namespace std;

class Game{
    public:
        Game();
        void NewNum();
        void Show();
        int Alive();
        int Action();
        void Up();
        void Down();
        void Left();
        void Right();
        void Reverse();
        void Cell();
        void GameOver(int);
    private:
        int cellscore;
        int operscore;
        int lastscore;
        int tempscore;
        int succeeded;
        int succelim;
        int succrev;
        int lastelim;
        int chessboard[m][m];
        int laststate[m][m];
        int tempstate[m][m];
};

Game::Game(){
    succelim=0;
    succeeded=0;
    cellscore=0;
    operscore=0;
    lastscore=0;
    tempscore=0;
    succrev=0;
    lastelim=0;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) chessboard[i][j]=0;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) laststate[i][j]=0;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) tempstate[i][j]=0;
    cout<<"Hey man ! Welcome to my 2048 !"<<endl<<endl;
    cout<<"2048 is a puzzle video game that took the world by storm years ago.PLayers try to unite the same numbers in adajvent cells by moveig all the numbers int the cessboard up/down/left/right and is affirmed successful if number 2048 apprears."<<endl;
    cout<<"\nTips:\n1.A——Left\n2.S——Down\n3.D——Right\n4.W——Up\n5.Q——Quit\n6.R——Reverse\n";
    cout<<"Now let`s get started!Enjoy it!"<<endl<<endl;
    NewNum();
    Show();
}
void Game::NewNum(){
    srand(time(NULL));
    int x,y;
    do{
        x=rand() % m;
        y=rand() % m;
    }while(chessboard[x][y]!=0);
    if(chessboard[x][y]==0&&succelim>1) chessboard[x][y]=4;
    else chessboard[x][y]=2;
}
void Game::Show(){
    for(int i=0;i<m;i++){
        for(int j=0;j<7*m+m+1;j++) cout<<"-";
        cout<<endl;
        for(int j=0;j<2;j++){
            for(int k=0;k<m;k++) cout<<"|       ";
            cout<<"|"<<endl;
        }
        for(int j=0;j<m;j++){
            if(chessboard[i][j]) printf("|%5d  ",chessboard[i][j]);
            else cout<<"|       ";
        } 
        cout<<"|"<<endl;
        for(int j=0;j<2;j++){
            for(int k=0;k<m;k++) cout<<"|       ";
            cout<<"|"<<endl;
        }
    }
    for(int j=0;j<7*m+m+1;j++) cout<<"-";
    cout<<endl<<"Current score: "<<operscore<<endl<<"Max cell: "<<cellscore<<endl;
}
int Game::Alive(){
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(chessboard[i][j]==0) return 1;
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<m-1;j++){
            if(chessboard[i][j]==chessboard[i][j+1]) return 1;
        }
    }
    for(int j=0;j<m;j++){
        for(int i=0;i<m-1;i++){
            if(chessboard[i][j]==chessboard[i+1][j]) return 1;
        }
    }
    return 0;
}
int Game::Action(){
    string s;
    if(!Alive()){
        cout<<"No operations available..."<<endl;
        GameOver(1);
        return 0;
    }
    cin>>s;
    if(s.size()!=1){
        cout<<"Invalid instruction.Try again."<<endl;
        return 1;
    }
    switch(s[0]){
        case 'q':GameOver(2);return 0;
        case 'w':Up();Cell();break;
        case 's':Down();Cell();break;
        case 'a':Left();Cell();break;
        case 'd':Right();Cell();break;
        case 'r':Reverse();break;
        default:cout<<"Invalid instruction.Try again."<<endl;return 1;
    }
    if(cellscore>=2048&&!succeeded){
        cout<<"Congratulations!You`ve made a 2048!\nIf you want to continue and enter the Infinity Mode,input y.Otherwise this game will come to an end."<<endl;
        char c;
        cin>>c;
        if(c!='y'){
            cout<<"Congratulations! You did it!"<<endl;
            return 0;
        }
        cout<<"Infinity Mode!GoGoGo!"<<endl;
    }
    if(cellscore>=2048) succeeded=1;
    cout<<"Please input your instruction:"<<endl;
    return 1;
}
void Game::Up(){
    int moved=0,united=0;
    tempscore=operscore;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) tempstate[i][j]=chessboard[i][j];
    for(int j=0;j<m;j++){
        int ii=0,nz=0,r=0,rpt=0;
        int* temp=new int[m];
        for(int i=0;i<m-1;i++){
            if(chessboard[i][j]&&chessboard[i][j]==chessboard[i+1][j]){
                r=1;break;
            }
        }
        while(chessboard[ii][j]&&ii<m) ii++;
        while(!chessboard[ii][j]&&ii<m) ii++;
        if(ii==m&&!r) continue;
        moved++;
        for(int i=0;i<m;i++) if(chessboard[i][j]) temp[nz++]=chessboard[i][j];
        for(int i=0;i<nz;){
            if(i==nz-1) chessboard[rpt++][j]=temp[i++];
            else if(temp[i]==temp[i+1]){
                chessboard[rpt++][j]=temp[i]*2;
                operscore+=temp[i]*2;
                i+=2;
                united++;
            }else chessboard[rpt++][j]=temp[i++];
        }
        for(int i=rpt;i<m;i++) chessboard[i][j]=0;
    }
    if(!moved){
        cout<<"Operation up is invalid.Try other operations!"<<endl;
        return;
    }
    lastelim=succelim;
    succelim=united?succelim+1:0;
    lastscore=tempscore;
    succrev=0;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) laststate[i][j]=tempstate[i][j];
    NewNum();
    Show();
}
void Game::Down(){
    int moved=0,united=0;
    tempscore=operscore;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) tempstate[i][j]=chessboard[i][j];
    for(int j=0;j<m;j++){
        int ii=m-1,nz=0,r=0,rpt=m-1;
        int* temp=new int[m];
        for(int i=0;i<m-1;i++){
            if(chessboard[i][j]&&chessboard[i][j]==chessboard[i+1][j]){
                r=1;break;
            }
        }
        while(chessboard[ii][j]&&ii>=0) ii--;
        while(!chessboard[ii][j]&&ii>=0) ii--;
        if(ii==-1&&!r) continue;
        moved++;
        for(int i=m-1;i>=0;i--) if(chessboard[i][j]) temp[nz++]=chessboard[i][j];
        for(int i=0;i<nz;){
            if(i==nz-1) chessboard[rpt--][j]=temp[i++];
            else if(temp[i]==temp[i+1]){
                chessboard[rpt--][j]=temp[i]*2;
                operscore+=temp[i]*2;
                i+=2;
                united++;
            }else chessboard[rpt--][j]=temp[i++];
        }
        for(int i=rpt;i>=0;i--) chessboard[i][j]=0;
    }
    if(!moved){
        cout<<"Operation down is invalid.Try other operations!"<<endl;
        return;
    }
    lastelim=succelim;
    succelim=united?succelim+1:0;
    lastscore=tempscore;
    succrev=0;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) laststate[i][j]=tempstate[i][j];
    NewNum();
    Show();
}
void Game::Left(){
    int moved=0,united=0;
    tempscore=operscore;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) tempstate[i][j]=chessboard[i][j];
    for(int i=0;i<m;i++){
        int jj=0,nz=0,r=0,rpt=0;
        int* temp=new int[m];
        for(int j=0;j<m-1;j++){
            if(chessboard[i][j]&&chessboard[i][j]==chessboard[i][j+1]){
                r=1;break;
            }
        }
        while(chessboard[i][jj]&&jj<m) jj++;
        while(!chessboard[i][jj]&&jj<m) jj++;
        if(jj==m&&!r) continue;
        moved++;
        for(int j=0;j<m;j++) if(chessboard[i][j]) temp[nz++]=chessboard[i][j];
        for(int j=0;j<nz;){
            if(j==nz-1) chessboard[i][rpt++]=temp[j++];
            else if(temp[j]==temp[j+1]){
                chessboard[i][rpt++]=temp[j]*2;
                operscore+=temp[i]*2;
                j+=2;
                united++;
            }else chessboard[i][rpt++]=temp[j++];
        }
        for(int j=rpt;j<m;j++) chessboard[i][j]=0;
    }
    if(!moved){
        cout<<"Operation left is invalid.Try other operations!"<<endl;
        return;
    }
    lastelim=succelim;
    succelim=united?succelim+1:0;
    lastscore=tempscore;
    succrev=0;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) laststate[i][j]=tempstate[i][j];
    NewNum();
    Show();
}
void Game::Right(){
    int moved=0,united=0;
    tempscore=operscore;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) tempstate[i][j]=chessboard[i][j];
    for(int i=0;i<m;i++){
        int jj=m-1,nz=0,r=0,rpt=m-1;
        int* temp=new int[m];
        for(int j=0;j<m-1;j++){
            if(chessboard[i][j]&&chessboard[i][j]==chessboard[i][j+1]){
                r=1;break;
            }
        }
        while(chessboard[i][jj]&&jj>=0) jj--;
        while(!chessboard[i][jj]&&jj>=0) jj--;
        if(jj==-1&&!r) continue;
        moved++;
        for(int j=m-1;j>=0;j--) if(chessboard[i][j]) temp[nz++]=chessboard[i][j];
        for(int j=0;j<nz;){
            if(j==nz-1) chessboard[i][rpt--]=temp[j++];
            else if(temp[j]==temp[j+1]){
                chessboard[i][rpt--]=temp[j]*2;
                operscore+=temp[i]*2;
                j+=2;
                united++;
            }else chessboard[i][rpt--]=temp[j++];
        }
        for(int j=rpt;j>=0;j--) chessboard[i][j]=0;
    }
    if(!moved){
        cout<<"Operation right is invalid.Try other operations!"<<endl;
        return;
    }
    lastelim=succelim;
    succelim=united?succelim+1:0;
    lastscore=tempscore;
    succrev=0;
    for(int i=0;i<m;i++) for(int j=0;j<m;j++) laststate[i][j]=tempstate[i][j];
    NewNum();
    Show();
}
void Game::Reverse(){
    if(!succrev&&operscore){
        cout<<"Now we return to the last state.Remember don`t trace back continuously.That`s useless."<<endl;
        operscore=lastscore;
        succelim=lastelim;
        succrev=1;
        for(int i=0;i<m;i++) for(int j=0;j<m;j++) chessboard[i][j]=laststate[i][j];
        Show();
    }else cout<<"Continuous tarce back invalid.Try other opertations."<<endl;
}
void Game::Cell(){
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            cellscore=max(cellscore,chessboard[i][j]);
        }
    }
}
void Game::GameOver(int ss){
    if(cellscore<2048) cout<<"The highest number you achieved int this game is: "<<cellscore<<endl;
    else cout<<"Congratulations!The highest number you achieved int this game is"<<cellscore<<"! You did it! So cool!"<<endl;
    cout<<"Your operation score is "<<operscore<<"!AO LI GEI!"<<endl;
    if(ss==1){
        cout<<"The game has ended.\nInput an positive integer if you want to restart,and a negative one if you don`t."<<endl;
        cin>>ss;
        if(!ss>0){
            cout<<"Game over.See you next time!"<<endl;
            exit(0);
        }
    }else if(ss==2){
        cout<<"Are you sure to quit this game?Input an integer to quit."<<endl;
        cin>>ss;
        cout<<"Game over.See you next time!"<<endl;
        exit(0);
    }
}

int main(){
    int sig;
    while(1){
        cout<<"Tab any number key to start he game.<<<<<<>>>>>>Tab any other keys to exit."<<endl;
        cin>>sig;
        if(!(sig>=0)){
            cout<<"Successfully exited.See you next time."<<endl;
            exit(0);
        }
        Game game;
        while(game.Action()) ;
    }    
}
