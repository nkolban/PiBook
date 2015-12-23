#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl.h>


static void checkRC(CURLcode rc, char *message) {
  if (rc != CURLE_OK) {
    printf("Error: %d %s\n", rc, message);
  }
}

int main(int argc, char *argv[]) {
  printf("About to start\n");
  char urlText[100];

  CURLcode rc;
  CURL *curl = curl_easy_init();
  if (curl == NULL) {
    printf("Failed to setup curl\n");
    exit(-1);
  }
  while(1) {
    int value = rand() % 20;
    printf("Setting value: %d\n", value);
    sprintf(urlText, "https://api.thingspeak.com/update?api_key=D7YJKGFR1WV5D0UD&field1=%d", value);
    curl_easy_setopt(curl, CURLOPT_URL, urlText);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    rc = curl_easy_perform(curl);
    checkRC(rc, "perform");
    sleep(20);
  }
  curl_easy_cleanup(curl);
  printf("Ending\n");
  return 0;
}
