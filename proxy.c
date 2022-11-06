#include <stdio.h>
#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr =
    "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 "
    "Firefox/10.0.3\r\n";

void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
// void get_filetype(char *filename, char *filetype);
// void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

// int main() {
//   printf("%s", user_agent_hdr);
//   return 0;
// }

/*  메인함수  */
int main(int argc, char **argv)
{
  int listenfd, connfd, clientfd;
  char hostname[MAXLINE], port[MAXLINE];
  char *buf[MAXLINE];
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  rio_t rio;
  /* Check command line args */
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
  listenfd = Open_listenfd(argv[1]); // 듣기 소켓 오픈
  /* 무한 서버 루프 */
  while (1)
  {
    clientlen = sizeof(clientaddr);
    /* 중선 -> 송희 */
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); // line:netp:tiny:accept
    Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
    printf("Accepted connection from (%s, %s)\n", hostname, port);
    Close(connfd);
    
    /* 송희 : 검열하기 (구현중...) */

    /* 송희 -> 예린 */
    clientfd = Open_clientfd(hostname, port);
    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin)!=NULL){
      Rio_writen(clientfd, )
    }

    /* 서버쪽 연결 종료 */
     // line:netp:tiny:close
  }
}

/* read_requesthdrs: 요청 헤더를 읽고 무시하기 */
void read_requesthdrs(rio_t *rp)
{
  char buf[MAXLINE];

  Rio_readlineb(rp, buf, MAXLINE);
  while (strcmp(buf, "\r\n"))
  {
    Rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
  }
  return;
}

// /* parse_uri: HTTP URI를 분석하기 */
// int parse_uri(char *uri, char *filename, char *cgiargs)
// {
//   char *ptr;
//   /* 실행파일의 홈 디렉토리 : cgi-bin */
//   /* cgi-bin을 포함하는 uri는 dynamic contents 요청임을 가정 */
//   if (!strstr(uri, "cgi-bin"))
//   {                      /* Static content */
//     strcpy(cgiargs, ""); /* cgi argument를 지우고 */
//     strcpy(filename, ".");
//     strcat(filename, uri);           /* uri를 상대 리눅스 경로이름으로 변환 (e.g. ./index.html) */
//     if (uri[strlen(uri) - 1] == '/') // uri가 '/'로 끝난다면
//       strcat(filename, "home.html"); // 기본 파일이름 추가
//     return 1;
//   }
//   else
//   { /* Dynamic content */
//     ptr = index(uri, '?');
//     /* cgi argument 추출 */
//     if (ptr)
//     {
//       strcpy(cgiargs, ptr + 1);
//       *ptr = '\0';
//     }
//     else
//       strcpy(cgiargs, "");
//     /* 나머지 uri를 상대 리눅스 경로이름으로 변환 */
//     strcpy(filename, ".");
//     strcat(filename, uri);
//     return 0;
//   }
// }

/*
 * get_filetype - Derive file type from filename
 */
// void get_filetype(char *filename, char *filetype)
// {
//   if (strstr(filename, ".html"))
//     strcpy(filetype, "text/html");
//   else if (strstr(filename, ".gif"))
//     strcpy(filetype, "image/gif");
//   else if (strstr(filename, ".png"))
//     strcpy(filetype, "image/png");
//   else if (strstr(filename, ".jpg"))
//     strcpy(filetype, "image/jpeg");
//   else if (strstr(filename, ".mp4"))
//     strcpy(filetype, "video/mp4");
//   else
//     strcpy(filetype, "text/plain");
// }

// /* clienterror : 에러 메시지를 클라이언트에게 전송 */
// void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
// {
//   char buf[MAXLINE], body[MAXBUF];

//   /* Build the HTTP response body */
//   sprintf(body, "<html><title>Tiny Error</title>");
//   sprintf(body, "%s<body bgcolor="
//                 "ffffff"
//                 ">\r\n",
//           body);
//   sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
//   sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
//   sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);
//   /* Print the HTTP response */
//   sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
//   Rio_writen(fd, buf, strlen(buf));
//   sprintf(buf, "Content-type: text/html\r\n");
//   Rio_writen(fd, buf, strlen(buf));
//   sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
//   Rio_writen(fd, buf, strlen(buf));
//   Rio_writen(fd, body, strlen(body));
// }
