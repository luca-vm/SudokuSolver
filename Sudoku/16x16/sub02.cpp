#include <iostream>
#include <forward_list>
#include <vector>

// Adaptation of the basic principle of Dancing links originally by Donald Knuth

using namespace std;

forward_list<int> solvedGrid; 
int grid[16][16];

bool Solved = false;

struct Sudoku
{    
    struct header; 
    struct node
    {
        int row;
        header *head;
        node *up, *down, *right, *left;
    };

    struct header : node
    {
        int count; 
        header *right, *left;
    };
    
    int n, numRow, numCol;
    header *root; 

    vector<vector<node>> row;
    vector<header> col;

    Sudoku()
    {       
        numCol = 1 + (4 * 16 * 16); 
        numRow = 16 * 16 * 16;       

        row = vector<vector<node>>(numRow, vector<node>(4, node())); 
        col = vector<header>(numCol, header());                      

        root = &(col[numCol - 1]); 

        for (int i = 0; i < numCol; i++) 
        {
            col[i].left = &(col[(i + numCol - 1) % numCol]);
            col[i].right = &(col[(i + 1) % numCol]);
            col[i].up = &col[i];
            col[i].down = &col[i];

            col[i].count = 0; 
        }

        int n = 16 * 16;         
        int box[i]Width = 4; 

        for (int i = 0; i < numRow; i++) 
        {
            int colIn, currRow = i / (16 * 16), currCol = (i / 16) % 16, off = i % 16;

            if (grid[currRow][currCol] != 0 && grid[currRow][currCol] != off + 1) 
                continue;

            for (int j = 0; j < 4; j++) 
            {
                int startCol = n * j; 

               switch (j)
                {
                case 0: 
                    colIn = i / 16;
                    break;
                case 1: 
                    colIn = n + (currRow * 16) + off;
                    break;
                case 2: 
                    colIn = startCol + off + ((i / 16) % 16) * 16;
                    break;
                case 3: 
                    colIn = startCol + off + (box[i]Width * (currRow / box[i]Width) + (currCol / box[i]Width)) * 16 ;
                    break;
                } 


                row[i][j].right = &(row[i][(j + 1) % 4]);
                row[i][j].left = &(row[i][(j + 3) % 4]);
                row[i][j].row = i;
                row[i][j].down = &col[colIn]; 
                row[i][j].up = col[colIn].up;   
                row[i][j].head = &col[colIn];   
                row[i][j].up->down = &row[i][j]; 
                row[i][j].down = &col[colIn];   
                col[colIn].up->down = &(row[i][j]); 
                col[colIn].up = &(row[i][j]);

                col[colIn].count++; 
            }
        }
    };

    void Solve()
    {
        if (root->right == root) 
        {
            Solved = true;

            int curRow, curCol, off;

        for (int &i : solvedGrid) 
        {   
            curRow = i / (16 * 16);
            curCol = (i / 16) % 16;
            off = 1 + i % 16;
            grid[curRow][curCol] = off; 
        }

        for (int i = 0; i < 16; i++) 
        {
            for (int j = 0; j < 16; j++)
            {
                if (grid[i][j] >= 10)
                    cout << char(grid[i][j] + 55);
                else
                    cout << grid[i][j];

                if (j != 15)
                    cout << " ";
            }

            cout << endl;
        }
            return;
        }

        header *bestCol = root->right; 

        for (header *i = root->right; i != root; i = i->right) 
        {
            if (i->count < bestCol->count) 
                bestCol = i;
        }

        cover(bestCol); 

        for (node *currRow = bestCol->down; currRow != bestCol; currRow = currRow->down)
        {

            solvedGrid.push_front(currRow->row); 

            for (node *currCol = currRow->right; currCol != currRow; currCol = currCol->right) 
                cover(currCol->head);                                                          

            Solve();             
            solvedGrid.pop_front();

            for (node *currCol = currRow->left; currCol != currRow; currCol = currCol->left) 
                uncover(currCol->head);
        }

        uncover(bestCol);
    }

    void uncover(header *col)
    {
       
        for (node *j = col->up; j != col; j = j->up) 
        {
            for (node *i = j->left; i != j; i = i->left) 
            {
             i->head->count++; 
                i->up->down = i; 
                i->down->up = i;
            }
        }

        col->right->left = col; 
        col->left->right = col;
    }

    void cover(header *col)
    {
        col->right->left = col->left;  
        col->left->right = col->right; 

        for (node *j = col->down; j != col; j = j->down) 
        {
            for (node *i = j->right; i != j; i = i->right) 
            {
                i->head->count--; 
                i->up->down = i->down; 
                i->down->up = i->up;
            }
        }
    }
};

int main()
{
    string line;

    int i = 0;

    for (int rows = 0; rows < 16; ++rows){
        
        for (int cols = 0; cols < 16; ++cols){
            char x[i];
            cin >> x[i];
            if ((x[i] >= 48)&&(x[i] <= 57)){
                 grid[rows][cols] = x[i] - 48;
            }
            else
            {
                grid[rows][cols] = char(x[i]) - 55;
            }
            
             
        }
    }

    Sudoku Grid;
    Grid.Solve();

    if (Solved == false)
        cout << "No Solution" << endl;

    return 0;
}