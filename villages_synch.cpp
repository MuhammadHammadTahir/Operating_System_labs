#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
pthread_mutex_t bridge_mutex = PTHREAD_MUTEX_INITIALIZER;
int northbound_count = 0;
int southbound_count = 0;
void cross_bridge(const char* direction) {
 printf("Farmer crossing the bridge %s\n", direction);
 usleep(rand() % 1000000); // Sleep for up to 1 second
}
void* northbound_farmer(void* arg) {
 while (1) {
 pthread_mutex_lock(&bridge_mutex);
 northbound_count++;
 if (southbound_count > 0) {
 northbound_count--;
 pthread_mutex_unlock(&bridge_mutex);
 continue;
 }
 cross_bridge("Northbound");
 northbound_count--;
 pthread_mutex_unlock(&bridge_mutex);
 }
 return NULL;
}

 
void* southbound_farmer(void* arg) {
 while (1) {
 pthread_mutex_lock(&bridge_mutex);
 southbound_count++;
 if (northbound_count > 0) {
 southbound_count--;
 pthread_mutex_unlock(&bridge_mutex);
 continue;
 }
 cross_bridge("Southbound");
 southbound_count--;
 pthread_mutex_unlock(&bridge_mutex);
 }
 return NULL;
}
int main() {
 srand(time(NULL)); 
 pthread_t northbound_thread, southbound_thread;
 pthread_create(&northbound_thread, NULL, northbound_farmer, NULL);
 pthread_create(&southbound_thread, NULL, southbound_farmer, NULL);
 pthread_join(northbound_thread, NULL);
 pthread_join(southbound_thread, NULL);
 return 0;
}
