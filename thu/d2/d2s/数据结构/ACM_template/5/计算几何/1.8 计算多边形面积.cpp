//1.8 ����������� 
//����������� 
//��ı�Ŵ�0~n-1 
double CalcArea(Point p[],int n)
{
    double res=0;
	for(int i=0;i<n;i++) 
        res+=(p[i]^p[(i+1)%n])/2; 
    return fabs(res);
}
