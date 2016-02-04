// gcc -o test_ngx_queue ../src/*.c  test_ngx_queue.c -I ../src/
// mkdir -v logs
// cd logs
// touch error.log
// cd ..
// ./test_ngx_queue

#include "../src/ngx_core.h"


typedef struct{
    u_char *str;
    ngx_queue_t queue;
    int num;
}test_node;


ngx_int_t cmp_test_node(const ngx_queue_t *a,const ngx_queue_t*b){
    test_node * a_node = ngx_queue_data(a,test_node,queue);
    test_node * b_node = ngx_queue_data(b,test_node,queue);
    return (a_node->num > b_node->num);
}

int main(int argc, char *argv[])
{
    ngx_int_t n;
    ngx_log_t * log;

    ngx_queue_t queue_container;
    ngx_queue_t *q;
    test_node node[5];
    test_node *ele_node;
    ngx_pagesize = getpagesize();
    n =  ngx_strerror_init();
    if (n == NGX_ERROR){
        return NGX_ERROR;
    }

    ngx_time_init();
    log =  ngx_log_init((u_char *)"./");
    ngx_use_stderr = 0;
    if (log == NULL){
        ngx_log_stderr(NGX_ERROR,(const char*)"can not init log ");
        return NGX_ERROR;
    }

    ngx_queue_init(&queue_container);

    for (n = 0;n < 5;n++){
        node[n].num = n;
    }

    ngx_queue_insert_tail(&queue_container,&node[0].queue);
    ngx_queue_insert_head(&queue_container,&node[1].queue);
    ngx_queue_insert_after(&queue_container,&node[2].queue);
    ngx_queue_insert_head(&queue_container,&node[3].queue);
    ngx_queue_insert_tail(&queue_container,&node[4].queue);

    for (q = ngx_queue_head(&queue_container);
         q != ngx_queue_sentinel(&queue_container);
         q = ngx_queue_next(q)){
        ele_node = ngx_queue_data(q,test_node,queue);
        printf("%d\n",ele_node->num);
    }

    ngx_queue_sort(&queue_container,cmp_test_node);
    for (q = ngx_queue_head(&queue_container);
         q != ngx_queue_sentinel(&queue_container);
         q = ngx_queue_next(q)){
        ele_node = ngx_queue_data(q,test_node,queue);
        printf("%d\n",ele_node->num);
    }


     return NGX_OK;
}

