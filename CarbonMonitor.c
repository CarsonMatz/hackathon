#include <stdio.h>
#include <time.h>

float linearRegression(const float* x, const float* y, int n);
void addData(float* x, float* y, float newX, float newY, int n);

int main()
{
    int n = 20;
    float x[n], y[n];
    for (int i = 0; i < n; i++)
    {
        x[i] = -1;
        y[i] = -1;
    } // preset array of size n so each value has -1
    float newX, newY; // for newest data point
    addData(x, y, newX, newY, n); // adding new data to the back, and removing old data from the front of the array
    float slope = linearRegression(x, y, n);  // finding linear regression
}


float linearRegression(const float* x, const float* y, int n)
{
    float sumX = 0;
    float sumX2 = 0;
    float sumY = 0;
    float sumXY = 0;
    for (int i = 0; i < n; i++)
    {
        sumX = sumX + x[i];
        sumX2 = sumX2 + x[i]*x[i];
        sumY = sumY + y[i];
        sumXY = sumXY + x[i]*y[i];
    }
     return (n*sumXY-sumX*sumY)/(n*sumX2-sumX*sumX);
}

void addData(float* x, float* y, float newX, float newY, int n)
{
    if (x[n-1] == -1)
    {
        for (int i = 0; i < n; i++)
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
        for (int i = 0; i < n; i++)
        {
            x[i] = x[i+1];
            y[i] = y[i+1];
        }
        x[n-1] = newX;
        y[n-1] = newY;
    }
}