#include<bits/stdc++.h>
using namespace std;
struct MCMFMINE{
	const static int MAXP=1000000;
	const static int MAXE=2000000;
	const static int MINF=1e8;
	struct EDGE{
		int from,to,cap,flow,cost,next;
	}ed[MAXE<<1];
	int S,T,head[MAXP],num,pre[MAXP],vis[MAXP],dis[MAXP];
	void init(int S,int T){
		memset(head,-1,sizeof head);
		num=0;
		this->S=S;this->T=T;
	}
	void add(int u,int v,int w,int c){
		ed[num]={u,v,w,0,c,head[u]};head[u]=num++;
		ed[num]={v,u,0,0,-c,head[v]};head[v]=num++;
	}
	bool spfa(){
		queue<int>q;
		for(int i=S;i<=T;i++)dis[i]=MINF,vis[i]=0,pre[i]=-1;
		dis[S]=0,vis[S]=1;q.push(S);
		while(!q.empty()){
			int u=q.front();q.pop();vis[u]=0;
			for(int i=head[u];i!=-1;i=ed[i].next){
				EDGE E=ed[i];
				if(dis[E.to]>dis[u]+E.cost&&E.cap>E.flow){
					dis[E.to]=dis[u]+E.cost;
					pre[E.to]=i;
					if(!vis[E.to]){
						vis[E.to]=1;
						q.push(E.to);
					}
				}
			}
		}
		return pre[T]!=-1;
	}
	void MCMF(int &cost,int &flow){
		flow=cost=0;
		while(spfa()){
			int minv=MINF;
			for(int i=pre[T];i!=-1;i=pre[ed[i^1].to])minv=min(minv,ed[i].cap-ed[i].flow);
			for(int i=pre[T];i!=-1;i=pre[ed[i^1].to]){
				ed[i].flow+=minv;
				ed[i^1].flow-=minv;
				cost+=ed[i].cost*minv;
			}
			flow+=minv;
		}
	}
}mcmf; 
int main(){
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	mcmf.init(0,n+1);
	for(int i=1;i<=n;i++){
		int p;
		scanf("%d",&p);
		int r;
		scanf("%d",&r);
		int pre,res;
		for(int j=1;j<=r;j++){
			int x;
			scanf("%d",&x);
			if(x==-1)x=n+1;
			if(j==1)res=x;
			else if(j==r){
				mcmf.add(x,res,p,1);
				mcmf.add(pre,x,p,1);
			}
			else mcmf.add(pre,x,p,1);
			pre=x;
		}
	} 
	int anscost,ansflow;
	mcmf.MCMF(anscost,ansflow);
	printf("%d\n",anscost);
}


