#include <iostream>
using namespace std;

pair<int,int> input[50001];
int tree[200001];

int find(int def, int start, int end){
	if(input[start].first == def){
		return start;
	}
	else if(start == end){
		return -1;
	}

	int mid = (start + end)/2;

	if(input[mid].first >= def){
		return find(def,start,mid);
	}
	else{
		return find(def,mid+1,end);
	}
}

int findSub(int def, int start, int end){
	if(start == end){
		return start;
	}

	int mid = (start + end)/2;

	if(input[mid].first >= def){
		return find(def,start,mid);
	}
	else{
		return find(def,mid+1,end);
	}
}

int init(int node, int start, int end){
	if(start == end){
		return tree[node] = input[start].second;
	}

	int mid = (start+end)/2;

	return tree[node] = max(init(node*2, start, mid), init(node*2+1,mid+1,end));
}

int getMax(int node, int front, int back, int start, int end){
	if((end < front) || (back < start))return 0;

	if((front <= start) && (end <= back)){
		return tree[node];
	}

	int mid = (start + end)/2;

	return max(getMax(node*2, front, back, start, mid), getMax(node*2+1, front, back, mid+1, end));
}

void print(int indexX, int indexY){
	if((input[indexX].first - input[indexY].first) == (indexX - indexY)){
		cout << "true" <<'\n';
	}
	else{
		cout << "maybe" << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	int x,y;
    n = 50000;

	for(int i = 0; i < n; i++){
        input[i].first = i;
        input[i].second = i;
	}

	init(1,0,n-1);

	cin >> m;
	for(int i = 0; i < m; i++){
		cin >> y >> x;

		int indexY = find(y,0,n-1);
		int indexX = find(x,0,n-1);

		if(indexY == -1 && indexX == -1){
			cout << "maybe" <<'\n';
		}
		else if(indexY == -1){
			int periodMax = getMax(1, findSub(y,0,n-1)+1, indexX-1, 0, n-1);
			if(periodMax < input[indexX].second){
				cout << "maybe" <<'\n';
			}
			else{
				cout << "false" << '\n';
			}
		}
		else if(indexX == -1){
			int periodMax = getMax(1, indexY+1, findSub(x,0,n-1)-1, 0, n-1);
			if(periodMax < input[indexY].second){
				cout << "maybe" <<'\n';
			}
			else{
				cout << "false" << '\n';
			}
		}
		else{
			if(input[indexY].second < input[indexX].second){
			cout << "false" <<'\n';
			}
			else if(indexY+1 == indexX){
				print(indexX,indexY);
			}
			else if(getMax(1, indexY+1, indexX-1, 0, n-1) < input[indexX].second ){
				print(indexX,indexY);
			}
			else{
				cout << "false" << '\n';
			}
		}
	}
}