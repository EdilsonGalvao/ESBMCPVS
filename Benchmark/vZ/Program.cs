using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Z3;

namespace PVS
{
    public partial class Program
    {
        #region Matrix of values
        //area, efficiency, num cells, NOCT, mii, miv, Iscref, Vocref, Pmref, Imref, Vmref, VmpNOCT, cost
        private static float[,] _panelData = {
            {1.94432f, 0.1620f, 72f, 45f,  0.00053f,  -0.0031f,  9.18f, 45.1f,  315f, 8.16f, 36.6f,  33.4f,  268.40f},
            {1.94432f, 0.1646f, 72f, 45f,  0.00053f,  -0.0031f,  9.26f, 45.3f,  320f, 8.69f, 36.8f,  33.6f,  190.00f},
            {1.94432f, 0.1672f, 72f, 45f,  0.00053f,  -0.0031f,  9.34f, 45.5f,  325f, 8.78f, 37.0f,  33.7f,  216.67f},
            {1.94432f, 0.1697f, 72f, 45f,  0.00053f,  -0.0031f,  9.45f, 45.6f,  330f, 8.88f, 37.2f,  33.9f,  170.30f},
            {2.19384f, 0.1515f, 80f, 47f,  0.00020f,  -0.0048f,  8.86f, 50.8f,  340f, 8.26f, 41.2f,  37.0f,  214.20f},
            {1.41075f, 0.1600f, 54f, 47f,  0.0000318f,-0.00123f, 8.21f, 32.9f,  200f, 7.61f, 32.9f,  23.2f,  300.00f},
            {1.62688f, 0.1690f, 60f, 47f,  0.00039f,  -0.00307f, 9.44f, 38.84f, 275,  8.81f, 31.22f, 26.72f, 150.00f},
            {1.94035f, 0.1855f, 72f, 45f,  0.00039f,  -0.00307f, 9.73f, 47.60f, 360,  9.33f, 38.59f, 34.96f, 237.24f},
            {1.00640f, 0.1515f, 36f, 45f,  0.00033f,  -0.0039f,  8.81f, 22.30f, 150,  8.20f, 18.30f, 14.40f, 94.75f},
            {0.99960f, 0.1500f, 36f, 46f,  0.00060f,  -0.0037f,  8.61f, 22.90f, 150f, 8.12f, 18.50f, 14.61f, 108.50f},
            {1.97904f, 0.1700f, 72f, 45f,  0.0005f,   -0.003f,   9.33f, 45.6f,  330f, 8.85f, 37.3f,  34.4f,  118f},
            {1.94432f, 0.1697f, 72f, 45f,  0.0006f,   -0.003f,   9.57f, 44.72f, 330f, 8.86f, 37.26f, 34.28f, 131.25f},
            {1.94432f, 0.1926f, 72f, 45f,  0.00048f,  -0.004f,   10.67f,47.80f, 380f, 9.74f, 39.02f, 36.48f, 155.52f},
            {1.984f,   0.1991f, 144f, 45f, 0.00049f,  -0.0029f,  10.31f,49.10f, 395f, 9.83f, 40.2f,  37.5f,  178.03f},
            {1.984f,   0.1789f, 144f, 45f, 0.0005f,   -0.0029f,  9.59f, 46.8f,  355f, 9.02f, 39.4f,  36.60f, 144.26f},
            {2.20918f, 0.1924f, 144f, 42f, 0.0005f,   -0.0029f,  11.29f,48.00f, 425f, 10.71f,39.70f, 36.00f, 187.41f},
            {2.17357f, 0.1960f, 144f, 45f, 0.00048f,  -0.0027f,  11.39f,48.7f,  435f, 10.64f,40.9f,  36.4f,  225.11f}
        };

        //efficiency, voltage, capacityC20, Vbulk, Vfloat, cost
        private static float[,] _batteryData = {
            {0.85f, 12f, 80f,  14.4f, 13.8f, 131.00f},
            {0.85f, 12f, 105f, 14.4f, 13.8f, 150.00f},
            {0.85f, 12f, 150f, 14.4f, 13.8f, 324.75f},
            {0.85f, 12f, 175f, 14.4f, 13.8f, 299.75f},
            {0.85f, 12f, 220f, 14.4f, 13.8f, 374.75f},
            {0.85f, 12f, 60f,  14.4f, 13.8f, 114.75f},
            {0.85f, 12f, 80f,  14.4f, 13.2f, 138.00f},
            {0.85f, 12f, 150f, 14.4f, 13.2f, 275.00f},
            {0.85f, 12f, 170f, 14.4f, 13.2f, 299.01f},
            {0.85f, 12f, 220f, 14.4f, 13.2f, 330.73f},
            {0.85f, 12f, 220f, 14.4f, 13.2f, 279.33f},
            {0.85f, 12f, 220f, 14.14f, 13.2f, 243.69f},
            {0.85f, 12f, 220f, 14.4f, 13.2f, 290.59f},
            {0.85f, 12f, 250f, 14.4f, 13.2f, 1836.55f},
            {0.85f, 12f, 300f, 14.4f, 13.2f, 1930.34f},
            {0.85f, 12f, 36f,  14.4f, 13.2f, 77.00f},
            {0.85f, 12f, 45f,  14.4f, 13.2f, 85.00f}
        };

        //efficiency, nominal current, voltage  output, Vmpptmin=vbat+1, Vcmax, cost
        private static float[,] _controllerData = {
            {0.98f, 35f, 24f, 13f, 145f, 294.95f},
            {0.98f, 15f, 24f, 13f,  75f, 88.40f},
            {0.98f, 15f, 24f, 13f, 100f, 137.70f},
            {0.98f, 50f, 24f, 13f, 100f, 294.95f},
            {0.98f, 20f, 24f, 13f, 100f, 132.25f},
            {0.98f, 30f, 24f, 13f, 100f, 161.00f},
            {0.98f, 40f, 24f, 13f, 100f, 184.75f},
            {0.97f, 20f, 24f, 13f, 100f, 217.25f},
            {0.97f, 30f, 24f, 13f, 100f, 297.25f},
            {0.98f, 50f, 48f, 13f, 150f, 347.82f},
            {0.98f, 60f, 48f, 13f, 150f, 388.91f},
            {0.96f, 60f, 60f, 13f, 140f, 1072.50f},
            {0.98f, 100f, 24f, 14f, 150f, 750.18f},
            {0.98f, 40f, 24f, 13f, 150f, 281.39f},
            {0.98f, 50f, 24f, 13f, 150f, 356.43f},
            {0.98f, 60f, 24f, 13f, 150f, 530.70f},
            {0.98f, 45f, 24f, 13f, 150f, 506.50f},
            {0.95f, 100f, 48f, 13f, 400f, 1800f},
            {0.95f, 250f, 48f, 13f, 384f, 2300f}};

        //efficiency, VinDC, VoutAC, PACref, MAXACref, cost
        private static float[,] _inverterData = {
            {0.93f, 48f, 110f, 700f, 1600f, 400.00f},
            {0.93f, 48f, 110f, 1200f, 2400f, 750.00f},
            {0.93f, 24f, 120f, 1200f, 2400f, 450.00f},
            {0.91f, 24f, 120f, 280f, 750f, 149.75f},
            {0.91f, 24f, 120f, 400f, 1000f, 187.25f},
            {0.93f, 12f, 220f, 600f, 1350f, 342.25f},
            {0.93f, 24f, 120f, 800f, 1200f, 500.00f},
            {0.90f, 12f, 120f, 900f, 2000f, 649.75f},
            {0.82f, 12f, 120f, 1000f, 2000f, 1122.25f},
            {0.90f, 24f, 125f, 1800f, 2900f, 1669.75f},
            {0.93f, 24f, 110f, 3000f, 6900f, 1144.14f},
            {0.93f, 24f, 220f, 1200f, 2400f, 212.00f},
            {0.95f, 24f, 220f, 2000f, 4600f, 775.00f},
            {0.95f, 24f, 220f, 1600f, 3200f, 544.03f},
            {0.93f, 24f, 110f, 1200f, 2400f, 506.50f},
            {0.88f, 48f, 220f, 10000f, 30000f, 2270.64f},
            {0.93f, 48f, 220f, 3000f, 6000f, 1125.59f}};
        #endregion

        //Basic input to calculate the best combination of equipments.
        private static int Phouse = int.MaxValue, Psurge = int.MaxValue, Econsumption = int.MaxValue;
        private static int VAC = int.MaxValue;

        //The list of minimum values found locally.
        //The lowest value in this list is the best option based on cost.
        private static List<Equipaments> Equipaments = new List<Equipaments>();

        static void Main(string[] args)
        {
            if (args.Length > 0)
            {
                Microsoft.Z3.Global.ToggleWarningMessages(true);
                Log.Open("test.log");

                int cValue;
                int.TryParse(args.FirstOrDefault(), out cValue);

                if (cValue != 0)
                {
                    SetCase(cValue);

                    var startedAt = DateTime.Now;
                    var lowest = Solve(int.MaxValue, cValue);

                    Console.WriteLine($"TC 0{cValue} - Solved Time: ({(DateTime.Now - startedAt).TotalSeconds}) Seconds.");
                    Console.WriteLine($"{lowest}\r\n");
                }
            }
            else
            {
                Console.WriteLine($"Invalid");
            }
        }

        /// <summary>
        /// Found the best equipament
        /// </summary>
        /// <param name="maxCost">Maximum possible cost</param>
        /// <param name="tcNumber">TC number</param>
        /// <returns>The best equipament to TC</returns>
        private static Equipaments Solve(float maxCost, int tcNumber)
        {
            Dictionary<string, string> cfg = new Dictionary<string, string>()
                {{ "AUTO_CONFIG", "true" }, { "MODEL", "true" }};

            Equipaments.Clear();

            Parallel.ForEach(GenerateSet(), c =>
            {
                var isLowest = GetLowestCost(c, new Context(), maxCost);

                if (isLowest)
                {
                    lock (c)
                    {
                        maxCost = c.Cost;
                        Equipaments.Add(c);
                    }
                }
            });


            //foreach (var c in GenerateSet())
            //{
            //    if (GetLowestCost(c, new Context(), maxCost))
            //    {
            //        lock (c)
            //        {
            //            maxCost = c.Cost;
            //            Equipaments.Add(c);
            //        }
            //    }
            //}

            return Equipaments
                .Where(x => x != null)
                .OrderBy(x => x.Cost)
                .FirstOrDefault();
        }

        /// <summary>
        /// PVS Base equation.
        /// </summary>
        /// <param name="seq">Equipament</param>
        /// <param name="ctx">Context of Z3</param>
        /// <param name="cost">Lowest Cost that was found previously</param>
        /// <returns></returns>
        private static bool GetLowestCost(Equipaments seq, Context ctx, float cost)
        {
            var opt = ctx.MkOptimize();

            var s32b = ctx.MkFPSort32();

            int NTP, NPP, NPS, NBtotal, NBS, NBP, NPmin;
            float Ecorrected, Fobj, Pminpanels, ItotalPVpanels, VtotalPVpanels, Eb, DODdaycalc, IminDCbus, DODmax;

            float Insol = 3.89f; //(kWh/m2/day CRESESB 2016)
            int SOClimit = 75;
            int autonomy = 48; //autonomy in hours
            int Vsystem = 24;
            int Vbat = 12;

            opt.Add(ctx.MkGe(ctx.MkIntConst("Panel"), ctx.MkInt(seq.IdxPanel)));
            opt.Add(ctx.MkGe(ctx.MkIntConst("Inverter"), ctx.MkInt(seq.IdxInverter)));
            opt.Add(ctx.MkGe(ctx.MkIntConst("Controller"), ctx.MkInt(seq.IdxController)));
            opt.Add(ctx.MkGe(ctx.MkIntConst("Battery"), ctx.MkInt(seq.IdxBattery)));

            #region Values
            float nb = _batteryData[seq.IdxBattery, 0];
            int capacity = (int)_batteryData[seq.IdxBattery, 2];
            float BatteryCost = _batteryData[seq.IdxBattery, 5];

            float ControllerCost = _controllerData[seq.IdxController, 5];
            float VCmax = _controllerData[seq.IdxController, 4];
            int IC = (int)_controllerData[seq.IdxController, 1];
            float nc = _controllerData[seq.IdxController, 0];

            float InverterCost = _inverterData[seq.IdxInverter, 5];
            int PACref = (int)_inverterData[seq.IdxInverter, 3];
            int VinDC = (int)_inverterData[seq.IdxInverter, 1];
            int VoutAC = (int)_inverterData[seq.IdxInverter, 2];
            int MAXACref = (int)_inverterData[seq.IdxInverter, 4];
            float ni = _inverterData[seq.IdxInverter, 0];

            float Pmref = _panelData[seq.IdxPanel, 8];
            float Imref = _panelData[seq.IdxPanel, 9];
            float Vmref = _panelData[seq.IdxPanel, 10];
            float PanelCost = _panelData[seq.IdxPanel, 12];
            #endregion

            Ecorrected = Econsumption / (nb * nc * ni);
            Pminpanels = (float)(1.25 * Ecorrected / Insol);
            NPmin = (int)((Pminpanels - 1) / Pmref) + 1;

            NPP = 2;
            if ((NPmin % 2) == 0)
                NPS = NPmin / 2; //even number
            else
                NPS = (NPmin + 1) / 2; //odd number

            NTP = NPS * NPP;
            ItotalPVpanels = NPP * Imref;

            //IC >= ItotalPVpanels
            opt.Assert(ctx.MkFPGEq(ctx.MkFP(IC, s32b), ctx.MkFP(ItotalPVpanels, s32b)));

            VtotalPVpanels = NPS * Vmref;

            //VCmax >= VtotalPVpanels
            var vcmax = ctx.MkFP(VCmax, ctx.MkFPSort32());
            var vtotalPV = ctx.MkFP(VtotalPVpanels, ctx.MkFPSort32());


            opt.Assert(ctx.MkFPGEq(vcmax, vtotalPV));

            DODmax = (100 - SOClimit) * 2;
            autonomy = 2;
            Eb = autonomy * Ecorrected * 2;
            DODdaycalc = Ecorrected * 100 / Eb;
            IminDCbus = Eb / (float)Vsystem;
            NBS = Vsystem / Vbat; //fixed value 
            NBP = (int)(((IminDCbus - 1) / capacity) + 1); //calculando e arredondando
            NBtotal = NBS * NBP;

            //controller vs inverter check
            var cic = VCmax * IC * nc;

            opt.Assert(ctx.MkFPGEq(ctx.MkFP(cic, s32b), ctx.MkFP(PACref, s32b)));
            opt.Assert(ctx.MkFPGEq(ctx.MkFP(VinDC, s32b), ctx.MkFP(Vsystem, s32b)));

            var minus = (VAC - VAC * 15 / 100);
            var plus = (VAC + VAC * 15 / 100);

            //(VoutAC >= (VAC - VAC * 15 / 100))
            opt.Assert(ctx.MkFPGEq(ctx.MkFP(VoutAC, s32b), ctx.MkFP(minus, s32b)));
            //(VoutAC <= (VAC + VAC * 15 / 100))
            opt.Assert(ctx.MkFPLEq(ctx.MkFP(VoutAC, s32b), ctx.MkFP(plus, s32b)));
            //(Phouse <= PACref)
            opt.Assert(ctx.MkFPLEq(ctx.MkFP(Phouse, s32b), ctx.MkFP(PACref, s32b)));
            //(Psurge <= MAXACref)
            opt.Assert(ctx.MkFPLEq(ctx.MkFP(Psurge, s32b), ctx.MkFP(MAXACref, s32b)));

            Fobj = ControllerCost + InverterCost + (NTP * PanelCost) + (NBtotal * BatteryCost);

            //opt.Assert(ctx.MkFPLEq(ctx.MkFP(Fobj, s32b), ctx.MkFP(cost, s32b)));

            seq.Cost = Fobj;
            seq.NBtotal = NBtotal;
            seq.LCC = (float)(Fobj + Fobj * 0.05 + 20 * 289.64);
            seq.VinDC = VinDC;
            seq.PACref = PACref;
            seq.NTP = NTP;
            seq.NPS = NPS;
            seq.NPP = NPP;
            seq.NBS = NBS;
            seq.NBP = NBP;
            seq.PmRef = Pmref;
            seq.IC = IC;
            seq.VCMax = VCmax;
            seq.BatteryCapacity = capacity;


            if (opt.Check() == Status.SATISFIABLE)
            {
                seq.Model = opt.Model;

                return true;
            }
            else
                return false;
        }

        /// <summary>
        /// Set case to test
        /// </summary>
        /// <param name="showcase">TC Number</param>
        private static void SetCase(int showcase)
        {
            switch (showcase)
            {
                case 1:
                    Phouse = 342; Psurge = 342; Econsumption = 3900;
                    VAC = 127;
                    break;
                case 2:
                    Phouse = 814; Psurge = 980; Econsumption = 4800;
                    VAC = 127;
                    break;
                case 3:
                    Phouse = 815; Psurge = 980; Econsumption = 4880;
                    VAC = 127;
                    break;
                case 4:
                    Phouse = 253; Psurge = 722; Econsumption = 3600;
                    VAC = 127;
                    break;
                case 5:
                    Phouse = 263; Psurge = 732; Econsumption = 2500;
                    VAC = 127;
                    break;
                case 6:
                    Phouse = 322; Psurge = 896; Econsumption = 4300;
                    VAC = 127;
                    break;
                case 7:
                    Phouse = 1586; Psurge = 2900; Econsumption = 14400;
                    VAC = 220;
                    break;

                default:
                    Phouse = int.MaxValue; Psurge = int.MaxValue; Econsumption = int.MaxValue;
                    break;
            }
        }

        /// <summary>
        /// Generate all possible combinations of values into matrix database
        /// </summary>
        /// <returns>List of possible equipaments</returns>
        private static List<Equipaments> GenerateSet()
        {
            List<Equipaments> eq = new List<Equipaments>();

            for (int p = 0; p < GetArraySize(_panelData); p++)
                for (int b = 0; b < GetArraySize(_batteryData); b++)
                    for (int c = 0; c < GetArraySize(_controllerData); c++)
                        for (int i = 0; i < GetArraySize(_inverterData); i++)
                            eq.Add(new Equipaments()
                            {
                                IdxPanel = p,
                                IdxBattery = b,
                                IdxController = c,
                                IdxInverter = i
                            });
            return eq;
        }

        /// <summary>
        /// Get Size of Equipament List
        /// </summary>
        /// <param name="arr">Set of Equipament</param>
        /// <returns></returns>
        private static int GetArraySize(float[,] arr)
        {
            if (arr.Length > 0)
                return arr.GetLength(0);
            else
                return -1;
        }
    }

    public class Equipaments
    {
        public int IdxPanel { get; set; }
        public int IdxBattery { get; set; }
        public int IdxController { get; set; }
        public int IdxInverter { get; set; }
        public float Cost { get; set; }
        public Model Model { get; set; }
        public int NBtotal { get; set; }
        public float LCC { get; set; }
        public int VinDC { get; set; }
        public float PACref { get; set; }
        public int NTP { get; set; }
        public int NPS { get; set; }
        public int NPP { get; set; }
        public int NBS { get; set; }
        public int NBP { get; set; }
        public float PmRef { get; set; }
        public int IC { get; set; }
        public float VCMax { get; set; }
        public int BatteryCapacity { get; set; }

        public override string ToString()
        {
            return
                $"LCC: US$ {LCC} \r\n" +
                $"COST: US$ {Cost} \r\n" +
                $"NTP: {NTP}x{PmRef}w \r\n" +
                $"NBT: {NBtotal}x{BatteryCapacity}Ah \r\n" +
                $"Controller: {IC}A x {VCMax}V \r\n" +
                $"Inverter: {PACref}W x {VinDC}v \r\n" +
                $"Index: P[{IdxPanel}]; B[{IdxBattery}]; C[{IdxController}]; I[{IdxInverter}]  ";
        }
    }
}
