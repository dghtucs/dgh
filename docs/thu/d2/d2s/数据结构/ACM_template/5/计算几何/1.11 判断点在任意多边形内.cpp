//1.11 �жϵ������������� 
//*�жϵ������������� 
//���߷���poly[]�Ķ�����Ҫ���ڵ���3,��ı��0~n-1 
//����ֵ 
//-1:����͹������� 
//0:����͹����α߽��� 
//1:����͹������� 
int inPoly(Point p,Point poly[],int n)
{
	int cnt;
	Line ray,side;
	cnt=0;
	ray.s=p;
	ray.e.y=p.y;
	ray.e.x=-100000000000.0;//-INF,ע��ȡֵ��ֹԽ�� 
	for(int i=0;i<n;i++)
	{
		side.s=poly[i];
		side.e=poly[(i+1)%n];
		if(OnSeg(p,side))return 0;
		//���ƽ�����򲻿��� 
		if(sgn(side.s.y-side.e.y)==0)
			continue;
		if(OnSeg(side.s,ray))
		{
			if(sgn(side.s.y-side.e.y)>0)cnt++;
		}
		else if(OnSeg(side.e,ray))
		{
			if(sgn(side.e.y-side.s.y)>0)cnt++;
		}
		else if(inter(ray,side))
		cnt++;
	}
	if(cnt%2==1)return 1;
	else return -1;
}
