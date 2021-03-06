
#ifndef PARSER_H
#define PARSER_H



enum HTTPMethod{
    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE
};

typedef struct REQUEST{
    int method;
    float HTTPVersion;
    char *URI,
    *host,
    *user_agent,
    *accept,
    *accept_language,
    *accept_encoding,
    *DNT,
    *connection,
    *referer,
    *misc;
}REQUEST;

REQUEST HTTPrequest_parser(char *request);

#endif //PARSER_H