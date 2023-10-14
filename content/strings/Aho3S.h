/**
 * Author: Yusuf Sholeh(?)
 * Date: 2015-02-18
 * License: CC0
 * Source: Yes
 * Description: Aho-Corasick by Kak Ucup
 */
#pragma once

struct AhoCorasick {
	int trie[N][26], fail[N], saiz;
	AhoCorasick() {
		memset(trie[0],-1,sizeof trie[0]);
		saiz = 0;
	}
	void add(string str) {
		int cur = 0;
		for(int i = 0 ; i < str.length() ; i++) {
			int nex = str[i] - 'a';
			if(trie[cur][nex] == -1) {
				trie[cur][nex] = ++saiz;
				memset(trie[saiz],-1,sizeof trie[saiz]);
			}
			cur = trie[cur][nex];
		}
	}
	void build() {
		queue<int> q; fail[0] = 0;
		rep(i,0,26) {
			if(trie[0][i] == -1) trie[0][i] = 0;
			else {
				int nex = trie[0][i];
				fail[nex] = 0;
				q.push(nex);
			}}
		while(!q.empty()) {
			int now = q.front();	q.pop();
			for(int i = 0 ; i < 26 ; i++)
				if(trie[now][i] == -1) trie[now][i] = trie[fail[now]][i];
				else {
					int nex = trie[now][i];
					fail[nex] = trie[fail[now]][i];	q.push(nex);
				}
		}	
	}
	int getIndex(string str) {
		int cur = 0;
		for(int i = 0 ; i < str.length() ; i++) {
			//checkChar(str[i]);
			cur = trie[cur][str[i] - 'a'];
		}
		return cur;
	}
};
