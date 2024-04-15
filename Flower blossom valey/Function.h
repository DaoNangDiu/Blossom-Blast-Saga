#ifndef FUNCTION_H
#define FUNCTION_H
#include<bits/stdc++.h>
#define MATRIX_WIDTH (10)
#define MATRIX_HEIGHT (5)
using namespace std;

const int target = 500, moves = 20 ;

int rstart = 0, cstart = 0;
int cropped = 0 ;

char elementCheck( int i )
{
    switch (i)
    {
    case 0:
    case 5:
        return 'fl';
        break;
    case 1:
    case 6:
        return 'tr';
        break;
    case 2:
    case 7:
        return 'fi';
        break;
    case 3:
    case 8:
        return 'wa';
        break;
    case 4:
    case 9:
        return 'tr';
        break;
    case 10:
        return 'be';
        break;
    default:
        break;
    }
}
void getColChain(int i, int j, vector<pair<int,int>> &chainList, int** matrix)
{
    chainList.push_back(make_pair(i,j));
    int neighCol = j-1;
    while ( neighCol >= 0 )
    {
        if( elementCheck(matrix[i][neighCol]) == elementCheck(matrix[i][j]) )
        {
            chainList.push_back(make_pair(i,neighCol));
            neighCol--;
        }
        else break;
    }
    neighCol = j+1;
    while ( elementCheck(neighCol) < elementCheck(MATRIX_HEIGHT))
    {
        if( matrix[i][neighCol] == matrix[i][j] )
        {
            chainList.push_back(make_pair(i,neighCol));
            neighCol++;
        }
        else break;
    }
}

void getRowChain(int i, int j, vector<pair<int,int>> &chainList, int** matrix)
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

void plain ( int** matrix,int i, int j)
{
    vector<pair<int,int>> colChainList;
    vector<pair<int,int>> rowChainList;
    getRowChain(i,j,rowChainList,matrix );
    getColChain(i,j,colChainList,matrix);
    int ColSize = colChainList.size();
    int RowSize = rowChainList.size();
    if ( RowSize >= 3 )
    {
        for (auto index : rowChainList )
        {
            if ( matrix[index.first][index.second] >= 5 && matrix[index.first][index.second] < 10 )
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
            }
            else
                matrix[index.first][index.second] = -1;
        }
    }
    if ( ColSize >= 3 )
    {
        for (auto index : colChainList )
        {
            if ( matrix[index.first][index.second] >= 5 && matrix[index.first][index.second] < 10 )
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
            }
            else
                matrix[index.first][index.second] = -1;
        }
    }
}


void stripes ( int** matrix, int i, int j )
{
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
            matrix[index.first][index.second] = -1;
        }
        for ( auto index : colChainList )
        {
            matrix[index.first][index.second] = -1;
        }
        matrix[i][j] = temp + 5;
    }
}

void bee ( int** matrix, int i, int j )
{
    int temp = matrix[i][j];
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
        }
        matrix[i][j] = 10;
    }
    if ( RowSize >= 5 )
    {
        for ( auto index : rowChainList )
        {
            matrix[index.first][index.second] = -1;
        }
        matrix[i][j]=10;
    }
}

void beeplain( int** matrix, int i, int j, int selectedX, int selectedY )
{
    if( matrix[selectedX][selectedY] == 10 )
    {
        if ( matrix[i][j] >= 0 && matrix[i][j] < 5 )
        {
            int temp = matrix[i][j];
            matrix[selectedX][selectedY] = -1;
            matrix[i][j] = -1;
            for ( int x = 0 ; x < MATRIX_WIDTH ; x++ )
                for ( int y = 0 ; y < MATRIX_HEIGHT ; y++ )
                {
                    if ( matrix[x][y] == temp ) matrix[x][y] = -1;
                }
        }
    }
    if( matrix[i][j] == 10 )
    {
        if ( matrix[selectedX][selectedY] >= 0 && matrix[selectedX][selectedY] < 5 )
        {
            int temp = matrix[selectedX][selectedY];
            matrix[selectedX][selectedY] = -1;
            matrix[i][j] = -1;
            for ( int x = 0 ; x < MATRIX_WIDTH ; x++ )
                for ( int y = 0 ; y < MATRIX_HEIGHT ; y++ )
                {
                    if ( matrix[x][y] == temp ) matrix[x][y] = -1;
                }
        }
    }
}


#endif // FUNCTION_H
