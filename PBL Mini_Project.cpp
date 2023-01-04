//Building Game Interface 
//Games Like Tic Tac Toe and Sudoku
#include <iostream>
#include<list>
#include<cstdlib>
#include<string>
#include <ctime>
#include<fstream>
#define N 9
using namespace std;

typedef struct{
    int *row;
}WinList;
 //defining a class for player of tic tac toe game
class Player {
private:
    string name;
    int score;
public:
    Player()
    {
    	name = "";
    	score =0;
	}
    Player(string n)
    {
    	name = n;
    	score =0;
	}
 
    void won(){
        //increment the score
        score++;
    }
    int getScore(){ return this->score;}
    string getName(){ return this->name;}
};
 
class Game {
private:
    char board[9];
    int emptyIndex[9];
    int gameOn, againstComputer;
    int emptyCount;
    WinList winlist[8];
 
    void displayBoard(){
        cout <<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[0] <<" | "<<board[1]<<" | "<<board[2]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[3] <<" | "<<board[4]<<" | "<<board[5]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[6] <<" | "<<board[7]<<" | "<<board[8]<<endl;
        cout << "   |   |   "<<endl;
        cout <<endl;
    }
 
    void computerInput(){
        int pos;
        pos = rand()%10;
        if(emptyIndex[pos] == 1){
            if(emptyCount < 0)
                return;
            computerInput();
        } else {
            cout<< "Computer choose: " << pos+1 << endl;
            emptyIndex[pos] =1;
            emptyCount-=1;
            board[pos] = 'O';
        }
 
    }
 
    void playerInput(Player &player){
        int pos;string s;
        cout << endl;
        cout << "\t" << player.getName() <<" Turn: ";
        cout <<"\t Enter the position " << endl;
        cin >> pos;
        try{
             if(pos>9)
             throw s;
         }
         catch(...)
         {
             cout<<"Please enter valid number(0 to 9)"<<endl;
             cin>>pos;
         }
        pos -=1;
        if(emptyIndex[pos] == 1){
            cout << "-----Position not empty-------"<< endl;
            playerInput(player);
        } else {
            emptyIndex[pos] =1;
            emptyCount-=1;
            player.getName().compare("Player I") == 0 ? board[pos] ='X': board[pos] ='O';
               }
    }
    void checkWin(Player &p1,Player &p2){
        ofstream fout;
        int i,j,k;
        bool flag = false;
        char first_symbol;
        for(i=0; i<8; i++){
            first_symbol = board[winlist[i].row[0]];
 
            if((first_symbol != 'X') && (first_symbol != 'O')){
                flag = false;
                continue;
            }
            flag = true;
            for(j=0;j<3;j++){
                if(first_symbol != board[winlist[i].row[j]]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                gameOn = 0;
                if(first_symbol == 'X'){
                    cout << "-----------------------"<< endl;
                    cout << "\t Player I WON"<< endl;
                    cout << "-----------------------"<< endl;
                    p1.won();
                    fout.open("Tic_Tac_Toe",ios::app);
                    fout<<"Player I won"<<endl;
                    fout.close();
                } else {
                    p2.won();
                    if(againstComputer){
                        cout << "-----------------------"<< endl;
                        cout << "\t Computer WON"<< endl;
                        cout << "-----------------------"<< endl;
                        fout.open("Tic_Tac_Toe",ios::app);
                        fout<<"COMPUTER win"<<endl;
                        fout.close();
                    } else {
                        cout << "-----------------------"<< endl;
                        cout << "\t Player II WON"<< endl;
                        cout << "-----------------------"<< endl;
                        fout.open("Tic_Tac_Toe",ios::app);
                        fout<<"Player II win"<<endl;
                        fout.close();
                    }
                }
                displayScore(p1,p2);
                break;
            }
        }
    }
        void play(Player &p1,Player &p2){
            char rematch ='\0';
            int hand = 0;
            gameOn =1;
            displayBoard();
            while((emptyCount > 0) && (gameOn != 0)){
 
                if(againstComputer)
                    hand == 1 ? computerInput(): playerInput(p2);
                else
                    hand == 1 ? playerInput(p1): playerInput(p2);
                hand= !hand;
                displayBoard();
                checkWin(p1,p2);
            }
            if (emptyCount <=0){
                cout << "      -----------------------"<< endl;
                cout << "\t No WINNER"<< endl;
                cout << "      -----------------------"<< endl;
            }
            cout<< endl;
            cout << "Rematch Y/N: ";
            cin >> rematch;
            if((rematch == 'Y')||(rematch == 'y')){
                init();
                play(p1,p2);
            }
        }
    void displayScore(Player &p1, Player &p2){
        cout << endl;
        cout << "\t SCORE: \t";
        if(againstComputer)
            cout<<" Player I: " <<p1.getScore()<<" \t Computer: "<<p2.getScore()<< endl;
        else
            cout<<" Player I: " <<p1.getScore()<<" \t Player II: "<<p2.getScore()<< endl;
    }
public:
    Game(){
    	emptyCount = 0;
    	gameOn = 1;
    	againstComputer =0;
        init();
        winlist[0].row = new int[3]{0,1,2};
        winlist[1].row = new int[3]{3,4,5};
        winlist[2].row = new int[3]{6,7,8};
        winlist[3].row = new int[3]{0,3,6};
        winlist[4].row = new int[3]{1,4,7};
        winlist[5].row = new int[3]{2,5,8};
        winlist[6].row = new int[3]{0,4,8};
        winlist[7].row = new int[3]{2,4,6};
    }
 
    void init(){
        gameOn = 1;
 
        emptyCount =0;
        srand(time(0));
        for(size_t i=0; i<10; i++){
            emptyIndex[i] = 0;
            board[i] = (i+1) +'0';
            emptyCount++;
        }
        emptyCount--;
    }
 
    void onePlayerGame(){
        //Creating Player
        Player p("Player I");
        Player c("Computer");
        cout << "       -----------------------"<< endl;
        cout << "\t Player I: X \t Computer: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        againstComputer = 1;
        play(c,p);
    }
    void twoPlayerGame(){
        //Creating Player
        Player p("Player I");
        Player c("Player II");
        cout << "       -----------------------"<< endl;
        cout << "\t Player I: X \t Player II: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        againstComputer = 0;
        play(c,p);
    }
};
void tictactoe()
{
  int ch;
  ofstream fout;
 
    while(1){
        cout<< "      ----------MENU----------" << endl;
        cout << "\t 1. 1 Player game" <<endl;
        cout << "\t 2. 2 Player game" <<endl;
        cout << "\t 3. Return to Main menu " <<endl;
        cout <<"      ------------------------" << endl;
        cout << endl;
        cout <<"\t Select an option" << endl;
        cin >> ch;
        switch(ch){
        case 1:{
            Game *game = new Game;
            game->init();
            game->onePlayerGame();
            }
            break;
        case 2:{
            Game *game = new Game;
            game->init();
            game->twoPlayerGame();
            }
            break;
        case 3:
            return;
        default:
            cout << "OOPs Invalid Option! TRY AGAIN";
        }
    }
}
class SudokuG{
    public:
 int grid[9][9] = {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
     };
void readGrid()
{
 cout<<"Enter the elements row by row"<<endl;string s;
 for(int i=0;i<9;i++)
   {
     for(int j=0;j<9;j++)
       {
         cin>>grid[i][j];
         try{
             if(grid[i][j]>9)
             throw s;
         }
         catch(...)
         {
             cout<<"Please enter valid number(0 to 9)"<<endl;
             cin>>grid[i][j];
         }
       }
   }
}
};
class Sudokucheck : public SudokuG
{
    public:
    bool isPresentInCol(int col, int num){ //check whether num is present in col or not
   for (int row = 0; row < N; row++)
      if (grid[row][col] == num)
         return true;
   return false;
}
bool isPresentInRow(int row, int num){ //check whether num is present in row or not
   for (int col = 0; col < N; col++)
      if (grid[row][col] == num)
         return true;
   return false;
}
bool isPresentInBox(int boxStartRow, int boxStartCol, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (grid[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}
void sudokuGrid(){ //print the sudoku grid after solve
 ofstream fout;
 fout.open("Sudoku",ios::app);
   for (int row = 0; row < N; row++){
      for (int col = 0; col < N; col++){
         if(col == 3 || col == 6)
            cout << " | ";
         cout << grid[row][col] <<" ";
         fout<<grid[row][col]<<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<N; i++)
            cout << "---";
      }
      cout << endl;
      fout<<endl;
   }
   fout.close();
}
bool findEmptyPlace(int &row, int &col){ //get empty location and update row and column
   for (row = 0; row < N; row++)
      for (col = 0; col < N; col++)
         if (grid[row][col] == 0) //marked with 0 is empty
            return true;
   return false;
}
bool isValidPlace(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
col - col%3, num);
}
};
class Sudokusolve : public Sudokucheck
{
    public:
bool solveSudoku(){
   int row, col;
   if (!findEmptyPlace(row, col))
      return true; //when all places are filled
   for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
      if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the grid
         grid[row][col] = num;
         if (solveSudoku()) //recursively go for other rooms in the grid
            return true;
         grid[row][col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   }
   return false;
}
};
void Sudoku()
{
  int ch;
  Sudokusolve s;
  cout<<"Enter Your Choice of Game Type\n1] System Input\n2] User Input \n3] Go to Main Menu\n"<<endl;
  cin>>ch;
  switch(ch)
    {
      case 1:
        if (s.solveSudoku() == true)
        {s.sudokuGrid();}
        else
        {cout << "No solution exists";}
      break;
      case 2:
        s.readGrid();
      if (s.solveSudoku() == true)
        {s.sudokuGrid();}
      else
        {cout << "No solution exists";}
      break;
      case 3:
      return;
      }
}
int main(){
  int choice,ch;
  cout<<"\t-----WELCOME TO GAME ARENA-----"<<endl;
  do{
  cout<<"Enter the choice of Game You Want to play\n1] Sudoku \n2] Tic Tac Toe \n3] Exit"<<endl;
  cin>>choice;
    switch(choice)
      {
        case 1:
        Sudoku();
          break;
        case 2:
        tictactoe();
        break;
        case 3:
        exit(0);
        break;
        }
    }while(choice != 3);
}
