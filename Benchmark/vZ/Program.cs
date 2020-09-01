using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using Microsoft.Z3;

namespace PVS
{
    class Program
    {
        //area, efficiency, num cells, NOCT, mii, miv, Iscref, Vocref, Pmref, Imref, Vmref, VmpNOCT, cost
        public static float[,] _panelData = {
            {1.94432f, 0.1620f, 72f, 45f, 0.00053f,   -0.0031f,  9.18f, 45.1f,  315f, 8.16f, 36.6f,  33.4f,  268.40f},
            {1.94432f, 0.1646f, 72f, 45f, 0.00053f,   -0.0031f,  9.26f, 45.3f,  320f, 8.69f, 36.8f,  33.6f,  190.00f},
            {1.94432f, 0.1672f, 72f, 45f, 0.00053f,   -0.0031f,  9.34f, 45.5f,  325f, 8.78f, 37.0f,  33.7f,  216.67f},
            {1.94432f, 0.1697f, 72f, 45f, 0.00053f,   -0.0031f,  9.45f, 45.6f,  330f, 8.88f, 37.2f,  33.9f,  170.30f},
            {2.19384f, 0.1515f, 80f, 47f, 0.00020f,   -0.0048f,  8.86f, 50.8f,  340f, 8.26f, 41.2f,  37.0f,  214.20f},
            {1.41075f, 0.1600f, 54f, 47f, 0.0000318f, -0.00123f, 8.21f, 32.9f,  200f, 7.61f, 32.9f,  23.2f,  300.00f},
            {1.62688f, 0.1690f, 60f, 47f, 0.00039f,   -0.00307f, 9.44f, 38.84f, 275,  8.81f, 31.22f, 26.72f, 150.00f},
            {1.94035f, 0.1855f, 72f, 45f, 0.00039f,   -0.00307f, 9.73f, 47.60f, 360,  9.33f, 38.59f, 34.96f, 237.24f},
            {1.00640f, 0.1515f, 36f, 45f, 0.00033f,   -0.0039f,  8.81f, 22.30f, 150,  8.20f, 18.30f, 14.40f, 94.75f},
            {0.99960f, 0.1500f, 36f, 46f, 0.00060f,   -0.0037f,  8.61f, 22.90f, 150f, 8.12f, 18.50f, 14.61f, 108.50f}};

        //efficiency, voltage, capacityC20, Vbulk, Vfloat, cost
        public static float[,] _batteryData = {
            {0.85f, 12f, 80f,  14.4f, 13.8f, 131.00f},
            {0.85f, 12f, 105f, 14.4f, 13.8f, 150.00f},
            {0.85f, 12f, 150f, 14.4f, 13.8f, 324.75f},
            {0.85f, 12f, 175f, 14.4f, 13.8f, 299.75f},
            {0.85f, 12f, 220f, 14.4f, 13.8f, 374.75f},
            {0.85f, 12f, 60f, 14.4f, 13.8f, 114.75f},
            {0.85f, 12f, 80f, 14.4f, 13.2f, 138.00f},
            {0.85f, 12f, 150f, 14.4f, 13.2f, 275.00f},
            {0.85f, 12f, 170f, 14.4f, 13.2f, 299.01f},
            {0.85f, 12f, 220f, 14.4f, 13.2f, 330.73f}};

        //efficiency, nominal current, voltage  output, Vmpptmin=vbat+1, Vcmax, cost
        public static float[,] _controllerData = {
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
            {0.96f, 60f, 60f, 13f, 140f, 1072.50f}};

        //efficiency, VinDC, VoutAC, PACref, MAXACref, cost
        public static float[,] _inverterData = {
            {0.93f, 48f, 110f, 700f, 1600f, 400.00f},
            {0.93f, 48f, 110f, 1200f, 2400f, 750.00f},
            {0.93f, 24f, 120f, 1200f, 2400f, 450.00f},
            {0.91f, 24f, 120f, 280f, 750f, 149.75f},
            {0.91f, 24f, 120f, 400f, 1000f, 187.25f},
            {0.93f, 12f, 220f, 600f, 1350f, 342.25f},
            {0.93f, 24f, 120f, 800f, 1200f, 500.00f},
            {0.90f, 12f, 120f, 900f, 2000f, 649.75f},
            {0.82f, 12f, 120f, 1000f, 2000f, 1122.25f},
            {0.90f, 24f, 125f, 1800f, 2900f, 1669.75f}};

        private static int Phouse = 263, Psurge = 732, Econsumption = 2500;

        static void Main(string[] args)
        {
            Microsoft.Z3.Global.ToggleWarningMessages(true);
            Log.Open("test.log");

            Dictionary<string, string> cfg = new Dictionary<string, string>()
            {{ "AUTO_CONFIG", "true" }, { "MODEL", "true" }};

            for (int i = 1; i <= 7; i++)
            {
                SetCase(i);
                using (Context ctx = new Context(cfg))
                {
                    Init(ctx, int.MaxValue, i);

                    ctx.Dispose();
                }
            }

            Console.ReadLine();
        }

        private static void SetCase(int showcase)
        {
            switch (showcase)
            {
                case 1:
                    Phouse = 342; Psurge = 342; Econsumption = 3900;
                    break;
                case 2:
                    Phouse = 814; Psurge = 980; Econsumption = 4800;
                    break;
                case 3:
                    Phouse = 815; Psurge = 980; Econsumption = 4880;
                    break;
                case 4:
                    Phouse = 253; Psurge = 722; Econsumption = 3600;
                    break;
                case 5:
                    Phouse = 263; Psurge = 732; Econsumption = 2500;
                    break;
                case 6:
                    Phouse = 322; Psurge = 896; Econsumption = 4300;
                    break;
                case 7:
                    Phouse = 1586; Psurge = 2900; Econsumption = 14400;
                    break;

                default:
                    Phouse = int.MaxValue; Psurge = int.MaxValue; Econsumption = int.MaxValue;
                    break;
            }
        }
        private static bool Init(Context ctx, float maxCost, int tcNumber)
        {
            var start = DateTime.Now;
            Console.WriteLine($"----- CASE {tcNumber} -----");

            var pEquip = new List<Equipaments>();

            foreach (var seq in GenerateSet())
            {
                var floor = GetLowCost(seq, ctx, maxCost);

                if (floor)
                {
                    maxCost = seq.Cost;

                    pEquip.Add(seq);
                }
            }

            var lowestCost = pEquip.OrderBy(x => x.Cost)
                                   .FirstOrDefault();

            if (lowestCost != null)            
                Console.WriteLine($"({(DateTime.Now - start).TotalSeconds} Sec) {lowestCost.ToString()}");
            else            
                Console.WriteLine($"UNSAT ({(DateTime.Now - start).TotalSeconds})");

            Console.WriteLine("");

            return true;
        }
        private static List<Equipaments> GenerateSet()
        {
            List<Equipaments> eq = new List<Equipaments>();

            for (int p = 0; p < GetArraySize(_panelData); p++)
                for (int b = 0; b < GetArraySize(_batteryData); b++)
                    for (int c = 0; c < GetArraySize(_controllerData); c++)
                        for (int i = 0; i < GetArraySize(_inverterData); i++)
                            eq.Add(new Equipaments()
                            {
                                Panel = p,
                                Battery = b,
                                Controller = c,
                                Inverter = i
                            });
            return eq;
        }
        private static bool GetLowCost(Equipaments seq, Context ctx, float cost)
        {
            var opt = ctx.MkOptimize();

            var s32b = ctx.MkFPSort32();

            int NTP, NPP, NPS, NBtotal, NBS, NBP, NPmin;
            float Ecorrected, Fobj, Pminpanels, ItotalPVpanels, VtotalPVpanels, Eb, DODdaycalc, IminDCbus, DODmax;

            float Insol = 3.80f; //(kWh/m2/day CRESESB 2016)
            int SOClimit = 75;
            int autonomy = 48; //autonomy in hours
            int Vsystem = 24;
            int VAC = 127;
            int Vbat = 12;

            opt.Add(ctx.MkGe(ctx.MkIntConst("Panel"), ctx.MkInt(seq.Panel)));
            opt.Add(ctx.MkGe(ctx.MkIntConst("Inverter"), ctx.MkInt(seq.Inverter)));
            opt.Add(ctx.MkGe(ctx.MkIntConst("Controller"), ctx.MkInt(seq.Controller)));
            opt.Add(ctx.MkGe(ctx.MkIntConst("Battery"), ctx.MkInt(seq.Battery)));

            #region Values
            float nb = _batteryData[seq.Battery, 0];
            int capacity = (int)_batteryData[seq.Battery, 2];
            float BatteryCost = _batteryData[seq.Battery, 5];

            float ControllerCost = _controllerData[seq.Controller, 5];
            float VCmax = _controllerData[seq.Controller, 4];
            int IC = (int)_controllerData[seq.Controller, 1];
            float nc = _controllerData[seq.Controller, 0];

            float InverterCost = _inverterData[seq.Inverter, 5];
            int PACref = (int)_inverterData[seq.Inverter, 3];
            int VinDC = (int)_inverterData[seq.Inverter, 1];
            int VoutAC = (int)_inverterData[seq.Inverter, 2];
            int MAXACref = (int)_inverterData[seq.Inverter, 4];
            float ni = _inverterData[seq.Inverter, 0];

            float Pmref = _panelData[seq.Panel, 8];
            float Imref = _panelData[seq.Panel, 9];
            float Vmref = _panelData[seq.Panel, 10];
            float PanelCost = _panelData[seq.Panel, 12];
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
            var _phouse = ctx.MkInt(Phouse);
            var _pacref = ctx.MkInt(PACref);
            var _psurge = ctx.MkInt(Psurge);
            var _maxacref = ctx.MkInt(MAXACref);

            var lefteq = (ctx.MkLe(_phouse, _pacref));
            var righteq = (ctx.MkLe(_psurge, _maxacref));

            opt.Assert(ctx.MkEq(lefteq, ctx.MkTrue()));
            opt.Assert(ctx.MkEq(righteq, ctx.MkTrue()));
            opt.Assert(ctx.MkAnd(lefteq, righteq));

            Fobj = NTP * PanelCost + NBtotal * BatteryCost + ControllerCost + InverterCost;
            opt.Assert(ctx.MkFPLEq(ctx.MkFP(Fobj, s32b), ctx.MkFP(cost, s32b)));

            seq.Cost = Fobj;
            seq.NBtotal = NBtotal;
            seq.LCC = (float)(Fobj + Fobj * 0.05 + 20 * 289.64);
            seq.VinDC = VinDC;
            seq.PACref = PACref;

            if (opt.Check() == Status.SATISFIABLE)
            {
                seq.Model = opt.Model;

                return true;
            }
            else
                return false;
        }
        private static int GetArraySize(float[,] panelData)
        {
            if (panelData.Length > 0)
                return panelData.GetLength(0);
            else
                return -1;
        }
    }

    public class Equipaments
    {
        public int Panel { get; set; }
        public int Battery { get; set; }
        public int Controller { get; set; }
        public int Inverter { get; set; }
        public float Cost { get; set; }
        public Model Model { get; set; }
        public int NBtotal { get; set; }
        public float LCC { get; set; }
        public int VinDC { get; set; }
        public float PACref { get; set; }
        
        public override string ToString()
        {
            return $"Panel: {Panel} | Battery:{Battery} | Controller:{Controller} | Inverter:{Inverter} |" +
                $" NTP | NBT: {NBtotal} x | Controller: | Inverter: {PACref} / {VinDC} | LCC: US$ {LCC} | Cost: {Cost}";
        }
    }
}
