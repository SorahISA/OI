#include <iostream>
#include <queue>
#include <cstring>
#define _ ios::sync_with_stdio(0); cin.tie(0);
using namespace std;
int** graph;
int parent[300]={0};
int n,v;
bool visit[300]={false};
bool inline min(int &a,int &b){
    return a<b;
}
bool bfs(int r[300][300],int v){
    memset(visit,0,sizeof(visit));
    queue<int>q;
    q.push(0);
    visit[0] = true;
    parent[0] = -1;
    while(!q.empty()){
        int a = q.front();
        //cout<<a<<endl;
        q.pop();
        for(int i=0;i<v;i++){
            if(!visit[i] && r[a][i]>0){
                q.push(i);
                visit[i]=true;
                parent[i] = a;
            }
        }
    }
    return visit[v-1];
}

int ford(int v){
	//cout<<"hahahah";
    int r[300][300];
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            r[i][j]=graph[i][j];
        }
    }
	//cout<<r[0][1]<<endl;  
    int max = 0;
    while (bfs(r,v)){
        int flow = 1e9;
        for(int i=v-1;i>0;i=parent[i]){
            if(flow > r[parent[i]][i])
                flow = r[parent[i]][i];
        }
        for(int i=v-1;i>0;i=parent[i]){
            r[parent[i]][i] -= flow;
            r[i][parent[i]] += flow;
        }
        max += flow;
    }
    return max;
}

int main() {
	int num,v;
	cin>>num;
	v=2*num+2;
	graph = new int*[v]();
	int gr[num+1][3];
	for(int i=0;i<v;i++)graph[i]=new int[v]();
	for(int i=1;i<=num;i++){
		cin>>gr[i][0]>>gr[i][1]>>gr[i][2];
		graph[0][i]=1;
	}
    for(int i = 1; i <= num; i++){
        for(int j = num+1; j < v-1; j++){
            if(i!=j-num){
            	if(gr[i][0]<gr[j-num][0] && gr[i][1]<gr[j-num][1] && gr[i][2]<gr[j-num][2])
            	graph[i][j] = 1;
			}
        }
    }
	for(int i=num+1;i<v-1;i++){
		graph[i][v-1]=1;
	}
	// for(int i=0;i<v;i++){
	// 	for(int j=0;j<v;j++){
	// 		cout<<graph[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
 //    cout<<endl<<"----------------------------"<<endl;	
	// for(int i=1;i<v;i++)cout<<graph[0][i]<<" ";
	int a=ford(v);
 //    cout<<endl<<"----------------------------"<<endl;
	cout<<num-a<<endl;
	// for(int i=0;i<v;i++){
	// 	for(int j=0;j<v;j++){
	// 		cout<<graph[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }	
    return 0;
}
/*
3
3 2 1
4 3 2
5 3 2
*/