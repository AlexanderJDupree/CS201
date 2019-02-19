#include <stdio.h>
#include <sys/time.h>

int main()
{
    long points = 0;
    struct timeval start, end;

    gettimeofday(&start, NULL);

    printf("\nPress ENTER to stop timer\n");
    getchar();

    gettimeofday(&end, NULL);

    // points is time elapsed in ms
    points = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000);

    printf("\nTime elapsed: %ld", points);

    return 0;
}
