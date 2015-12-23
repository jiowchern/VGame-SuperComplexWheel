using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Regulus.Utility;


using VGame.CLR;

namespace Spreadsheet
{
    class Program
    {
        static void Main(string[] args)
        {
            var view = new Regulus.Utility.ConsoleViewer();
            var input = new Regulus.Utility.ConsoleInput(view);
            
            var console = new Regulus.Utility.Console(input, view);

            bool run = true;
            var wheel = new VGame.CLR.Wheel();
            console.Command.Register("Quit" , () => { run = false; });
            console.Command.Register("Spin", () => { _Spin(view , wheel); });

            console.Command.Register("Export", () => { _Export(view, wheel); });
            console.Command.Register<string>("Import[path]", (path) => { _Import(view, wheel , path); });

            while (run)
            {
                
                input.Update();
            }
        }

        private static void _Import(Regulus.Utility.Console.IViewer view, Wheel wheel, string path)
        {
            try
            {
                var buffer = System.IO.File.ReadAllText(path);
                var set = Newtonsoft.Json.JsonConvert.DeserializeObject<VGame.CLR.Dump.WheelFieldSet>(buffer);
                wheel.Import(ref set);
            }
            catch(Exception)
            {
                view.WriteLine("失敗");
                throw;
            }
            view.WriteLine("成功");
        }
        private static void _Export(Regulus.Utility.Console.IViewer view, Wheel wheel)
        {
            var data = wheel.Export();

            var guid = System.Guid.NewGuid();
            var path = $"Export{guid}.txt";
            view.WriteLine(path);
            System.IO.File.WriteAllText(path, Newtonsoft.Json.JsonConvert.SerializeObject(data));
        }

        private static void _Spin(Regulus.Utility.Console.IViewer view, VGame.CLR.Wheel wheel)
        {
            var ir = new VGame.CLR.Input
            {
                Switch = 1,
                RunTime = 1,
                GameRate = 1,
                MaxBet = 10,
                MinBet = 1,
                Bet = 9,
                GameUndulate = 8,
                Line = 7,
                RecCycle = 6,
                WupCondi1 = 1,
                WupCondi2 = 1,
                WupRate = 1,
                Free = 0,
                Fever = 0,
                WinSet = 1
            };
            view.WriteLine("嘗試讀取Input.txt...");
            if(System.IO.File.Exists("Input.txt"))
            {
                view.WriteLine("成功.");
                var readed = System.IO.File.ReadAllText("Input.txt");
                ir = Newtonsoft.Json.JsonConvert.DeserializeObject<VGame.CLR.Input>(readed);
            }
            else
            {
                view.WriteLine("失敗.");
                view.WriteLine("建立預設Input.txt ...");

                System.IO.File.WriteAllText("Input.txt", Newtonsoft.Json.JsonConvert.SerializeObject(ir));
            }

            var output = wheel.Spin(ir);

            var guid = System.Guid.NewGuid();
            var inputPath = $"Input{guid}.txt";
            view.WriteLine(inputPath);
            System.IO.File.WriteAllText(inputPath , Newtonsoft.Json.JsonConvert.SerializeObject(ir));

            var outputPath = $"Output{guid}.txt";
            view.WriteLine(outputPath);
            System.IO.File.WriteAllText(outputPath, Newtonsoft.Json.JsonConvert.SerializeObject(output));

        }
    }
}
