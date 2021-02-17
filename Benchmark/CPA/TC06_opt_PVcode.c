extern void __VERIFIER_error() __attribute__((__noreturn__));
extern void __VERIFIER_assume(int expression);
unsigned int nondet_uint();
unsigned char nondet_uchar();

//#include <stdio.h>

//area, efficiency, num cells, NOCT, mii, miv, Iscref, Vocref, Pmref, Imref, Vmref, VmpNOCT, cost
float _panelSet[17][13] = {
	{1.94432, 0.1620, 72, 45, 0.00053, -0.0031, 9.18, 45.1, 315, 8.16, 36.6, 33.4, 268.40},
	{1.94432, 0.1646, 72, 45, 0.00053, -0.0031, 9.26, 45.3, 320, 8.69, 36.8, 33.6, 190.00},
	{1.94432, 0.1672, 72, 45, 0.00053, -0.0031, 9.34, 45.5, 325, 8.78, 37.0, 33.7, 216.67},
	{1.94432, 0.1697, 72, 45, 0.00053, -0.0031, 9.45, 45.6, 330, 8.88, 37.2, 33.9, 170.30},
	{2.19384, 0.1515, 80, 47, 0.00020, -0.0048, 8.86, 50.8, 340, 8.26, 41.2, 37.0, 214.20},
	{1.41075, 0.1600, 54, 47, 0.0000318, -0.00123, 8.21, 32.9, 200, 7.61, 32.9, 23.2, 300.00},
	{1.62688, 0.1690, 60, 47, 0.00039, -0.00307, 9.44, 38.84, 275, 8.81, 31.22, 26.72, 150.00},
	{1.94035, 0.1855, 72, 45, 0.00039, -0.00307, 9.73, 47.60, 360, 9.33, 38.59, 34.96, 237.24},
	{1.00640, 0.1515, 36, 45, 0.00033, -0.0039, 8.81, 22.30, 150, 8.20, 18.30, 14.40, 94.75},
	{0.99960, 0.1500, 36, 46, 0.00060, -0.0037, 8.61, 22.90, 150, 8.12, 18.50, 14.61, 108.50},
	{1.97904, 0.1700, 72, 45, 0.0005, -0.003, 9.33, 45.6, 330, 8.85, 37.3, 34.4, 118},
	{1.94432, 0.1697, 72, 45, 0.0006, -0.003, 9.57, 44.72, 330, 8.86, 37.26, 34.28, 131.25},
	{1.94432, 0.1926, 72, 45, 0.00048, -0.004, 10.67, 47.80, 380, 9.74, 39.02, 36.48, 155.52},
	{1.984, 0.1991, 144, 45, 0.00049, -0.0029, 10.31, 49.10, 395, 9.83, 40.2, 37.5, 178.03},
	{1.984, 0.1789, 144, 45, 0.0005, -0.0029, 9.59, 46.8, 355, 9.02, 39.4, 36.60, 144.26},
	{2.20918, 0.1924, 144, 42, 0.0005, -0.0029, 11.29, 48.00, 425, 10.71, 39.70, 36.00, 187.41},
	{2.17357, 0.1960, 144, 45, 0.00048, -0.0027, 11.39, 48.7, 435, 10.64, 40.9, 36.4, 225.11}};

//efficiency, voltage, capacityC20, Vbulk, Vfloat, cost
float _batterySet[17][6] = {
	{0.85, 12, 80, 14.4, 13.8, 131.00},
	{0.85, 12, 105, 14.4, 13.8, 150.00},
	{0.85, 12, 150, 14.4, 13.8, 324.75},
	{0.85, 12, 175, 14.4, 13.8, 299.75},
	{0.85, 12, 220, 14.4, 13.8, 374.75},
	{0.85, 12, 60, 14.4, 13.8, 114.75},
	{0.85, 12, 80, 14.4, 13.2, 138.00},
	{0.85, 12, 150, 14.4, 13.2, 275.00},
	{0.85, 12, 170, 14.4, 13.2, 299.01},
	{0.85, 12, 220, 14.4, 13.2, 330.73},
	{0.85, 12, 220, 14.4, 13.2, 279.33},
	{0.85, 12, 220, 14.14, 13.2, 243.69},
	{0.85, 12, 220, 14.4, 13.2, 290.59},
	{0.85, 12, 250, 14.4, 13.2, 1836.55},
	{0.85, 12, 300, 14.4, 13.2, 1930.34},
	{0.85, 12, 36, 14.4, 13.2, 77.00},
	{0.85, 12, 45, 14.4, 13.2, 85.00}};

//efficiency, nominal current, voltage  output, Vmpptmin=vbat+1, Vcmax, cost
float _controllerSet[19][6] = {
	{0.98, 35, 24, 13, 145, 294.95},
	{0.98, 15, 24, 13, 75, 88.40},
	{0.98, 15, 24, 13, 100, 137.70},
	{0.98, 50, 24, 13, 100, 294.95},
	{0.98, 20, 24, 13, 100, 132.25},
	{0.98, 30, 24, 13, 100, 161.00},
	{0.98, 40, 24, 13, 100, 184.75},
	{0.97, 20, 24, 13, 100, 217.25},
	{0.97, 30, 24, 13, 100, 297.25},
	{0.98, 50, 48, 13, 150, 347.82},
	{0.98, 60, 48, 13, 150, 388.91},
	{0.96, 60, 60, 13, 140, 1072.50},
	{0.98, 100, 24, 14, 150, 750.18},
	{0.98, 40, 24, 13, 150, 281.39},
	{0.98, 50, 24, 13, 150, 356.43},
	{0.98, 60, 24, 13, 150, 530.70},
	{0.98, 45, 24, 13, 150, 506.50},
	{0.95, 100, 48, 13, 400, 1800},
	{0.95, 250, 48, 13, 384, 2300}};

//efficiency, VinDC, VoutAC, PACref, MAXACref, cost
float _inverterSet[17][6] = {
	{0.93, 48, 110, 700, 1600, 400.00},
	{0.93, 48, 110, 1200, 2400, 750.00},
	{0.93, 24, 120, 1200, 2400, 450.00},
	{0.91, 24, 120, 280, 750, 149.75},
	{0.91, 24, 120, 400, 1000, 187.25},
	{0.93, 12, 220, 600, 1350, 342.25},
	{0.93, 24, 120, 800, 1200, 500.00},
	{0.90, 12, 120, 900, 2000, 649.75},
	{0.82, 12, 120, 1000, 2000, 1122.25},
	{0.90, 24, 125, 1800, 2900, 1669.75},
	{0.93, 24, 110, 3000, 6900, 1144.14},
	{0.93, 24, 220, 1200, 2400, 212.00},
	{0.95, 24, 220, 2000, 4600, 775.00},
	{0.95, 24, 220, 1600, 3200, 544.03},
	{0.93, 24, 110, 1200, 2400, 506.50},
	{0.88, 48, 220, 10000, 30000, 2270.64},
	{0.93, 48, 220, 3000, 6000, 1125.59}
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

	NBS = Vsystem / Vbat;					//fixed value
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

	if (Fobj < LOWEST && Fobj > -1)
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
	int ps = 17; //2;
	int bs = 17;
	int cs = 19; //4;
	int is = 17; //3;

	int count = 0;

	//2. Define Test Case 1..7
	setTestCase(6);

	//3. Perform Test
	for (int p = 0; p < ps; p++)
	{
		for (int b = 0; b < bs; b++)
		{
			for (int c = 0; c < cs; c++)
			{
				for (int i = 0; i < is; i++)
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