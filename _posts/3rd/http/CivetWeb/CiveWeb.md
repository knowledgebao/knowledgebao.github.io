# 1. CiveWeb

- [1. CiveWeb](#1-civeweb)
  - [1.1. 简介](#11-简介)
  - [1.2. 主要结构](#12-主要结构)
  - [1.3. API](#13-api)
    - [1.3.1. 全局API](#131-全局api)
    - [1.3.2. websocket-server](#132-websocket-server)
    - [1.3.3. websocket-client](#133-websocket-client)
    - [1.3.4. http(s)-server](#134-https-server)
    - [1.3.5. http(s)-client](#135-https-client)
  - [1.4. 参考资料](#14-参考资料)

## 1.1. 简介

嵌入式的http服务库。
[头文件](https://github.com/civetweb/civetweb/blob/master/include/civetweb.h)

## 1.2. 主要结构

```C++
struct mg_context;    /* Handle for the HTTP service itself */
struct mg_connection; /* Handle for the individual connection */
/* This structure contains information about the HTTP request. */
struct mg_request_info;
/* This structure contains information about the HTTP response. */
/* This structure may be extended in future versions. */
struct mg_response_info;
```

## 1.3. API

### 1.3.1. 全局API

```C++
unsigned mg_init_library(unsigned features);
unsigned mg_exit_library(void);
struct mg_context *mg_start(const struct mg_callbacks *callbacks,
                            void *user_data,
                            const char **configuration_options);
void mg_stop(struct mg_context *);
```

```C++
//对 mg_context 上锁
void mg_lock_context(struct mg_context *ctx);
void mg_unlock_context(struct mg_context *ctx);
//发送文件
void mg_send_mime_file2(struct mg_connection *conn,...);
```

### 1.3.2. websocket-server

```C++
//启动websocket接口,设置下边的回调
void mg_set_websocket_handler(struct mg_context *ctx,...,callback);
//发送数据
int mg_websocket_write(struct mg_connection *conn,...);
```

```C++
//回调函数
//client 请求到来，return 0运行接入，return 1拒绝接入
typedef int (*mg_websocket_connect_handler)(const struct mg_connection *,...);
//连接成功，准备发送数据
typedef void (*mg_websocket_ready_handler)(struct mg_connection *, ...);
//client 数据到来，return 0关闭链接，return 1保持打开
/*if (flags & 0x80) {
        flags &= 0x7f;
        switch (flags) {
        case MG_WEBSOCKET_OPCODE_TEXT:
        case MG_WEBSOCKET_OPCODE_CONNECTION_CLOSE:
        defalut:
        }
 }
*/
typedef int (*mg_websocket_data_handler)(struct mg_connection *,int flags,char *data,size_t data_len,void *udata)
//client is closed
typedef void (*mg_websocket_close_handler)(const struct mg_connection *,...);
```

```C++
//websocket 调用 meg_write 或 mg_printf 时，需要获取唯一锁
void mg_lock_connection(struct mg_connection *conn);
void mg_unlock_connection(struct mg_connection *conn);
```

### 1.3.3. websocket-client

```C++
//建立连接
struct mg_connection *mg_connect_websocket_client(...);
//发送数据
int mg_websocket_client_write(struct mg_connection *conn,...);
```

### 1.3.4. http(s)-server

```C++
typedef int (*mg_request_handler)(struct mg_connection *conn, void *cbdata);
//启动 http 接口,mg_request_handler回调
void mg_set_request_handler(struct mg_context *ctx,...);
//发数据
int mg_write(struct mg_connection *, const void *buf, size_t len);
//获取请求数据
const struct mg_request_info *mg_get_request_info(const struct mg_connection *);
//读取远端数据
int mg_read(struct mg_connection *, void *buf, size_t len);

//处理 form-data 数据
struct mg_form_data_handler {
    //数据到来，当传输的是文件时，filename表示传输的文件名，path/pathlen 下载目录，return FORM_FIELD_STORAGE_STORE有效
    //return FORM_FIELD_STORAGE_STORE 触发 field_store 回调。return FORM_FIELD_STORAGE_GET 触发 field_get 回调。
    int (*field_found)(const char *key,const char *filename,char *path,size_t pathlen,void *user_data);
    //当 field_found 返回 FORM_FIELD_STORAGE_GET 时，触发，返回 form-data 数据。
    int (*field_get)(const char *key,const char *value,size_t valuelen,void *user_data);
    //当 field_found 返回 FORM_FIELD_STORAGE_STORE 时，完成文件下载时触发，如果文件存在会被覆盖。
    int (*field_store)(const char *path, long long file_size, void *user_data);
    void *user_data;
};
int mg_handle_form_request(struct mg_connection *conn,struct mg_form_data_handler *fdh);
```

### 1.3.5. http(s)-client

```C++
//建立连接
struct mg_connection *mg_connect_client(...);
//发送和接收参考 http(s)-server
```

## 1.4. 参考资料

1. [官网](https://github.com/civetweb/civetweb)
2. [doc](https://github.com/civetweb/civetweb/tree/master/docs)
3. [源码走读rgw内置civetweb的参数初始化过程](https://cloud.tencent.com/developer/article/1032846)
4. [海思编译](https://blog.csdn.net/qq_35810476/article/details/100763484)
