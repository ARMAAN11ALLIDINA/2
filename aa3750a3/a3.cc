#include <iostream>
#include <vector>
#include <string>
using namespace std;
void Output(vector<vector<bool>>& board, vector<string>& lines, bool last);
void Solve(vector<vector<bool>>& board, vector<string>& lines, int N, int& solNum, int cnt=0, int iStart=0, int jStart=0, int depth=0){
    if(cnt>=N){
        Output(board, lines, false);
        ++solNum;
        return;
    }
    for (int i=iStart; i<board.size(); ++i)
        for (int j=i==iStart?jStart:0; j<board[i].size(); ++j) {
            bool attacked=false;
            for (int k=0; k<(board.size()>board[i].size()?board.size():board[i].size()); ++k)
                if(k<board[i].size()&&k!=j&&board[i][k]||k<board.size()&&k!=i&&board[k][j]||k<board.size()&&k!=i&&0<=j-i+k&&j-i+k<board[i].size()&&board[k][j-i+k]||k<board.size()&&k!=i&&0<=j+i-k&&j+i-k<board[i].size()&&board[k][j+i-k]){
                    attacked=true;
                    break;
                }
            if(attacked)
                continue;
            board[i][j]=true;
            Solve(board, lines, N, solNum, cnt+1, i, j+1, depth+1);
            board[i][j]=false;
        }
    if(depth==0)
        Output(board, lines, true);
}
void Output(vector<vector<bool>>& board, vector<string>& lines, bool last){
    if(1){
        if(!last){
            for(int i=0; i<board.size(); ++i){
                for (int j=0; j<board[i].size(); ++j)
                    lines[i].push_back(board[i][j]?'Q':'.');
                lines[i]+="|";
            }
        }
        if(lines.at(0).size()>=70||last&&!lines.at(0).empty()){
            for(int i=0; i<lines.size(); ++i)
                cout<<lines[i]<<endl;
            for(int j=0; j<lines.at(0).size(); ++j)
                 cout<<(lines.at(0)[j]=='|'? '+':'-');
            cout<<endl;
            lines.clear();
            lines.resize(board.size());
        }
    }
}
int main(){
    int N;
    cout<<"enter number of queens"<<endl;
    cin>>N;
    vector<vector<bool>> board(N, vector<bool>(N));
    vector<string> lines(N);
    int solNum=0;
    Solve(board, lines, N, solNum);
    cout<<"Number of solutions: "<<solNum<<endl;
}

