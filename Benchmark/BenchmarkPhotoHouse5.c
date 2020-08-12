#include <stdio.h>
#define INT_MAX 2147483647

float PanelData[5][13] = {{1.94432, 0.1620, 72, 45, 0.00053, -0.0031, 9.18, 45.1, 315, 8.16, 36.6, 33.4, 268.40},
                          {1.94432, 0.1646, 72, 45, 0.00053, -0.0031, 9.26, 45.3, 320, 8.69, 36.8, 33.6, 190.00},
                          {1.94432, 0.1672, 72, 45, 0.00053, -0.0031, 9.34, 45.5, 325, 8.78, 37.0, 33.7, 216.67},
                          {1.94432, 0.1697, 72, 45, 0.00053, -0.0031, 9.45, 45.6, 330, 8.88, 37.2, 33.9, 170.30},
                          {0.99960, 0.1500, 36, 46, 0.00060, -0.0037, 8.61, 22.90, 150, 8.12, 18.50, 14.61, 108.50}};
                          

float BatteryData[5][6] = {{0.85, 12, 80, 14.4, 13.8, 131.00},
                           {0.85, 12, 105, 14.4, 13.8, 150.00},
                           {0.85, 12, 150, 14.4, 13.8, 324.75},
                           {0.85, 12, 175, 14.4, 13.8, 299.75},
                           {0.85, 12, 220, 14.4, 13.2, 330.73}};


float ControllerData[5][6] = {{0.98, 35, 24, 13, 145, 294.95},
                              {0.98, 15, 24, 13, 75, 88.40},
                              {0.98, 50, 48, 13, 150, 347.82},
                              {0.98, 60, 48, 13, 150, 388.91},
                              {0.96, 60, 60, 13, 140, 1072.50}};


float InverterData[5][6] = {{0.93, 48, 110, 700, 1600, 400.00},
                            {0.93, 48, 110, 1200, 2400, 750.00},
                            {0.91, 24, 120, 280, 750, 149.75},
                            {0.91, 24, 120, 400, 1000, 187.25},
                            {0.90, 24, 125, 1800, 2900, 1669.75}};





int getLowestCost(int num_rows, int num_cols, float arr[num_rows][num_cols])
{
    int totalCost = INT_MAX;

    int cost_column = num_cols - 1;

    for (int i = 0; i < num_rows; i++)
    {
        int v = arr[i][cost_column];

        if (v < totalCost)
            totalCost = v;
    }

    if (totalCost == INT_MAX)
        return -1;
    else
        return totalCost;
}

int getTotalCost()
{
    int cost_panel = getLowestCost(sizeof(PanelData) / sizeof(PanelData[0]), sizeof(PanelData[0]) / sizeof(PanelData[0][0]), PanelData);

    int cost_baterry = getLowestCost(sizeof(BatteryData) / sizeof(BatteryData[0]), sizeof(BatteryData[0]) / sizeof(BatteryData[0][0]), BatteryData);

    int cost_controller = getLowestCost(sizeof(ControllerData) / sizeof(ControllerData[0]), sizeof(ControllerData[0]) / sizeof(ControllerData[0][0]), ControllerData);

    int cost_inverter = getLowestCost(sizeof(InverterData) / sizeof(InverterData[0]), sizeof(InverterData[0]) / sizeof(InverterData[0][0]), InverterData);

    int cost_total = cost_panel + cost_baterry + cost_controller + cost_inverter;

    return cost_total;
}

int main()
{
    int total = getTotalCost();

    return 0;
}