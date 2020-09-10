#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

int main(){

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  // char buffer[SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    printf("Error for socket --> Timestamp: %d\n",(int)time(NULL));
    exit(1);
  }
  printf("Socket Done --> Timestamp: %d\n",(int)time(NULL));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr))< 0) {
    exit(1);
  }
  printf("Bind Done --> Timestamp: %d\n",(int)time(NULL));

  if(listen(sockfd, 10) == 0){
    printf("Listening Started --> Timestamp: %d\n",(int)time(NULL));
	}
  else
  {
    exit(1);
  }

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
//   char buffer[SIZE];
// int n;
  char *buffer[SIZE];
  int s = recv(new_sock, buffer, 2048, 0);
  if (s<0){
      printf("recieving Failed --> Timestamp: %d\n",(int)time(NULL));
  }
  else
  {
      printf("%s\n", buffer);
  };
  FILE *fp;
  fp = fopen(buffer, "r");
  if (fp == NULL) {
    printf("File Reading Error --> Timestamp: %d\n",(int)time(NULL));
    exit(1);
  }else{
    printf("filefound --> Timestamp: %d\n",(int)time(NULL));
  }
  char data[SIZE] = {0};
  while(1) {
    // int n = fgets(data, SIZE,fp)
    if (fgets(data, SIZE, fp) == NULL){
      // bzero(data, SIZE);
      // exit(1)
      break;
    }
    if (send(new_sock, data, sizeof(data), 0) <0) {
      printf("Error in sending File --> Timestamp: %d\n",(int)time(NULL));
      exit(1);
    }
    bzero(data, SIZE);
  }
  printf("Completed --> Timestamp: %d\n",(int)time(NULL));

  return 0;
}