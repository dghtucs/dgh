/*
 * Next[]�ĺ��壺x[i-Next[i]...i-1]=x[0...Next[i]-1] 
 * Next[i]Ϊ����x[i-z...i-1]=x[0...z-1]�����zֵ������x������ƥ�䣩 
 */
void kmp_pre(char x[],int m,int Next[])
{
	int i,j;
	j=Next[0]=-1;
	i=0;
	while(i<m)
	{
		while(-1!=j && x[i]!=x[j])j=Next[j];
		Next[++i]=++j;
	}
}
/* 
 * kmpNext[]����˼��Next'[i]=Next[Next[...[Next[i]]]] (ֱ��Next'[i]<0����x[Next'[i]]!=x[i]) 
 * ������Ԥ������Կ�һЩ 
 */ 
void preKMP(char x[],int m,int kmpNext[])
{
	int i,j;
	j=kmpNext[0]=-1;
	i=0;
	while(i<m)
	{
		while(-1!=j && x[i]!=x[j])j=kmpNext[j];
		if(x[++i]==x[++j])kmpNext[i]=kmpNext[j];
		else kmpNext[i]=j;
	}
}
/* 
 * ����x��y�г��ֵĴ����������ص� 
 */
int Next[10010];
int KMP_Count(char x[],int m,char y[],int n)//x��ģʽ����y������
{
	int i,j;
	int ans=0;
	preKMP(x,m,Next);
	//kmp_pre(x,m,Next);
	i=j=0;
	while(i<n)
	{
		while(-1!=j&&y[i]!=x[j])j=Next[j];
		i++;j++;
		if(j>=m)
		{
			ans++;
			j=Next[j];
		}
	}
	return ans;
}
