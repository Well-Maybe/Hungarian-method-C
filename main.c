#include<stdio.h>
#include<stdbool.h>

#define M 100//任务数量
int N;
int v[M][M];//系数矩阵
int S[M][M] ;//解矩阵
int e[M] ;//位置标记数组0
int c[M] ;//位置标记数组0
int r[M] ;//行标记数组-1
int l[M]; //列标记数组-1
void row()   //减去行上最小值
{

    int i, j;
    for (i = 0; i < N; i++) {
        int f = v[i][0];
        for (j = 0; j < N; j++) {
            if (v[i][j] < f)
                f = v[i][j];
        }
        for (j = 0; j < N; j++) {
            v[i][j] = v[i][j] - f;
        }
    }

}

void column()//减去列上最小值
{
    int i, j;
    for (i = 0; i < N; i++) {
        int f = v[0][i];
        for (j = 0; j < N; j++) {
            if (v[j][i] < f)
                f = v[j][i];
        }
        for (j = 0; j < N; j++) {
            v[j][i] = v[j][i] - f;
        }
    }
}
void scribing()//划线
{

    int temp=0;
    int temp1=0;
    for (int i = 0; i < N; i++)
    {
        int count=0;
        for (int j = 0; j < N; j++) {
            if (v[i][j]==0)
            {
                count++;
            }
        }

        if (count==0)
        {
            bool ff=true;
            for (int k = 0; k <N ; k++) {
                if (r[k]==i)ff=false;
            }
            if (ff)
            {
            r[temp]=i;
            temp++;
            }
        }
    }

      bool isExit =true;
     while(isExit)
     {
         int t=0;
         for (int i = 0; i < N; i++) {
             if (r[i] != -1) {
                 for (int j = 0; j < N; j++) {
                     if (v[r[i]][j] == -1) {
                         bool ff = true;
                         for (int k = 0; k < N; k++) {
                             if (l[k] == j)ff = false;

                         }
                         if (ff) {
                             l[temp1] = j;
                             temp1++;
                             t++;
                         }
                     }
                 }
             }
         }
         for (int i = 0; i < N; i++) {
             if (l[i] != -1) {
                 for (int j = 0; j < N; j++) {
                     if (v[j][l[i]] == 0) {
                         bool ff = true;
                         for (int k = 0; k < N; k++) {
                             if (r[k] == j)ff = false;
                         }
                         if (ff) {
                             r[temp] = j;
                             temp++;
                             t++;
                         }
                     }
                 }
             }
         }
         if (t==0)
         {
             isExit=false;
         }
     }
}
void calculate()//计算
{
    int temp=1000;//最小值懒得取了随便取个
    for (int i = 0; i <N ; i++) {
        if (r[i]!=-1)
        {
            for (int j = 0; j <N ; ++j) {
              if (v[r[i]][j]<temp && v[r[i]][j]>0)
              {
                  temp=v[r[i]][j];
              }
            }
        }
    }
    for (int i = 0; i <N ; i++) {
        if (r[i]!=-1)
        {
            for (int j = 0; j <N ; ++j) {
                v[r[i]][j]=v[r[i]][j]-temp;
            }
        }
    }
    for (int i = 0; i <N ; i++) {
        if (l[i]!=-1)
        {
            for (int j = 0; j < N; j++) {
                v[j][l[i]]=v[j][l[i]]+temp;
            }
        }
    }

}
void makeZero()//-1归零
{
    for (int i = 0; i <N ; i++)
    {
        for (int j = 0; j < N; j++) {
            if(v[i][j]==-1)
            {
                v[i][j]=0;
            }
        }
    }
}
bool isOptimal()   //是否最优
{
    int count=0;
    for (int i = 0; i < N;i++)
    {
        for (int j = 0; j < N ; j++)
        {
            if(v[i][j]==0)
                count++;
        }
    }
    if (count==N)
    {
        makeZero();
        printf("-----------------Value matrix-----------------\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d    ", v[i][j]);
            }
            printf("\n");

        }
        printf("-------------------------------------------------\n");

        printf("-----------------Solution matrix-----------------\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d    ", S[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("--------------------------------------------------\n");
        return true;
    }

    return false;



}
void zero()   //划圈和划0
{
    for (int rl = 0; rl <N ; rl++)
    {
        for (int i = 0; i < N; ++i) {
            S[rl][i]=0;
        }
    }


    int a = 0;
    for (int z = 0; z < N * N; z++) {


        for (int i = 0; i < N; i++) //1-N个圈
        {
            for (int k = 0; k < N; k++) {
                int countt = 0;
                for (int j = 0; j < N; j++) {
                    if (v[j][k] == 0)
                        countt++;
                }
                c[i] = countt;
            }
            int f1 = 0;
            int f = 0;
            int g = -1;
            for (int j = 0; j < N; ++j) {
                if (v[i][j] == 0) {
                    f++;

                    g = j;
                }
                if (v[i][j] == 0 || v[i][j] == -1) {
                    f1++;
                }

            }
            if (f1 == a && a > 1) {

                int q = 0;
                for (int j = 0; j < N; j++) {
                    if (v[i][j] == 0) {
                        e[q] = j;
                        q++;
                    }
                }
                q = e[0];
                for (int j = 0; j < N; j++) {
                    if (c[q] > c[e[j]] && c[e[j]] > 0) {
                        q = e[j];
                    }
                }
                g = q;
            }
            if ((f == a && a == 1) || (f1 == a && a > 1)) {
                S[i][g] = 1;
                for (int j = 0; j < N; j++) {
                    if (v[i][j] == 0 && j != g) {
                        v[i][j] = -1;
                    }
                }
                for (int j = 0; j < N; j++) {
                    if (v[j][g] == 0 && j != i) {
                        v[j][g] = -1;
                    }
                }

            }

            for (int j = 0; j < N; j++) {
                c[j] = 0;
            }

        }


        a++;
    }

}
void insert(int q[],int p)
{
    for (int i = 0; i < N; i++) {
        q[i]=p;
    }
}
void input(){
    printf("请输入任务数N:\n");
    scanf("%d",&N);
    printf("请输入系数矩阵 %dX%d\n",N,N);
    for(int i=0;i<N;i++)
    {
        for (int j=0;j<N;j++)
        {
            scanf("%d",&v[i][j]);
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
           S[i][j]=0;
        }
    }
    insert(e,0);
    insert(c,0);
    insert(r,-1);
    insert(l,-1);

}
int main() {
input();
    row();
    column();
    zero();
    while (!isOptimal())
    {
        scribing();
        calculate();
        makeZero();
        zero();
    }


}


