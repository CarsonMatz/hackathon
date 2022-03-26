#include <stdio.h>
#include <time.h>

float linearRegression(const float x[5], const float y[5]);
void addData(float x[5], float y[5], float newX, float newY);

int main()
{
    float x[5] = {-1, -1, -1, -1, -1}, y[5] = {-1, -1, -1, -1, -1};
    for (int i = 0; i < 5; i++)
    {
        addData(x, y, i+1, i+2);
    }
    float slope = linearRegression(x, y); 
    float newX, newY; // for newest data point
    newX = 25;
    newY = 25;
    for(int i = 0; i < 5; i++)
    {
        printf("\nx is: %f ", x[i]);
        printf("and y is: %f", y[i]);
    }
    addData(x, y, newX, newY);
    for(int i = 0; i < 5; i++)
    {
        printf("\nx is: %f ", x[i]);
        printf("and y is: %f", y[i]);
    }
}

float linearRegression(const float x[5], const float y[5])
{
    float sumX = 0;
    float sumX2 = 0;
    float sumY = 0;
    float sumXY = 0;
    for (int i = 0; i < 5; i++)
    {
        sumX = sumX + x[i];
        sumX2 = sumX2 + x[i]*x[i];
        sumY = sumY + y[i];
        sumXY = sumXY + x[i]*y[i];
    }
     return (5*sumXY-sumX*sumY)/(5*sumX2-sumX*sumX);
}

void addData(float x[5], float y[5], float newX, float newY)
{
    if (x[4] == -1)
    {
        for (int i = 0; i < 5; i++)
        {
            if (x[i] == -1)
            {
                x[i] = newX;
                y[i] = newY;
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            x[i] = x[i+1];
            y[i] = y[i+1];
        }
        x[4] = newX;
        y[4] = newY;
    }
    
}