//��'�ٵ���ɫ��'�жϣ����ڵ���ɫ������ͬɫ�򲻳���
bool BFS()//����ͼBFS�ж�
{
    queue<int> Q;
    int judge[MAXN];// �ж϶���ͼʱ 0-1��
    int v;
    for(int i=0;i<=n;i++) 
        judge[i]=-1;
    for(int j=1;j<=n;j++)
    {
        if(judge[j]==-1)
        {
            Q.push(j);
            judge[j]=0;
            uN.push_back(j);//������벿��
            while(!Q.empty())
            {
                v=Q.front();
                Q.pop();
                for(int i=1;i<=n;i++)
                {
                    if(g[v][i])
                    {
                        if(judge[i]==-1)
                        {
                            judge[i]=(judge[v]+1)%2;
                            Q.push(i);
                            if(judge[i]==0)
                            {
                                uN.push_back(i);//������벿��
                            }
                            else
                            {
                                vN.push_back(i);//�����Ұ벿��
                            }
                        }
                        else
                        {
                            if(judge[i]==judge[v])
                                return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}