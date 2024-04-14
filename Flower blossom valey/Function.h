#ifndef FUNCTION_H
#define FUNCTION_H
#include<bits/stdc++.h>
#define MATRIX_WIDTH (10)
#define MATRIX_HEIGHT (5)
using namespace std;

const int target = 500, moves = 20 ;

int rstart = 0, cstart = 0;
int cropped = 0 ;
void getColChain(int i, int j, vector<pair<int,int>> &chainList, int** matrix)
{
    chainList.push_back(make_pair(i,j));
    int neighCol = j-1;
    while ( neighCol >= 0 )
    {
        if( matrix[i][neighCol] == matrix[i][j] )
        {
            chainList.push_back(make_pair(i,neighCol));
            neighCol--;
        }
        else break;
    }
    neighCol = j+1;
    while ( neighCol < MATRIX_HEIGHT )
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
        if ( matrix[neighRow][j] == matrix[i][j] )
        {
            chainList.push_back(make_pair(neighRow,j));
            neighRow--;
        }
        else break;
    }
    neighRow = i+1;
    while ( neighRow < MATRIX_WIDTH )
    {
        if ( matrix[neighRow][j] == matrix[i][j] )
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
            matrix[index.first][index.second] = -1;
        }
    }
    if ( ColSize >= 3 )
    {
        for (auto index : colChainList )
        {
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

void bee ( int** matrix , int i , int j )
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
#endif // FUNCTION_H
