using System;
using System.IO;
using System.Linq;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Formula
{
    internal class NativeWheel :IWheel
    {
        Value<SpinResult> IWheel.SpinNormal(int bet, int line)
        {

            try
            {
                return NativeWheel._SpinNormal(bet, line);
            }
            catch(System.Reflection.TargetInvocationException tie)
            {

                throw tie;
            }
            catch(System.BadImageFormatException bfe)
            {
                throw bfe;
            }
            catch(FileNotFoundException fnfe)
            {
                throw fnfe;
            }
            catch(Exception e)
            {
                
                throw e;
            }
            
        }

        private static Value<SpinResult> _SpinNormal(int bet, int line)
        {
            var wheel = new VGame.CLR.Wheel();
            var ir = new VGame.CLR.Input
            {
                Switch = 1,
                RunTime = 1,
                GameRate = 1,
                MaxBet = 10,
                MinBet = 1,
                Bet = bet,
                GameUndulate = 8,
                Line = line,
                RecCycle = 6,
                WupCondi1 = 1,
                WupCondi2 = 1,
                WupRate = 1,
                Free = 0,
                Fever = 0,
                WinSet = 0
            };

            var result = wheel.Spin(ir);

            var spinResult = new SpinResult
            {
                Symbols = (from reel in result.Reels select (SYMBOL) reel ).ToArray(),
                ExpectedScore = result.Score,
                Score = Regulus.Utility.Random.Instance.NextInt(0, 1000)
            };
            return spinResult;
        }

        Value<SpinResult> IWheel.SpinFree(int bet, int line)
        {
            return new SpinResult()
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Score = Regulus.Utility.Random.Instance.NextInt(0, 9999)
                ,
                Symbols = new[]
                {
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                }
            };
        }

        Value<SpinResultLittleGame> IWheel.SpinLittle(int bet)
        {
            return new SpinResultLittleGame
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Symbol = Regulus.Utility.Random.Instance.NextEnum<SYMBOL>()
            };
        }

        Value<SpinResultRatio> IWheel.SpinRatio(int bet)
        {
            return new SpinResultRatio
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Symbol = Regulus.Utility.Random.Instance.NextEnum<SYMBOL_RATIO>()
            };
        }
    }
}