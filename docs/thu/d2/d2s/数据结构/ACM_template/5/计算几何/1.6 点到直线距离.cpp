//1.6 �㵽ֱ�߾��� 
//�㵽ֱ�߾��� 
//����Ϊresult,�ǵ㵽ֱ������ĵ� 
Point PointToLine(Point P,Line L) 
{ 
    Point result; 
    double t=((P-L.s)*(L.e-L.s))/((L.e-L.s)*(L.e-L.s)); 
    result.x=L.s.x+(L.e.x-L.s.x)*t; 
    result.y=L.s.y+(L.e.y-L.s.y)*t; 
    return result; 
}
