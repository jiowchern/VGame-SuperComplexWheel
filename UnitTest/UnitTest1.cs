using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;


using VGame.CLR;

namespace UnitTest
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestNormal()
        {
            var wheel = new VGame.CLR.Wheel();
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
                Fever =  0,
                WinSet = 0
            };

            var result = wheel.Spin(ir);

            Assert.AreEqual(15 , result.Reels.Length);
        }
        [TestMethod]
        public void TestFree()
        {
            var wheel = new VGame.CLR.Wheel();
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
                Free = 1,
                Fever = 0,
                WinSet =  0,

            };

            var result = wheel.Spin(ir);

            Assert.AreEqual(15, result.Reels.Length);
        }


        [TestMethod]
        public void TestFever()
        {
            var wheel = new VGame.CLR.Wheel();
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
                Fever = 1,
                WinSet = 0
            };

            var result = wheel.Spin(ir);

            Assert.AreEqual(15, result.Reels.Length);
        }


        [TestMethod]
        public void TestWup()
        {
            var wheel = new VGame.CLR.Wheel();
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

            var result = wheel.Spin(ir);

            Assert.AreEqual(15, result.Reels.Length);
        }


        [TestMethod]
        public void TestDump()
        {
            var wheel = new VGame.CLR.Wheel();
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

            wheel.Spin(ir);
            var data = wheel.Export();
            data.Reel.stcReelFeverData[0].uwGetIndex = 12345;

            wheel.Import(ref data);

            var data2 = wheel.Export();
            
            Assert.AreEqual(12345, data2.Reel.stcReelFeverData[0].uwGetIndex);
        }
    }
}
