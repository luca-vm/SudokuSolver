#include <iostream>
#include <stack>
#include <vector>

using namespace std; 

bool UsedInCol(int grid[9][9], int cols, int i)
{
    for (int rows = 0; rows < 9; rows++){
        if (grid[rows][cols] == i){
        return false;
        }       
    }     
    return true;
}
 
bool UsedInBox[i](int grid[9][9], int box[i]StartRow, int box[i]StartCol, int i)
{
    for (int rows = 0; rows < 3; rows++){
        for (int cols = 0; cols < 3; cols++){
            if (grid[rows + box[i]StartRow][cols + box[i]StartCol] == i)
                return false;
        }         
    }
        
    return true;
}

bool UsedInRow(int grid[9][9], int rows, int i)
{
    for (int cols = 0; cols < 9; cols++){
        if (grid[rows][cols] == i){
             return false;
        }         
    }
        
    return true;
}
 

bool Valid(int grid[9][9], int rows, int cols, int i)
{    
    return (UsedInRow(grid, rows, i))  && (UsedInBox[i](grid, rows - rows % 3, cols - cols % 3, i)) && (UsedInCol(grid, cols, i));
}

bool FindEmpty (int grid[9][9], int& rows, int& cols, bool empt)
{
    if (empt){
        for (rows = 0; rows < 9; rows++){
            for (cols = 0; cols < 9; cols++){
                if (grid[rows][cols] == 0){
                    return true;
                }               
            }          
        }
    }
    else 
    {
      for (rows; rows < 9; rows++){
            for (cols = 0; cols < 9; cols++){
                if (grid[rows][cols] == 0){
                    return true;
                }       
            }          
        }  
    }
        
    return false;
}

int CalcI(int grid[9][9], int rows, int cols){

    vector<int> choices = {1,2,3,4,5,6,7,8,9};

    if (cols == 7){
        int total = 1;
        int x[i];
        for (int j = 0; j < 7; j++){
            total *= grid[rows][j];
        }

        x[i] = (9*8*7*6*5*4*3*2) / total; 

        for (int k = 1; k <= x[i]; k++){
            if ((x[i] / k <= 9)&&(x[i] % k == 0)){
                return k;
            }
        }
    }

     if (rows == 7){
        int total = 1;
        int x[i];
        for (int j = 0; j < 7; j++){
            total *= grid[j][cols];
        }

        x[i] = (9*8*7*6*5*4*3*2) / total; 

        for (int k = 1; k <= x[i]; k++){
            if ((x[i] / k <= 9)&&(x[i] % k == 0)){
                return k;
            }
        }
    }



    if (cols == 8){
        int total = 0;
        for (int j = 0; j < 8; j++){
            total += grid[rows][j];
        }

        return (45 - total);
    }

    if (rows == 8){
        int total = 0;
        for (int j = 0; j < 8; j++){
            total += grid[j][cols];
        }

        return (45 - total);
    }

    return 1;

}

bool Solve(int grid[9][9]){

    stack<pair<int,int>> stack1;

    int rows, cols, i;
    bool empt = stack1.empty();

    while (FindEmpty(grid, rows, cols, empt)){

        stack1.push({rows, cols});
        i = CalcI(grid, rows, cols);
        empt = stack1.empty();

        while (!Valid(grid, stack1.top().first , stack1.top().second, i))
        {
            
            if (i < 9)
            {
                i++;    
            } 
            else
            { 
                i++;
                while (i > 9){
                    grid[stack1.top().first][stack1.top().second] = 0;
                    stack1.pop();
                    
                    if (!stack1.empty()){
                        rows = stack1.top().first;
                        i = grid[stack1.top().first][stack1.top().second] + 1;
                    }
                    else
                    {
                        return false;
                    }
                }
                      
            }
                        
        }  
         grid[stack1.top().first][stack1.top().second] = i;    
    }  
       
    
    return true;
} 

int main(){

    int grid[9][9];

    for (int rows = 0; rows < 9; ++rows){
        
        for (int cols = 0; cols < 9; ++cols){
            cin >> grid[rows][cols];
             
        }
    }

    if (Solve(grid)){

        for (int rows = 0; rows < 9; ++rows){
            
            for (int cols = 0; cols < 9; ++cols){
                    cout << grid[rows][cols] << ' ';

                     if (cols != 8)
                    cout << " ";
                    
                }
            cout << endl;
        }
    } 
    else
    {
        cout << "No Solution" << endl;

    }    
    return 0;
}
    
   


