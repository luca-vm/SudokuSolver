#include <iostream>

using namespace std; 


bool Valid(int grid[9][9], int rows, int cols, int i);

bool FindEmpty (int grid[9][9], int& rows, int& cols);
 

bool Solve(int grid[9][9])
{
    int rows, cols;
 
    if (!FindEmpty(grid, rows, cols)){

        return true;
    }
 
    for (int i = 1; i < 10; i++)
    {
         
        if (Valid(grid, rows, cols, i))
        {
             
            grid[rows][cols] = i;

            if (Solve(grid)){
                return true;
            }

            grid[rows][cols] = 0;
        }
    }

    return false;
}
 

bool FindEmpty (int grid[9][9], int& rows, int& cols)
{
    for (rows = 0; rows < 9; rows++){
        for (cols = 0; cols < 9; cols++){
            if (grid[rows][cols] == 0){
                 return true;
            }               
        }          
    }
        
    return false;
}
 
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
    return (grid[rows][cols] == 0) && (UsedInRow(grid, rows, i))  && (UsedInBox[i](grid, rows - rows % 3, cols - cols % 3, i)) && (UsedInCol(grid, cols, i));
}
 
int main()
{
    
    int grid[9][9];

    for (int rows = 0; rows < 9; ++rows){
        
        for (int cols = 0; cols < 9; ++cols){
            cin >> grid[rows][cols];
        }
    }


    if (Solve(grid)){

        for (int rows = 0; rows < 9; rows++)
        {
            for (int cols = 0; cols < 9; cols++){
                 cout << grid[rows][cols] << " ";
                
                if (cols != 8)
                    cout << " ";
                    
            }      
            cout << endl;

            
        }    
    }
    else {
        cout << "No Solution" << endl;
    }
        
    return 0;
}