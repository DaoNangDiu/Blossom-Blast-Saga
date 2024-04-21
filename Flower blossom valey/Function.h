#ifndef FUNCTION_H
#define FUNCTION_H
#include<bits/stdc++.h>
int MATRIX_WIDTH;
int MATRIX_HEIGHT;
using namespace std;

int target;
int moves  ;
int score;
ifstream f("Level 1.txt");

char element;
void nhapfile()
{
     f >> moves >> target >> MATRIX_WIDTH >> MATRIX_HEIGHT;
     cout << moves << " " << target << " " << MATRIX_WIDTH << " " << MATRIX_HEIGHT;
}
char elementCheck( int i )
{
    switch (i)
    {
    case 0:
    case 5:
    case 11:
        return 'h';
        break;
    case 1:
    case 6:
    case 12:
        return 'c';
        break;
    case 2:
    case 7:
    case 13:
        return 'l';
        break;
    case 3:
    case 8:
    case 14:
        return 'n';
        break;
    case 4:
    case 9:
    case 15:
        return 'd';
        break;
    case 10:
        return 'o';
        break;
    default:
        break;
    }
}

void scorer ( char element, int num )
{
    switch(element)
    {
    case 'h':
    case 'c':
    {
        score += (30*num);
        break;
    }
    case 'n':
    case 'l':
    {
        score += (40*num);
        break;
    }
    case 'r':
    {
        score+= (50*num);
        break;
    }
    default:
    {
        break;
    }
    }
}

void getRowChain(int i, int j, vector<pair<int,int>> &chaiList, int** matrix)
{
    chaiList.push_back(make_pair(i,j));
    int neighCol = j-1;
    while ( neighCol >= 0 )
    {
        if( elementCheck(matrix[i][neighCol]) == elementCheck(matrix[i][j]) )
        {
            chaiList.push_back(make_pair(i,neighCol));
            neighCol--;
        }
        else break;
    }
    neighCol = j+1;
    while ( neighCol < MATRIX_HEIGHT )
    {
        if( matrix[i][neighCol] == matrix[i][j] )
        {
            chaiList.push_back(make_pair(i,neighCol));
            neighCol++;
        }
        else break;
    }
}

void getColChain(int i, int j, vector<pair<int,int>> &chainList, int** matrix)
{
    chainList.push_back(make_pair(i,j));
    int neighRow = i-1;
    while ( neighRow >= 0 )
    {
        if ( elementCheck(matrix[neighRow][j]) == elementCheck(matrix[i][j]) )
        {
            chainList.push_back(make_pair(neighRow,j));
            neighRow--;
        }
        else break;
    }
    neighRow = i+1;
    while ( neighRow < MATRIX_WIDTH )
    {
        if ( elementCheck(matrix[neighRow][j]) == elementCheck(matrix[i][j]) )
        {
            chainList.push_back(make_pair(neighRow,j));
            neighRow++;
        }
        else break;
    }
}

void plain ( int** matrix,int i, int j, int& score)
{
    vector<pair<int,int>> colChainList;
    vector<pair<int,int>> rowChainList;
    getRowChain(i,j,rowChainList,matrix );
    getColChain(i,j,colChainList,matrix);
    int ColSize = colChainList.size();
    int RowSize = rowChainList.size();
    if ( RowSize >= 3 )
    {
        element = elementCheck(matrix[i][j]);
        for (auto index : rowChainList )
        {
            if ( matrix[index.first][index.second] >= 5 && matrix[index.first][index.second] < 10 )
            {
                for ( int x = -1 ; x <= 1 ; x++ )
                    for ( int y = -1 ; y <= 1 ; y++ )
                    {
                        if ( matrix[index.first+x][index.second+y] > 10 )
                        {
                            matrix[index.first+x][index.second+y] -= 11;
                        }
                        else
                        {
                            matrix[index.first-1][index.second] = -1;
                            matrix[index.first+1][index.second] = -1;
                            matrix[index.first][index.second-1] = -1;
                            matrix[index.first][index.second+1] = -1;
                            matrix[index.first-1][index.second-1] = -1;
                            matrix[index.first+1][index.second+1] = -1;
                            matrix[index.first-1][index.second+1] = -1;
                            matrix[index.first+1][index.second-1] = -1;
                            matrix[index.first][index.second] = -1;
                            scorer(element,6);
                        }
                    }
            }
            else
            {
                if ( matrix[index.first][index.second] > 10 )
                    matrix[index.first][index.second] -= 11;
                else
                {
                    matrix[index.first][index.second] = -1;
                    scorer(element,1);
                }
            }
        }
    }
    if ( ColSize >= 3 )
    {
        for (auto index : colChainList )
        {
            if ( matrix[index.first][index.second] >= 5 && matrix[index.first][index.second] < 10 )
            {
                for ( int x = -1 ; x <= 1 ; x++ )
                    for ( int y = -1 ; y <= 1 ; y++ )
                    {
                        if ( matrix[index.first+x][index.second+y] > 10 )
                        {
                            matrix[index.first+x][index.second+y] -= 11;
                        }
                        else
                        {
                            matrix[index.first-1][index.second] = -1;
                            matrix[index.first+1][index.second] = -1;
                            matrix[index.first][index.second-1] = -1;
                            matrix[index.first][index.second+1] = -1;
                            matrix[index.first-1][index.second-1] = -1;
                            matrix[index.first+1][index.second+1] = -1;
                            matrix[index.first-1][index.second+1] = -1;
                            matrix[index.first+1][index.second-1] = -1;
                            matrix[index.first][index.second] = -1;
                            scorer(element,6);
                        }
                    }
            }
            else
            {
                if ( matrix[index.first][index.second] > 10 )
                    matrix[index.first][index.second] -= 11;
                else
                {
                    matrix[index.first][index.second] = -1;
                    scorer(element,1);
                }
            }
        }
    }
}


void stripes ( int** matrix, int i, int j )
{
    element = elementCheck(matrix[i][j]);
    int temp = matrix[i][j];
    vector<pair<int,int>> colChainList;
    vector<pair<int,int>> rowChainList;
    getRowChain(i,j,rowChainList,matrix );
    getColChain(i,j,colChainList,matrix);
    int ColSize = colChainList.size();
    int RowSize = rowChainList.size();
    if ( ColSize >= 3 && RowSize >= 3 )
    {
        for ( auto index : rowChainList )
        {
            if (matrix[index.first][index.second] > 10 )
                matrix[index.first][index.second] -= 11;
            else
                matrix[index.first][index.second] = -1;
        }
        for ( auto index : colChainList )
        {
            matrix[index.first][index.second] = -1;
        }
        scorer(element,ColSize+RowSize-1);
        matrix[i][j] = temp + 5;
    }
}

void bee ( int** matrix, int i, int j )
{
    element = elementCheck(matrix[i][j]);
    vector<pair<int,int>> colChainList;
    vector<pair<int,int>> rowChainList;
    getRowChain(i,j,rowChainList,matrix );
    getColChain(i,j,colChainList,matrix);
    int ColSize = colChainList.size();
    int RowSize = rowChainList.size();
    if ( ColSize >= 5 )
    {
        for ( auto index : colChainList )
        {
            matrix[index.first][index.second] = -1;
            cout << index.first << " " << index.second << endl;

        }
        scorer(element,ColSize);
        matrix[i][j] = 10;
    }
    if ( RowSize >= 5 )
    {
        for ( auto index : rowChainList )
        {
            matrix[index.first][index.second] = -1;
            cout << index.first << " " << index.second << endl;

        }
        scorer(element,RowSize);
        matrix[i][j]=10;
    }
}

void beeplain( int** matrix, int i, int j, int selectedX, int selectedY )
{
    if( matrix[selectedX][selectedY] == 10 )
    {
        if ( matrix[i][j] >= 0 && matrix[i][j] < 5 )
        {
            element = elementCheck(matrix[i][j]);
            int temp = matrix[i][j];
            matrix[selectedX][selectedY] = -1;
            matrix[i][j] = -1;
            for ( int x = 0 ; x < MATRIX_WIDTH ; x++ )
                for ( int y = 0 ; y < MATRIX_HEIGHT ; y++ )
                {
                    if ( matrix[x][y] == temp )
                    {
                        matrix[x][y] = -1;
                        scorer(element,1);
                    }
                }
        }
    }
    if( matrix[i][j] == 10 )
    {
        if ( matrix[selectedX][selectedY] >= 0 && matrix[selectedX][selectedY] < 5 )
        {
            int temp = matrix[selectedX][selectedY];
            element = elementCheck(temp);
            matrix[selectedX][selectedY] = -1;
            matrix[i][j] = -1;
            for ( int x = 0 ; x < MATRIX_WIDTH ; x++ )
                for ( int y = 0 ; y < MATRIX_HEIGHT ; y++ )
                {
                    if ( matrix[x][y] == temp )
                    {
                        matrix[x][y] = -1;
                        scorer(element,1);
                    }
                }
        }
    }
}

void stripes2 ( int** matrix, int i, int j, int selectedX, int selecttedY )
{
    if ( matrix[i][j] >= 5 && matrix[i][j] < 10 && matrix[selectedX][selecttedY] >= 5 && matrix[selectedX][selecttedY] < 10 )
    {
        for ( int x = -2 ; x <= 1 ; x++)
            for ( int y = -2; y <= 1 ; y++ )
            {
                scorer(elementCheck(matrix[i+x][j+y]),1);
                scorer(elementCheck(matrix[selectedX+x][selecttedY+y]),1);
                matrix[i+x][j+y] = -1;
                matrix[selectedX+x][selecttedY+y] = -1;
            }
    }
}

void bee2 (int** matrix, int i, int j,int selectedX, int selectedY)
{
    if ( matrix[i][j] == 10 && matrix[selectedX][selectedY] == 10 )
    {
        matrix[i][j]=-1;
        matrix[selectedX][selectedY]=-1;
        for ( int x =0  ; x < MATRIX_WIDTH ; x++)
            for ( int y = 0 ; y < MATRIX_HEIGHT ; y++ )
            {
                scorer(elementCheck(matrix[x][y]),1);
                matrix[x][y] = -1;
            }
    }
}


#endif // FUNCTION_H

