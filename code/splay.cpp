int ch[maxn][2], far[maxn], typ[maxn], sz[maxn], val[maxn], tot, root;

inline void upd(int x) {
	if (!x) return ;
	sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
}

inline void init() {
	tot = 1;
	root = 0;
}

inline int new_node() {
	int x = tot++;
	ch[x][0] = ch[x][1] = 0;
	far[x] = 0; typ[x] = 0;
	sz[x] = 1;
	return x;
}

inline void setc(int x, int c, int y) {
	if (c < 2)
		ch[x][c] = y;
	else
		root = y;
	if (y) {
		far[y] = x;
		typ[y] = c;
	}
}

inline void rot(int x)
{
	int y = far[x], c = typ[x];
	//push_down(y);
	//push_down(x);
	setc(far[y], typ[y], x);
	setc(y, c, ch[x][!c]);
	setc(x, !c, y);
	upd(y);
	upd(x);
}

void splay(int x, int f = -1)
{
	if (!x) return ;
	while (far[x] != f) {
		if (far[far[x]] == f)
			rot(x);
		else {
			int y = far[x];
			if (typ[x] == typ[y])
				rot(y);
			else
				rot(x);
			rot(x);
		}
	}
}

inline void insert(int y, int x) // insert node x after y
{
	splay(y);
	//push_down(y);
	if (!ch[y][1]) {
		setc(y, 1, x);
	} else {
		y = ch[y][1];
		while (ch[y][0]) {
			//push_down(y);
			y = ch[y][0];
		}
		//push_down(y)
		setc(y, 0, x);
	}
	splay(x);
}

inline int find(int k) {
	int x = root;
	
	while (x) {
		//push_down(x);
		if (k <= sz[ch[x][0]]) {
			x = ch[x][0];
		} else if (k == sz[ch[x][0]] + 1) {
			splay(x);
			return x;
		} else {
			k -= sz[ch[x][0]] + 1;
			x = ch[x][1];
		}
	}
	return 0;
}

inline void erase(int x) { //remove single node x
	if (!x) return ;
	splay(x);
	//push_down(x);
	if (ch[x][0] == 0) {
		setc(far[x], typ[x], ch[x][1]);
		return ;
	}
	int y = ch[x][0];
	//push_down(y);
	while (ch[y][1]) {
		y = ch[y][1];
		//push_down(y);
	}
	setc(y, 1, ch[x][1]);
	setc(far[x], typ[x], ch[x][0]);
	upd(y);
	splay(y);
}
