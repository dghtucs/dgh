void FMT(int *A,int o)
{
	//oΪʶ������
	for(int i=1;i<ST;i<<=1)//ST-1��ʾȫ��
		for(int j=0;j<ST;j++)
			if(i&j) (A[j]+=A[j^i]*o)%=MOD;
}
for(int i=0;i<=n;i++) FMT(g[i],1);
for(int i=0;i<=n;i++) FMT(f[i],1);
//h[i][k] ����i��Ԫ�صļ���k�Ľ��i==__builtin_popcount(k)ʱ״̬��Ч,f��gͬ��
for(int i=0;i<=n;i++)
{
	for(int j=0;j<=i;j++)
		for(int k=0;k<ST;k++)
			(h[i][k]+=1ll*f[j][k]*g[i-j][k]%MOD)%=MOD;
	FMT(h[i],-1);
	for(int k=0;k<ST;k++) if(cnt[k]!=i) h[i][k]=0;//cnt[k]=__builtin_popcount(k)
	//if(i!=n) FMT(h[i],1);//cf 914G�ò�������ʱ��֪�������ɶ��
}
