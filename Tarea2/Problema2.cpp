#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <sstream>

float sum(float P[], int i, int j);

float spectedCost(float P[], int n)
{
  float cost[n][n];

  for (int i = 0; i<n; i++)
  {
    for (int j = 0; j<n; j++)
    {
      if (i==j)
      {
        cost[i][j]=P[i];
      }
      else
      {
        cost[i][j]=0;
      }
    }
  }

  for (int d=2; d<=n; d++)
  {
    for (int i=0; i<=n-d+1; i++)
    {
      int j = i+d-1;
      cost[i][j] = INT_MAX;

      for (int r=i; r<=j; r++)
      {
        float c = ((r > i)? cost[i][r-1]:0) + ((r < j)? cost[r+1][j]:0) + sum(P, i, j);
        if (c < cost[i][j])
          cost[i][j] = c;
      }
    }
		// for (int i = 0; i<n; i++)
    // {
    //   for (int j = 0; j<n; j++)
    //   {
    //     printf("%.2f ", cost[i][j]);
    //   }
    //   printf("\n");
    // }
    // printf("\n");
  }
  return cost[0][n-1];
}

float sum(float P[], int i, int j)
{
  float s = 0;
  for (int k = i; k <=j; k++)
    s += P[k];
  return s;
}

int main()
{
  int n = 0;
  std::string data;

	while(std::cin >> n)
  {
    std::cin.ignore();

    std::getline(std::cin, data);
    std::stringstream stream(data);

    float P[n];
    for (int i = 0; i < n; i++)
    {
      stream >> P[i];
    }

    printf("%.4f\n", spectedCost(P, n));
  }
  return 0;
}
