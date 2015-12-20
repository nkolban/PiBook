#include <stdio.h>
#include <gps.h>

int main(int argc, char *argv[]) {
  printf("Starting gps client test\n");
  struct gps_data_t gps_data;
  int ret = gps_open("localhost", "2947", &gps_data);
  printf("ret from gps_open=%d\n", ret);
  if (ret != 0) {
    return 0;
  }
  gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
  while(1) {
    if (gps_waiting(&gps_data, 500) != 0) {
      if (gps_read(&gps_data) != -1) {
        printf("fix: %f, %f\n", \
          gps_data.fix.latitude,
          gps_data.fix.longitude);
      } else {
        printf("Error\n");
      }
    }
  }
  gps_close(&gps_data);
}
