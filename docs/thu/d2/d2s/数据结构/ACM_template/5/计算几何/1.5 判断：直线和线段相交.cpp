//1.5 �жϣ�ֱ�ߺ��߶��ཻ 
bool Seg_inter_line(Line l1,Line l2) //�ж�ֱ��l1���߶�l2�Ƿ��ཻ 
{
	return sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e))<=0;
}
