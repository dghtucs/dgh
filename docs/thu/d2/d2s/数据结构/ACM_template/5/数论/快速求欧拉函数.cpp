
ll phi[MAXN];
void init()
{
	int i,j;
	for(i=1;i<MAXN;i++)
		phi[i]=i;
	for(i=2;i<MAXN;i++)
		if(i==phi[i]) //��ʱiΪ����
			for(j=i;j<MAXN;j+=i)  //j�ۼ�i
				phi[j]=(phi[j]/i)*(i-1); //j������i,����i������,����ŷ������
}

//���û��Ժ������ʣ��ֽ�������֮��������
ll phi(ll n)
{
	ll ret=n;
	for(ll i=2;i*i<=n;i++)
	{
		if(n%i==0) ret=ret/i*(i-1);
		while(n%i==0) n/=i;
	}
	if(n>1) ret=ret/n*(n-1);
	return ret;
}
