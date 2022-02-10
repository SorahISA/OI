

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> example1 = {
    {1,1,1,1,0},
    {1,1,0,1,0},
    {1,1,0,1,0},
    {0,0,0,1,0},
    {0,0,0,0,0}
};

vector<vector<int>> example2 = {
    {1,1,0,0,0},
    {0,0,0,0,0},
    {0,0,1,0,0},
    {0,0,0,1,1},
    {0,0,0,0,1}
};

vector<vector<int>> example3 = {
    {1,0,1,1,0},
    {1,0,1,0,0},
    {1,0,1,1,0},
    {0,0,0,1,0},
    {0,0,0,1,0}
};

vector<vector<int>> example4 = {
    {1,0,1,0,1},
    {0,0,0,1,0},
    {0,1,1,0,0},
    {0,0,1,1,1},
	{0,0,0,0,1}
};

vector<vector<int>> example5 = {
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,1,0,0},
    {0,0,0,0,0},
    {0,0,1,0,0}
};


void dfs(vector<vector<int>>& grid , int x , int y , int m , int n)
{
    if(x < 0 || y < 0 || x >= n || y >= m || grid[y][x]== 0)
        return;
        
    grid[y][x] = 0;
    dfs(grid,x + 1,y,m,n);
    dfs(grid,x - 1,y,m,n);
    dfs(grid,x,y + 1,m,n);
    dfs(grid,x,y - 1,m,n);
}

int Flying_Squirrel(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        
        int m = grid.size();
        int n = grid[0].size();
        
        int ans = 0;
        for(int y = 0; y < m; y++)
        {
            for(int x = 0 ; x < n; x++)
            {
                if(grid[y][x] == 1)
                {
                    ++ans;
                    dfs(grid,x,y,m,n);
                }
            }
        }
        
        return ans;
}
    

int main()
{
   cout << "output 1 : " << Flying_Squirrel(example1) << endl;
   cout << "output 2 : " << Flying_Squirrel(example2) << endl;
   cout << "output 3 : " << Flying_Squirrel(example3) << endl;
   cout << "output 4 : " << Flying_Squirrel(example4) << endl;
   cout << "output 5 : " << Flying_Squirrel(example5) << endl;

    return 0;
}




