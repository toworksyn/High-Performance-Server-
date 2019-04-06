//
// Latest edit on 2019/2/28.
//


#ifndef HTTP_PARSE_H
#define HTTP_PARSE_H

#define CR '\r'
#define LF '\n'

// http请求行解析
int sy_http_parse_request_line(sy_http_request_t *request);
// http请求体解析
int sy_http_parse_request_body(sy_http_request_t *request);

#endif
