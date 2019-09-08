#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
int size;
pthread_mutex_t mutex;
pthread_mutex_t mutex1;

int main()
{
   int i ,j  , time=0,time1=0,position,temp,*ptr,*ptr1;
    float average_waiting_time,average_turnaround_time;
    printf("Enter number of process:  ");
    scanf("%d",&size);
    ptr=&size;
    int burst_time[*ptr],arrival_time[*ptr],sequence[*ptr],completion_time[*ptr],turning_time[*ptr];
	
    for(i=0;i<size;i++)
    {
        printf("Enter Arrival Time of P%d : ",i+1);
        scanf("%d",&arrival_time[i]);
        sequence[i]=i+1;  
	        
    }
    for(i=0;i<size;i++)
    {
        printf("Enter Burst Time of P%d : ",i+1);
        scanf("%d",&burst_time[i]);          
    }
    for(i=0;i<size;i++)
    {
        position=i;
        for(j=i+1;j<size;j++)
        {
            if(burst_time[j]<burst_time[position])
                position=j;
        }
 
        temp=burst_time[i];
        burst_time[i]=burst_time[position];
    	burst_time[position]=temp;
 
        temp=sequence[i];
        sequence[i]=sequence[position];
        sequence[position]=temp;
	    temp=arrival_time[i];
         arrival_time[i]=arrival_time[position];
        arrival_time[position]=temp;
    }
 	
    completion_time[0] = 0;
    for(i=1;i<size;i++)
    {
        completion_time[i]=0;
        for(j=0;j<i;j++)
            completion_time[i]+=burst_time[j];
 
        time+=completion_time[i];
    }
  	average_waiting_time=(float)time/size;      
     time1=0;
 
    printf("\nProcess\t    Burst Time \t   Arrival Time   \tWaiting Time\tTurnaround Time");
    for(i=0;i<size;i++)
    {
        turning_time[i]=burst_time[i]+completion_time[i];     //calculate turnaround time
        time1+=turning_time[i];
        printf("\np%d\t\t  %d\t\t  %d\t\t  %d\t\t\t%d", sequence[i],burst_time[i],arrival_time[i],completion_time[i],turning_time[i]);
    }
 
    average_turnaround_time=(float)time1/size;     
    printf("\n\nAverage Waiting Time=%f",average_waiting_time);
    printf("\nAverage Turnaround Time=%f\n",average_turnaround_time);
	for(i=0;i<size;i++)
	{
		if(burst_time[i]>10)
		{
			 pthread_mutex_lock(&mutex); 
			printf("Process %d is executing for 10 seconds",sequence[i]);
			sleep(10);
			printf("\n\nCPU is IDLE\n");
			sleep(3);
			 pthread_mutex_unlock(&mutex); 
		}
		else
		{
			 pthread_mutex_lock(&mutex1); 
		printf("Process %d is executing for %d seconds",sequence[i],burst_time[i]);	
		sleep(burst_time[i]);
		printf("\n\nCPU is IDLE\n");
		sleep(3);
		 pthread_mutex_unlock(&mutex1); 
		}
	}
	
	printf("\nTHANKYOU YOU FOR USING\nDEVELOPED BY:\nRAHUL VERMA \n11811619\nK18lE");
	return 0;
}

