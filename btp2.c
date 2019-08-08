#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int rank;
struct node{
	int val;
	struct node* next;
}node;
int cmp(const void *pa, const void *pb){
	const int *a = pa;
	const int *b = pb;
	return a[0] - b[0];
}
int intersection1(int n, int x3[], int i, int x1[], int x2[]);
int comp1(const void *pa, const void *pb){
	const int *a = pa;
	const int *b = pb;
	return b[1] - a[1];
}
void LocalMCE(int xy[], int xy1, int b[][2], struct node *a[], int n, int **A, int kk, int **A1, int kk1, int x1[], int k1, int x2[], int k2){
	int z[n], z1, i, j, s = -1, s1 = 0, s2 = 0;
	if(k1 == 0 && k2 == 0){
		if(xy1 > 2){
			//printf("\n");
			for(int rt = 0; rt < xy1; rt++){
			//	printf("%d ", xy[rt]);
			}
			//printf("\n");
		}
	//	printf("from process %d\n", rank);
	}
	else if(k1 != 0){
		//printf("kk%d ", k1);
		for(i = 0; i < k1; i++){
			int up1 = x1[i];
			for(j = 0; j < kk; j++){
				if(A[j][1] == up1){
					int r = intersection1(n, z, k1, x1, A[j]);
					//printf("gg%dgg", r);
					if(s < r){
						s = r;
						s1 = i;
						s2 = j;
					}
					break;
				}
			}
		}
		int up = x1[s1];
//		printf("upupu %d upuup", up);
//		printf("xx%dxx\n", x1[s1]);
		int r = intersection1(n, z, k1, x1, A[s2]);
//		printf("rrrrrrrr %d %d %drrr", r, A[s2][1], A[s2][0]);
		int i1 = 0, j1 = 0, k = 0, U[n][2];
		while(i1 < k1){
			if(j1 < r){
				if(x1[i1] == z[j1]){
					//x1[i1] = n + 1;
					i1++;
					j1++;
				}
				else if(x1[i1] < z[j1]){
					U[k][0] = x1[i1];
					k++;
					i1++;
				}
				else{
					j1++;
				}
			}
			else{
				U[k][0] = x1[i1];
				k++;
				i1++;
			}
		}
		for(i = 0; i < k; i++){
//			printf("jj%d ", U[i][0]);
			U[i][1] = 0;
			//printf("ggggggg%dggggggg", U[i][0]);
			struct node *h = a[U[i][0] - 1];
			while(h != NULL){
				if(b[h -> val - 1][1] > b[xy[0] - 1][1]){
					U[i][1]++;
				}
				h = h -> next;
			}
		}
		qsort( U, k, sizeof(int *), comp1);
		for(i = 0; i < k; i++){
//			printf("UUUU %d UUU", U[i][0]);
		}
//		printf("vvvvvv");
//		printf("hhhhhh%dhhhhhhh\n", k);
		for(i = 0; i < k; i++){
//			printf("iiiiiiiiiiiii");
			int u = U[i][0];
			for(j = 0; j < k1; j++){
				if(U[i][0] == x1[j]){
					x1[j] = n + 1;
					qsort( x1, k1, sizeof(int), cmp);
					k1--;
					break;
				}
			}
			for(j = 0; j < kk; j++)
				if(A[j][1] == U[i][0])
					break;
			int sx = j;
			int r = intersection1(n, z, k1, x1, A[j]);		//cand -> x1; cand' -> z;
//			printf("\nooo%doo\n", r);
			for(j = 0; j < k1; j++){
//				printf("11%d ", x1[j]);
			}
			for(j = 0; j < r; j++){
//				printf("22%d ", z[j]);
			}
//			printf("pppppppp%d ", r);
//			printf("ffffff");
//			printf("\nllllfffllllllll\n");
//			printf("ffffff");
			//if(r != 0){
			int **J = (int **)malloc((n + 1)*sizeof(int *));
			int **J1 = (int **)malloc((n + 1)*sizeof(int *));
			for(j = 0; j < n + 1; j++){
				J[j] = (int *)malloc((n + 1)*sizeof(int));
				J1[j] = (int *)malloc((n + 1)*sizeof(int));
			}
			//if(r != 0){
			int l1 = 0, l2 = 0;
			//J[l1] = (int *)malloc((n + 1)*sizeof(int));
			//J1[l2] = (int *)malloc((n + 1)*sizeof(int));
//			printf("ffffff");
			for(j = 0; j < r; j++){
				int w = z[j], p;
				for(p = 0; p < kk; p++){
					if(A[p][1] == w){
						break;
					}
				}
				int z1[n + 1], r1;
				r1 = intersection1(n, z1, r, z, A[p]);
				//A[p][0] = r1 + 1;
				//J[l1] = (int *)malloc((n + 1)*sizeof(int));
				J[l1][0] = r1 + 1;
				J[l1][1] = w;
				for(int y = 2; y < r1 + 2; y++){
					J[l1][y] = z1[y - 2];
				}
				r1 = intersection1(n, z1, k2, x2, A1[p]);
				//J1[l2] = (int *)malloc((n + 1)*sizeof(int));
				J1[l2][0] = r1 + 1;
				J1[l2][1] = w;
				//A1[p][0] = r1 + 1;
				for(int y = 2; y < r1 + 2; y++){
					J1[l2][y] = z1[y - 2];
				}
				l1++;
				l2++;
				//J[l1] = (int *)malloc((n + 1)*sizeof(int));
				//J1[l2] = (int *)malloc((n + 1)*sizeof(int));
			}
			//if(r != 0){
			int xt[n + 1];
			int r2 = intersection1(n, xt, k2, x2, A1[sx]);
//			printf("22222e%d %d %d %d222||", r2, k2, A1[sx][1] - 1, u);
			xy[xy1] = u;
			xy1++;
			for(int y = 0; y < xy1; y++){
//				printf("%dbbbbbbbbbb\n", xy[y]);
			}
//			printf("kkkkrrr %d rrrkkk", r);
			//printf("5555555%d ", r2);

			LocalMCE( xy, xy1, b, a, n, J, l1, J1, l2, z, r, xt, r2);
			xy1--;
			x2[k2] = u;
			k2++;
			for(int y = 0; y <= n; y++){
				free(J[y]);
				free(J1[y]);
			}
			free(J);
			free(J1);
		}
	}
}
int intersection(int b[][2], int x3[], int n, struct node *a[], int v1, int v2, int f){
	v1--;
	v2--;
	int x1[n], x2[n];
	struct node* h;
	h = a[v1];
	int i = 0;
	while(h != NULL){
		x1[i] =  h -> val;
		i++;
		h = h -> next;
	}
	int j = 0;
	h = a[v2];
	while(h != NULL){
		x2[j] =  h -> val;
		j++;
		h = h -> next;
	}
	qsort( x1, i, sizeof(int), cmp);
	qsort( x2, j, sizeof(int), cmp);
	int i1 = 0, j1 = 0, k = 1;
	/*for(i1 = 0; i1 < j; i1++){
		printf("g %d g", x2[i1]);
	}*/
	i1 = 0;
	while(i1 < i && j1 < j){
		if(x1[i1] == x2[j1]){
			int gg = x1[i1] - 1;
			if(f == 0 || b[v1][1] < b[gg][1]){
				x3[k] = x1[i1];
				k++;
			}
			i1++;
			j1++;
		}
		else if(x1[i1] < x2[j1])
			i1++;
		else
			j1++;
	}
	return k;
}
int intersection1(int n, int x3[], int i, int x1[], int x2[]){
	qsort( x1, i, sizeof(int), cmp);
	//qsort( x2, j, sizeof(int), cmp);
	int i1 = 0, j1 = 2, k = 0, j = x2[0] + 1, u[n];
	//printf("\n");
	/*for(k = 0; k < i; k++){
		printf("dd%d ", x1[k]);
	}
	for(k = 1; k < j; k++){
		printf("hh%d ", x2[k]);
	}
	printf("\n");*/
	k = 0;
	i1 = 0;
	while(i1 < i && j1 < j){
		if(x1[i1] == x2[j1]){
			x3[k] = x1[i1];
			k++;
			i1++;
			j1++;
		}
		else if(x1[i1] < x2[j1])
			i1++;
		else
			j1++;
	}
	return k;
}
void freeList(struct node* head)
{
   struct node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}
int comp(const void *pa, const void *pb){
	const int *a = pa;
	const int *b = pb;
	return a[1] - b[1];
}
int compa(const void *pa, const void *pb){
	const int *a = pa;
	const int *b = pb;
	return a[0] - b[0];
}
int main(int argc, char** argv){
	// Initialize the MPI environment
	MPI_Init(&argc, &argv);

	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	// Get the rank of the process
	//int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);
	int vi = world_size - 1;
	if(rank == 0){
		int n, k, i, j, c1;
		scanf("%d", &n);
		int b[n][2], c[n];
		struct node *a[n], *head;
		for(i = 0; i < n; i++){
			scanf("%d", &k);
			b[i][0] = i;
			b[i][1] = k;
			a[i] = (struct node*)malloc(sizeof(node));
			head = a[i];
			for(j = 0; j < k; j++){
				scanf("%d", &c1);
				head -> val = c1;
				head -> next = NULL;
				if(j < k - 1){
					head -> next = (struct node*)malloc(sizeof(node));
					head = head -> next;
				}
			}
		}
		qsort( b, n, sizeof(int *), comp);
		for(i = 0; i < n; i++){
			head = a[i];
	//		printf("%d  ", i);
			while(head != NULL){
	//			printf("%d ",head -> val);
				head = head -> next;
			}
			c[i] = b[i][0];
			b[i][1] = i;
	//		printf("\n");
	//		printf("   %d %d", b[i][0], b[i][1]);
	//		printf("\n");
	//		printf("\n");
		}
		qsort( b, n, sizeof(int *), compa);
		int cc[n];
		for(i = 0; i < n; i++){
			int z = c[i] + 1;
			cc[n - i - 1] = c[i];
//			printf("%d ", z);
		}
//		printf("\n");
		j = 0;
		int g[n], g1[n];
		for(i = 0; i < n; i++){
			g[i] = b[i][0];
			g1[i] = b[i][1];
		}
		for(i = 1; i <= vi; i++){
			MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			/*for(int ik = 0; ik < n; ik++){
				MPI_Send(b[ik], 2, MPI_INT, i, 0, MPI_COMM_WORLD);
			}*/
			MPI_Send(g, n, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(g1, n, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		struct node *h, *h1;
		int sk = 0;
		while(j < n){
			int buf;
			MPI_Status status;
			// receive message from any source
			MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			//printf("%d %d \n", j, buf);
			//int replybuf[];
			// send reply back to sender of the message received above
			//MPI_send(buf, 32, MPI_INT, status.MPI_SOURCE, tag, MPI_COMM_WORLD);
			//i = status.MPI_SOURCE;
			i = buf;
			//printf("%dllllll\n", sk);
			MPI_Send(&sk, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			//for(i = 1; i <= vi; i++){
				/*if(j >= n){
					break;
				}*/
			int v = cc[j] + 1, count = 0;
			MPI_Send(&v, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			v--;
			h = a[v];
			int sa[125], f[n], t = 0;
			while(h != NULL){
				int tem = h -> val;
				if(b[tem - 1][1] > b[v][1]){
					count++;
				}
				f[t] = tem;
				t++;
				//MPI_Send(&tem, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				h = h -> next;
			}
			MPI_Send(&t, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(f, t, MPI_INT, i, 0, MPI_COMM_WORLD);
			//int te = -1;
			//MPI_Send(&te, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			h = a[v];
			MPI_Send(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			while(h != NULL){
				int tem = h -> val;
				if(b[tem - 1][1] > b[v][1]){
					MPI_Send(&tem, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
					tem--;
					h1 = a[tem];
					t = 0;
					while(h1 != NULL){
						int tem1 = h1 -> val;
						/*if(b[tem - 1][1] > b[v][1]){
							count++;
						}*/
						f[t] = tem1;
						t++;
						//MPI_Send(&tem1, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
						h1 = h1 -> next;
					}
					MPI_Send(&t, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
					MPI_Send(f, t, MPI_INT, i, 0, MPI_COMM_WORLD);
					//MPI_Send(&te, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				}
				h = h -> next;
			}
			j++;
			//}
		}
		j = 0;
		sk = 1;
		while(j < world_size - 1){
			int buf;
			MPI_Status status;
			MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			//i = status.MPI_SOURCE;
			MPI_Send(&sk, 1, MPI_INT, buf, 0, MPI_COMM_WORLD);
			j++;
		}
	}
	else{
		//printf("xxx%d  ", rank);
		int n, v, temp;
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int b[n][2], g[n], g1[n];
		MPI_Recv(g, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(g1, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		/*for(int ik = 0; ik < n; ik++){
			//MPI_Send(b[ik], 2, MPI_INT, i, 0, MPI_COMM_WORLD);
			
			//printf("hi");
		}*/
		for(int i = 0; i < n; i++){
			b[i][0] = g[i];
			b[i][1] = g1[i];
		}
		/*for(i = 0; i < n; i++){
			a[i] = (struct node*)malloc(sizeof(node));
		}*/
		int r = rank - 1, f[n], t;
		while(1){
			int rk = 1, sk;
			MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			MPI_Recv(&sk, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(sk == 1){
				//printf("gggg");
				break;
			}
			//printf("rank1: %d", rank);
			struct node *h;
			struct node **a = (struct node**)malloc(n*sizeof(struct node*));
			//r = r + vi;
			for (int i = 0; i < n; i++) {
				a[i] = NULL;
			}
			//printf("zzz\n");
			MPI_Recv(&v, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//printf("%d\n",v);
			//printf("%d zzz\n", v);
			a[v - 1] = (struct node*)malloc(sizeof(struct node));
			h = a[v - 1];
			int xxx = 0;
			MPI_Recv(&t, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(f, t, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			h -> next = NULL;
			int t1 = 0;
			while(t1 < t){
				//printf("rank4: %d", rank);
				//MPI_Recv(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				//printf("rank4: %d %dhhhhh", rank, temp);
				//h = (struct node*)malloc(sizeof(node));
				/*if(temp == -1){
					//h = NULL;
					break;
				}*/
				/*if(h == NULL){
					printf("gggggjjjj\n");
					h = (struct node*)malloc(sizeof(node));
				}*/
				if(xxx != 0){
					h -> next = (struct node*)malloc(sizeof(node));
					h = h -> next;
				}
				h -> val = f[t1];
				t1++;
				h -> next = NULL;
				//h -> next = (struct node*)malloc(sizeof(node));
				//h = h -> next;
				//h -> next = NULL;
				//h = h -> next;
				xxx++;
			}
			//printf("xxx%d   \n", r);
			xxx = 0;
			h = a[v - 1];
			/*while(h != NULL){
				printf("%d %dzzz", h -> val, v);
				h = h -> next;
				xxx++;
			}
			printf("    ooo %d\n", v);*/
			//printf("xxx%d   \n", r);
			//printf("ggggg\n");
			//printf("rank10: %d", xxx);
			int count, c1 = 0;
			MPI_Recv(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//printf("rank3: %d %d/t ", rank, count);
			while(c1 < count){
				
				MPI_Recv(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				//printf("    rank5: %d", temp);
				a[temp - 1] = (struct node*)malloc(sizeof(node));
				xxx = 0;
				h = a[temp - 1];
				int vv = temp;
				h -> next = NULL;
				//printf("rank5: %d", rank);
				MPI_Recv(&t, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(f, t, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				t1 = 0;
				while(t1 < t){
					//printf("rank6: %d", rank);
					//MPI_Recv(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					//printf("temp: %d", temp);
					//h = (struct node*)malloc(sizeof(node));
					/*if(temp == -1){
						break;
					}*/
					if(xxx != 0){
						h -> next = (struct node*)malloc(sizeof(node));
						h = h -> next;
					}
					h -> val = f[t1];
					t1++;
					h -> next = NULL;
					/*h -> val = temp;
					h -> next = (struct node*)malloc(sizeof(node));
					h = h -> next;
					h -> next = NULL;*/
					xxx++;
				}
				c1++;
				xxx = 0;
				h = a[vv - 1];
				/*while(h != NULL){
					printf("%d %deee", h -> val, vv);
					h = h -> next;
					xxx++;
				}
				printf("    ooo %d\n", vv);*/
			}
			//printf("rank6  ");
			int q;// = intersection(x3, n, c, a, 1, 2);
			int x1[n + 1], x2[n + 1], x3[n + 1], x4[n + 1];
			int i2 = 0, j2 = 0;
			int bn = 0;
			//h = a[0];
			/*printf("%dff", q);
			for(i = 0; i < q; i++){
				printf("%djjj ", x3[i]);
			}
			printf("\n");*/
			/*while(h != NULL){
				x1[i2] = h -> val;
				h = h -> next;
				i2++;
			}
			h = a[1];
			while(h != NULL){
				if(b[1][1] < b[h -> val - 1][1]){
					x2[j2] = h -> val;
					j2++;
				}
				h = h -> next;
			}
			q = intersection1(x3, i2, x1, j2, x2);
			printf("%dff", q);
			for(i = 0; i < q; i++){
				printf("%djjj ", x3[i]);
			}*/
			int k1, k2;
		//	printf("\n%dxx\n", c[0]);
			//int v = c[j];
	//		printf("%d %diiiiiiii\n", v, j);
			//printf("%d xx", v);
			v--;
			h = a[v];
			
			int q1, kk1 = 0, kk = 0;
			//printf("gg-1  ");
			int **A = (int **)malloc((n + 1)*sizeof(int *));
			int **A1 = (int **)malloc((n + 1)*sizeof(int *));
			for(int j = 0; j < n + 1; j++){
				A[j] = (int *)malloc((n + 1)*sizeof(int));
				A1[j] = (int *)malloc((n + 1)*sizeof(int));
			}
			//printf("gg0");
			k1 = k2 = 0;
			//printf("rank6  ");
			//h = NULL;
			while(h != NULL){
				//printf("gg1 %d", h -> val);
				if(b[h -> val - 1][1] > b[v][1]){
					x1[k1] = h -> val;
					//printf("gg2");
					k1++;
					x3[0] = x4[0] = h -> val;
					q = intersection(b, x3, n, a, v + 1, h -> val, 1);
					q1 = intersection(b, x4, n, a, v + 1, h -> val, 0);
	//				printf("gggg %d %d gggggggggg", q, q1);
					/*for(i = 0; i < q; i++){
						printf("%d ", x3[i]);
					}
					printf("\n");
					for(i = 0; i < q1; i++){
						printf("%d ", x4[i]);
					}
					printf("\n\n");*/
					//A[kk] = (int *)malloc((n + 1)*sizeof(int));
					A[kk][0] = q;
					for(int l = 0; l < q; l++){
						A[kk][l + 1] = x3[l];
					}
					kk++;
					//A1[kk1] = (int *)malloc((n + 1)*sizeof(int));
					A1[kk1][0] = q1;
					for(int l = 0; l < q1; l++){
						A1[kk1][l + 1] = x4[l];
					}
					kk1++;
				}
				else{
					x2[k2] = h -> val;
					k2++;
				}
				h = h -> next;
			}
			//printf("gg3");
			/*for(int l = 0; l < kk1; l++){
				for(int l1 = 1; l1 <= A1[l][0]; l1++){
					printf("%d ", A1[l][l1]);
				}
				printf("\n");
			}
			//printf("yy\n");
			for(int l = 0; l < kk; l++){
				for(int l1 = 1; l1 <= A[l][0]; l1++){
					printf("%d ", A[l][l1]);
				}
				printf("\n");
			}*/
			//printf("xxx");
			int xy[n + 1];
			xy[0] = v + 1;
			//printf("rank2: %d  %d     ", rank, r);
			LocalMCE(xy, 1, b, a, n, A, kk, A1, kk1, x1, k1, x2, k2);
		//	printf("\nttttttttttttttt\n");
			//break;
			for(int i = 0; i <= n; i++){
				free(A[i]);
				free(A1[i]);	
			}
			free(A);
			free(A1);
			for(int i = 0; i < n; i++){
				freeList(a[i]);
				a[i] = NULL;
				
			}
			free(a);
			r = r + vi;
			printf("%d\n",v);
			//printf("rank2: %d  %d     ", rank, r);
		}
	}
	MPI_Finalize();
}
