/*
 * 115200 baud = approx 8.681 microseconds. If the capture delay
 * was set to approx 4 microseconds, that would sample at least 
 * twice per data bit. This will also poll much more data.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

//const int CAPTURE_DELAY = 1; 		// in milliseconds
const int CAPTURE_DELAY_MICROSECONDS = 1;   //microseconds
const int CAPTURE_LENGTH = 10;	// in milliseconds
const int NUM_PROBES = 2;
const int TRIGGER = 29;
const int PIN1 = 26;
const int PIN2 = 27;
int finished;
FILE *fp;

/*
 * For now, this demo will read the signal on a pin for some time
 * and map it using gnuplot when finished. Should be simple enough.
 */

void *capture_length()
{
	delay(CAPTURE_LENGTH);
	finished = 1;
}

int setup()
{
	wiringPiSetup();
	switch(NUM_PROBES)
	{
		case 1:
			pinMode(PIN1, INPUT);
			break;
		case 2:
			pinMode(PIN1, INPUT);
			pinMode(PIN2, INPUT);
			pinMode(TRIGGER, INPUT);
			break;
		default:
			return 0;
	}
	fp = fopen(".output.csv", "w");
	return 0;
}

int main()
{
	if(setup())
		return EXIT_FAILURE;
	finished = 0;
	int count = 0;
	while(digitalRead(TRIGGER) == 0){printf("Waiting..\n");}
	pthread_t t1;	// one thread for the capture length timer
	switch(NUM_PROBES)
	{
		case 1:
			pthread_create(&t1, NULL, capture_length, NULL);
			while(!finished)
			{
				fprintf(fp, "%i, %i\n", count++, digitalRead(PIN1));
				delayMicroseconds(CAPTURE_DELAY_MICROSECONDS);
			}
			pthread_exit(NULL);
			close(fp);
			break;
		case 2:
			pthread_create(&t1, NULL, capture_length, NULL);
			while(!finished)
			{
				fprintf(fp, "%i, %i, %i\n", count++, digitalRead(PIN1), digitalRead(PIN2));
//				delay(CAPTURE_DELAY);
				delayMicroseconds(CAPTURE_DELAY_MICROSECONDS);
			}
			pthread_exit(NULL);
			close(fp);
			break;
		

		default:
			printf("Program is not configured for this number of probes.\n");
			printf("Quitting..\n");
			break;
	}
	return EXIT_SUCCESS;
}
