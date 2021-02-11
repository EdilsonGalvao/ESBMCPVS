extern void __VERIFIER_error() __attribute__((__noreturn__));
extern void __VERIFIER_assume(int expression);
unsigned int nondet_uint();
unsigned char nondet_uchar();

//#include <stdio.h>

//area, efficiency, num cells, NOCT, mii, miv, Iscref, Vocref, Pmref, Imref, Vmref, VmpNOCT, cost
float _panelSet[4][13] = {
    {1.97904, 0.1700, 72, 45, 0.0005, -0.003, 9.33, 45.6, 330, 8.85, 37.3, 34.4, 118},
    {1.984, 0.1991, 144, 45, 0.00049, -0.0029, 10.31, 49.10, 395, 9.83, 40.2, 37.5, 178.03},
    {1.984, 0.1789, 144, 45, 0.0005, -0.0029, 9.59, 46.8, 355, 9.02, 39.4, 36.60, 144.26},
    {2.20918, 0.1924, 144, 42, 0.0005, -0.0029, 11.29, 48.00, 425, 10.71, 39.70, 36.00, 187.41}};

//efficiency, voltage, capacityC20, Vbulk, Vfloat, cost
float _batterySet[1][6] = {
    {0.85, 12, 220, 14.14, 13.2, 243.69},
};

//efficiency, nominal current, voltage  output, Vmpptmin=vbat+1, Vcmax, cost
float _controllerSet[4][6] = {
    {0.98, 20, 24, 13, 100, 132.25},
    {0.98, 30, 24, 13, 100, 161.00},
    {0.98, 40, 24, 13, 150, 281.39},
    {0.95, 100, 48, 13, 400, 1800},
};

//efficiency, VinDC, VoutAC, PACref, MAXACref, cost
float _inverterSet[3][6] = {
    {0.93, 24, 120, 1200, 2400, 450.00},
    {0.91, 24, 120, 280, 750, 149.75},
    {0.91, 24, 120, 400, 1000, 187.25}
    // {0.95, 24, 220, 1600, 3200, 544.03}
};

const int MAX_INTEGER = 2147483647;
unsigned int LOWEST = MAX_INTEGER;

//12V, 24V, 36V or 48V: DC Bus voltage definition
int Vsystem = 24;
int autonomyDays = 2, SOClimit = 75, Vbat = 12;
float Insol = 3.80;
float LCC;

/*
 * these properties represent electrical specifications for each project.
 */
int Phouse = MAX_INTEGER, Psurge = MAX_INTEGER, Econsumption = MAX_INTEGER;
VAC = MAX_INTEGER;

unsigned int pValue = -1, bValue = -1, cValue = -1, iValue = -1;

void setTestCase(int tc)
{
    VAC = 127;

    switch (tc)
    {
    case 1:
        Phouse = 342;
        Psurge = 342;
        Econsumption = 3900;
        break;

    case 2:
        Phouse = 814;
        Psurge = 980;
        Econsumption = 4800;
        break;

    case 3:
        Phouse = 815;
        Psurge = 980;
        Econsumption = 4880;
        break;

    case 4:
        Phouse = 253;
        Psurge = 722;
        Econsumption = 3600;
        break;

    case 5:
        Phouse = 263;
        Psurge = 732;
        Econsumption = 2500;
        break;

    case 6:
        Phouse = 322;
        Psurge = 896;
        Econsumption = 4300;
        break;

    case 7:
        Phouse = 1586;
        Psurge = 2900;
        Econsumption = 14400;
        VAC = 220;
        break;

    default:
        Phouse = MAX_INTEGER;
        Psurge = MAX_INTEGER;
        Econsumption = MAX_INTEGER;
        break;
    }
}

float getLowestCost(int panel, int battery, int controller, int inverter)
{
    float percentMaintence = .05, qttYears = 20, costMaintenceByYear = 289.64;
    int NTP, NPP, NPS, NBtotal, NBS, NBP, NPmin;
    float Ecorrected, Fobj, Pminpanels, ItotalPVpanels, VtotalPVpanels, Eb, DODdaycalc, IminDCbus, DODmax;

    //Recovery Panel Specification
    float Pmref = _panelSet[panel][8];
    float Imref = _panelSet[panel][9];
    float Vmref = _panelSet[panel][10];
    float PanelCost = _panelSet[panel][12];

    //Recovery Battery Specification
    float nb = _batterySet[battery][0];
    float Vbat = (int)_batterySet[battery][1];
    int capacity = (int)_batterySet[battery][2];
    float BatteryCost = _batterySet[battery][5];

    //Recovery Charge Controller Specification
    float nc = _controllerSet[controller][0];
    int IC = (int)_controllerSet[controller][1];
    float VCmax = _controllerSet[controller][4];
    float ControllerCost = _controllerSet[controller][5];

    //Recovery Inverter Specification
    float ni = _inverterSet[inverter][0];
    int VinDC = (int)_inverterSet[inverter][1];
    int VoutAC = (int)_inverterSet[inverter][2];
    int PACref = (int)_inverterSet[inverter][3];
    int MAXACref = (int)_inverterSet[inverter][4];
    float InverterCost = _inverterSet[inverter][5];

    Ecorrected = Econsumption / (nb * nc * ni);

    Pminpanels = 1.25 * Ecorrected / Insol;

    NPmin = ((Pminpanels - 1) / Pmref) + 1;

    NPP = 2;
    if ((NPmin % 2) == 0)
        NPS = NPmin / 2; //even number
    else
        NPS = (NPmin + 1) / 2; //odd number

    NTP = NPS * NPP;

    ItotalPVpanels = NPP * Imref;
    VtotalPVpanels = NPS * Vmref;

    if (!(IC >= ItotalPVpanels))
        return MAX_INTEGER;

    if (!(VCmax >= VtotalPVpanels))
        return MAX_INTEGER;

    DODmax = (100 - SOClimit) * 2;
    Eb = autonomyDays * Ecorrected * 2;
    DODdaycalc = Ecorrected * 100 / Eb;
    IminDCbus = Eb / (float)Vsystem;

    NBS = Vsystem / Vbat;                   //fixed value
    NBP = ((IminDCbus - 1) / capacity) + 1; //calculando e arredondando
    NBtotal = NBS * NBP;

    if (!(VCmax * IC * nc) >= PACref)
        return MAX_INTEGER;

    if (!(VinDC >= Vsystem))
        return MAX_INTEGER;

    if (!(VoutAC >= (VAC - (VAC * 15 / 100))))
        return MAX_INTEGER;

    if (!(VoutAC <= (VAC + (VAC * 15 / 100))))
        return MAX_INTEGER;

    if (!((Phouse <= PACref) && (Psurge <= MAXACref)))
        return MAX_INTEGER;

    Fobj = NTP * PanelCost + NBtotal * BatteryCost + ControllerCost + InverterCost;

    LCC = Fobj + (Fobj * percentMaintence + qttYears * costMaintenceByYear);

    if (Fobj < LOWEST)
    {
        LOWEST = Fobj;

        pValue = panel;
        bValue = battery;
        cValue = controller;
        iValue = inverter;
    }

    return Fobj;
}

int main()
{
    int common_size = 4;
    int common_extra = 1;

    int count = 0;

    //2. Define Test Case 1..7
    setTestCase(1);

    //3. Perform Test
    for (int p = 0; p < common_size; p++)
    {
        for (int b = 0; b < common_extra; b++)
        {
            for (int c = 0; c < common_size; c++)
            {
                for (int i = 0; i < 3; i++)
                {
                    count++;

                    getLowestCost(p, b, c, i);

                    //printf("getLowestCost(%i, %i, %i, %i);\n", p, b, c, i);
                }
            }
        }
    }

    //printf("Cost: %i", LOWEST);
    if (!(pValue == -1 && bValue == -1 && cValue == -1 && iValue == -1))
        __VERIFIER_error();

    return 0;
}