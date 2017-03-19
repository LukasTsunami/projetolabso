
filho(int readfd,int writefd)
{
  char *getHostname = "cat /etc/hostname"; //Recupera o Hostname
  char *getIPLocal = "hostname -I"; //Recupera o IP Local
  char *getMemUsed = "free -m | head -n 2 | tail -n 1 | awk '{print $3}'"; // Memoria usada em MEGABYTES
  char *getMemTotal = "free -m | head -n 2 | tail -n 1 | awk '{print $2}'"; //Memoria Total em MEGABYTES
  char *getCPUusage= "top -n 1 | head -n 3 | tail -n 1 | awk '{print $2}'"; //CPU usado em %
  char *buff[BUFF];
  char enviaPorPipe[BUFFPIPE];
  FILE *fp;

  while(1)
  {
    if((fp = popen(getHostname, "r")) == NULL)
     printf("ERROR 404");
    if(fgets(buff, BUFF, fp) == NULL)
      printf("ERROR 404");

    strcat(enviaPorPipe, buff);

    pclose(fp);


    if((fp = popen(getIPLocal, "r")) == NULL)
     printf("ERROR 404");
    if(fgets(buff, BUFF, fp) == NULL)
      printf("ERROR 404");

    strcat(enviaPorPipe, buff);
    pclose(fp);

    if((fp = popen(getMemUsed, "r")) == NULL)
     printf("ERROR 404");
    if(fgets(buff, BUFF, fp) == NULL)
      printf("ERROR 404");

    strcat(enviaPorPipe, buff);
    pclose(fp);

    if((fp = popen(getMemTotal, "r")) == NULL)
     printf("ERROR 404");
    if(fgets(buff, BUFF, fp) == NULL)
      printf("ERROR 404");

    strcat(enviaPorPipe, buff);
    pclose(fp);

    if((fp = popen(getCPUusage, "r")) == NULL)
     printf("ERROR 404");
    if(fgets(buff, BUFF, fp) == NULL)
      printf("ERROR 404");

    strcat(enviaPorPipe, buff);
    pclose(fp);


    write(writefd, enviaPorPipe, BUFFPIPE);
    enviaPorPipe[0] = '\0';
  }

}
