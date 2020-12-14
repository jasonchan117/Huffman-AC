/***************************************************************[<0;96;13M] 
	> Created Time: 2018年08月10日 星期五 22时14分00秒
 ************************************************************************/


 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #define BASE 26
 #define BL 'a'

 typedef struct Node {
         char *str;
         int flag;
         struct Node *next[BASE];
         struct Node *fail;

 } Node;

 Node *get_new_node() {
         return (Node *)calloc(sizeof(Node), 1);

 }

 void clear(Node *node) {
         if (node == NULL) return ;
     for (int i = 0; i < BASE; i++) {
                 if (node->next[i] == NULL) continue;
                 clear(node->next[i]);
             
     }
         if (node->flag) free(node->str);
         free(node);
         return ;

 } 

 Node *insert(Node *root, const char *str) {
         if (root == NULL) root = get_new_node();
         Node *p = root;
     for (int i = 0; str[i]; i++) {
                 if (p->next[str[i] - BL] == NULL) p->next[str[i] - BL] = get_new_node();
                 p = p->next[str[i] - BL];
             
     }
         p->flag = 1;
         p->str = strdup(str);
         return root;

 }

 void build_ac(Node *root) {
         #define MAX_N 10000000
         if (root == NULL) return ;
         Node **queue = (Node **)malloc(sizeof(Node *) * MAX_N);
         int head = 0, tail = 0;
         queue[tail++] = root;
     while (head < tail) {
                 Node *node = queue[head++];
         for (int i = 0; i < BASE; i++) {
                         if (node->next[i] == NULL) continue;
                         Node *p = node->fail;
                         while (p && p->next[i] == NULL) p = p->fail;
                         if (p == NULL) node->next[i]->fail = root;
             else {
                 //printf("%d",p->next[i]==NULL);
                 node->next[i]->fail = p->next[i];
             }
            
                         queue[tail++] = node->next[i];
                     
         }
             
     }
         free(queue);
         return ;
         #undef MAX_N

 }

 void search_ac(Node *root, const char *text) {
         Node *p = root;
     for (int i = 0; text[i]; i++) {
        
         while (p && p->next[text[i] - BL] == NULL) p = p->fail;
         if (p == NULL) p = root;
        else p = p->next[text[i] - BL];
                 Node *q = p;
         while (q) {
                if (q->flag) printf("find string : %s\n", q->str);
                q = q->fail;
                       
         }
             
     }
         return ;

 }

 int main() {
         Node *root = NULL;
         root = insert(root, "ab");
         root = insert(root, "cd");
         root = insert(root, "ds");
        
         build_ac(root);
         search_ac(root, "abfdsafcd");
         clear(root);
         return 0;

 }

