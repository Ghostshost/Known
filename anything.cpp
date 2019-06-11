#include<iostream>
#include<fstream>
using namespace std;
//ͼ���ڽӱ�ı�ʾ
#define max_ver 20
struct Arcnode{
int adjvex; //�û���ָ�򶥵��λ��
Arcnode *nextarc;
};
 
struct vnode{
char data;
Arcnode *firstarc;
};
typedef enum{dg,udg}Graphkind;//����ͼ������ͼ
typedef vnode Adjlist[max_ver];
 
struct Mgraph{
Adjlist vertices;
int vexnum,arcnum;
Graphkind kind;
};
 
void createUDG(Mgraph &M){
M.kind=udg;
cout<<"����������ͼ�Ľڵ����ͱ���"<<endl;
cin>>M.vexnum>>M.arcnum;
cout<<"����������ͼ�Ķ���"<<endl;
 
for(int i=0;i!=M.vexnum;++i){cin>>(M.vertices)[i].data;  M.vertices[i].firstarc=NULL;}
cout<<"��һ�����������Ķ��Լ�����ߵ���Ϣ"<<endl;
int x;
cout<<"�������һ������Ķ�"<<endl;
for(int i=0;i!=M.vexnum;++i){
    cin>>x;
    for(int j=0;j!=x;++j){
        Arcnode* tem=new Arcnode;
        cin>>tem->adjvex;
        tem->nextarc=M.vertices[i].firstarc;
        M.vertices[i].firstarc=tem;
    }
    if(i!=M.vexnum){
  cout<<"��������һ������Ķ�"<<endl;}
}
}
 
 
void printgraph(Mgraph M){
cout<<"�����ڽӱ�ʾͼ�ı��ַ�ʽ��"<<endl;
cout<<"ͼ�Ķ���,����Ķ� �������ڽӵĵ��λ��"<<endl;
 
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
 
 
 
//Ѱ����ͨͼ�Ĺؽڵ�
int low[1000];
 
 int counts=1;
//�㷨7.11 low[v]�Ķ���Ӧ����v�ĺ���Լ�һ���ر��ܵ����������ȵ�dfs
void Dfsarticul(Mgraph G,int v0,int &counts){
    int mins;
 visited[v0]=mins=++counts; //v0�ǵ�counts�����ʵĽڵ�
 
        for(Arcnode *p=G.vertices[v0].firstarc; p;p=p->nextarc ){//��v0��ÿ���ڽӶ�����м��
 
        int w=p->adjvex; //wΪ�ڽӵ�
 
        if(visited[w]==0){ //���δ�����ʣ�����deep��
            Dfsarticul(G,w,counts); //����ǰ���low[w];
            if(low[w]<mins)mins=low[w];  //������low[]С��mins ������mins
            if(low[w]>=visited[v0]){cout<<G.vertices[v0].data<<"  "; }//���v0��ĳ�����ӵ�low����visited[v0]����û�л�ָ�����ǹؽڵ�
 }
 else if(visited[w]<mins){ mins=visited[w];}    //��������ʡ���wΪv0�����ȣ�
    }
 
 
low[v0]=mins;
}
 
 
 
//�㷨7.10
void Findarticul(Mgraph G){
 
   visited[0]=1;//0�Žڵ�Ϊ��
    for(int i=1;i!=G.vexnum;++i){visited[i]=0;} //��������Ϊ0 ��δ����
    Arcnode *p=G.vertices[0].firstarc;
    int v; v=p->adjvex;
    Dfsarticul(G,v,counts);//��v�ڵ㿪ʼdeeptravel���ҹؽڵ�
 
 
    if(counts<G.vexnum){//û�б����꣬˵������������
        cout<<G.vertices[0].data<<"  ";//��Ϊ�ؽڵ㣬����������
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
