


#include <stdio.h>


int main()
{/// một mảng thực cấp không quá 20x20
  float a[20][20];
  int i,j,n,m;
  ///Nhap mang thuc
  printf(">>>WELLCOME<<<");
  printf("\n Nhap vao so dong  va cot cua mang.");
  scanf("%d %d",&n,&m);
  for(i=0;i<n;i++)
  {
      for(j=0;j<m;j++)
      {
          printf("\n Nhap vao gia tri cua phan tu a[%d][%d]:",i,j);
          scanf("%f",&a[i][j]);
      }
  }
  /// in ra phan tu cua mang

printf(" \nIn ra mang X \n");
 for(i=0;i<n;i++)
  {
      for(j=0;j<m;j++)
      {

          printf(" %4f", a[i][j]);
      }
      printf("\n");
  }
}
