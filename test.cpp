/*************************************************************************
	> File Name: test.cpp
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年08月07日 星期二 11时15分52秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#include "./frequency.h"
#include "./huffman.h"
#include "./trie.h"
#include "./sear.h"
#include <string.h>
#define CHAR_NUM 256



int insert_and_search(hashtable *h,unsigned char *origin,Trie root,char (*huf_code)[100],char *temp,unsigned char *ans,int word_cnt){
    while(scanf("%s",origin)!=EOF){
        if(origin[0]=='-') break;
        memset(temp,0,sizeof(temp));
        int ind=0,i;
        for(i=0;origin[i];++i){
            for(int j=0;huf_code[origin[i]][j];++j){
                temp[ind++]=huf_code[origin[i]][j];
            }
        }
        word_cnt+=i;
        temp[ind]='\0';
        printf("%s\n",temp);
        root=insert(root,temp);
    }
    printf("done\n");
    memset(ans,0,sizeof(ans));
    while(~scanf("%s",ans)){

        memset(temp,0,sizeof(temp));
        int ind=0;
        for(int i=0;ans[i];++i){
            for(int j=0;huf_code[ans[i]][j];++j){
                temp[ind++]=huf_code[ans[i]][j];
            }
        }
        temp[ind]='\0';


        if(search(root,temp)){
            printf("%s\n",temp);
            memset(ans,0,sizeof(ans));
            huff_to_str(temp,h,ans,huf_code);
            printf("find %s : YES\n",ans);
        }
        else printf("FALSE\n");
        memset(ans,0,sizeof(ans));
    }
}




int main() {
    char str[6] = "input";
    int freq[256] = {0};
    read_file(str, freq);
    for (int i = 0; i < 256; i++) {
        printf("[%3d ---- %3d] ", i, freq[i]);
         if (i % 3 == 0) printf("\n");
    }
    printf("\n");
    HFNode *arr[CHAR_NUM] = {0};
    char buff[100];
    char huf_code[256][100] = {0};
    int cnt = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] == 0) {
            cnt += 1;
            continue;
        }
        HFNode *new_node = get_new_node();
        new_node->ch = (char)i;
        new_node->freq = freq[i];
        arr[i - cnt] = new_node;
    }
    build(CHAR_NUM - cnt, arr);
    extract(arr[0], buff, huf_code, 0);
    for (int i = 0; i < CHAR_NUM; i++) {
        if (huf_code[i][0] == 0) continue;
        printf("%d : %s : %d\n", i, huf_code[i], StrtoInt(huf_code[i]));
    }
    printf("\n");
    FILE *fp = fopen(str, "r");
    Trie root = NULL;
    int word_cnt = 0;
    unsigned char origin[100]={0};
    char temp[500]={0};
    unsigned char ans[100]={0};

    hashtable *h=init(100000);
    for(int i=0;i<CHAR_NUM;i++){
        insert_ha(h,huf_code[i],i);
    }
    insert_and_search(h,origin,root,huf_code,temp,ans,word_cnt);
    return 0;
}
