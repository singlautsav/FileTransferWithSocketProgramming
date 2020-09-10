
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#define SIZE 1024


int main(int argc, char *argv[]){

  int sockfd;
  struct sockaddr_in server_addr;
  // FILE *fp;
  char filename[SIZE];
  
  
  // scanf("%s", filename);
  printf("%s", filename);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    printf("Error for socket --> Timestamp: %d\n",(int)time(NULL));
    exit(1);
  }
  printf("Sockets Done --> Timestamp: %d\n",(int)time(NULL));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    printf("Error for socket connection --> Timestamp: %d\n",(int)time(NULL));
    exit(1);
  }
  printf("Connected to sercver --> Timestamp: %d\n",(int)time(NULL));

  // fp = fopen(filename, "r");
  // if (fp == NULL) {
  //   perror("[-]Error in reading file.");
  //   printf("Timestamp: %d\n",(int)time(NULL));
  //   exit(1);
  // }
//   bzero(filename, SIZE);
  // char filename2[1025];
  // strcpy(filename2,filename);
  // printf(filename2);
  printf("EnterFileName: ");
  fgets(filename, sizeof(filename),stdin);
  strtok(filename,"\n");
  if (send(sockfd,filename,sizeof(filename),0)<0){
      printf("SendingFailed");
      exit(1);
  }
  else
  {
      printf("sent \n");
  }

  // addr_size = sizeof(new_addr);
  // new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  // // printf("[+] sending file. \n");
  int n;
  FILE *fp;
  fp = fopen(filename, "w");
  // char *filename = "recv.txt";
  char buffer[SIZE];
  int a = 1;
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      if (a==1){
        printf("File Not found error --> Timestamp: %d\n",(int)time(NULL));
        exit(1);
      }
      break;
    }
    printf("%i ", a);
    printf("File data Recieved --> Timestamp: %d\n",(int)time(NULL));
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
    a+=1;
  }
  // printf("Timestamp: %d\n",(int)time(NULL));

	printf("Done Closing -->Timestamp: %d\n",(int)time(NULL));
  // printf(");
  close(sockfd);

  return 0;
}