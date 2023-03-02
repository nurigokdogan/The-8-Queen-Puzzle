#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void HCS(int[]);
void generateChild(int[],int);
int numOfAttacks(int[]);
void generateRandom(int[]);
int findIndex(int,int);
void arrCopy(int[],int[]);
void swap(int[],int,int);
void displayBoard(int[]);

int main()
{
    
    int board[64];
    for (int i = 0; i < 64; i++)
    {
        board[i] = 0;
    }
    
   
    generateRandom(board);
    cout << "Olusturulan tahta:";
    displayBoard(board);
    
    HCS(board);
    
    if (numOfAttacks(board) > 0)
    {
        cout << "\n\nCozulemedi. Peak:";
        displayBoard(board);
        cout << endl << endl;
    }
    
    else
    {
        cout << "\n\nCozuldu.";
        displayBoard(board);
        cout << endl << endl;
    }
    
    return 0;
}

void HCS(int initialState[])
{
    int current[64]; 
    arrCopy(current, initialState);
    const int MAX = 28;
    int next[64]; 
    int child[64]; 
    
    while (true)
    {
        int min = MAX;
        
        arrCopy(child,current);
        
        int currentQueen = 0;
        
        for (int i = 0; i < 56; i++) 
        {
            generateChild(child, currentQueen);
            
            int attacks = numOfAttacks(child);
            
            if (attacks < min)
            {
                min = attacks;
                arrCopy(next,child);
            }
            
           
            if (i % 7 == 6) 
            {
               
                generateChild(child, currentQueen);
                
                
                currentQueen++;
            }
        }
        
        if (min >= numOfAttacks(current))
        {
            arrCopy(initialState,current); 
            break; 
        }
        
        arrCopy(current,next);
    }
}

void generateChild(int board[], int currentQueen) 
{
    int currentRow;
    
    for (int i = 0; i < 8; i++) 
    {
        if (board[findIndex(i,currentQueen)] == 1)
        {
            currentRow = i;
            break;
        }
    }
    
    if (currentRow < 7)
    {
       
        swap(board, findIndex(currentRow,currentQueen), findIndex(currentRow + 1,currentQueen));
    }
    
    else if (currentRow == 7) 
    {
        
        swap(board, findIndex(currentRow,currentQueen), findIndex(0,currentQueen));
    }
}

int numOfAttacks(int board[])
{
    
    int index[8];
    int indexPos = 0;
    
    for (int i = 0; i < 64; i++)
    {
        if (board[i] == 1)
        {
            index[indexPos] = i;
            indexPos++;
        }
    }
    
  
    int rowAttacks = 0;
    
    for (int i = 0; i < 7; i++) 
    {
        for (int j = i + 1; j < 8; j++) 
        {
            if ((index[i] / 8) == (index[j] / 8)) 
                rowAttacks++;
        }
    }
    
   
    int row1, row2, col1, col2, diagAttacks = 0;
    
    for (int i = 0; i < 7; i++) 
    {
        row1 = index[i] / 8;
        col1 = index[i] % 8;
        
        for (int j = i + 1; j < 8; j++) 
        {
            row2 = index[j] / 8;
            col2 = index[j] % 8;
            
            if (abs(row1 - row2) == abs(col1 - col2))
                diagAttacks++;
        }
    }
    
    return rowAttacks + diagAttacks;
}

void generateRandom(int board[])
{
    int t = (unsigned int)time(0);
    srand(t);
    int r;
    
    for (int i = 0; i < 8; i++)
    {
        r = rand() % 8; 
        
        for (int j = 0; j < 8; j++)
        {
            if (j == r)
                board[findIndex(j, i)] = 1;
        }
    }
}

int findIndex(int row, int col)
{
    int index = 0;
    index += (row * 8);
    index += col;
    
    return index;
}

void arrCopy(int arr1[], int arr2[])
{
    for (int i = 0; i < 64; i++)
    {
        arr1[i] = arr2[i];
    }
}

void swap(int board[], int index1, int index2)
{
    if (board[index1] == 0)
    {
        board[index1] = 1;
        board[index2] = 0;
    }
    else if (board[index1] == 1)
    {
        board[index1] = 0;
        board[index2] = 1;
    }
}

void displayBoard(int board[])
{
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
            cout << endl;
        
        if (board[i] == 0)
            cout << "0 ";
        
        else if (board[i] == 1)
            cout << "1 ";
    }
}
