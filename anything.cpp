#include<iostream>
#include<fstream>
using namespace std;
//图的邻接表的表示
#define max_ver 20
struct Arcnode{
int adjvex; //该弧所指向顶点的位置
Arcnode *nextarc;
};
 
struct vnode{
char data;
Arcnode *firstarc;
};
typedef enum{dg,udg}Graphkind;//有向图，无向图
typedef vnode Adjlist[max_ver];
 
struct Mgraph{
Adjlist vertices;
int vexnum,arcnum;
Graphkind kind;
};
 
void createUDG(Mgraph &M){
M.kind=udg;
cout<<"请输入无向图的节点数和边数"<<endl;
cin>>M.vexnum>>M.arcnum;
cout<<"请输入无向图的顶点"<<endl;
 
for(int i=0;i!=M.vexnum;++i){cin>>(M.vertices)[i].data;  M.vertices[i].firstarc=NULL;}
cout<<"请一次输入各顶点的度以及其各边的信息"<<endl;
int x;
cout<<"请输入第一个顶点的度"<<endl;
for(int i=0;i!=M.vexnum;++i){
    cin>>x;
    for(int j=0;j!=x;++j){
        Arcnode* tem=new Arcnode;
        cin>>tem->adjvex;
        tem->nextarc=M.vertices[i].firstarc;
        M.vertices[i].firstarc=tem;
    }
    if(i!=M.vexnum){
  cout<<"请输入下一个顶点的度"<<endl;}
}
}
 
 
void printgraph(Mgraph M){
cout<<"这是邻接表示图的表现方式："<<endl;
cout<<"图的顶点,顶点的度 ，与其邻接的点的位置"<<endl;
 
for(int i=0;i!=M.vexnum;++i){cout<<(M.vertices)[i].data<<"  ";
Arcnode *p;
p=M.vertices[i].firstarc;
for(;p!=NULL;p=p->nextarc){
    cout<<p->adjvex<<" ";
}
 
cout<<endl;
 
  }
cout<<endl;
 
 
}
 
 
 
 
int visited[1000];
 
 
 
//寻找连通图的关节点
int low[1000];
 
 int counts=1;
//算法7.11 low[v]的定义应该是v的后代以及一条回边能到达的最高祖先的dfs
void Dfsarticul(Mgraph G,int v0,int &counts){
    int mins;
 visited[v0]=mins=++counts; //v0是第counts个访问的节点
 
        for(Arcnode *p=G.vertices[v0].firstarc; p;p=p->nextarc ){//对v0的每个邻接顶点进行检查
 
        int w=p->adjvex; //w为邻接点
 
        if(visited[w]==0){ //如果未被访问，继续deep、
            Dfsarticul(G,w,counts); //返回前求得low[w];
            if(low[w]<mins)mins=low[w];  //其后代的low[]小于mins 则重置mins
            if(low[w]>=visited[v0]){cout<<G.vertices[v0].data<<"  "; }//如果v0的某个孩子的low大于visited[v0]，即没有回指，则是关节点
 }
 else if(visited[w]<mins){ mins=visited[w];}    //如果被访问。则w为v0的祖先，
    }
 
 
low[v0]=mins;
}
 
 
 
//算法7.10
void Findarticul(Mgraph G){
 
   visited[0]=1;//0号节点为根
    for(int i=1;i!=G.vexnum;++i){visited[i]=0;} //其他设置为0 ，未访问
    Arcnode *p=G.vertices[0].firstarc;
    int v; v=p->adjvex;
    Dfsarticul(G,v,counts);//从v节点开始deeptravel查找关节点
 
 
    if(counts<G.vexnum){//没有遍历完，说明有两颗子树
        cout<<G.vertices[0].data<<"  ";//根为关节点，继续遍历。
        while(p->nextarc){
            p=p->nextarc; v=p->adjvex;
            if(visited[v]==0){Dfsarticul(G,v,counts);}
        }
    }
 
}
 
 
 
 
int main()
{ ifstream infile("rebuf.txt");
 
cin.rdbuf(infile.rdbuf());
Mgraph M;
createUDG(M);
 
printgraph(M);
 
cout<<"\n\n\n";
 
Findarticul(M);
 
    return 0;
}
