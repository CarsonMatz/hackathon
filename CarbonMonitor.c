#include <stdio.h>
#include <time.h>

float linearRegression(const float x[5], const float y[5]);
void addData(float x[5], float y[5], float newX, float newY);

int main()
{
    float x[5] = {-1, -1, -1, -1, -1}, y[5] = {-1, -1, -1, -1, -1}; // preset array of size 5 so each value has -1
    float newX, newY; // for newest data point
    addData(x, y, newX, newY); // adding new data to the back, and removing old data from the front of the array
    float slope = linearRegression(x, y);  // finding linear regression
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