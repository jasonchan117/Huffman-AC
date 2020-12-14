/*************************************************************************
	> File Name: AC.h
	> Author: 
	> Mail: 
	> Created Time: 2018年08月10日 星期五 20时10分11秒
 ************************************************************************/

#ifndef _AC_H
#define _AC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 2
#define BL '0'
int node_cnt;
typedef struct Node_AC{
    char *str;
    int flag;
    struct Node_AC *next[BASE];
    struct Node_AC *fail;

} Node_AC;

Node_AC *get_AC() {
    node_cnt++;
    return (Node_AC *)calloc(sizeof(Node_AC), 1);
}

void clear_AC(Node_AC *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        if (node->next[i] == NULL) continue;
        clear_AC(node->next[i]);
    }
    if (node->flag) free(node->str);
    free(node);
    return ;
} 

Node_AC *insert_AC(Node_AC *root, const char *str) {
    
    if (root == NULL) root = get_AC();
    Node_AC *p = root;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BL] == NULL) p->next[str[i] - BL] = get_AC();
        p = p->next[str[i] - BL];
    }
    p->flag = 1;
    p->str = strdup(str);
    
    return root;
}

void build_ac(Node_AC *root) {
    #define MAX_N 1000000
    if (root == NULL) return ;
    Node_AC **queue = (Node_AC **)malloc(sizeof(Node_AC *) * MAX_N);
    int head = 0, tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        Node_AC *node = queue[head++];
        for (int i = 0; i < BASE; i++) {
            if (node->next[i] == NULL) continue;
            Node_AC *p=node->fail;
            while(p&&p->next[i]==NULL) p=p->fail;
            
            if (p == NULL) node->next[i]->fail = root;
            else node->next[i]->fail = p->next[i];
            
            queue[tail++] = node->next[i];                
        }
    }
    free(queue);
    return ;
    #undef MAX_N
}

void search_ac(Node_AC *root, char *text,char **huf_str) {
    Node_AC *p = root;
    int ind=0;
    for (int i = 0; text[i]; i++) {
        
        while (p && p->next[text[i] - BL] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else p = p->next[text[i] - BL];
        Node_AC *q = p;
        while (q) {
            
            if (q->flag) huf_str[ind++]=strdup(q->str);
            q = q->fail;        
        }
    }
    huf_str[ind]=0;
    return ;

}


#endif
