#include <stdio.h>
#include <string.h>
#include <mosquitto.h>

int main(int argc, char *argv[]) {
  char *host="pc9100";
  int port = 1883;
  char *message = "hello world!";
  char *topic = "greeting";
  
  mosquitto_lib_init();
  struct mosquitto *mosq = mosquitto_new(
    NULL,  // Generate an id
    true,  // Create a clean session
    NULL); // No callback param
  int rc = mosquitto_connect(
    mosq, // Client handle
    host, // Host of the broker
    port, // Port of the broker
    false); // No keepalive
  if (rc != MOSQ_ERR_SUCCESS) {
    printf("Error with connect: %d\n", rc);
    return(rc);
  }
  mosquitto_publish(
    mosq, // Client handle
    NULL, // Message id
    topic, // Topic
    strlen(message)+1, // Length of message
    (const void *)message, // Message to be sent
    0, // QoS = 0
    false); // Not retained
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
}
