#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int main()
{
	static const int MAX_LEN = 210;
	static char str[MAX_LEN];
	int t;
	scanf("%d", &t);
	for(int z = 0; z != t; ++z)
	{
		scanf("%s", str);
		int n = strlen(str);
		static int dp[MAX_LEN][MAX_LEN][4]; //0: none 1:( 2:[ 3:{
		static const int INF = 1 << 29;
		for(int i = 0; i != n; ++i)
			for(int j = 0; j != n; ++j)
				dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = dp[i][j][3] = INF;
		for(int i = 0; i != n; ++i)
		{
			if(str[i] == '{' || str[i] == '(' || str[i] == '[' || str[i] == ')' || str[i] == ']' || str[i] == '}')
				dp[i][i][0] = 1;
			else
				dp[i][i][0] = 0;
		}
		for(int j = 1; j != n; ++j)
			for(int i = 0; i + j != n; ++i)
			{
				int penality = (str[i] != '(') + (str[i + j] != ')');
				if(j == 1)
					dp[i][i + j][1] = min(dp[i][i + j][1], penality);
				else
					dp[i][i + j][1] = min(dp[i][i + j][1], min(dp[i + 1][i + j - 1][1], dp[i + 1][i + j - 1][0]) + penality);

				penality = (str[i] != '[') + (str[i + j] != ']');
				if(j == 1)
					dp[i][i + j][2] = min(dp[i][i + j][2], penality);
				else
					dp[i][i + j][2] = min(dp[i][i + j][2], min(dp[i + 1][i + j - 1][2], dp[i + 1][i + j - 1][0]) + penality);

				penality = (str[i] != '{') + (str[i + j] != '}');
				if(j == 1)
					dp[i][i + j][3] = min(dp[i][i + j][3], penality);
				else
					dp[i][i + j][3] = min(dp[i][i + j][3], min(dp[i + 1][i + j - 1][3], dp[i + 1][i + j - 1][0]) + penality);

				penality = (str[i] == '(' || str[i] == '[' || str[i] == '{' || str[i] == ')' || str[i] == ']' || str[i] == '}');

				dp[i][i + j][0] = min(dp[i][i + j][0], dp[i + 1][i + j][0] + penality);
				dp[i][i + j][1] = min(dp[i][i + j][1], dp[i + 1][i + j][1] + penality);
				dp[i][i + j][2] = min(dp[i][i + j][2], dp[i + 1][i + j][2] + penality);
				dp[i][i + j][3] = min(dp[i][i + j][3], dp[i + 1][i + j][3] + penality); 
				penality = (str[i + j] == '(' || str[i + j] == '[' || str[i + j] == '{' || str[i + j] == ')' || str[i + j] == ']' || str[i + j] == '}');
				dp[i][i + j][0] = min(dp[i][i + j][0], dp[i][i + j - 1][0] + penality);
				dp[i][i + j][1] = min(dp[i][i + j][1], dp[i][i + j - 1][1] + penality);
				dp[i][i + j][2] = min(dp[i][i + j][2], dp[i][i + j - 1][2] + penality);
				dp[i][i + j][3] = min(dp[i][i + j][3], dp[i][i + j - 1][3] + penality); 
				for(int k = i; k != i + j; ++k)
				{
					dp[i][i + j][0] = min(dp[i][i + j][0], dp[i][k][0] + dp[k + 1][i + j][0]);
					dp[i][i + j][1] = min(dp[i][i + j][1], dp[i][k][0] + dp[k + 1][i + j][1]);
					dp[i][i + j][1] = min(dp[i][i + j][1], dp[i][k][1] + dp[k + 1][i + j][0]);
					dp[i][i + j][1] = min(dp[i][i + j][1], dp[i][k][1] + dp[k + 1][i + j][1]);
					dp[i][i + j][1] = min(dp[i][i + j][1], dp[i][k][1] + dp[k + 1][i + j][2]);
					dp[i][i + j][1] = min(dp[i][i + j][1], dp[i][k][1] + dp[k + 1][i + j][3]);
					dp[i][i + j][2] = min(dp[i][i + j][2], dp[i][k][0] + dp[k + 1][i + j][2]);
					dp[i][i + j][2] = min(dp[i][i + j][2], dp[i][k][2] + dp[k + 1][i + j][0]);
					dp[i][i + j][2] = min(dp[i][i + j][2], dp[i][k][2] + dp[k + 1][i + j][1]);
					dp[i][i + j][2] = min(dp[i][i + j][2], dp[i][k][2] + dp[k + 1][i + j][2]);
					dp[i][i + j][2] = min(dp[i][i + j][2], dp[i][k][2] + dp[k + 1][i + j][3]);
					dp[i][i + j][3] = min(dp[i][i + j][3], dp[i][k][0] + dp[k + 1][i + j][3]);
					dp[i][i + j][3] = min(dp[i][i + j][3], dp[i][k][3] + dp[k + 1][i + j][0]);
					dp[i][i + j][3] = min(dp[i][i + j][3], dp[i][k][3] + dp[k + 1][i + j][1]);
					dp[i][i + j][3] = min(dp[i][i + j][3], dp[i][k][3] + dp[k + 1][i + j][2]);
					dp[i][i + j][3] = min(dp[i][i + j][3], dp[i][k][3] + dp[k + 1][i + j][3]);
				}
			}
		printf("%d\n", min(min(dp[0][n - 1][1], dp[0][n - 1][2]), dp[0][n - 1][3]));
	}
}
