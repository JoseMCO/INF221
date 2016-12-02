#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <sstream>

float sum(float P[], int i, int j);

float spectedCost(float P[], int n)
{
  float C[n][n];
  // Completa la matriz de costos,
  // en la diagonal con las probabilidades y el resto con 0s
  for (int i = 0; i<n; i++)
  {
    for (int j = 0; j<n; j++)
    {
      if (i==j)
      {
        C[i][j]=P[i];
      }
      else
      {
        C[i][j]=0;
      }
    }
  }

  C[n][n-1]=0;

  for (int d=0; d<=n-1; d++)
  {
    for (int i=0; i<=n-d; i++)
    {
      int j = i+d;
      float minval = INT_MAX;

      for (int k=i; k<=j; k++)
      {
        float c = ((k > i)? C[i][k-1]:0) + ((k < j)? C[k+1][j]:0);
        if (c < minval) {
          minval = c;
        }
      }
      C[i][j] = minval + sum(P, i, j);
    }
		// for (int i = 0; i<n; i++)
    // {
    //   for (int j = 0; j<n; j++)
    //   {
    //     printf("%.2f ", C[i][j]);
    //   }
    //   printf("\n");
    // }
    // printf("\n");
  }
  return C[0][n-1];
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
