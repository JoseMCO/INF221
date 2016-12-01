#include <stdio.h>
#include <limits.h>
#include <vector>
#include <iostream>
using std::vector;

// Retorna el máximo entre dos enteros
int max(int a, int b) {
	if (a>b)
		return a;
	return b;
}

// Retorna el máximo entre 3 enteros
int max(int a, int b, int c) {
	return max(max(a, b), c);
}

//Retorna la suma máxima posible en arr tal que arr[m] pertenezca a el
vector<int> maxCrossingSum(vector<int> arr, int l, int m, int r){
    int sum = 0, ll=l,rr=r;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--){
        sum = sum + arr[i];
        if (sum > left_sum){
          left_sum = sum;
          ll=i;
        }
    }

    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m+1; i <= r; i++){
        sum = sum + arr[i];
        if (sum > right_sum){
          right_sum = sum;
          rr=i;
        }
    }

    vector<int> result(3);
    result[0]=left_sum + right_sum;
    result[1]=ll;
    result[2]=rr;
    return result;
}

//Retorna la suma máxima del subarreglo arr[l..h]
vector<int> maxSubArraySum(vector<int> arr, int l, int r){
  if (l == r){
      vector<int> result(3);
      result[0]=arr[l];
      result[1]=l;
      result[2]=r;
      return result;
  }

  int m = (l + r)/2;

  vector<int> left_sum  = maxSubArraySum(arr, l, m);
  vector<int> right_sum = maxSubArraySum(arr, m+1, r);
  vector<int> cross_sum = maxCrossingSum(arr, l, m, r);
  int maxSum            = max(left_sum[0], right_sum[0], cross_sum[0]);

  if (maxSum == left_sum[0]) {
    return left_sum;
  }
  else if (maxSum == right_sum[0]) {
    return right_sum;
  }
  else /*(maxSum == cross_sum[0])*/ {
    return cross_sum;
  }
}

int main(){
  vector<int> arr;
  int n = 0;
  while(std::cin >> n) {
    arr.resize(arr.size()+1);
    arr[arr.size()-1] = n;
  }
  vector<int> result = maxSubArraySum(arr, 0, arr.size()-1);

  printf("%d %d\n%d\n", result[1]+1, result[2]+1, result[0]);
  return 0;
}
