//1.12 �ж�͹����� 
//�ж�͹����� 
//�����߱� 
//�������˳ʱ�����Ҳ��������ʱ����� 
//��ı��1~n-1 
bool isconvex(Point poly[],int n)
{
	bool s[3];
	memset(s,false,sizeof(s));
	for(int i=0;i<n;i++)
	{
		s[sgn((poly[(i+1)%n]-poly[i])^(poly[(i+2)%n]-poly[i]))+1]=true;
		if(s[0]&&s[2])return false;
	}
	return true;
}
